#ifndef POKEPLATINUM_FIELD_HM_CACHE_H
#define POKEPLATINUM_FIELD_HM_CACHE_H

#include "bag.h"
#include "party.h"

/**
 * @brief Invalidate the field HM eligibility cache.
 *
 * Call this whenever the party composition changes (catch, deposit, withdraw,
 * trade, evolution). The cache will be lazily recomputed on the next
 * FieldHMCache_Update call.
 */
void FieldHMCache_Invalidate(void);

/**
 * @brief Recompute the field HM eligibility cache if dirty.
 *
 * Call once per frame at the start of field input processing, before any
 * FieldHMCache_CanUse calls. Does nothing if the cache is already current.
 *
 * @param party     The player's current party.
 * @param bag       The player's current bag.
 */
void FieldHMCache_Update(Party *party, Bag *bag);

/**
 * @brief Check if any party mon is eligible to use a given HM field move.
 *
 * A mon is eligible if it already knows the move, or if the corresponding HM
 * is in the bag and the mon can learn it. O(1) — just a bitmask read.
 *
 * @param move  The HM move ID (e.g. MOVE_WATERFALL).
 * @return TRUE if any eligible party mon exists, FALSE otherwise.
 */
BOOL FieldHMCache_CanUse(u16 move);

#endif // POKEPLATINUM_FIELD_HM_CACHE_H
