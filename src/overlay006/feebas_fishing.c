#include "overlay006/feebas_fishing.h"

#include <nitro.h>

#include "field/field_system.h"

#include "inlines.h"

// Returns TRUE 50% of the time to simulate Feebas's 50% encounter rate.
// Any fishing tile on the Feebas map is eligible.
BOOL PlayerAvatar_IsFacingFeebasTile(FieldSystem *fieldSystem)
{
    if (LCRNG_RandMod(2) == 0) {
        return FALSE;
    }

    return TRUE;
}

void LoadFeebasLevelRange(u8 *maxLevel, u8 *minLevel)
{
    (*maxLevel) = 20;
    (*minLevel) = 10;
}

// I guess they didn't want to hardcode this...for some reason...
void LoadFeebasFromNARC(int *species)
{
    int *narcData = NARC_AllocAtEndAndReadWholeMemberByIndexPair(NARC_INDEX_ARC__ENCDATA_EX, 0, HEAP_ID_FIELD1);
    (*species) = (*narcData);

    Heap_Free(narcData);
}
