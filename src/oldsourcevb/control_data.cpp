Attribute VB_Name = "mod_ControlData"
Public BoundKey(255) As Integer
Public BoundKeyType(255) As String

Public KeyCounter As Integer
Public aKeys(255) As String

Public CTRL_MOVELEFT As Integer
Public CTRL_MOVERIGHT As Integer
Public CTRL_JUMP As Integer
Public CTRL_CROUCH As Integer
Public CTRL_TOGGLECONSOLE As Integer
Public CTRL_SHOWGAMESTATS As Integer
Public CTRL_KILL As Integer

Function KeyNames(iNum As Integer) As String

    aKeys(&H1) = "ESC"
    aKeys(&H2) = "1"
    aKeys(&H3) = "2"
    aKeys(&H4) = "3"
    aKeys(&H5) = "4"
    aKeys(&H6) = "5"
    aKeys(&H7) = "6"
    aKeys(&H8) = "7"
    aKeys(&H9) = "8"
    aKeys(&HA) = "9"
    aKeys(&HB) = "0"
    aKeys(&HC) = "-"             ' - on main keyboard
    aKeys(&HD) = "="
    aKeys(&HE) = "BACKSPACE"                  ' backspace
    aKeys(&HF) = "TAB"
    aKeys(&H10) = "Q"
    aKeys(&H11) = "W"
    aKeys(&H12) = "E"
    aKeys(&H13) = "R"
    aKeys(&H14) = "T"
    aKeys(&H15) = "Y"
    aKeys(&H16) = "U"
    aKeys(&H17) = "I"
    aKeys(&H18) = "O"
    aKeys(&H19) = "P"
    aKeys(&H1A) = "LBRACKET"
    aKeys(&H1B) = "RBRACKET"
    aKeys(&H1C) = "RETURN" ' Enter on main keyboard
    aKeys(&H1D) = "LCONTROL"
    aKeys(&H1E) = "A"
    aKeys(&H1F) = "S"
    aKeys(&H20) = "D"
    aKeys(&H21) = "F"
    aKeys(&H22) = "G"
    aKeys(&H23) = "H"
    aKeys(&H24) = "J"
    aKeys(&H25) = "K"
    aKeys(&H26) = "L"
    aKeys(&H27) = ";"
    aKeys(&H28) = "APOSTROPHE"
    aKeys(&H29) = "GRAVE" ' accent grave
    aKeys(&H2A) = "LSHIFT"
    aKeys(&H2B) = "\"
    aKeys(&H2C) = "Z"
    aKeys(&H2D) = "X"
    aKeys(&H2E) = "C"
    aKeys(&H2F) = "V"
    aKeys(&H30) = "B"
    aKeys(&H31) = "N"
    aKeys(&H32) = "M"
    aKeys(&H33) = ","
    aKeys(&H34) = "." ' . on main keyboard
    aKeys(&H35) = "/" ' / on main keyboard
    aKeys(&H36) = "RSHIFT"
    aKeys(&H37) = "MULTIPLY" ' * on numeric keypad
    aKeys(&H38) = "LALT" ' left Alt
    aKeys(&H39) = "SPACE"
    aKeys(&H3A) = "CAPITAL"
    aKeys(&H3B) = "F1"
    aKeys(&H3C) = "F2"
    aKeys(&H3D) = "F3"
    aKeys(&H3E) = "F4"
    aKeys(&H3F) = "F5"
    aKeys(&H40) = "F6"
    aKeys(&H41) = "F7"
    aKeys(&H42) = "F8"
    aKeys(&H43) = "F9"
    aKeys(&H44) = "F10"
    aKeys(&H45) = "NUMLOCK"
    aKeys(&H46) = "SCROLL" ' Scroll Lock
    aKeys(&H47) = "NUMPAD7"
    aKeys(&H48) = "NUMPAD8"
    aKeys(&H49) = "NUMPAD9"
    aKeys(&H4A) = "NUMSUBTRACT" ' - on numeric keypad
    aKeys(&H4B) = "NUMPAD4"
    aKeys(&H4C) = "NUMPAD5"
    aKeys(&H4D) = "NUMPAD6"
    aKeys(&H4E) = "NUMADD" ' + on numeric keypad
    aKeys(&H4F) = "NUMPAD1"
    aKeys(&H50) = "NUMPAD2"
    aKeys(&H51) = "NUMPAD3"
    aKeys(&H52) = "NUMPAD0"
    aKeys(&H53) = "NUMDECIMAL" ' . on numeric keypad
    aKeys(&H56) = "DIK_OEM_102 < > | on UK/Germany keyboards"
    aKeys(&H57) = "F11"
    aKeys(&H58) = "F12"
    aKeys(&H64) = "DIK_F13 on (NEC PC98) "
    aKeys(&H65) = "DIK_F14 on (NEC PC98) "
    aKeys(&H66) = "DIK_F15 on (NEC PC98) "
    aKeys(&H70) = "DIK_KANA on (Japanese keyboard)"
    aKeys(&H73) = "DIK_ABNT_C1 / ? on Portugese (Brazilian) keyboards "
    aKeys(&H79) = "DIK_CONVERT on (Japanese keyboard)"
    aKeys(&H7B) = "DIK_NOCONVERT on (Japanese keyboard)"
    aKeys(&H7D) = "DIK_YEN on (Japanese keyboard)"
    aKeys(&H7E) = "DIK_ABNT_C2 on Numpad . on Portugese (Brazilian) keyboards "
    aKeys(&H8D) = "DIK_NUMPADEQUALS = on numeric keypad (NEC PC98) "
    aKeys(&H90) = "DIK_PREVTRACK on Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) "
    aKeys(&H91) = "DIK_AT (NEC PC98) "
    aKeys(&H92) = "DIK_COLON (NEC PC98) "
    aKeys(&H93) = "DIK_UNDERLINE (NEC PC98) "
    aKeys(&H94) = "DIK_KANJI on (Japanese keyboard)"
    aKeys(&H95) = "DIK_STOP (NEC PC98) "
    aKeys(&H96) = "DIK_AX (Japan AX) "
    aKeys(&H97) = "DIK_UNLABELED (J3100) "
    aKeys(&H99) = "NEXTTRACK" ' Next Track
    aKeys(&H9C) = "NUMPADENTER" ' Enter on numeric keypad
    aKeys(&H9D) = "RCONTROL"
    aKeys(&HA0) = "MUTE" ' Mute
    aKeys(&HA1) = "CALCULATOR" ' Calculator
    aKeys(&HA2) = "PLAYPAUSE" ' Play / Pause
    aKeys(&HA4) = "MEDIASTOP" ' Media Stop
    aKeys(&HAE) = "VOLUMEDOWN" ' Volume -
    aKeys(&HB0) = "VOLUMEUP" ' Volume +
    aKeys(&HB2) = "WEBHOME" ' Web home
    aKeys(&HB3) = "DIK_NUMPADCOMMA" ' , on numeric keypad (NEC PC98)
    aKeys(&HB5) = "NUMDIVIDE" ' / on numeric keypad
    aKeys(&HB7) = "SYSRQ"
    aKeys(&HB8) = "RMENU" ' right Alt
    aKeys(&HC5) = "PAUSE" ' Pause
    aKeys(&HC7) = "HOME" ' Home on arrow keypad
    aKeys(&HC8) = "UP" ' UpArrow on arrow keypad
    aKeys(&HC9) = "PRIOR" ' PgUp on arrow keypad
    aKeys(&HCB) = "LEFT" ' LeftArrow on arrow keypad
    aKeys(&HCD) = "RIGHT" ' RightArrow on arrow keypad
    aKeys(&HCF) = "END" ' End on arrow keypad
    aKeys(&HD0) = "DOWN" ' DownArrow on arrow keypad
    aKeys(&HD1) = "NEXT" ' PgDn on arrow keypad
    aKeys(&HD2) = "INSERT" ' Insert on arrow keypad
    aKeys(&HD3) = "DELETE" ' Delete on arrow keypad
    aKeys(&HDB) = "LWIN" ' Left Windows key
    aKeys(&HDC) = "RWIN" ' Right Windows key
    aKeys(&HDD) = "APPS" ' AppMenu key
    aKeys(&HDE) = "POWER" ' System Power
    aKeys(&HDF) = "SLEEP" ' System Sleep
    aKeys(&HE3) = "WAKE" ' System Wake
    aKeys(&HE5) = "WEBSEARCH" ' Web Search
    aKeys(&HE6) = "WEBFAVORITES" ' Web Favorites
    aKeys(&HE7) = "WEBREFRESH" ' Web Refresh
    aKeys(&HE8) = "WEBSTOP" ' Web Stop
    aKeys(&HE9) = "WEBFORWARD" ' Web Forward
    aKeys(&HEA) = "WEBBACK" ' Web Back
    aKeys(&HEB) = "MYCOMPUTER" ' My Computer
    aKeys(&HEC) = "MAIL" ' Mail
    aKeys(&HED) = "MEDIASELECT" ' Media Select

    KeyNames = aKeys(iNum)

End Function


Function KeyInt(aKey As String) As Integer

    aKeys(&H1) = "ESC"
    aKeys(&H2) = "1"
    aKeys(&H3) = "2"
    aKeys(&H4) = "3"
    aKeys(&H5) = "4"
    aKeys(&H6) = "5"
    aKeys(&H7) = "6"
    aKeys(&H8) = "7"
    aKeys(&H9) = "8"
    aKeys(&HA) = "9"
    aKeys(&HB) = "0"
    aKeys(&HC) = "-"             ' - on main keyboard
    aKeys(&HD) = "="
    aKeys(&HE) = "BACKSPACE"                  ' backspace
    aKeys(&HF) = "TAB"
    aKeys(&H10) = "Q"
    aKeys(&H11) = "W"
    aKeys(&H12) = "E"
    aKeys(&H13) = "R"
    aKeys(&H14) = "T"
    aKeys(&H15) = "Y"
    aKeys(&H16) = "U"
    aKeys(&H17) = "I"
    aKeys(&H18) = "O"
    aKeys(&H19) = "P"
    aKeys(&H1A) = "LBRACKET"
    aKeys(&H1B) = "RBRACKET"
    aKeys(&H1C) = "RETURN" ' Enter on main keyboard
    aKeys(&H1D) = "LCONTROL"
    aKeys(&H1E) = "A"
    aKeys(&H1F) = "S"
    aKeys(&H20) = "D"
    aKeys(&H21) = "F"
    aKeys(&H22) = "G"
    aKeys(&H23) = "H"
    aKeys(&H24) = "J"
    aKeys(&H25) = "K"
    aKeys(&H26) = "L"
    aKeys(&H27) = ";"
    aKeys(&H28) = "APOSTROPHE"
    aKeys(&H29) = "GRAVE" ' accent grave
    aKeys(&H2A) = "LSHIFT"
    aKeys(&H2B) = "\"
    aKeys(&H2C) = "Z"
    aKeys(&H2D) = "X"
    aKeys(&H2E) = "C"
    aKeys(&H2F) = "V"
    aKeys(&H30) = "B"
    aKeys(&H31) = "N"
    aKeys(&H32) = "M"
    aKeys(&H33) = ","
    aKeys(&H34) = "." ' . on main keyboard
    aKeys(&H35) = "/" ' / on main keyboard
    aKeys(&H36) = "RSHIFT"
    aKeys(&H37) = "MULTIPLY" ' * on numeric keypad
    aKeys(&H38) = "LALT" ' left Alt
    aKeys(&H39) = "SPACE"
    aKeys(&H3A) = "CAPITAL"
    aKeys(&H3B) = "F1"
    aKeys(&H3C) = "F2"
    aKeys(&H3D) = "F3"
    aKeys(&H3E) = "F4"
    aKeys(&H3F) = "F5"
    aKeys(&H40) = "F6"
    aKeys(&H41) = "F7"
    aKeys(&H42) = "F8"
    aKeys(&H43) = "F9"
    aKeys(&H44) = "F10"
    aKeys(&H45) = "NUMLOCK"
    aKeys(&H46) = "SCROLL" ' Scroll Lock
    aKeys(&H47) = "NUMPAD7"
    aKeys(&H48) = "NUMPAD8"
    aKeys(&H49) = "NUMPAD9"
    aKeys(&H4A) = "NUMSUBTRACT" ' - on numeric keypad
    aKeys(&H4B) = "NUMPAD4"
    aKeys(&H4C) = "NUMPAD5"
    aKeys(&H4D) = "NUMPAD6"
    aKeys(&H4E) = "NUMADD" ' + on numeric keypad
    aKeys(&H4F) = "NUMPAD1"
    aKeys(&H50) = "NUMPAD2"
    aKeys(&H51) = "NUMPAD3"
    aKeys(&H52) = "NUMPAD0"
    aKeys(&H53) = "NUMDECIMAL" ' . on numeric keypad
    aKeys(&H56) = "DIK_OEM_102 < > | on UK/Germany keyboards"
    aKeys(&H57) = "F11"
    aKeys(&H58) = "F12"
    aKeys(&H64) = "DIK_F13 on (NEC PC98) "
    aKeys(&H65) = "DIK_F14 on (NEC PC98) "
    aKeys(&H66) = "DIK_F15 on (NEC PC98) "
    aKeys(&H70) = "DIK_KANA on (Japanese keyboard)"
    aKeys(&H73) = "DIK_ABNT_C1 / ? on Portugese (Brazilian) keyboards "
    aKeys(&H79) = "DIK_CONVERT on (Japanese keyboard)"
    aKeys(&H7B) = "DIK_NOCONVERT on (Japanese keyboard)"
    aKeys(&H7D) = "DIK_YEN on (Japanese keyboard)"
    aKeys(&H7E) = "DIK_ABNT_C2 on Numpad . on Portugese (Brazilian) keyboards "
    aKeys(&H8D) = "DIK_NUMPADEQUALS = on numeric keypad (NEC PC98) "
    aKeys(&H90) = "DIK_PREVTRACK on Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) "
    aKeys(&H91) = "DIK_AT (NEC PC98) "
    aKeys(&H92) = "DIK_COLON (NEC PC98) "
    aKeys(&H93) = "DIK_UNDERLINE (NEC PC98) "
    aKeys(&H94) = "DIK_KANJI on (Japanese keyboard)"
    aKeys(&H95) = "DIK_STOP (NEC PC98) "
    aKeys(&H96) = "DIK_AX (Japan AX) "
    aKeys(&H97) = "DIK_UNLABELED (J3100) "
    aKeys(&H99) = "NEXTTRACK" ' Next Track
    aKeys(&H9C) = "NUMPADENTER" ' Enter on numeric keypad
    aKeys(&H9D) = "RCONTROL"
    aKeys(&HA0) = "MUTE" ' Mute
    aKeys(&HA1) = "CALCULATOR" ' Calculator
    aKeys(&HA2) = "PLAYPAUSE" ' Play / Pause
    aKeys(&HA4) = "MEDIASTOP" ' Media Stop
    aKeys(&HAE) = "VOLUMEDOWN" ' Volume -
    aKeys(&HB0) = "VOLUMEUP" ' Volume +
    aKeys(&HB2) = "WEBHOME" ' Web home
    aKeys(&HB3) = "DIK_NUMPADCOMMA" ' , on numeric keypad (NEC PC98)
    aKeys(&HB5) = "NUMDIVIDE" ' / on numeric keypad
    aKeys(&HB7) = "SYSRQ"
    aKeys(&HB8) = "RMENU" ' right Alt
    aKeys(&HC5) = "PAUSE" ' Pause
    aKeys(&HC7) = "HOME" ' Home on arrow keypad
    aKeys(&HC8) = "UP" ' UpArrow on arrow keypad
    aKeys(&HC9) = "PRIOR" ' PgUp on arrow keypad
    aKeys(&HCB) = "LEFT" ' LeftArrow on arrow keypad
    aKeys(&HCD) = "RIGHT" ' RightArrow on arrow keypad
    aKeys(&HCF) = "END" ' End on arrow keypad
    aKeys(&HD0) = "DOWN" ' DownArrow on arrow keypad
    aKeys(&HD1) = "NEXT" ' PgDn on arrow keypad
    aKeys(&HD2) = "INSERT" ' Insert on arrow keypad
    aKeys(&HD3) = "DELETE" ' Delete on arrow keypad
    aKeys(&HDB) = "LWIN" ' Left Windows key
    aKeys(&HDC) = "RWIN" ' Right Windows key
    aKeys(&HDD) = "APPS" ' AppMenu key
    aKeys(&HDE) = "POWER" ' System Power
    aKeys(&HDF) = "SLEEP" ' System Sleep
    aKeys(&HE3) = "WAKE" ' System Wake
    aKeys(&HE5) = "WEBSEARCH" ' Web Search
    aKeys(&HE6) = "WEBFAVORITES" ' Web Favorites
    aKeys(&HE7) = "WEBREFRESH" ' Web Refresh
    aKeys(&HE8) = "WEBSTOP" ' Web Stop
    aKeys(&HE9) = "WEBFORWARD" ' Web Forward
    aKeys(&HEA) = "WEBBACK" ' Web Back
    aKeys(&HEB) = "MYCOMPUTER" ' My Computer
    aKeys(&HEC) = "MAIL" ' Mail
    aKeys(&HED) = "MEDIASELECT" ' Media Select

    Dim X As Integer
    For X = 0 To 255
        If aKeys(X) = aKey Then
            KeyInt = X
        End If
    Next X

End Function

Function BoundKeys(aKey As String) As Integer

    Dim X As Integer

    For X = 0 To 255
        If BoundKeyType(X) = aKey Then
            BoundKeys = X
        End If
    Next X

End Function

Public Sub INIT_DefaultKeys()

Dim X As Integer
For X = 1 To 255
    BoundKeyType(X) = "LOL"
    BoundKey(X) = 255
Next X

BoundKeyType(0) = "JUMP"
BoundKeyType(1) = "LEFT"
BoundKeyType(2) = "RIGHT"
BoundKeyType(3) = "CROUCH"
BoundKeyType(4) = "FIRE"
BoundKeyType(5) = "SUICIDE"
BoundKeyType(6) = "TOGGLEMUS"
BoundKeyType(7) = "TOGGLESFX"
BoundKeyType(8) = "GAMESTATS"
BoundKeyType(9) = "SAY"
BoundKeyType(10) = "WEAPON1"
BoundKeyType(11) = "WEAPON2"
BoundKeyType(12) = "WEAPON3"
BoundKeyType(13) = "WEAPON4"
BoundKeyType(14) = "WEAPON5"
BoundKeyType(15) = "WEAPON6"
BoundKeyType(16) = "WEAPON7"
BoundKeyType(17) = "WEAPON8"
BoundKeyType(18) = "WEAPON9"
BoundKeyType(19) = "WEAPONMELEE"
BoundKeyType(20) = "JETPAK"

BoundKey(0) = &H11  'Jump         = w
BoundKey(1) = &H1E  'Left         = a
BoundKey(2) = &H20  'Right        = d
BoundKey(3) = &H1F  'Crouch       = s
BoundKey(4) = &H25  'Fire         = k
BoundKey(5) = &H16  'Suicide      = u
BoundKey(6) = &H31  'Toggle Music = n
BoundKey(7) = &H32  'Toggle SFX   = m
BoundKey(8) = &HF   'Status       = tab
BoundKey(9) = &H14  'Say          = t
BoundKey(10) = &H2  'Weapon 1     = 1
BoundKey(11) = &H3  'Weapon 2     = 2
BoundKey(12) = &H4  'Weapon 3     = 3
BoundKey(13) = &H5  'Weapon 4     = 4
BoundKey(14) = &H6  'Weapon 5     = 5
BoundKey(15) = &H7  'Weapon 6     = 6
BoundKey(16) = &H8  'Weapon 7     = 7
BoundKey(17) = &H9  'Weapon 8     = 8
BoundKey(18) = &HA  'Weapon 9     = 9
BoundKey(19) = &HB  'Melee Weapon = 0
BoundKey(20) = &H26 'Jetpak       = l


End Sub
