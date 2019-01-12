Attribute VB_Name = "mod_GlobalData"
Public DX As New DirectX7 'DIRECTX!

'--------------------------.
'Some variables and stuff. |
'--------------------------'
Public ActCore_VERSION As String
Public ActCore_INITED As Boolean

Public UseVideoMem As Boolean
Public WideScreen As Boolean
Public WindowedResX As Long
Public WindowedResY As Long

Public PrevMapIndex As Integer

'-------------------------------------------------------------.
'This holds the framenumber for the character menu animation. |
'-------------------------------------------------------------'
Public CYCLENUM As Integer

'-------------------------------------------------------------.
'This holds the mirroring setting for the character painting. |
'-------------------------------------------------------------'
Public ReverseFlag As Boolean

Public TmpStoryFix As Integer

Public Enum TEAMTYPE
    tRED = 0
    rBLUE = 1
End Enum

'-------------------.
'Create the Spawns. |
'-------------------'
Public Type SPAWN_TYPE
    X As Long
    Y As Long
    BUSY As Boolean
    Team As TEAMTYPE
End Type
Public SPAWNPOINT(32 - 1) As SPAWN_TYPE
Public SPAWNPOINTS As Integer
Public RESPAWNTIMER As Integer
Public RESPAWNTIME As Integer

Public Enum gMODE_ENUM
    TRAINING_BOTPLAY = 0
    MULTIPLAY_FFA = 1
    MULTIPLAY_CTF = 2
    STORYMODE = 99
End Enum
Public GAMEMODE As gMODE_ENUM

Public Type EXTRAITEMTYPE
    itType As Integer
    itX As Long
    itY As Long
    itAnimLen As Integer
    itAnimPos As Integer
    itAnimHeight As Integer
    itAnimWidth As Integer
End Type
Public ExtraItem(0 To 32) As EXTRAITEMTYPE
Public ExtraItems As Integer

Public STORYMAP As Integer

Public gSTARTED As Boolean
Public mLOADING As Boolean

'-------------------------------------------------.
'Create the Character with some example settings. |
'-------------------------------------------------'
Public Type CHARACTER_TYPE
    Animation As STATE_ENUM
    ANIMATIONNUM As Integer
    ANIMATIONLENGTH As Integer
    Model As Integer
    MENUANIMATION As Integer
    X As Long
    Y As Long
    StandingOnGround As Boolean
    CANJUMP As Boolean
    JUMPING As Boolean
    CROUCHING As Boolean
    YSpeed As Integer
    name As String
    Team As TEAMTYPE
    TeamName As String
    FALLING As Boolean
    FREEZE As Boolean
    JETPAK As Boolean
    CROSSHAIR As Integer
    CROSSHAIRNUM As Integer
    Health As Integer
    ARMOR As Integer
    ARMORMAX As Integer
    Frags As Integer
    DEATH As Integer
    Dead As Boolean
    FIRING As Boolean
    GOTJUMPASSIST As Boolean
    JUMPASSISTTIME As Integer
    JUMPASSISTREADY As Boolean
    GotShield As Boolean
    GOTHEARTSENS As Boolean
    SHIELDTIME As Integer
    GOTCAP As Boolean
    SHIELDFLASH As Boolean
    JUMPASSISTFLASH As Boolean
    FLASHTIME As Integer
    PLACINGMineFlag As Boolean
    PLACINGMineTime As Integer
    PLACINGMineTimeMax As Integer
    GOTSUIT As Boolean
End Type
Public CHARACTER As CHARACTER_TYPE

'----------------------------------------------.
'The Animationstate enums for easy navigation. |
'----------------------------------------------'
Public Enum STATE_ENUM
    STANDING = 0
    RUNNING = 1
    FIRING = 2
    FIRINGRUNNING = 3
    FIRINGRUNNINGBACKWARDS = 4
    JETPAK = 5
    INAIR = 6
    FIRINGINAIR = 7
    AIRSHAFT = 8
    JUMPING = 20
    CROUCHING = 21
    CRAWLING = 22
End Enum

'----------------------.
'Some other variables. |
'----------------------'
Public LoadingMenuFlag As Boolean
Public ShutdownNoErrorFlag As Boolean
Public LoadingCompletion As Long

'-----------------------------.
'Create the main mapsettings. |
'-----------------------------'
Public MapHeight As Integer, MapWidth As Integer 'map width height from file
Public MapName As String, MapSkin As String
Public MapCol As String, MapCreator As String  'other mapinfo from mapfile
Public MapSong As Integer



'------------------.
'Custom Map Stuff. |
'------------------'

Public cMapCount As Integer
Public cMapSelected As Integer

Public SSCount As Long
Public StartGameSwitch As Boolean
Public ShowMotDSwitch As Boolean

'-------------------------------.
'Function to control loopspeed. |
'-------------------------------'
Public Declare Function GetTickCount Lib "kernel32" () As Long

'-----------------------------------------------------.
'This is variables that hold the tickcount for timing |
'of loops..                                           |
'-----------------------------------------------------'
Public lTickCount As Long, lOldTickCount As Long, _
lTickCount2 As Long, lOldTickCount2 As Long, _
lTickCount3 As Long, lOldTickCount3 As Long, _
lTickCount4 As Long, lOldTickCount4 As Long, _
lTickCount5 As Long, lOldTickCount5 As Long, _
lTickCount6 As Long, lOldTickCount6 As Long, _
lTickCount7 As Long, lOldTickCount7 As Long, _
lTickCount8 As Long, lOldTickCount8 As Long, _
lTickCount9 As Long, lOldTickCount9 As Long, _
lTickCount10 As Long, lOldTickCount10 As Long, _
lTickCount11 As Long, lOldTickCount11 As Long, _
lTickCount12 As Long, lOldTickCount12 As Long, _
lTickCount13 As Long, lOldTickCount13 As Long

'------------------------------.
'Function to control mousevis. |
'------------------------------'
Public Declare Function ShowCursor& Lib "user32" (ByVal bShow As Long)

Public Sub LoadcMapList()

With frmMain.FilecMap
    If (Dir(App.Path & "\maps\") = "") Then Exit Sub
    .Path = App.Path & "\maps\"
End With
    
    cMapCount = frmMain.FilecMap.ListCount
    

        
    Dim i As Integer
    
    For i = 0 To cMapCount - 1
        frmMain.ListcMap.AddItem App.Path & "\maps\" & frmMain.FilecMap.List(i)

            
        DoEvents
        
    Next i
    
    cMapSelected = 0

End Sub


Public Sub LOADPREVIEW(Filename As String)

On Local Error GoTo NOTFOUND

If (Dir(Filename) = "") Then GoTo NOTFOUND

If mLOADING = True Then Exit Sub

'------------------------------------------------.
'This loads the map and stores in the map-array. |
'------------------------------------------------'
If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
If EngineLogEnabled Then WriteEngineLOG LOGFILE, "LOADING OF MAP " & Filename & " STARTED"

cEnabled = False

Dim q As Long, w As Long, e As Integer, t As Integer, t2 As Integer

Dim tstr As String, tInt As Integer, z As Integer

Open Filename For Input As 1

    Line Input #1, tstr
        MapName = tstr
    Line Input #1, tstr
        MapCreator = tstr
    Line Input #1, tstr
        MapSkin = tstr
    Line Input #1, tstr
        MapFX = tstr
    Line Input #1, tstr
    
    Line Input #1, tstr
        MapWidth = Int(tstr)
    Line Input #1, tstr
        MapHeight = Int(tstr)
        
    rTOTMAP.Left = 0
    rTOTMAP.Right = MapWidth * 32
    rTOTMAP.Top = 0
    rTOTMAP.Bottom = MapHeight * 32
    
    Dim ddckey As DDCOLORKEY
    Set DDS_COLLISIONMAP = Nothing

    'Now let's set the surface description
    DDSD_COLLISIONMAP.lFlags = DDSD_CAPS And DDSD_WIDTH And DDSD_HEIGHT
    If UseVideoMem Then
        DDSD_COLLISIONMAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_COLLISIONMAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    DDSD_COLLISIONMAP.lWidth = MapWidth * 32
    DDSD_COLLISIONMAP.lHeight = MapHeight * 32
    'now create the other off-screen surface
    If (Dir(App.Path & "\maps\" & MapSkin & ".col.bmp") = "") Then
        Set DDS_COLLISIONMAP = DD.CreateSurfaceFromFile(App.Path & "\maps\" & MapSkin & ".col.bmp", DDSD_COLLISIONMAP)
        ddckey.low = 0: ddckey.high = 0
        DDS_COLLISIONMAP.SetColorKey DDCKEY_SRCBLT, ddckey
    Else
        Set DDS_COLLISIONMAP = DD.CreateSurfaceFromFile(App.Path & "\maps\" & MapSkin & ".col.bmp", DDSD_COLLISIONMAP)
        ddckey.low = 0: ddckey.high = 0
        DDS_COLLISIONMAP.SetColorKey DDCKEY_SRCBLT, ddckey
    End If
            
    CreateGuidemapSurface
    
Do Until EOF(1)
    
    Line Input #1, tstr
    For i = 0 To Len(tstr) - 1
        
        CreateGuideMap CLng(i), CLng(tInt)
        DoEvents
        
    Next
    
tInt = tInt + 1

DoEvents
    
Loop
Close

Exit Sub

NOTFOUND:
    Exit Sub

End Sub


Public Sub LoadData()

    LoadPlayerModelData
    CHARACTER.DEATH = 0
    CHARACTER.X = 256
    CHARACTER.Y = 256

End Sub



Public Sub LoadPlayerModelData()

    CHARACTER.Model = 0

End Sub

Public Sub LoadMap(Filename As String)

On Local Error GoTo ErrOut

If (Dir(Filename) = "") Then GoTo NOTFOUND

If mLOADING = True Then Exit Sub
'If NetworkStatus = SUCCESS Then SendItem tACK, False, 1

'------------------------------------------------.
'This loads the map and stores in the map-array. |
'------------------------------------------------'
If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
If EngineLogEnabled Then WriteEngineLOG LOGFILE, "LOADING OF MAP " & Filename & " STARTED"

cEnabled = False
mLOADING = True
LoadingMenuFlag = True
LoadingCompletion = 0
gSTARTED = False

MENU.VisibleMenu = MNUMain
DoEvents
OverlayMenu = False
RunningMapEditor = False

ResetMapObjects

Dim q As Long, w As Long, e As Integer, t As Integer, t2 As Integer

'-----------------------------------------.
'Dim some temporary strings and integers. |
'-----------------------------------------'
Dim tstr As String, tInt As Integer, z As Integer

'--------------.
'Open the map. |
'--------------'
Open Filename For Input As 1
    '--------------------------------------------------.
    'Take the first line of file and store in mapname. |
    '--------------------------------------------------'
    Line Input #1, tstr
        MapName = tstr
    '---------------------------------------------------.
    'Take the second line of file and store in creator. |
    '---------------------------------------------------'
    Line Input #1, tstr
        MapCreator = tstr
    '--------------------------------------------------------.
    'Take the third/forth line of file and store in mapskin. |
    '--------------------------------------------------------'
    Line Input #1, tstr
        MapSkin = tstr
    Line Input #1, tstr
        If tstr = "1" Then
            GAMEMODE = MULTIPLAY_CTF
        ElseIf tstr = "2" Then
            GAMEMODE = MULTIPLAY_FFA
        ElseIf tstr = "99" Then
            GAMEMODE = STORYMODE
        Else
            GAMEMODE = MULTIPLAY_FFA
        End If
    Line Input #1, tstr
        If Len(tstr) > 0 Then
            MapSong = Int(tstr) 'Used for StoryMode
        End If
        
    '------------------------------------------------.
    'Take the fifth line of file and store in width. |
    '------------------------------------------------'
    Line Input #1, tstr
        MapWidth = Int(tstr)
    '-------------------------------------------------.
    'Take the sixth line of file and store in height. |
    '-------------------------------------------------'
    Line Input #1, tstr
        MapHeight = Int(tstr)
        
    rTOTMAP.Left = 0
    rTOTMAP.Right = MapWidth * 32
    rTOTMAP.Top = 0
    rTOTMAP.Bottom = MapHeight * 32
    
        '-------------.
    'MAP SURFACE! |
    '-------------'

    Dim ddckey As DDCOLORKEY
    Set DDS_MAP = Nothing

    'Now let's set the surface description
    DDSD_MAP.lFlags = DDSD_CAPS And DDSD_WIDTH And DDSD_HEIGHT
    If UseVideoMem Then
        DDSD_MAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    DDSD_MAP.lWidth = MapWidth * 32
    DDSD_MAP.lHeight = MapHeight * 32
    'now create the other off-screen surface
    Set DDS_MAP = DD.CreateSurfaceFromFile(App.Path & "\maps\" & MapSkin, DDSD_MAP)
    
    ddckey.low = 0: ddckey.high = 0
    DDS_MAP.SetColorKey DDCKEY_SRCBLT, ddckey
    
    '---------------.
    'COLLISION MAP! |
    '---------------'

    Set DDS_COLLISIONMAP = Nothing

    'Now let's set the surface description
    DDSD_COLLISIONMAP.lFlags = DDSD_CAPS And DDSD_WIDTH And DDSD_HEIGHT
    If UseVideoMem Then
        DDSD_COLLISIONMAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_COLLISIONMAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    DDSD_COLLISIONMAP.lWidth = MapWidth * 32
    DDSD_COLLISIONMAP.lHeight = MapHeight * 32
    'now create the other off-screen surface
    If (Dir(App.Path & "\maps\" & MapSkin & ".col.bmp") = "") Then
        Set DDS_COLLISIONMAP = DD.CreateSurfaceFromFile(App.Path & "\maps\" & MapSkin & ".col.bmp", DDSD_COLLISIONMAP)
        ddckey.low = 0: ddckey.high = 0
        DDS_COLLISIONMAP.SetColorKey DDCKEY_SRCBLT, ddckey
    Else
        Set DDS_COLLISIONMAP = DD.CreateSurfaceFromFile(App.Path & "\maps\" & MapSkin & ".col.bmp", DDSD_COLLISIONMAP)
        ddckey.low = 0: ddckey.high = 0
        DDS_COLLISIONMAP.SetColorKey DDCKEY_SRCBLT, ddckey
    End If
        
    '----------------------------------.
    'Read the map until the file ends. |
    '----------------------------------'
    
    'CREATE THE GUIDEMAP SURFACE (NEEDS MAPWIDTH, MAPHEIGHT)
    CreateGuidemapSurface
    
Do Until EOF(1)
    
    Line Input #1, tstr
    
    For i = 0 To Len(tstr) - 1
    
        q = i * 32
        w = tInt * 32
        
        Randomize
          
        CreateMapObject Mid(tstr, i + 1, 1), q, w
        
        'If Map(q, w) = "S" Then
        If Mid(tstr, i + 1, 1) = "S" Then
        
            SPAWNPOINT(z).X = q
            SPAWNPOINT(z).Y = w
            SPAWNPOINT(z).Team = rBLUE
            SPAWNPOINT(z).BUSY = False
            z = z + 1
            
        'ElseIf Map(q, w) = "s" Then
        ElseIf Mid(tstr, i + 1, 1) = "s" Then
        
            SPAWNPOINT(z).X = q
            SPAWNPOINT(z).Y = w
            SPAWNPOINT(z).Team = tRED
            SPAWNPOINT(z).BUSY = False
            z = z + 1
        
        ElseIf Mid(tstr, i + 1, 1) = "9" Then
            
            StoryEnemy(StoryEnemyCount(0)).PosX = q
            StoryEnemy(StoryEnemyCount(0)).PosY = w
            StoryEnemy(StoryEnemyCount(0)).Spawned = True
            StoryEnemy(StoryEnemyCount(0)).EnemyType = Lurker
        
        End If
        
        CreateGuideMap CLng(i), CLng(tInt)
        DoEvents
        
    Next
    
tInt = tInt + 1
LoadingCompletion = LoadingCompletion + 1

DoEvents
    
Loop
Close

SPAWNPOINTS = z
LoadMapExtras Filename & "_EXTRA.txt"
    
mLOADING = False

If EngineLogEnabled Then WriteEngineLOG LOGFILE, "LOADING OF MAP " & Filename & " COMPLETED SUCCESSFULLY"
If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""

If NetworkStatus <> SUCCESS Then
    Start_Game
Else
    SendItem tACK, True, 0
    StartGameMusic LOBBY
    MENU.VisibleMenu = MNULobby
End If

Exit Sub

NOTFOUND:
    
    LoadingCompletion = 0
    mLOADING = False
        
    cCmdFeed "COULD NOT FIND MAP " & Filename, True
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: COULD NOT FIND MAP " & Filename
        
    If GAMEMODE = STORY Then
    
        bQuit = True
        gSTARTED = False
        MapName = ""
        
    End If
    
    Exit Sub
    
ErrOut:

    LoadingCompletion = 0
    mLOADING = False
        
    cCmdFeed "ERROR WHILE LOADING MAP " & Filename & ". TRY SWITCH TO SYSTEM MEMORY INSTEAD OF VIDEO.", True
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: ERROR WHILE LOADING MAP " & Filename
    
    bQuit = True
    gSTARTED = False
    MapName = ""

End Sub

Public Sub LoadMapExtras(Filename As String)

ExtraItems = 0
On Local Error Resume Next

If (Dir(Filename) = "") Then Exit Sub

Dim numitems As Integer
Dim tstr As String
Dim tLoop As Integer

    Open Filename For Input As 1

    Line Input #1, tstr
        numitems = CStr(tstr)
    
    For tLoop = 0 To numitems - 1
    
        Line Input #1, tstr
        ExtraItem(tLoop).itX = CLng(tstr)
        
        Line Input #1, tstr
        ExtraItem(tLoop).itY = CLng(tstr)
        
        Line Input #1, tstr
        ExtraItem(tLoop).itType = CInt(tstr)
        
        Line Input #1, tstr
        ExtraItem(tLoop).itAnimLen = CInt(tstr)
        
        Line Input #1, tstr
        ExtraItem(tLoop).itAnimWidth = CInt(tstr)
        
        Line Input #1, tstr
        ExtraItem(tLoop).itAnimHeight = CInt(tstr)
        
        'Reset animation
        ExtraItem(tLoop).itAnimPos = 0
        
        ExtraItems = ExtraItems + 1
        
    Next tLoop
        
    Close
    
End Sub

Sub Main()

If App.PrevInstance Then End
'on local error Resume Next

INIT_DefaultKeys



CFGFile = App.Path & "\default.cfg"
LOGFILE = App.Path & "\engine.log"

    If (Dir(App.Path & "\screenshots", vbDirectory) = "") Then
        MkDir App.Path & "\screenshots"
    End If
    
    frmMain.fSSCount.Path = App.Path & "\screenshots"
    SSCount = frmMain.fSSCount.ListCount - 1
    If SSCount < 0 Then SSCount = 0
    
    bPacketMotD(0) = 11
    bPacketMotD(1) = 12
    bPacketMotD(2) = 13
    
    mod_Network.bMotD0 = "WELCOME TO Activated.Core"
    mod_Network.bMotD1 = "DEBUG VERSION"
    mod_Network.bMotD2 = ActCore_VERSION
    mod_Network.bMotNotice = "http://eb3k.jiisuki.net"

    Dim tmpValue As String
    tmpValue = ReadCFG(CFGFile, "ENGINELOG")
    If tmpValue = "" Then
        EngineLogEnabled = False
    Else
        EngineLogEnabled = CBool(tmpValue)
    End If
    
Dim sOption As String
sOption = Left$(Command, 1)

If sOption = "/" Then
            
    Dim tmpL As Long
    tmpL = Len(Command)
               
    Dim sCommand As String
    sCommand = Mid$(Command, 2, (tmpL - 1))
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, ">> STARTING WITH COMMAND: " & sCommand
    
End If

If sCommand = "" Then sCommand = "NONE"


    ActCore_VERSION = "VERSION ALPHA " & App.Major & "." & App.Minor & "." & App.Revision
    ActCore_INITED = False
    

    If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "New Logged Run started."
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
    

    
        CFG_INIT
        
            
    Dialog.Label2 = UCase("hides cursor...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        
            
    '        DIALOGPB = DIALOGPB + 1
    '        Dialog.PB.Value = DIALOGPB
    
    Dialog.Label2 = UCase("loading credits...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        Credits_INIT
        
    '        DIALOGPB = DIALOGPB + 1
    '        Dialog.PB.Value = DIALOGPB
        
    Dialog.Label2 = UCase("loading intro...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
        
        Intro_INIT
        
     '       DIALOGPB = DIALOGPB + 1
     '       Dialog.PB.Value = DIALOGPB
        
    Dialog.Label2 = UCase("loading fmod engine...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        Sound_INIT
            
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, "USING DRIVER: " & UCase(GetStringFromPointer(FSOUND_GetDriverName(count)))
     '       DIALOGPB = DIALOGPB + 1
     '       Dialog.PB.Value = DIALOGPB
            
    Dialog.Label2 = UCase("creating bots...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    'If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
    '
        
        CreateBots
     '   If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
        
     '       DIALOGPB = DIALOGPB + 1
     '       Dialog.PB.Value = DIALOGPB
            
    Dialog.Label2 = UCase("creating weapon instances...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    'If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
    '
        
        WeapInit
    '    If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
        
     '       DIALOGPB = DIALOGPB + 1
     '       Dialog.PB.Value = DIALOGPB
    
    Dialog.Label2 = UCase("loading console...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        Console_INIT
        
    '        DIALOGPB = DIALOGPB + 1
    '        Dialog.PB.Value = DIALOGPB
    
    Dialog.Label2 = UCase("initializing hud...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        HUD_INIT
        
    '        DIALOGPB = DIALOGPB + 1
    '        Dialog.PB.Value = DIALOGPB
    
    Dialog.Label2 = UCase("loading player model data...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        LoadPlayerModelData
        
    '        DIALOGPB = DIALOGPB + 1
    '        Dialog.PB.Value = DIALOGPB
        
    Dialog.Label2 = UCase("loading custom maplist...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
        
        LoadcMapList
        
    '        DIALOGPB = DIALOGPB + 1
    '        Dialog.PB.Value = DIALOGPB
    
    Dialog.Label2 = UCase("reseting instructions list")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        InstructionsPage = 1
        
    '        DIALOGPB = DIALOGPB + 1
    '        Dialog.PB.Value = DIALOGPB
    
    'Dialog.Label2 = UCase("Check music!")
    'If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        
            
    '        DIALOGPB = DIALOGPB + 1
    '        Dialog.PB.Value = DIALOGPB
    
    Dialog.Label2 = UCase("updating music information...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        PlayingInfo = CheckPlayingInfo(True)
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("playing '" & PlayingInfo & "'")
        
     '       DIALOGPB = DIALOGPB + 1
     '       Dialog.PB.Value = DIALOGPB
            
            
        InitRayTraceEngine
    
    Dialog.Label2 = UCase("various variables resetting...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        DXBitDepth = 32 'Depth, will be 4 bit later on.
        AIM_DEPTH = 64  'For crosshair control ingame
        SCRWidth = 320 '320  'Retro resolution.
        SCRHeight = 240 '240
        Randomize
        Starfield.CLR_R = Int(Rnd * 256)
        Randomize
        Starfield.CLR_G = Int(Rnd * 256)
        Randomize
        Starfield.CLR_B = Int(Rnd * 256)
        
        RESPAWNTIME = 3
        
        'Starfield.CLR_G = 255
        'Starfield.CLR_B = 255
        
        MOUSE_SPEED = 0.5
        ServerName = GetRandomName
        JoinIpAddress = "localhost"
        MapName = "NoMapLoaded"
    
    Dialog.Label2 = UCase("loading completed. starting up...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    '
    
        Dialog.Timer1.ENABLED = False
     '   Unload Dialog
     
    Dim tmpScreen As Variant
    tmpScreen = MsgBox("Windowed mode?", vbYesNo, "Windowed mode")
    If tmpScreen = vbYes Then
        ScreenMode = 0
    Else
        ScreenMode = 1
    End If
    
    If ScreenMode = 1 Then
        'WideScreen = CVar(MsgBox("Widescreen?", vbYesNo, "Widescreen"))
    Else
        'WideScreen = False
    End If
    
    frmMain.tmr_StarDirection.Interval = 10000
    SELECTEDMENU = MNUMultiplayer
    TmpStoryFix = 0
    
    r.Left = 0
    r.Top = 0
    r.Right = SCRWidth
    r.Bottom = SCRHeight
    
    If ScreenMode = 0 Then
        frmWindowedRes.Show
    Else
        ShowCursor 0
        ActCore_INIT ScreenMode, sCommand
    End If
    
End Sub

Public Sub ActCore_INIT(InitScreenMode As Integer, Optional sCommand As String)

'------------------------------.
'This Sub inits the game       |
'sets the screenmode and start |
'the dx paintloop              |
'------------------------------'

cWhite = RGB(255, 255, 255)
cBlack = RGB(0, 0, 0)
cRed = RGB(0, 0, 255)
cGreen = RGB(0, 255, 0)
cBlue = RGB(255, 0, 0)

DrawFPS = False


On Local Error GoTo Shutdowner

    'create the DirectDraw object
    Set DD = DX.DirectDrawCreate("")

    'resize the form to the right size
    
    If LCase(sCommand) = "windowededitor" Then InitScreenMode = 0
    
    If InitScreenMode = 0 Then
    
        frmMain.BorderStyle = 0
        frmMain.Width = WindowedResX * Screen.TwipsPerPixelX '768 * Screen.TwipsPerPixelX
        frmMain.Height = WindowedResY * Screen.TwipsPerPixelY '480 * ...
        'frmMain.BorderStyle = 4
        frmMain.Show

        'remember the screenmode
        SMode = InitScreenMode
    
        '-----------.
        'Windowed!! |
        '-----------'
        
        'make your application a happy normal window
        Call DD.SetCooperativeLevel(frmMain.hwnd, DDSCL_NORMAL)
        
        
        'Indicate that the ddsCaps member is valid in this type
        DDSD_Primary.lFlags = DDSD_CAPS
        'This surface is the primary surface (what is visible to the user)
        DDSD_Primary.ddsCaps.lCaps = DDSCAPS_PRIMARYSURFACE
        'Your creating the primary surface now with the surface description you just set
        Set DDS_Primary = DD.CreateSurface(DDSD_Primary)
        
        'allocate the clipper
        Set ddClipper = DD.CreateClipper(0)
        ddClipper.SetHWnd frmMain.hwnd
        DDS_Primary.SetClipper ddClipper
        
        'This is going to be a plain off-screen surface
        DDSD_Back.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN + DDSCAPS_VIDEOMEMORY
        'tell create we want to set the width and height & caps
        DDSD_Back.lFlags = DDSD_CAPS Or DDSD_WIDTH Or DDSD_HEIGHT
        'at 640 by 480 in size
        DDSD_Back.lWidth = SCRWidth
        DDSD_Back.lHeight = SCRHeight
        'Now we create the 640x480 off-screen urface
        Set DDS_Back = DD.CreateSurface(DDSD_Back)
        'colour it in black
        DDS_Back.BltColorFill r, RGB(0, 0, 0)
        
    Else
        
        '--------------.
        'Full-screen!! |
        '--------------'
        
        frmMain.BorderStyle = 0
        If WideScreen Then
            'SCRWidth = 320
            'SCRHeight = 200
            frmMain.Move 0, 0, SCRWidth * Screen.TwipsPerPixelX, SCRHeight * Screen.TwipsPerPixelY
        Else
            frmMain.Move 0, 0, SCRWidth * Screen.TwipsPerPixelX, SCRHeight * Screen.TwipsPerPixelY
        End If
        frmMain.Show

        'remember the screenmode
        SMode = InitScreenMode
            
        'make your application full-screen
        Call DD.SetCooperativeLevel(frmMain.hwnd, DDSCL_FULLSCREEN Or DDSCL_ALLOWMODEX Or DDSCL_EXCLUSIVE)
        
        'set the screen mode
        If DXBitDepth <> 0 Then
            DD.SetDisplayMode SCRWidth, SCRHeight, DXBitDepth, 0, DDSDM_DEFAULT
        Else
            DD.SetDisplayMode SCRWidth, SCRHeight, 16, 0, DDSDM_DEFAULT
        End If

        'get the screen surface and create a back buffer too
        DDSD_Primary.lFlags = DDSD_CAPS Or DDSD_BACKBUFFERCOUNT
        DDSD_Primary.ddsCaps.lCaps = DDSCAPS_PRIMARYSURFACE Or DDSCAPS_FLIP Or DDSCAPS_COMPLEX  'Or DDSCAPS_3DDEVICE Or DDSCAPS_VIDEOMEMORY
        DDSD_Primary.lBackBufferCount = 1
        
        Set DDS_Primary = DD.CreateSurface(DDSD_Primary)

'        Set D3D = DD.GetDirect3D
'        Set D3DDevice = D3D.CreateDevice("IID_IDirect3DHALDevice", BackBuffer)
        
        'now grab the back surface (from the flipping chain)
        Dim caps As DDSCAPS2
        caps.lCaps = DDSCAPS_BACKBUFFER
        Set DDS_Back = DDS_Primary.GetAttachedSurface(caps)
                        
    End If
    
    'Init the gammaramp settings
    Gamma_INIT
    SetGamma GammaValue, GammaValue, GammaValue
        
    '---------------------------.
    'Lets show the main form!:D |
    '---------------------------'
    Dim ddsdTemp As DDSURFACEDESC2

    DDS_Primary.GetSurfaceDesc ddsdTemp
    If ddsdTemp.ddpfPixelFormat.lGBitMask = &H3E0 Then
      ClientVidMode = 555
    ElseIf ddsdTemp.ddpfPixelFormat.lGBitMask = &H7E0 Then
      ClientVidMode = 565
    Else
      ClientVidMode = 555
    End If
    'cCmdFeed "Client Video Mode: " & CStr(ClientVidMode), True
    
    '---------------.
    'Do init stuff. |
    '---------------'
    LoadMenuGFX
    Star_INIT
    
    HUD.ENABLED = True                  'Nice to have :P
    STORYMAP = 1                        'To start at lvl 1.
    
    If ShowIntro Then
        MENU.VisibleMenu = MNUIntro
    Else
        MENU.VisibleMenu = MNUMain
    End If
    
    DInput_INIT         'must be started when we have frmMain visible.
    
    
    
    ActCore_INITED = True  'startup
    
    If sCommand <> "NONE" Then
        MENU.VisibleMenu = MNUMultiplayerJoin
        If Left$(sCommand, 7) = "CONNECT" Then
            JoinIpAddress = Right$(sCommand, (Len(sCommand) - 7))
            MENU.VisibleMenu = MNUMultiplayerJoin
        End If
        cCmdFeed sCommand, False
    End If
    
    StartGameMusic INTRO
    
    RenderMenuLoop
    
    Exit Sub
    
Shutdowner:

    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: INITIALIZING ActCore DIRECTX WINDOW"
    ShutdownNoErrorFlag = False: Shutdown

End Sub

Public Sub Start_Game()

'on local error GoTo ErrOut
    
    '----------------------------.
    'Load surfaces and any data. |
    '----------------------------'
    LoadSurfaces
    LoadData
    Init_Physics
    'GAMEMODE = MULTIPLAY_FFA
    'WeaponReloadTime = 900
    StoryMapFinish = False
    
    gSTARTED = True
    bQuit = False
    CharacterSpawn
    
    If GAMEMODE = TRAINING_BOTPLAY Then
        Dim i As Integer
        For i = 0 To UBound(BotClient)
            BotClient(i).Spawn
        Next i
    End If
    
    OverlayMenu = False
    HUD.ENABLED = False
    ShowMotDSwitch = True
    
    frmMain.tmr_MotDDisplayTimer.ENABLED = True
    '-------------------------------.
    'Begin the main rendering loop. |
    '-------------------------------'
    If GAMEMODE = STORYMODE Then
        Select Case MapSong
            Case 1
                StartGameMusic GAME1
            Case 2
                StartGameMusic GAME2
            Case 3
                StartGameMusic GAME3
            Case 4
                StartGameMusic GAME4
            Case 5
                StartGameMusic GAME5
            Case 6
                StartGameMusic GAME6
            Case 7
                StartGameMusic GAME7
            Case 8
                StartGameMusic GAME8
            Case 9
                StartGameMusic GAME9
            Case Else
                StartGameMusic GAME1
        End Select
    Else
        StartGameMusic SelectedMusic
    End If
    
    MENU.VisibleMenu = MNUMain
    SELECTEDMENU = MNUMultiplayer
    
    Renderloop
    
    Exit Sub
    
ErrOut:

    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: STARTING GAME SUB"
    
End Sub



Public Function GetRandomDeathMsg(Optional ByVal cFixed As Integer = 255) As String

    Dim i As Integer
    Randomize
    
    If cFixed = 255 Then
        i = Int(Rnd * (frmMain.lst_DeathMSGs.ListCount - 1)) + 1
    Else
        i = cFixed
    End If
    
    GetRandomDeathMsg = frmMain.lst_DeathMSGs.List(i)

End Function



Public Sub Shutdown(Optional ByVal BRUTAL As Boolean = False, Optional ErrText As String)
    
    
    
    frmMain.Hide
    
    If BRUTAL Then
            
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, "BRUTAL SHUTDOWN STARTED"
        
        Unload frmMain
            
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, "UNLOADED MAIN"
        
        FSOUND_Close
        
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, "SOUND ENGINE CLOSED"
            
        Set DX = Nothing
            
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, "DIRECTX KILLED"
            
        ShowCursor 1
        
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, "CURSOR VIS"
            
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, "BRUTAL SHUTDOWN COMPLETED AT [" & Time & "]"
            
        GoTo BRUT
        
    End If
    
    Dialog.Show
    Dialog.Label1 = "0"
    Dialog.Timer1.ENABLED = True
    
    Dialog.Label4 = UCase(ActCore_VERSION)
    If ShutdownNoErrorFlag Then
        Dialog.Caption = "Status: UNLOADING Activated Core..."
    Else
        Dialog.Caption = "Status: ERROR OCCURED, UNLOADING Activated Core..."
    End If
    
        StopMusicPlaying
        WriteCFG CFGFile, "MP3SONG", CStr(mp3song - 1)
        
        
    Dialog.Label2 = UCase("unloading fmod engine...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
    
        FSOUND_Close
        
    
    Dialog.Label2 = UCase("unloading main...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
    
        Unload frmMain
        If NetworkStatus = SUCCESS Then
            UnloadClient
        End If
        
    
    Dialog.Label2 = UCase("unloading direct draw...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
    
        Set DD = Nothing
        
        
    Dialog.Label2 = UCase("unloading direct input...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
    
        Terminate_DInput
        
    
    Dialog.Label2 = UCase("unloading music playing...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
    
        
        
    Dialog.Label2 = UCase("unloading direct x...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
    
        Set DX = Nothing

        
            
    Dialog.Label2 = UCase("terminating bots...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
    
        TerminateBots
    

        
    Dialog.Label2 = UCase("makes cursor visible...")
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
    
        ShowCursor 1
        
        
    If ShutdownNoErrorFlag Then
        Dialog.Label2 = UCase("shutdown completed. thanks for playing.")
    Else
        Dialog.Label2 = ErrText
    End If
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, ""
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, Dialog.Label2
    
        
    Unload Dialog
    End
    
BRUT:
    
    End
    
ENDSHUT:

    
            
End Sub

Public Sub Sound_INIT()

    SampleFreq = 44100

    'This is the first thing you have to do before you can start working with fmod
    Dim result As Boolean
    
    FSOUND_SetOutput FSOUND_OUTPUT_DSOUND

    result = FSOUND_Init(SampleFreq, 32, FSOUND_INIT_GLOBALFOCUS)
    If Not result Then
        'An error occured
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "An error occured initializing fmod!" & _
        FSOUND_GetErrorString(FSOUND_GetError)
        ShutdownNoErrorFlag = False: Shutdown
    End If
    
    FSOUND_SetVolume FSOUND_ALL, 255
    FSOUND_SetVolumeAbsolute FSOUND_ALL, 255
        
End Sub

Public Sub ReadMapInfo(Filename As String)

'------------------------.
'This loads the mapinfo. |
'------------------------'

Dim q As Long, w As Long, e As Integer, t As Integer, t2 As Integer

'-----------------.
'Simple errorfix. |
'-----------------'
If Filename = "" Then Exit Sub

Dim tstr As String

Open Filename For Input As 1

    Line Input #1, tstr
        MapName = tstr
    Line Input #1, tstr
        MapCreator = tstr
    Line Input #1, tstr
        MapSkin = tstr
    Line Input #1, tstr
        MapCol = tstr
    Line Input #1, tstr
        MapWidth = Int(tstr)
    Line Input #1, tstr
        MapHeight = Int(tstr)
        
Close

End Sub

Public Sub EventPause(sngSeconds As Single)

    '// A Single will convert to scientific notation when concatenating a
    '//  number resulting in 8-digits or more. This can introduce inaccuracies
    '//  as a result of the number being rounded when converted. Therefore we
    '//  must declare doubles when working with the date counter to avoid
    '//  converting to scientific notation.
    Dim dblTotal As Double, dblDateCounter As Double, sngStart As Single
    Dim dblReset As Double, sngTotalSecs As Single, intTemp As Integer
        '// For our purposes, it's better to concatenate five zeros onto the
        '//  end of our date counter, then ADD any Timer values to it.
        dblDateCounter = ((Year(Date) + Month(Date) + Day(Date)) _
          & 0 & 0 & 0 & 0 & 0)
        '// Initialize start time.
        sngStart = Timer
        '// We also need to adjust for the possible resetting of Timer()
        '//  (such as if the Time happens to be just before midnight) when
        '//  adding the Pause time onto the Start time. The folowing formula
        '//  takes ANY value of the total seconds, whether it's above or below
        '//  the 86400 limit, and converts it to a format compatible to the
        '//  date counter.
        sngTotalSecs = (sngStart + sngSeconds)
        intTemp = (sngTotalSecs \ 86400)   '// Return the integer portion only
        dblReset = (intTemp * 100000) + (sngTotalSecs - (intTemp * 86400))
        '// Now we can initialize our total time.
        dblTotal = dblDateCounter + dblReset
    
    '// Timer loop
    Do
        DoEvents        '// Make sure any other tasks get some attention
    '// For this to work properly, we cannot create a variable with the
    '//  concatenated expression and plug it in unless we reset the variable
    '//  during the loop. Much better to do it like this:

    Loop While (dblDateCounter + Timer) < dblTotal
    
End Sub

Public Function GetRandomName() As String

    Randomize
    Dim tmpValue As String, i As Integer, tName As String
    tName = ""

For i = 0 To (Int(Rnd * 5) + 3)

NewLetter:
                        
    If i = 0 Then
        tmpValue = Chr(Int(Rnd * 25) + 65) 'First letter UCase
    Else
        tmpValue = Chr(Int(Rnd * 25) + 97) 'Rest LCase
    End If

If i > 0 Then
            
    If Int(i / 2) = (i / 2) Then
        If tmpValue = "a" Or tmpValue = "e" Or tmpValue = "i" Or tmpValue = "o" Or tmpValue = "u" Or tmpValue = "y" Then
            'It has got a vowel.
        Else
            DoEvents
            GoTo NewLetter 'fix new letter
        End If
    End If
    
    If Right(tName, 1) = tmpValue Or Right(tName, 1) = UCase(tmpValue) Then
        GoTo NewLetter 'fix new letter
    End If
    
End If
    
    tName = tName & tmpValue
    
Next i

GetRandomName = tName

End Function
