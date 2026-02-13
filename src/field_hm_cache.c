#include "field_hm_cache.h"

#include "constants/heap.h"
#include "constants/items.h"
#include "constants/moves.h"

#include "item.h"
#include "pokemon.h"

// One entry per HM, in HM01-HM08 order.
static const u16 sHMMoves[NUM_HMS] = {
    MOVE_CUT,
    MOVE_FLY,
    MOVE_SURF,
    MOVE_STRENGTH,
    MOVE_DEFOG,
    MOVE_ROCK_SMASH,
    MOVE_WATERFALL,
    MOVE_ROCK_CLIMB,
};

// Bit N is set if any party mon is eligible to use HM(N+1) as a field move.
static u8 s_eligibilityMask;

// TRUE when the cache needs to be recomputed.
static BOOL s_dirty = TRUE;

static void Recompute(Party *party, Bag *bag)
{
    u8 hmIdx;
    int i;
    int partyCount = Party_GetCurrentCount(party);

    s_eligibilityMask = 0;

    for (hmIdx = 0; hmIdx < NUM_HMS; hmIdx++) {
        u8 tmhmIdx = NUM_TMS + hmIdx;
        u16 hmMove = sHMMoves[hmIdx];
        BOOL hasHMInBag = Bag_GetItemQuantity(bag, FIRST_HM_IDX + hmIdx, HEAP_ID_FIELD1) > 0;

        for (i = 0; i < partyCount; i++) {
            Pokemon *mon = Party_GetPokemonBySlotIndex(party, i);

            if (Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL)) {
                continue;
            }

            // Check move slots first — no heap allocation.
            if (Pokemon_GetValue(mon, MON_DATA_MOVE1, NULL) == hmMove
                || Pokemon_GetValue(mon, MON_DATA_MOVE2, NULL) == hmMove
                || Pokemon_GetValue(mon, MON_DATA_MOVE3, NULL) == hmMove
                || Pokemon_GetValue(mon, MON_DATA_MOVE4, NULL) == hmMove) {
                s_eligibilityMask |= (1 << hmIdx);
                break;
            }

            // Fall back to learnability check — only when HM is in bag.
            // Pokemon_CanLearnTM allocates from the heap, so it runs only
            // during this infrequent recompute, never in the per-frame hot path.
            if (hasHMInBag && Pokemon_CanLearnTM(mon, tmhmIdx)) {
                s_eligibilityMask |= (1 << hmIdx);
                break;
            }
        }
    }

    s_dirty = FALSE;
}

void FieldHMCache_Invalidate(void)
{
    s_dirty = TRUE;
}

void FieldHMCache_Update(Party *party, Bag *bag)
{
    if (s_dirty) {
        Recompute(party, bag);
    }
}

BOOL FieldHMCache_CanUse(u16 move)
{
    u8 hmIdx = Item_HMIndexForMove(move);

    if (hmIdx == 0xFF) {
        return FALSE;
    }

    return (s_eligibilityMask >> hmIdx) & 1;
}
