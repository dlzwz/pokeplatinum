#include "macros/scrcmd.inc"
#include "res/text/bank/route_222.h"


    ScriptEntry _00D7
    ScriptEntry _007D
    ScriptEntry _00EA
    ScriptEntry _0101
    ScriptEntry _0118
    ScriptEntry _012F
    ScriptEntry _0146
    ScriptEntry _0022
    ScriptEntryEnd

_0022:
    ClearFlag FLAG_UNK_0x026B
    SetFlag FLAG_UNK_0x026A
    End

_007D:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GoToIfSet FLAG_UNK_0x00CE, _00C2
    Message 0
    SetVar VAR_0x8004, ITEM_TM56
    SetVar VAR_0x8005, 1
    GoToIfCannotFitItem VAR_0x8004, VAR_0x8005, VAR_RESULT, _00CD
    Common_GiveItemQuantity
    SetFlag FLAG_UNK_0x00CE
    GoTo _00C2

_00C2:
    Message 1
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_00CD:
    Common_MessageBagIsFull
    CloseMessage
    ReleaseAll
    End

_00D7:
    NPCMessage 2
    End

_00EA:
    ShowArrowSign 4
    End

_0101:
    ShowArrowSign 5
    End

_0118:
    ShowLandmarkSign 6
    End

_012F:
    ShowLandmarkSign 7
    End

_0146:
    NPCMessage 3
    End

    .balign 4, 0
