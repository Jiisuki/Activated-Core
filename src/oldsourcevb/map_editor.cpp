Attribute VB_Name = "mod_MapEditor"
Public RunningMapEditor As Boolean
Public bQuit3 As Boolean
Public ACTIVETILEROW As Integer
Public MAPSCreated As Boolean
Public EditPosX As Long
Public EditPosY As Long
Public MAP() As String
Public SELECTEDTILE As Integer
Public LOADMAPFLAG As Boolean
Public NEWMAPFLAG As Integer
Public tMapWidth As String
Public tMapHeight As String
Public MAPFILENAME As String
Public ACTIVETILESET As Integer
Public TMPGUIDE As Boolean

Public Sub INIT_MAPEDITOR(Optional fName As String = "")

    cEnabled = False
    RunningMapEditor = True
    MAPSCreated = False
    EditPosX = 0
    EditPosY = 0
    LOADMAPFLAG = False
    NEWMAPFLAG = 0
    MENU.VisibleMenu = MNUMain
    gSTARTED = False
    OverlayMenu = False
    TMPGUIDE = False
    
    ACTIVETILEROW = 1
    ACTIVETILESET = 1
    
'on local error GoTo ErrOut
        
    LoadSurfaces
    bQuit3 = False
    
    If fName <> "" Then LOADMAPSURFACE fName
                
    StartGameMusic MNU
    RENDERMAPEDITORLOOP
    
    Exit Sub
    
ErrOut:

    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: STARTING GAME SUB"

End Sub

Public Sub EXIT_MAPEDITOR(Optional tMap As String = "")
    
    RunningMapEditor = False
    If tMap <> "" Then
        cCmdFeed "MAP " & tMap
        Exit Sub
    Else
        RenderMenuLoop
    End If
    
End Sub

Public Sub RENDERMAPEDITORLOOP()

    'on local error GoTo Shutdowner

'------------------------------------------.
'This sub is the main menu renderloop.     |
'This flips the backbuffer so we can se it |
'on the primary screen buffer..            |
'------------------------------------------'

'the rectangles for windowed mode
    Dim r2 As RECT
    
'--------------------.
'Lets start the loop |
'--------------------'

    Do
    
        '-------------------------.
        'Draw current menu screen |
        '-------------------------'
        CheckMouse
        If LOADMAPFLAG Then
            DRAWLOADMAPFRAME
        ElseIf NEWMAPFLAG <> 0 Then
            DRAWNEWMAPFRAME
        Else
            DRAWEDITORFRAME
        End If
        
        '----------------------------------.
        'Flip the double buffered surfaces |
        'This is where the magic happens!  |
        '----------------------------------'
        If SMode = 0 Then 'Windowed mode
            DDS_Back.SetForeColor RGB(230, 140, 0)
            DDS_Back.DrawBox 0, 0, 320, 240
            DX.GetWindowRect frmMain.hwnd, r2
            r2.Top = r2.Top
            r2.Bottom = r2.Top + 480
            DDS_Primary.Blt r2, DDS_Back, r, DDBLTFAST_NOCOLORKEY + DDBLTFAST_WAIT
            
        Else   'Full-Screen
        
            DDS_Primary.Flip Nothing, DDFLIP_WAIT

        End If

    '-----------------------------.
    'Now we make time for windows |
    'to do other things           |
    '-----------------------------'
        DoEvents
    
    '--------------------------.
    'Loop until we say stop ;) |
    '--------------------------'
    
    Loop Until bQuit3
    
    EXIT_MAPEDITOR
    RenderMenuLoop
    
    
    Exit Sub
    
Shutdowner:
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: MENU RENDERLOOP"
    ShutdownNoErrorFlag = False: Shutdown

End Sub

Public Sub LOADQUICKPREVIEW()

'on local error GoTo Shutdowner
Dim cy As Long, DX As Long
For cx = 0 To MapWidth
For cy = 0 To MapHeight

If cx = 0 And cy = 0 Then
    DDS_GuideMap.BltColorFill HUD.SIZE_GUIDEMAP, 0
End If
'----------------------------------------------------------.
'This is alike the mapdrawing sub. This draws an fx layer, |
'tunnels and stuff onto the player.                        |
'----------------------------------------------------------'
    Dim e As Long, D As Long
    Dim r As RECT, r2 As RECT
        
        e = cx * 32
        D = cy * 32
        
    DDS_COLLISIONMAP.Lock rTOTMAP, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0

        If DDS_COLLISIONMAP.GetLockedPixel(e, D) = cWhite Then
            
            DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
            DDS_GuideMap.SetLockedPixel cx, cy, RGB(255, 255, 255) 'Uses BGR Order.
            DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP
                                                    
        ElseIf DDS_COLLISIONMAP.GetLockedPixel(e + 31, D) = cWhite Then
            
            DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
            DDS_GuideMap.SetLockedPixel cx, cy, RGB(255, 255, 255) 'Uses BGR Order.
            DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP
        
        ElseIf DDS_COLLISIONMAP.GetLockedPixel(e, D) = cBlue Then  'jumper
            
            DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
            DDS_GuideMap.SetLockedPixel cx, cy, RGB(255, 0, 0) 'Uses BGR Order.
            DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP
            
        ElseIf DDS_COLLISIONMAP.GetLockedPixel(e, D) = cRed Then  'inst-death
            
            DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
            DDS_GuideMap.SetLockedPixel cx, cy, RGB(0, 0, 255) 'Uses BGR Order.
            DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP
            
        ElseIf DDS_COLLISIONMAP.GetLockedPixel(e, D) = RGB(128, 128, 128) Then 'hz
            
            DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
            DDS_GuideMap.SetLockedPixel cx, cy, RGB(0, 0, 128) 'Uses BGR Order.
            DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP
        
        ElseIf DDS_COLLISIONMAP.GetLockedPixel(e, D) = cGreen Then  'inst-death
            
            DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
            DDS_GuideMap.SetLockedPixel cx, cy, RGB(0, 128, 0) 'Uses BGR Order.
            DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP

        End If
        
        If MAP(cx, cy) <> "1" And MAP(cx, cy) <> "J" And MAP(cx, cy) <> "Z" And MAP(cx, cy) <> "^" And MAP(cx, cy) <> " " Then
            If MAP(cx, cy) = "s" Then
                DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
                DDS_GuideMap.SetLockedPixel cx, cy, RGB(0, 0, 128)
                DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP
            ElseIf MAP(cx, cy) = "S" Then
                DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
                DDS_GuideMap.SetLockedPixel cx, cy, RGB(128, 0, 0)
                DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP
            Else
                DDS_GuideMap.Lock HUD.SIZE_GUIDEMAP, DDSD_GuideMap, DDLOCK_WAIT, 0
                DDS_GuideMap.SetLockedPixel cx, cy, RGB(128, 128, 128)
                DDS_GuideMap.Unlock HUD.SIZE_GUIDEMAP
            End If
        End If
        
    DDS_COLLISIONMAP.Unlock rTOTMAP
    
Next cy
Next cx

    DDS_Back.SetForeColor RGB(255, 255, 255)
    DDS_Back.DrawBox 320 - MapWidth, 0, 320, MapHeight
    
    Exit Sub
    
Shutdowner:
    Shutdown
    
    
End Sub

Public Sub DRAWNEWMAPFRAME()

    DDS_Back.BltColorFill r, RGB(0, 0, 0)
    
    If Starfield.ON Then
        StarPhysics
        DrawStars
    End If
    
    If NEWMAPFLAG = 1 Then
        DrawText UCase("ENTER MAP NAME"), 160 - ((Len("ENTER MAP NAME") / 2) * 8), 100, 0, 2
        DrawText UCase(MapName), 160 - ((Len(MapName) / 2) * 8), 120, 0, 2
    ElseIf NEWMAPFLAG = 2 Then
        DrawText UCase("ENTER YOUR NAME"), 160 - ((Len("ENTER YOUR NAME") / 2) * 8), 100, 0, 2
        DrawText UCase(MapCreator), 160 - ((Len(MapCreator) / 2) * 8), 120, 0, 2
    ElseIf NEWMAPFLAG = 3 Then
        DrawText UCase("ENTER MAP WIDTH"), 160 - ((Len("ENTER MAP WIDTH") / 2) * 8), 100, 0, 2
        DrawText UCase(tMapWidth), 160 - ((Len(CStr(tMapWidth)) / 2) * 8), 120, 0, 2
    ElseIf NEWMAPFLAG = 4 Then
        DrawText UCase("ENTER MAP HEIGHT"), 160 - ((Len("ENTER MAP HEIGHT") / 2) * 8), 100, 0, 2
        DrawText UCase(tMapHeight), 160 - ((Len(CStr(tMapHeight)) / 2) * 8), 120, 0, 2
    ElseIf NEWMAPFLAG = 5 Then
        DrawText UCase("ENTER MAP FILENAME"), 160 - ((Len("ENTER MAP FILENAME") / 2) * 8), 100, 0, 2
        DrawText UCase(MAPFILENAME), 160 - ((Len(MAPFILENAME) / 2) * 8), 120, 0, 2
    End If
    
End Sub

Public Sub DRAWLOADMAPFRAME()

    DDS_Back.BltColorFill r, RGB(0, 0, 0)
    
    If Starfield.ON Then
        StarPhysics
        DrawStars
    End If
    
    DrawText UCase("ENTER MAP FILENAME"), 160 - ((Len("ENTER MAP FILENAME") / 2) * 8), 100, 0, 2
    DrawText UCase(MAPFILENAME), 160 - ((Len(MAPFILENAME) / 2) * 8), 120, 0, 2

End Sub

Public Sub DRAWEDITORFRAME()

    DDS_Back.BltColorFill r, RGB(0, 0, 0)
        
    If Starfield.ON Then
        StarPhysics
        DrawStars
    End If
    
    Dim rMEN As RECT
    rMEN.Left = 0: rMEN.Right = 320
    rMEN.Top = 0: rMEN.Bottom = 52
    DDS_Back.BltColorFill rMEN, RGB(32, 32, 32)
    
    'TILE 1-5 * row
    Dim i As Integer
    For i = 0 To 5
        If mintMouseX > (i * 32) And mintMouseX < (i * 32) + 32 And mintMouseY > 20 And mintMouseY < 52 Then
            If mblnLMouseButton And mnuClickFix = 0 Then
                frmMain.tmr_MenuClickFix.ENABLED = True
                mnuClickFix = mnuClickFix + 1: mblnLMouseButton = False
                PlaySample "menu\select.mp3"
                SELECTEDTILE = i
            End If
        End If
    Next i
    
    DrawText "TILE: " & CStr(ACTIVETILEROW) & "." & CStr(SELECTEDTILE), 200, 32, 0, 1
    
    Dim tmpValue As String
    'Previous Row Button
    tmpValue = "PREV ROW"
    If mintMouseX > 200 And mintMouseX < (200 + 8 * Len(tmpValue)) And mintMouseY > 24 And mintMouseY < 32 Then
        DrawText tmpValue, 200, 24, 0, 3
        If mblnLMouseButton And mnuClickFix = 0 Then
            frmMain.tmr_MenuClickFix.ENABLED = True
            mnuClickFix = mnuClickFix + 1: mblnLMouseButton = False
            PlaySample "menu\select.mp3"
            ACTIVETILEROW = ACTIVETILEROW - 1
            If ACTIVETILEROW <= 0 Then
                ACTIVETILEROW = 32
            End If
        End If
    Else
        DrawText tmpValue, 200, 24, 0, 2
    End If
    
    'Next Row Button
    tmpValue = "NEXT ROW"
    If mintMouseX > 200 And mintMouseX < (200 + 8 * Len(tmpValue)) And mintMouseY > 40 And mintMouseY < 48 Then
        DrawText tmpValue, 200, 40, 0, 3
        If mblnLMouseButton And mnuClickFix = 0 Then
            frmMain.tmr_MenuClickFix.ENABLED = True
            mnuClickFix = mnuClickFix + 1: mblnLMouseButton = False
            PlaySample "menu\select.mp3"
            ACTIVETILEROW = ACTIVETILEROW + 1
            If ACTIVETILEROW >= 33 Then
                ACTIVETILEROW = 1
            End If
        End If
    Else
        DrawText tmpValue, 200, 40, 0, 2
    End If
    
    
    'New Map
    tmpValue = "NEW MAP"
    If mintMouseX > 8 And mintMouseX < (8 + 8 * Len(tmpValue)) And mintMouseY > 2 And mintMouseY < 2 + 8 Then
        DrawText tmpValue, 2, 2, 0, 3
        If mblnLMouseButton And mnuClickFix = 0 Then
            frmMain.tmr_MenuClickFix.ENABLED = True
            mnuClickFix = mnuClickFix + 1: mblnLMouseButton = False
            PlaySample "menu\select.mp3"
            MapName = ""
            MAPFILENAME = ""
            MapCreator = ""
            tMapWidth = 32
            tMapHeight = 32
            NEWMAPFLAG = 1
        End If
    Else
        DrawText tmpValue, 2, 2, 0, 2
    End If
    
    'Load map
    tmpValue = "LOAD MAP"
    If mintMouseX > 92 And mintMouseX < (92 + 8 * Len(tmpValue)) And mintMouseY > 2 And mintMouseY < 2 + 8 Then
        DrawText tmpValue, 92, 2, 0, 3
        If mblnLMouseButton And mnuClickFix = 0 Then
            frmMain.tmr_MenuClickFix.ENABLED = True
            mnuClickFix = mnuClickFix + 1: mblnLMouseButton = False
            PlaySample "menu\select.mp3"
            MAPFILENAME = ""
            LOADMAPFLAG = True
        End If
    Else
        DrawText tmpValue, 92, 2, 0, 2
    End If
        
    tmpValue = "SAVE MAP"
    If mintMouseX > SCRWidth - (8 * Len(tmpValue)) - 8 And mintMouseX < (320 + 8 * Len(tmpValue)) - 8 And mintMouseY > 2 And mintMouseY < 2 + 8 Then
        DrawText tmpValue, 320 - (8 * Len(tmpValue)) - 8, 2, 0, 3
        If mblnLMouseButton And mnuClickFix = 0 Then
            frmMain.tmr_MenuClickFix.ENABLED = True
            mnuClickFix = mnuClickFix + 1: mblnLMouseButton = False
            PlaySample "menu\select.mp3"
            If MAPFILENAME = "" Then
                cCmdFeed "NO MAP LOADED OR CREATED", True
            Else
                SAVEMAP MAPFILENAME, MapCreator, CLng(MapWidth), CLng(MapHeight)
            End If
        End If
    Else
        DrawText tmpValue, 320 - (8 * Len(tmpValue)) - 8, 2, 0, 2
    End If
    
    tmpValue = "TEST MAP"
    If mintMouseX > SCRWidth - (8 * Len(tmpValue)) - 8 And mintMouseX < (320 + 8 * Len(tmpValue)) - 8 And mintMouseY > 10 And mintMouseY < 10 + 8 Then
        DrawText tmpValue, 320 - (8 * Len(tmpValue)) - 8, 10, 0, 3
        If mblnLMouseButton And mnuClickFix = 0 Then
            frmMain.tmr_MenuClickFix.ENABLED = True
            mnuClickFix = mnuClickFix + 1: mblnLMouseButton = False
            PlaySample "menu\select.mp3"
            If MAPFILENAME = "" Then
                cCmdFeed "NO MAP LOADED OR CREATED", True
            Else
                'SAVEMAP MAPFILENAME, MapCreator, CLng(MapWidth), CLng(MapHeight)
                EXIT_MAPEDITOR MAPFILENAME
            End If
        End If
    Else
        DrawText tmpValue, 320 - (8 * Len(tmpValue)) - 8, 10, 0, 1
    End If
    
    If MAPSCreated Then
        DRAWEDITEDMAP
    End If

    DDS_Back.SetForeColor RGB(255, 128, 64)
    DDS_Back.DrawBox 0, 64, 320, 224
    DDS_Back.DrawBox 0, 0, 320, 20
    DDS_Back.DrawBox 192, 19, 320, 53
    DDS_Back.DrawBox 0, 19, 320, 53
    DRAWTILESET ACTIVETILEROW
    
    If TMPGUIDE = True Then
        LOADQUICKPREVIEW
        DRAWGUIDEMAP
        DDS_Back.SetForeColor RGB(0, 128, 255)
        DDS_Back.DrawBox 320 - MapWidth + CInt(EditPosX / 32), CInt(EditPosY / 32), 320 - MapWidth + CInt(EditPosX / 32) + 10, CInt(EditPosY / 32) + 5
    End If
    
    If MAPSCreated Then
        PAINTTILE
    Else
        DrawCrosshair
    End If
    
    If cEnabled Then
        cDrawConsole
    End If

End Sub

Public Sub PAINTTILE()

Dim RT As RECT, tmpX As Long, tmpY As Long, j As Integer

    'DRAW
    tmpX = 0
    tmpY = 0
    'RT.Left = 0
    'RT.Top = 0
    'RT.Right = 32
    'RT.Bottom = 32
    
    If mintMouseX >= 0 And mintMouseX <= 320 And mintMouseY >= 64 And mintMouseY <= 240 Then
        
        For j = 1 To 64
            If mintMouseX > j * 32 Then tmpX = j * 32
            If mintMouseY > j * 32 Then tmpY = j * 32
        Next j
        
        DRAWTILEPREV tmpX, tmpY
        If mblnLMouseButton Then
            RT.Left = SELECTEDTILE * 32
            RT.Right = RT.Left + 32
            RT.Top = ACTIVETILEROW * 32 - 32
            RT.Bottom = RT.Top + 32
            DDS_MAP.BltFast tmpX + EditPosX, tmpY + EditPosY - 64, DDS_MAPTILES, RT, DDBLTFAST_WAIT
            DDS_COLLISIONMAP.BltFast tmpX + EditPosX, tmpY + EditPosY - 64, DDS_COLTILES, RT, DDBLTFAST_WAIT
            If ACTIVETILEROW = 8 Then
                If SELECTEDTILE = 0 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "J"
                If SELECTEDTILE = 1 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
                If SELECTEDTILE = 2 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
                If SELECTEDTILE = 4 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
                If SELECTEDTILE = 5 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "^"
            ElseIf ACTIVETILEROW = 9 Then
                If SELECTEDTILE = 0 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "a"
                If SELECTEDTILE = 1 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "d"
                If SELECTEDTILE = 2 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "g"
                If SELECTEDTILE = 3 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "j"
                If SELECTEDTILE = 4 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "y"
                If SELECTEDTILE = 5 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "s"
            ElseIf ACTIVETILEROW = 10 Then
                If SELECTEDTILE = 0 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "b"
                If SELECTEDTILE = 1 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "e"
                If SELECTEDTILE = 2 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "h"
                If SELECTEDTILE = 3 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "k"
                If SELECTEDTILE = 4 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "x"
                If SELECTEDTILE = 5 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "S"
            ElseIf ACTIVETILEROW = 11 Then
                If SELECTEDTILE = 0 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "c"
                If SELECTEDTILE = 1 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "f"
                If SELECTEDTILE = 2 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "i"
                If SELECTEDTILE = 3 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "l"
                If SELECTEDTILE = 4 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "Z"
                If SELECTEDTILE = 5 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "0"
            ElseIf ACTIVETILEROW = 13 Then
                If SELECTEDTILE = 0 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
                If SELECTEDTILE = 1 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
                If SELECTEDTILE = 2 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
                If SELECTEDTILE = 3 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "^"
                If SELECTEDTILE = 4 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
                If SELECTEDTILE = 5 Then MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
            ElseIf ACTIVETILEROW >= 28 Then
                MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "0"
            Else
                MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = "1"
            End If
        End If
        
        If mblnRMouseButton Then
            RT.Left = 5 * 32
            RT.Right = RT.Left + 32
            RT.Top = 11 * 32 - 32
            RT.Bottom = RT.Top + 32
            DDS_MAP.BltFast tmpX + EditPosX, tmpY + EditPosY - 64, DDS_MAPTILES, RT, DDBLTFAST_WAIT
            DDS_COLLISIONMAP.BltFast tmpX + EditPosX, tmpY + EditPosY - 64, DDS_COLTILES, RT, DDBLTFAST_WAIT
            MAP(CInt((tmpX + EditPosX) / 32), CInt((tmpY + EditPosY - 64) / 32)) = " "
        End If
        
    Else
        DrawCrosshair
    End If

End Sub

Public Sub SAVEMAP(tMapName As String, tMapCreator, tMapWidth As Long, tMapHeight As Long)

Dim fn As Integer
fn = FreeFile
Dim tstr As String

Open App.Path & "\maps\" & tMapName For Output As fn
    '--------------------------------------------------.
    'Take the first line of file and store in mapname. |
    '--------------------------------------------------'
        tstr = MapName
    Print #fn, tstr
    '---------------------------------------------------.
    'Take the second line of file and store in creator. |
    '---------------------------------------------------'
        tstr = tMapCreator
    Print #fn, tstr
        
    '--------------------------------------------------------.
    'Take the third/forth line of file and store in mapskin. |
    '--------------------------------------------------------'
        tstr = tMapName & ".bmp"
    Print #fn, tstr

        If GAMEMODE = MULTIPLAY_CTF Then
            tstr = "1"
        ElseIf GAMEMODE = MULTIPLAY_FFA Then
            tstr = "2"
        ElseIf GAMEMODE = STORYMODE Then
            tstr = "99"
        Else
            tstr = "2"
        End If
    Print #fn, tstr
    
    Print #fn, "0"

    '------------------------------------------------.
    'Take the fifth line of file and store in width. |
    '------------------------------------------------'
        tstr = CStr(tMapWidth)
    Print #fn, tstr
        
    '-------------------------------------------------.
    'Take the sixth line of file and store in height. |
    '-------------------------------------------------'
        tstr = CStr(tMapHeight)
    Print #fn, tstr
    
    tInt = 0
    
Do Until tInt >= tMapHeight
    
    tstr = ""
    Dim a As Integer
    For a = 0 To tMapWidth - 1
        tstr = tstr & MAP(a, tInt)
    Next a
    
    Print #fn, tstr
    
    tInt = tInt + 1
    
Loop
Close

SAVEMAPSURFACE tMapName, tMapWidth, tMapHeight

End Sub

Public Sub SAVEMAPSURFACE(tMapName As String, tMapWidth As Long, tMapHeight As Long)

    Set frmSaveMap.Picture = Nothing
    Set frmSaveMap.tmpSaveCol.Picture = Nothing
    Set frmSaveMap.tmpSaveMap.Picture = Nothing
    
    Dim r As RECT, r2 As RECT
    r.Left = 0
    r.Right = tMapWidth * 32
    r.Top = 0
    r.Bottom = tMapHeight * 32
    r2.Left = 0
    r2.Right = tMapWidth * 32
    r2.Top = 0
    r2.Bottom = tMapHeight * 32
    
    frmSaveMap.tmpSaveMap.Width = tMapWidth * 32
    frmSaveMap.tmpSaveMap.Height = tMapHeight * 32
    frmSaveMap.tmpSaveCol.Width = tMapWidth * 32
    frmSaveMap.tmpSaveCol.Height = tMapHeight * 32
    
    Dim a As Integer, b As Integer, RtO As RECT
    For a = 0 To tMapWidth - 1
        For b = 0 To tMapHeight - 1
            If Not MAP(a, b) = "1" And Not MAP(a, b) = "J" _
            And Not MAP(a, b) = "^" And Not MAP(a, b) = "0" Then
                RtO.Left = a * 32: RtO.Right = RtO.Left + 32
                RtO.Top = b * 32: RtO.Bottom = RtO.Top + 32
                DDS_MAP.BltColorFill RtO, RGB(0, 0, 0)
            End If
        Next b
    Next a
        
    DDS_MAP.BltToDC frmSaveMap.tmpSaveMap.hDC, r, r2
    DDS_COLLISIONMAP.BltToDC frmSaveMap.tmpSaveCol.hDC, r, r2
    SavePicture frmSaveMap.tmpSaveMap.Image, App.Path & "\maps\" & tMapName & ".bmp"
    SavePicture frmSaveMap.tmpSaveCol.Image, App.Path & "\maps\" & tMapName & ".bmp.col.bmp"
    
    cCmdFeed "MAP SAVED TO \MAPS\" & tMapName, True
    
    Dim RTIM As RECT
    For a = 0 To tMapWidth - 1
        For b = 0 To tMapHeight - 1
        
            If MAP(a, b) = "J" Then
                RTIM.Left = 0: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 224: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "^" Then
                RTIM.Left = 160: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 224: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "y" Then
                RTIM.Left = 128: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "x" Then
                RTIM.Left = 128: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "Z" Then
                RTIM.Left = 128: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "a" Then
                RTIM.Left = 0: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "b" Then
                RTIM.Left = 0: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "c" Then
                RTIM.Left = 0: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "d" Then
                RTIM.Left = 32: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "e" Then
                RTIM.Left = 32: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "f" Then
                RTIM.Left = 32: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "g" Then
                RTIM.Left = 64: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "h" Then
                RTIM.Left = 64: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "i" Then
                RTIM.Left = 64: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "j" Then
                RTIM.Left = 96: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "k" Then
                RTIM.Left = 96: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "l" Then
                RTIM.Left = 96: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "s" Then
                RTIM.Left = 160: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
            ElseIf MAP(a, b) = "S" Then
                RTIM.Left = 160: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
            Else
                RTIM.Left = 160: RTIM.Right = RTIM.Left + 32
                RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
            End If
            
            If Not MAP(a, b) = "1" And Not MAP(a, b) = " " Then
                DDS_MAP.BltFast a * 32, b * 32, DDS_MAPTILES, RTIM, DDBLTFAST_WAIT
            End If
        
        Next b
    Next a
    
    LOADQUICKPREVIEW
    TMPGUIDE = True

End Sub


Public Sub DRAWTILESET(tRow As Integer)

    Dim r As RECT, r2 As RECT
    'What
    r.Left = 0
    r.Right = r.Left + 192
    r.Top = tRow * 32 - 32
    r.Bottom = r.Top + 32
    
    'Where
    r2.Left = 0
    r2.Right = r2.Left + 192
    r2.Top = 20
    r2.Bottom = r2.Top + 32
    
    DDS_Back.Blt r2, DDS_MAPTILES, r, DDBLT_KEYSRC
    
    DDS_Back.SetForeColor RGB(0, 255, 0)
    DDS_Back.DrawBox SELECTEDTILE * 32, 20, (SELECTEDTILE * 32) + 32, 52

End Sub

Public Sub DRAWTILEPREV(tX As Long, tY As Long)

    Dim r As RECT, r2 As RECT
    'What
    r.Left = SELECTEDTILE * 32
    r.Right = r.Left + 32
    r.Top = ACTIVETILEROW * 32 - 32
    r.Bottom = r.Top + 32
    
    'Where
    r2.Left = tX
    r2.Right = r2.Left + 32
    r2.Top = tY
    r2.Bottom = r2.Top + 32
        
    If r2.Left <= 0 Then r2.Left = 0
    If r2.Right >= 320 Then r2.Right = 320
    If r2.Top <= 0 Then r2.Top = 0
    If r2.Bottom >= 240 Then r2.Bottom = 240
    
    DDS_Back.Blt r2, DDS_MAPTILES, r, DDBLT_WAIT
    DDS_Back.SetForeColor RGB(255, 255, 255)
    DDS_Back.DrawBox tX, tY, tX + 32, tY + 32
    

End Sub

Public Sub CREATEMAPSURFACE(tMapName As String, tMapWidth As Integer, tMapHeight As Integer)

    ReDim MAP(0 To tMapWidth, 0 To tMapHeight)
    
    Dim i As Long, k As Long
    For i = 0 To tMapWidth
        For k = 0 To tMapHeight
            MAP(i, k) = " "
        Next k
    Next i

    Dim ddckey As DDCOLORKEY
    
    Dim tmpr As RECT
    tmpr.Left = 0
    tmpr.Right = tMapWidth * 32
    tmpr.Top = 0
    tmpr.Bottom = tMapHeight * 32
    rTOTMAP.Left = 0: rTOTMAP.Right = MapWidth * 32
    rTOTMAP.Top = 0: rTOTMAP.Bottom = MapHeight * 32
    
    Set DDS_MAP = Nothing

    'Now let's set the surface description
    DDSD_MAP.lFlags = DDSD_CAPS Or DDSD_WIDTH Or DDSD_HEIGHT
    DDSD_MAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    DDSD_MAP.lWidth = tMapWidth * 32
    DDSD_MAP.lHeight = tMapHeight * 32
    'now create the other off-screen surface
    Set DDS_MAP = DD.CreateSurface(DDSD_MAP)
    
    ddckey.low = 0: ddckey.high = 0
    DDS_MAP.SetColorKey DDCKEY_SRCBLT, ddckey
    
    DDS_MAP.BltColorFill tmpr, RGB(128, 0, 64)
    DDS_MAP.SetForeColor RGB(255, 255, 255)
    DDS_MAP.DrawBox 0, 0, tMapWidth * 32, tMapHeight * 32
    
    '---------------.
    'COLLISION MAP! |
    '---------------'

    Set DDS_COLLISIONMAP = Nothing

    'Now let's set the surface description
    DDSD_COLLISIONMAP.lFlags = DDSD_CAPS Or DDSD_WIDTH Or DDSD_HEIGHT
    DDSD_COLLISIONMAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    DDSD_COLLISIONMAP.lWidth = tMapWidth * 32
    DDSD_COLLISIONMAP.lHeight = tMapHeight * 32
    'now create the other off-screen surface

    Set DDS_COLLISIONMAP = DD.CreateSurface(DDSD_COLLISIONMAP)
    ddckey.low = 0: ddckey.high = 0
    DDS_COLLISIONMAP.SetColorKey DDCKEY_SRCBLT, ddckey
    
    DDS_COLLISIONMAP.BltColorFill tmpr, RGB(0, 0, 0)
    DDS_MAP.SetForeColor RGB(255, 255, 255)
    DDS_MAP.DrawBox 0, 0, tMapWidth * 32, tMapHeight * 32

    MAPSCreated = True
    CreateGuidemapSurface

End Sub

Public Sub LOADMAPSURFACE(tMapName As String)

If (Dir(App.Path & "\maps\" & tMapName) = "") Then GoTo NOTFOUND

Dim q As Long, w As Long, e As Integer, t As Integer, t2 As Integer

'-----------------------------------------.
'Dim some temporary strings and integers. |
'-----------------------------------------'
Dim tstr As String, tInt As Integer, z As Integer

'--------------.
'Open the map. |
'--------------'
Open App.Path & "\maps\" & tMapName For Input As 1

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
         
    
    
    ReDim MAP(0 To MapWidth, 0 To MapHeight)
    
    Dim a As Integer, b As Integer
    For a = 0 To MapWidth
        For b = 0 To MapHeight
            MAP(a, b) = " "
        Next b
    Next a

    Dim ddckey As DDCOLORKEY
    
    Dim tmpr As RECT
    tmpr.Left = 0
    tmpr.Right = MapWidth * 32
    tmpr.Top = 0
    tmpr.Bottom = MapHeight * 32
    rTOTMAP.Left = 0: rTOTMAP.Right = MapWidth * 32
    rTOTMAP.Top = 0: rTOTMAP.Bottom = MapHeight * 32
    
    Set DDS_MAP = Nothing

    'Now let's set the surface description
    DDSD_MAP.lFlags = DDSD_CAPS Or DDSD_WIDTH Or DDSD_HEIGHT
    DDSD_MAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    DDSD_MAP.lWidth = MapWidth * 32
    DDSD_MAP.lHeight = MapHeight * 32
    'now create the other off-screen surface
    Set DDS_MAP = DD.CreateSurfaceFromFile(App.Path & "\maps\" & tMapName & ".bmp", DDSD_MAP)
    
    ddckey.low = 0: ddckey.high = 0
    DDS_MAP.SetColorKey DDCKEY_SRCBLT, ddckey
    
    '---------------.
    'COLLISION MAP! |
    '---------------'

    Set DDS_COLLISIONMAP = Nothing

    'Now let's set the surface description
    DDSD_COLLISIONMAP.lFlags = DDSD_CAPS Or DDSD_WIDTH Or DDSD_HEIGHT
    DDSD_COLLISIONMAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    DDSD_COLLISIONMAP.lWidth = MapWidth * 32
    DDSD_COLLISIONMAP.lHeight = MapHeight * 32
    'now create the other off-screen surface

    Set DDS_COLLISIONMAP = DD.CreateSurfaceFromFile(App.Path & "\maps\" & tMapName & ".bmp.col.bmp", DDSD_COLLISIONMAP)
    ddckey.low = 0: ddckey.high = 0
    DDS_COLLISIONMAP.SetColorKey DDCKEY_SRCBLT, ddckey
    
    CreateGuidemapSurface

tInt = 0

Do Until EOF(1)
    
    Line Input #1, tstr
    
    Dim i As Integer, RTIM As RECT
    For i = 0 To Len(tstr) - 1
        
        MAP(i, tInt) = Mid(tstr, i + 1, 1)
        If MAP(i, tInt) = "J" Then
            RTIM.Left = 0: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 224: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "^" Then
            RTIM.Left = 160: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 224: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "y" Then
            RTIM.Left = 128: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "x" Then
            RTIM.Left = 128: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "Z" Then
            RTIM.Left = 128: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "a" Then
            RTIM.Left = 0: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "b" Then
            RTIM.Left = 0: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "c" Then
            RTIM.Left = 0: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "d" Then
            RTIM.Left = 32: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "e" Then
            RTIM.Left = 32: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "f" Then
            RTIM.Left = 32: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "g" Then
            RTIM.Left = 64: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "h" Then
            RTIM.Left = 64: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "i" Then
            RTIM.Left = 64: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "j" Then
            RTIM.Left = 96: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "k" Then
            RTIM.Left = 96: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "l" Then
            RTIM.Left = 96: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "s" Then
            RTIM.Left = 160: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 256: RTIM.Bottom = RTIM.Top + 32
        ElseIf MAP(i, tInt) = "S" Then
            RTIM.Left = 160: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 288: RTIM.Bottom = RTIM.Top + 32
        Else
            RTIM.Left = 160: RTIM.Right = RTIM.Left + 32
            RTIM.Top = 320: RTIM.Bottom = RTIM.Top + 32
        End If
        
        If Not MAP(i, tInt) = "1" And Not MAP(i, tInt) = " " And Not MAP(i, tInt) = "0" Then
            DDS_MAP.BltFast i * 32, tInt * 32, DDS_MAPTILES, RTIM, DDBLTFAST_WAIT
        End If
        
    Next i
    tInt = tInt + 1
    
Loop
Close


    MAPSCreated = True
    LOADQUICKPREVIEW
    TMPGUIDE = True
    LOADMAPFLAG = False
    Exit Sub

    
NOTFOUND:
           
    cCmdFeed "COULD NOT FIND MAP " & Filename, True
    MAPSCreated = False
    LOADMAPFLAG = False
    
    Exit Sub

End Sub

Public Sub DRAWEDITEDMAP()

'--------------------------------------------------.
'This procedure draws the map onto the backbuffer. |
'--------------------------------------------------'

    '-----------------------------------------.
    'Some necessary variables and rectangles. |
    '-----------------------------------------'
    Dim r As RECT
    
    '----------------------------.
    'Where the heck will it go?! |
    '----------------------------'
    r.Left = 0
    r.Top = 64
    r.Right = 320
    r.Bottom = 224
        
    '--------------.
    'What to grab. |
    '--------------'
    rMAPCUT.Left = EditPosX
    rMAPCUT.Top = EditPosY
    rMAPCUT.Right = EditPosX + 320
    rMAPCUT.Bottom = EditPosY + 160
    
    If rMAPCUT.Bottom > (MapHeight * 32) Then
        rMAPCUT.Bottom = (MapHeight * 32)
        rMAPCUT.Top = rMAPCUT.Bottom - 160
    End If
    If rMAPCUT.Right > (MapWidth * 32) Then
        rMAPCUT.Right = (MapWidth * 32)
        rMAPCUT.Left = rMAPCUT.Right - 320
    End If
    If rMAPCUT.Left < 0 Then
        rMAPCUT.Left = 0
        rMAPCUT.Right = rMAPCUT.Left + 320
    End If
    If rMAPCUT.Top < 0 Then
        rMAPCUT.Top = 0
        rMAPCUT.Bottom = rMAPCUT.Top + 160
    End If
    
    '-------.
    'Paint. |
    '-------'
    DDS_Back.Blt r, DDS_MAP, rMAPCUT, DDBLT_KEYSRC

End Sub
