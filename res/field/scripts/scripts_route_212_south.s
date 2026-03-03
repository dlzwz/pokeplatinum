#include "macros/scrcmd.inc"
#include "res/text/bank/route_212_south.h"


    ScriptEntry _007D
    ScriptEntry _0090
    ScriptEntry _00A3
    ScriptEntry _00B6
    ScriptEntry _00CD
    ScriptEntry _00F9
    ScriptEntry _0022
    ScriptEntry _00E4
    ScriptEntryEnd

_0022:
    ClearFlag FLAG_UNK_0x0269
    SetFlag FLAG_UNK_0x0268
    End

_007D:
    NPCMessage 0
    End

_0090:
    NPCMessage 1
    End

_00A3:
    NPCMessage 2
    End

_00B6:
    ShowArrowSign 4
    End

_00CD:
    ShowLandmarkSign 5
    End

_00E4:
    ShowScrollingSign 6
    End

_00F9:
    NPCMessage 3
    End
