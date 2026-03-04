#include "scrcmd_game_corner_prize.h"

#include <nitro.h>
#include <string.h>

#include "generated/items.h"

#include "field_script_context.h"
#include "inlines.h"

typedef struct GameCornerPrize {
    u16 item;
    u16 price;
} GameCornerPrize;

BOOL ScrCmd_GetGameCornerPrizeData(ScriptContext *ctx)
{
    u16 index = ScriptContext_GetVar(ctx);
    u16 *item = ScriptContext_GetVarPointer(ctx);
    u16 *price = ScriptContext_GetVarPointer(ctx);

    static const GameCornerPrize sGameCornerPrizeData[] = {
        { ITEM_SILK_SCARF, 10 },
        { ITEM_WIDE_LENS, 10 },
        { ITEM_ZOOM_LENS, 10 },
        { ITEM_METRONOME, 10 },
        { ITEM_TM90, 20 },
        { ITEM_TM58, 20 },
        { ITEM_TM75, 40 },
        { ITEM_TM32, 40 },
        { ITEM_TM44, 60 },
        { ITEM_TM89, 60 },
        { ITEM_TM10, 60 },
        { ITEM_TM27, 80 },
        { ITEM_TM21, 80 },
        { ITEM_TM35, 100 },
        { ITEM_TM24, 100 },
        { ITEM_TM13, 100 },
        { ITEM_TM29, 100 },
        { ITEM_TM74, 150 },
        { ITEM_TM68, 200 }
    };

    *item = sGameCornerPrizeData[index].item;
    *price = sGameCornerPrizeData[index].price;

    return FALSE;
}
