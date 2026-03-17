#include "macros/scrcmd.inc"
#include "res/text/bank/pastoria_city_observatory_gate_2f.h"


    ScriptEntry _0016
    ScriptEntry _0078
    ScriptEntry _008B
    ScriptEntry _009E
    ScriptEntry _00B1
    ScriptEntryEnd

_0016:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    ShowMoney 20, 2
    Message 0
    ShowYesNoMenu VAR_RESULT
    CloseMessage
    GoToIfEq VAR_RESULT, MENU_YES, _003E
    HideMoney
    ReleaseAll
    End

_003E:
    GoToIfNotEnoughMoney 100, _006B
    RemoveMoney 100
    UpdateMoneyDisplay
    PlayFanfare SEQ_SE_DP_REGI
    WaitFanfare SEQ_SE_DP_REGI
    HideMoney
    GoToIfSet FLAG_UNK_0x0AA6, _VIEW_ONLY
    Message 6
    GetNationalDexEnabled VAR_0x8000
    GoToIfEq VAR_0x8000, 1, _NATDEX_LIST
_PRENAT_LIST:
    InitLocalTextListMenu 1, 1, 0, VAR_RESULT, FALSE
    AddListMenuEntry 8,  0      // Carnivine
    AddListMenuEntry 9,  1      // Skorupi
    AddListMenuEntry 10, 2      // Croagunk
    AddListMenuEntry 11, 3      // Quagsire
    AddListMenuEntry 12, 4      // Yanma
    AddListMenuEntry 13, 5      // Tropius
    AddListMenuEntry 14, 6      // Tangela
    GoTo _SHOW_LIST
_NATDEX_LIST:
    InitLocalTextListMenu 1, 1, 0, VAR_RESULT, FALSE
    AddListMenuEntry 8,  0      // Carnivine
    AddListMenuEntry 9,  1      // Skorupi
    AddListMenuEntry 10, 2      // Croagunk
    AddListMenuEntry 11, 3      // Quagsire
    AddListMenuEntry 12, 4      // Yanma
    AddListMenuEntry 13, 5      // Tropius
    AddListMenuEntry 14, 6      // Tangela
    AddListMenuEntry 15, 7      // Toxicroak
    AddListMenuEntry 16, 8      // Kecleon
    AddListMenuEntry 17, 9      // Drapion
    AddListMenuEntry 18, 10     // Kangaskhan
    AddListMenuEntry 19, 11     // Paras
    AddListMenuEntry 20, 12     // Exeggcute
    AddListMenuEntry 21, 13     // Shroomish
    AddListMenuEntry 22, 14     // Gulpin
_SHOW_LIST:
    ShowListMenu
    SetGreatMarshDailyMon VAR_RESULT
    SetFlag FLAG_UNK_0x0AA6
    Message 7
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_006B:
    Message 1
    WaitABXPadPress
    CloseMessage
    HideMoney
    ReleaseAll
    End

_VIEW_ONLY:
    StartGreatMarshLookout
    ReleaseAll
    End

_0078:
    NPCMessage 2
    End

_008B:
    NPCMessage 3
    End

_009E:
    NPCMessage 4
    End

_00B1:
    NPCMessage 5
    End
