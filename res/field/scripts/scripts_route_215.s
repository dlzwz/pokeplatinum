#include "macros/scrcmd.inc"
#include "res/text/bank/route_215.h"


    ScriptEntry _008D
    ScriptEntry _00A0
    ScriptEntry _00FA
    ScriptEntry _0111
    ScriptEntry _013D
    ScriptEntry _0150
    ScriptEntry _0022
    ScriptEntry _0128
    ScriptEntryEnd

_0022:
    ClearFlag FLAG_UNK_0x0273
    ClearFlag FLAG_UNK_0x0275
    SetFlag FLAG_UNK_0x0272
    SetFlag FLAG_UNK_0x0274
    End

_008D:
    NPCMessage 0
    End

_00A0:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_UNK_0x00CD, _00E5
    Message 1
    SetVar VAR_0x8004, ITEM_TM66
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, _00F0
    Common_GiveItemQuantity
    SetFlag FLAG_UNK_0x00CD
    GoTo _00E5

_00E5:
    Message 2
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_00F0:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

_00FA:
    ShowArrowSign 5
    End

_0111:
    ShowArrowSign 6
    End

_0128:
    ShowScrollingSign 7
    End

_013D:
    NPCMessage 3
    End

_0150:
    NPCMessage 4
    End

    .balign 4, 0
