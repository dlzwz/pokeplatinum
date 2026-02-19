#include "unk_0206C660.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "overlay006/npc_trade.h"
#include "overlay006/struct_npc_trade_animation_template.h"
#include "overlay095/ov95_02246C20.h"

#include "applications/pokemon_summary_screen/main.h"

#include "bag.h"
#include "evolution.h"
#include "field_task.h"
#include "field_transition.h"
#include "game_options.h"
#include "game_records.h"
#include "heap.h"
#include "party.h"
#include "pokedex.h"
#include "poketch.h"
#include "pokemon.h"
#include "save_player.h"

FS_EXTERN_OVERLAY(overlay95);

typedef struct {
    NpcTradeData *unk_00;
    u32 unk_04;
    int unk_08;
    TradeAnimationTemplate unk_0C;
    Pokemon *unk_24;
    Pokemon *unk_28;
    EvolutionData *evolutionData;
} UnkStruct_0206C660;

static BOOL sub_0206C680(FieldTask *param0);
static void sub_0206C660(FieldTask *param0);

void sub_0206C660(FieldTask *param0)
{
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(param0);
    UnkStruct_0206C660 *v1 = FieldTask_GetEnv(param0);

    {
        FS_EXTERN_OVERLAY(overlay95);

        static const ApplicationManagerTemplate v2 = {
            TradeSequence_Init,
            TradeSequence_Main,
            TradeSequence_Exit,
            FS_OVERLAY_ID(overlay95),
        };

        FieldTask_RunApplication(param0, &v2, &v1->unk_0C);
    }
}

static BOOL sub_0206C680(FieldTask *param0)
{
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(param0);
    UnkStruct_0206C660 *v1 = FieldTask_GetEnv(param0);

    switch (v1->unk_04) {
    case 0:
        ov6_02246254(fieldSystem, v1->unk_00, v1->unk_08, &v1->unk_0C, v1->unk_24, v1->unk_28);
        NpcTrade_ReceiveMon(fieldSystem, v1->unk_00, v1->unk_08);
        v1->unk_04++;
        break;
    case 1:
        FieldTransition_FadeOut(param0);
        v1->unk_04++;
        break;
    case 2:
        FieldTransition_FinishMap(param0);
        v1->unk_04++;
        break;
    case 3:
        sub_0206C660(param0);
        v1->unk_04++;
        break;
    case 4: {
        Party *party = SaveData_GetParty(fieldSystem->saveData);
        Pokemon *receivedMon = Party_GetPokemonBySlotIndex(party, v1->unk_08);
        int heldItem = Pokemon_GetValue(receivedMon, MON_DATA_HELD_ITEM, NULL);
        int evolutionType;
        int evolvedSpecies = Pokemon_GetEvolutionTargetSpecies(NULL, receivedMon, EVO_CLASS_BY_TRADE, heldItem, &evolutionType);

        if (evolvedSpecies != 0) {
            Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_26, 0x30000);
            v1->evolutionData = Evolution_Begin(
                NULL,
                receivedMon,
                evolvedSpecies,
                SaveData_GetOptions(fieldSystem->saveData),
                PokemonSummaryScreen_ShowContestData(fieldSystem->saveData),
                SaveData_GetPokedex(fieldSystem->saveData),
                SaveData_GetBag(fieldSystem->saveData),
                SaveData_GetGameRecords(fieldSystem->saveData),
                SaveData_GetPoketch(fieldSystem->saveData),
                evolutionType,
                0x4,
                HEAP_ID_26
            );
            v1->unk_04 = 5;
        } else {
            v1->unk_04 = 6;
        }
    } break;
    case 5:
        if (Evolution_IsDone(v1->evolutionData)) {
            Evolution_Free(v1->evolutionData);
            Heap_Destroy(HEAP_ID_26);
            v1->unk_04 = 6;
        }
        break;
    case 6:
        FieldTransition_StartMap(param0);
        v1->unk_04++;
        break;
    case 7:
        FieldTransition_FadeIn(param0);
        v1->unk_04++;
        break;
    case 8:
        Heap_Free(v1->unk_24);
        Heap_Free(v1->unk_28);
        Heap_Free(v1);
        return 1;
    }

    return 0;
}

void sub_0206C740(FieldTask *param0, NpcTradeData *param1, int param2, enum HeapID heapID)
{
    UnkStruct_0206C660 *v0 = Heap_Alloc(heapID, sizeof(UnkStruct_0206C660));

    memset(v0, 0, sizeof(UnkStruct_0206C660));

    v0->unk_04 = 0;
    v0->unk_00 = param1;
    v0->unk_08 = param2;
    v0->unk_24 = Pokemon_New(heapID);
    v0->unk_28 = Pokemon_New(heapID);

    FieldTask_InitCall(param0, sub_0206C680, v0);
}
