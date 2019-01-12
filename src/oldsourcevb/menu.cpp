/*Attribute VB_Name = "mod_Menu"
'This is a menu control system. It works by letting different menus be visible.
'Only one menu can be visible at once. This is not 100% flexible, but it gets
'the work done. For example, you have to rewrite the submenu codes for each menu,
'if you use a layout like me. If you only have one screen for each menu, it will
'work like a charm with a little tweak. My first system was like that, but now
'I just reused this system for my new one, and it works.
*/

//'Every menu must have a unique enum.
typedef enum{
  MNUMain 0
  MNUInstructions 1
  MNUMultiplayer 2
  MNUMultiplayerStart = 3
  MNUMultiplayerJoin = 4
  MNULobby = 5
  MNUOptions = 6
  MNUSoundSettings = 7
  MNUSelectCrosshair = 8
  MNUEditName = 9
  MNUEditTeamName = 10
  MNUSelectMap = 11
  MNUTitleScreen = 96
  MNULoad = 97
  MNUStory = 98
  MNUIntro = 99
  MNUCredits = 100
  MNUMapEditor = 101
  MNUQuit = 102
  MNUAimPoint = 103
  MNUSelectedMusic = 104
  MNUSelectedSound = 105
  MNUSelectedGameTune = 106
  MNUGameOver = 333
}enum_visible_menu;

/*'Create a type to use with the menu system,
'this will hold the different menus that can
'be visible.*/
typedef struct{
  enum_visible_menu Visible_Menu;
}Menu_Settings;

/*'This is for the keyboard control of the menu.
'Later I will skipp the mouse naviagation,
'and also skip the mouse usage ingame.*/
enum_visible_menu Selected_Menu;

/*'Construct a MENU. class that holds the type above
'as controls. You can add more controls if you like
'to use with the menu, but this works fine for me.
'For example I could have used this to store the tmpValue
'used for text output in the menu, as MENU.tmpValue*/
Menu_Settings Menu;

/*'Create the type for the intro text lines.
'This holds the TEXT, X and Y coordinates,
'font used, and a temporary color.
'The color is used for fading from black to white and
'than back again.
'MoveFactor is if you want the text to move,
'this is used with the credit system, which works
'exactly like this one.
'iFix is just a boolean for something I've forgotten.*/

typedef struct{ 
  char Text[32];
  unsigned int Y_Pos;
  unsigned int X_Pos;
  char Font;
  char Color[3];
  float Move_Factor;
  bool iFix;
}ActCoreIntroText;
ActCoreIntroText Intro_Line[32];

/*'A Variable to load from the configuration file,
'if the player wants to skip the introduction,
'he can write this in his cfg.*/
bool Show_Intro;

/*'The switch for showing that you can press any key
'to continue, after the intro is completed.*/
Dim IntroShowPressText As Boolean

'This is a variable to store which line is currently
'on display.
Dim CurrentLine As Integer

'Store maximum number of lines used.
Dim MaxLines As Integer

'This is to prevent to rapid clicks in the menu system,
'for use with the clickfix timer.
Public mnuClickFix As Integer

'To store which page is showing in the instructions box.
'This could also been stored in the MENU system as ex MENU.INSTRUCTIONPAGE
Public InstructionsPage As Integer

'To be able to show this menu ingame.
Public OverlayMenu As Boolean


   
    
    
    
    
    
    
    
    
    
    
    

'Time to load all grafics used in the menu system.

Public Sub LoadMenuGFX()

    LoadSurfaces

    'on local error GoTo ERRORHANDLER
    
    'Set transparent key to pure black.
    Dim ddckey As DDCOLORKEY
    ddckey.low = 0: ddckey.high = 0
    
    
    
    
    
    'Load new menu buttons and graphics.
    
    '  HEADER
    
    'Now let's set the surface description
    DDSD_MENUHEADER.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUHEADER.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUHEADER.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_MENUHEADER = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\header.bmp", DDSD_MENUHEADER)
    DDS_MENUHEADER.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    'Now let's set the surface description
    
    '  MAIN BUTTONS
    
    DDSD_MENUBUTTONS_0_0.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUBUTTONS_0_0.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUBUTTONS_0_0.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_MENUBUTTONS_0_0 = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\buttons0-0.bmp", DDSD_MENUBUTTONS_0_0)
    DDS_MENUBUTTONS_0_0.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    '  MULTIPLAYERBUTTONS
    
    'Now let's set the surface description
    DDSD_MENUBUTTONS_1_1.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUBUTTONS_1_1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUBUTTONS_1_1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_MENUBUTTONS_1_1 = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\buttons1-1.bmp", DDSD_MENUBUTTONS_1_1)
    DDS_MENUBUTTONS_1_1.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    '  OPTIONS BUTTONS
    
    'Now let's set the surface description
    DDSD_MENUBUTTONS_2_1.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUBUTTONS_2_1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUBUTTONS_2_1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_MENUBUTTONS_2_1 = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\buttons2-1.bmp", DDSD_MENUBUTTONS_2_1)
    DDS_MENUBUTTONS_2_1.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    '  GO BUTTON (FOR MULTIPLAYER SECTION)
    
    'Now let's set the surface description
    DDSD_MENUBUTTON_GO.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUBUTTON_GO.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUBUTTON_GO.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_MENUBUTTON_GO = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\buttonsgo.bmp", DDSD_MENUBUTTON_GO)
    DDS_MENUBUTTON_GO.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    '  PLAYERNAME BOX
    
    'Now let's set the surface description
    DDSD_MENUPLAYERNAME.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUPLAYERNAME.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUPLAYERNAME.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_MENUPLAYERNAME = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\playername.bmp", DDSD_MENUPLAYERNAME)
    DDS_MENUPLAYERNAME.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    '  SPACER LINES
    
    DDSD_MENULINES_1_1.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENULINES_1_1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENULINES_1_1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENULINES_1_1 = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\lines1-1.bmp", DDSD_MENULINES_1_1)
    DDS_MENULINES_1_1.SetColorKey DDCKEY_SRCBLT, ddckey
    
    DDSD_MENULINES_2_1.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENULINES_2_1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENULINES_2_1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENULINES_2_1 = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\lines2-1.bmp", DDSD_MENULINES_2_1)
    DDS_MENULINES_2_1.SetColorKey DDCKEY_SRCBLT, ddckey
    
    DDSD_MENULINES_STRAIGHT.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENULINES_STRAIGHT.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENULINES_STRAIGHT.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENULINES_STRAIGHT = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\lines-straight.bmp", DDSD_MENULINES_STRAIGHT)
    DDS_MENULINES_STRAIGHT.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    '  TEAM NAME BOX
    
    DDSD_MENUTEAMNAME.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUTEAMNAME.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUTEAMNAME.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENUTEAMNAME = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\teamname.bmp", DDSD_MENUTEAMNAME)
    DDS_MENUTEAMNAME.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    '  SOUND SETTINGS BOX
    
    DDSD_MENUSOUNDSETTINGS.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUSOUNDSETTINGS.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUSOUNDSETTINGS.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENUSOUNDSETTINGS = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\soundsettings.bmp", DDSD_MENUSOUNDSETTINGS)
    DDS_MENUSOUNDSETTINGS.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    '  INSTRUCTIONS BOX
    
    DDSD_MENUINSTRUCTIONBOX.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUINSTRUCTIONBOX.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUINSTRUCTIONBOX.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENUINSTRUCTIONBOX = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\instructions.bmp", DDSD_MENUINSTRUCTIONBOX)
    DDS_MENUINSTRUCTIONBOX.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    
    
    '  SERVER NAME BOX
    
    DDSD_MENUSERVERNAME.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUSERVERNAME.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUSERVERNAME.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENUSERVERNAME = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\servername.bmp", DDSD_MENUSERVERNAME)
    DDS_MENUSERVERNAME.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    
    '  JOIN IP BOX
    
    DDSD_MENUJOINIP.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUJOINIP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUJOINIP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENUJOINIP = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\joinip.bmp", DDSD_MENUJOINIP)
    DDS_MENUJOINIP.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    
    
    
    '  AIM OPTIONS BUTTON
    
    DDSD_MENUAIM.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MENUAIM.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MENUAIM.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MENUAIM = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\menuaim.bmp", DDSD_MENUAIM)
    DDS_MENUAIM.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    
    
    '  AIM SETTINGS BOX
    
    DDSD_AIMBOX.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_AIMBOX.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_AIMBOX.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_AIMBOX = DD.CreateSurfaceFromFile(App.Path & "\gfx\menu\aimbox.bmp", DDSD_AIMBOX)
    DDS_AIMBOX.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
        DDSD_MAP2.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MAP2.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MAP2.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    Set DDS_MAP2 = DD.CreateSurfaceFromFile(App.Path & "\gfx\bgtest.bmp", DDSD_MAP2)
    ddckey.low = 0: ddckey.high = 0
    DDS_MAP2.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    
    
    
    
    
    'Set Rectangle Definitions
    'This tells us where to cut from in the bitmap,
    'thus defines which part to use from the surface.
    'Smart way to store many things in one surface and
    'free up memory. Also used for animations.
    
    rStartGame.Left = 0: rStartGame.Right = 79: rStartGame.Top = 0: rStartGame.Bottom = 16
    rViewIntro.Left = 0: rViewIntro.Right = 79: rViewIntro.Top = 16: rViewIntro.Bottom = rViewIntro.Top + 16
    rOptions.Left = 0: rOptions.Right = 79: rOptions.Top = 32: rOptions.Bottom = rOptions.Top + 16
    rInstructions.Left = 0: rInstructions.Right = 79: rInstructions.Top = 48: rInstructions.Bottom = rInstructions.Top + 16
    rCredits.Left = 0: rCredits.Right = 79: rCredits.Top = 64: rCredits.Bottom = rCredits.Top + 16
    rQuit.Left = 0: rQuit.Right = 79: rQuit.Top = 80: rQuit.Bottom = 96
        
    rStartGameOver.Left = 79: rStartGameOver.Right = 158: rStartGameOver.Top = 0: rStartGameOver.Bottom = 16
    rViewIntroOver.Left = 79: rViewIntroOver.Right = 158: rViewIntroOver.Top = 16: rViewIntroOver.Bottom = rViewIntroOver.Top + 16
    rOptionsOver.Left = 79: rOptionsOver.Right = 158: rOptionsOver.Top = 32: rOptionsOver.Bottom = rOptionsOver.Top + 16
    rInstructionsOver.Left = 79: rInstructionsOver.Right = 158: rInstructionsOver.Top = 48: rInstructionsOver.Bottom = rInstructionsOver.Top + 16
    rCreditsOver.Left = 79: rCreditsOver.Right = 158: rCreditsOver.Top = 64: rCreditsOver.Bottom = rCreditsOver.Top + 16
    rQuitOver.Left = 79: rQuitOver.Right = 158: rQuitOver.Top = 80: rQuitOver.Bottom = 96
    
    rHost.Left = 0: rHost.Right = 33: rHost.Top = 0: rHost.Bottom = 16
    rJoin.Left = 0: rJoin.Right = 33: rJoin.Top = 16: rJoin.Bottom = 32
    
    rHostOver.Left = 33: rHostOver.Right = 66: rHostOver.Top = 0: rHostOver.Bottom = 16
    rJoinOver.Left = 33: rJoinOver.Right = 66: rJoinOver.Top = 16: rJoinOver.Bottom = 32
    
    rName.Left = 0: rName.Right = 40: rName.Top = 0: rName.Bottom = 16
    rTeam.Left = 0: rTeam.Right = 40: rTeam.Top = 16: rTeam.Bottom = 32
    rSound.Left = 0: rSound.Right = 40: rSound.Top = 32: rSound.Bottom = 48
    
    rNameOver.Left = 40: rNameOver.Right = 80: rNameOver.Top = 0: rNameOver.Bottom = 16
    rTeamOver.Left = 40: rTeamOver.Right = 80: rTeamOver.Top = 16: rTeamOver.Bottom = 32
    rSoundOver.Left = 40: rSoundOver.Right = 80: rSoundOver.Top = 32: rSoundOver.Bottom = 48
    
    rPlayerName.Left = 0: rPlayerName.Right = 106: rPlayerName.Top = 0: rPlayerName.Bottom = 26
    rTeamName.Left = 0: rTeamName.Right = 106: rTeamName.Top = 0: rTeamName.Bottom = 26
    
    rLines1_1.Left = 0: rLines1_1.Right = 16: rLines1_1.Top = 0: rLines1_1.Bottom = 34
    rLines2_1.Left = 0: rLines2_1.Right = 16: rLines2_1.Top = 0: rLines2_1.Bottom = 64
    
    rSoundSettings.Left = 0: rSoundSettings.Right = 114: rSoundSettings.Top = 0: rSoundSettings.Bottom = 36
    rSoundSettingsSelMusOver.Left = 114: rSoundSettingsSelMusOver.Right = 228: rSoundSettingsSelMusOver.Top = 0: rSoundSettingsSelMusOver.Bottom = 36
    rSoundSettingsSFXOver.Left = 114: rSoundSettingsSFXOver.Right = 228: rSoundSettingsSFXOver.Top = 36: rSoundSettingsSFXOver.Bottom = 72
    rSoundSettingsMusicOver.Left = 0: rSoundSettingsMusicOver.Right = 114: rSoundSettingsMusicOver.Top = 36: rSoundSettingsMusicOver.Bottom = 72
    
    rInstructionsBox.Left = 0: rInstructionsBox.Right = 204: rInstructionsBox.Top = 0: rInstructionsBox.Bottom = 138
    
    rServerName.Left = 0: rServerName.Right = 104: rServerName.Top = 0: rServerName.Bottom = 26
    
    rJoinIp.Left = 0: rJoinIp.Right = 132: rJoinIp.Top = 0: rJoinIp.Bottom = 26
    
    rAim.Left = 0: rAim.Right = 40: rAim.Top = 0: rAim.Bottom = 16
    rAimOver.Left = 40: rAimOver.Right = 80: rAimOver.Top = 0: rAimOver.Bottom = 16
    
    rAimBox.Left = 0: rAimBox.Right = 106: rAimBox.Top = 0: rAimBox.Bottom = 36
    

    
    
    
    
    
    
    
    
    'Now let's set the surface description
    DDSD_LOBBY.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_LOBBY.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_LOBBY.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_LOBBY = DD.CreateSurfaceFromFile(App.Path & "\gfx\lobby\main.bmp", DDSD_LOBBY)
    DDS_LOBBY.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    
    
    Dim p As Integer
    For p = 1 To UBound(DDSD_Charmap)
    
        'Now let's set the surface description
        DDSD_Charmap(p).lFlags = DDSD_CAPS
        If UseVideoMem Then
            DDSD_Charmap(p).ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
        Else
            DDSD_Charmap(p).ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
        End If
        'now create the other off-screen surface
        Set DDS_Charmap(p) = DD.CreateSurfaceFromFile(App.Path & "\gfx\charmap\" & p & ".bmp", DDSD_Charmap(p))
        DDS_Charmap(p).SetColorKey DDCKEY_SRCBLT, ddckey
        
    Next p
    





    'Now let's set the surface description
    DDSD_Crosshair.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_Crosshair.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_Crosshair.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_Crosshair = DD.CreateSurfaceFromFile(App.Path & "\gfx\hud\crosshairs.bmp", DDSD_Crosshair)
    DDS_Crosshair.SetColorKey DDCKEY_SRCBLT, ddckey
    
    'Now let's set the surface description
    DDSD_Console.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_Console.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_Console.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_Console = DD.CreateSurfaceFromFile(App.Path & "\gfx\hud\console.bmp", DDSD_Console)
    DDS_Console.SetColorKey DDCKEY_SRCBLT, ddckey
    
    'Now let's set the surface description
    DDSD_ConsoleBuffer.lFlags = DDSD_CAPS Or DDSD_WIDTH Or DDSD_HEIGHT
    If UseVideoMem Then
        DDSD_ConsoleBuffer.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_ConsoleBuffer.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    DDSD_ConsoleBuffer.lWidth = 320
    DDSD_ConsoleBuffer.lHeight = 160
    'now create the other off-screen surface
    Set DDS_ConsoleBuffer = DD.CreateSurface(DDSD_ConsoleBuffer)
    DDS_ConsoleBuffer.SetColorKey DDCKEY_SRCBLT, ddckey
    
    Exit Sub
    
ERRORHANDLER:
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: LOADING MENU GRAPHICS"
    ShutdownNoErrorFlag = False: Shutdown
    
End Sub

Public Sub RenderMenuLoop()

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
    
        FirstTime = timeGetTime
    
        '-------------------------.
        'Draw current menu screen |
        '-------------------------'
        CheckMouse
        DrawMenuFrame
        
        '----------------------------------.
        'Flip the double buffered surfaces |
        'This is where the magic happens!  |
        '----------------------------------'
                                
        If SMode = 0 Then   'Windowed mode
            DDS_Back.SetForeColor RGB(32, 32, 32)
            'DDS_Back.DrawBox 0, 0, 320, 240
            DX.GetWindowRect frmMain.hwnd, r2
            r2.Top = r2.Top
            r2.Bottom = r2.Top + WindowedResY
            
            DDS_Primary.Blt r2, DDS_Back, r, DDBLTFAST_NOCOLORKEY + DDBLT_WAIT
            
        Else   'Full-Screen
        
            DDS_Primary.Flip Nothing, DDFLIP_WAIT

        End If
    
    '-----------------------------.
    'Now we make time for windows |
    'to do other things           |
    '-----------------------------'
    
        Do Until timeGetTime >= FirstTime + 8
        Loop
        FPS = (1000 / (timeGetTime - FirstTime))
    
        DoEvents
    
    '--------------------------.
    'Loop until we say stop ;) |
    '--------------------------'
    
    Loop Until bQuit2
    
    If gSTARTED Then
        Renderloop
    Else
    
        '-------------------.
        'Shutdown Procedure |
        '-------------------'
    
        ShutdownNoErrorFlag = True
        Shutdown
    
    End If
    
    Exit Sub
    
Shutdowner:
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: MENU RENDERLOOP"
    ShutdownNoErrorFlag = False: Shutdown
    
End Sub
















Public Sub DrawMenuFrame()

'on local error GoTo Shutdowner
        
    Dim mbltfx As DDBLTFX
            
    '----------------------------.
    'Colour the background black |
    '----------------------------'
    DDS_Back.BltColorFill r, RGB(0, 0, 0)
        
    If Starfield.ON Then
        StarPhysics
        DrawStars
    End If
           
    If MENU.VisibleMenu = MNUCredits Then
        DrawCredit
    ElseIf MENU.VisibleMenu = MNUIntro Then
        DrawActCoreIntro
    ElseIf MENU.VisibleMenu = MNUStory Then
        DrawStory
    ElseIf MENU.VisibleMenu = MNUTitleScreen Then
        DrawMenu
    ElseIf MENU.VisibleMenu = MNUGameOver Then
        DrawMenu
    Else
        DrawMenu
        AnimateCrosshair
    End If
    
    If MENU.VisibleMenu <> MNUCredits Then
        If MENU.VisibleMenu <> MNUIntro Then
            If MENU.VisibleMenu <> MNUStory Then
                If MENU.VisibleMenu <> MNULobby Then
                    If MENU.VisibleMenu <> MNUTitleScreen Then
                        If MENU.VisibleMenu <> MNUGameOver Then
                            Dim rHeader As RECT
                            rHeader.Left = 0: rHeader.Right = 312: rHeader.Top = 0: rHeader.Bottom = 16
                            DDS_Back.BltFast 4, 4, DDS_MENUHEADER, rHeader, DDBLTFAST_SRCCOLORKEY
                        End If
                    End If
                End If
            End If
        End If
    End If
        
    If cEnabled Then
        cDrawConsole
    End If

    Exit Sub
    
Shutdowner:
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: DRAWING MENU FRAME"
    ShutdownNoErrorFlag = False: Shutdown
    
End Sub

Public Function SwitchMenu(toMenu As VISIBLEMNU, Optional GameOverCreds As Boolean = False) As Boolean

    PlaySample "menu\select.mp3"
    
    If toMenu = MNUCredits Then
        Credits_INIT
        If Not GameOverCreds Then StartGameMusic CREDTIS
        MENU.VisibleMenu = MNUCredits
        SwitchMenu = True
    ElseIf toMenu = MNUEditName Then
        MENU.VisibleMenu = MNUEditName
        SwitchMenu = True
    ElseIf toMenu = MNUEditTeamName Then
        MENU.VisibleMenu = MNUEditTeamName
        SwitchMenu = True
    ElseIf toMenu = MNUInstructions Then
        MENU.VisibleMenu = MNUInstructions
        SwitchMenu = True
    ElseIf toMenu = MNUIntro Then
        Intro_INIT
        StartGameMusic INTRO
        MENU.VisibleMenu = MNUIntro
        SwitchMenu = True
    ElseIf toMenu = MNULoad Then
        MENU.VisibleMenu = MNULoad
        SwitchMenu = True
    ElseIf toMenu = MNULobby Then
        StartGameMusic LOBBY
        MENU.VisibleMenu = MNULobby
        SwitchMenu = True
    ElseIf toMenu = MNUMain Then
        MENU.VisibleMenu = MNUMain
        SwitchMenu = True
    ElseIf toMenu = MNUMultiplayer Then
        MENU.VisibleMenu = MNUMultiplayer
        SwitchMenu = True
    ElseIf toMenu = MNUMultiplayerJoin Then
        MENU.VisibleMenu = MNUMultiplayerJoin
        SwitchMenu = True
    ElseIf toMenu = MNUMultiplayerStart Then
        MENU.VisibleMenu = MNUMultiplayerStart
        SwitchMenu = True
    ElseIf toMenu = MNUOptions Then
        MENU.VisibleMenu = MNUOptions
        SwitchMenu = True
    ElseIf toMenu = MNUSelectCrosshair Then
        MENU.VisibleMenu = MNUSelectCrosshair
        SwitchMenu = True
    ElseIf toMenu = MNUSelectMap Then
        PrevMapIndex = 0
        LOADPREVIEW App.Path & "\maps\" & frmMain.FilecMap.List(PrevMapIndex)
        MENU.VisibleMenu = MNUSelectMap
        SwitchMenu = True
    ElseIf toMenu = MNUSoundSettings Then
        MENU.VisibleMenu = MNUSoundSettings
        SwitchMenu = True
    ElseIf toMenu = MNUStory Then
        StartGameMusic STORY
        MENU.VisibleMenu = MNUStory
        SwitchMenu = True
    ElseIf toMenu = MNUTitleScreen Then
        StartGameMusic TITLESCREEN
        MENU.VisibleMenu = MNUTitleScreen
        SwitchMenu = True
    ElseIf toMenu = MNUMapEditor Then
        InstructionsPage = 0
        INIT_MAPEDITOR
        SwitchMenu = True
    ElseIf toMenu = MNUQuit Then
        bQuit = True
        bQuit2 = True
        SwitchMenu = True
    ElseIf toMenu = MNUAimPoint Then
        MENU.VisibleMenu = MNUSelectCrosshair
        SwitchMenu = True
    Else
        SwitchMenu = False
    End If

End Function















Public Sub DrawMenu()

'on local error GoTo ErrorSender
    
Dim tmpValue2 As String
tmpValue2 = ""


'Draw main menu buttons here. they will always be visible, no matter
'what sub-menu you are in.
If MENU.VisibleMenu <> MNUCredits Then
    If MENU.VisibleMenu <> MNUIntro Then
        If MENU.VisibleMenu <> MNUTitleScreen Then
            If MENU.VisibleMenu <> MNUStory Then
                If MENU.VisibleMenu <> MNUGameOver Then
                    If Not MENU.VisibleMenu = MNUSelectMap And Not MENU.VisibleMenu = MNULobby Then
                        DDS_Back.BltFast 4, 40, DDS_MENUBUTTONS_0_0, rStartGame, DDBLTFAST_SRCCOLORKEY
                        DDS_Back.BltFast 4, 58, DDS_MENUBUTTONS_0_0, rViewIntro, DDBLTFAST_SRCCOLORKEY
                        DDS_Back.BltFast 4, 76, DDS_MENUBUTTONS_0_0, rOptions, DDBLTFAST_SRCCOLORKEY
                        DDS_Back.BltFast 4, 94, DDS_MENUBUTTONS_0_0, rInstructions, DDBLTFAST_SRCCOLORKEY
                        DDS_Back.BltFast 4, 112, DDS_MENUBUTTONS_0_0, rCredits, DDBLTFAST_SRCCOLORKEY
                        DDS_Back.BltFast 4, 220, DDS_MENUBUTTONS_0_0, rQuit, DDBLTFAST_SRCCOLORKEY
                        'DrawText CheckPlayingInfo(False), 84, 8, 0, 2
                    End If
                End If
            End If
        End If
    End If
End If

If Not mLOADING Then

    If MENU.VisibleMenu = MNUIntro Then
    
    ElseIf MENU.VisibleMenu = MNUGameOver Then
        
        DrawText "GAME OVER", 160 - ((Len("GAME OVER") * 8) / 2), 64, 0, 3
        DrawText "YOU SCORED " & CStr(StoryPlayerPoints), 160 - ((Len("YOU SCORED " & CStr(StoryPlayerPoints)) * 8) / 2), 74, 0, 2
        If StoryPlayerPoints > StoryHiScore Then
            DrawText "NEW HISCORE!", 160 - ((Len("NEW HISCORE!") * 8) / 2), 132, 0, 2
            DrawText "ENTER YOUR NAME", 160 - ((Len("ENTER YOUR NAME") * 8) / 2), 142, 0, 2
            DrawText CHARACTER.name, 160 - ((Len(CHARACTER.name) * 8) / 2), 162, 0, 1
        Else
            Dim BadMess(0 To 2) As String
            BadMess(0) = ""
            BadMess(1) = ""
            BadMess(2) = ""
            If StoryPlayerPoints >= 0 And StoryPlayerPoints < 5000 Then
                BadMess(0) = "SORRY!"
                BadMess(1) = "BUT YOU REALLY SUCK"
                BadMess(2) = "AT THIS GAME"
            ElseIf StoryPlayerPoints >= 5000 And StoryPlayerPoints < 10000 Then
                BadMess(0) = "YOU ARE ONLY A BEGINNER"
                BadMess(1) = "WITHOUT ANY LUCK"
                BadMess(2) = "KEEP TRYING"
            ElseIf StoryPlayerPoints >= 10000 And StoryPlayerPoints < 12000 Then
                BadMess(0) = "STILL A LONG"
                BadMess(1) = "WAY TO WALK"
                BadMess(2) = "UNTIL THE TOP"
            Else
                BadMess(0) = "THE HIGHEST SCORE"
                BadMess(1) = "IS ALREADY INSANE"
                BadMess(2) = "TOUGH LUCK..."
            End If
            DrawText BadMess(0), 160 - ((Len(BadMess(0)) * 8) / 2), 142, 0, 3
            DrawText BadMess(1), 160 - ((Len(BadMess(1)) * 8) / 2), 152, 0, 3
            DrawText BadMess(2), 160 - ((Len(BadMess(2)) * 8) / 2), 162, 0, 3
        End If
    
    ElseIf MENU.VisibleMenu = MNUTitleScreen Then
        DDS_Back.Blt r, DDS_TITLESCREEN, rCutsScreen, DDBLT_KEYSRC
        msngFacing = Int(-60 * 360)
        
        DrawText "ACTIVATED.CORE", 8, 8, 0, 3
        DrawText ActCore_VERSION, 8, 16, 0, 2
        DrawText "Copyright 2008, Jiisuki", 8, 24, 0, 2
        DrawText "www.jiisuki.net", 8, 40, 0, 1
        
        DrawText "Press any key to proceed", 320 - 8 - (Len("Press any key to proceed") * 8), 240 - 16, 0, 2
    ElseIf MENU.VisibleMenu = MNUSelectMap Then
    
        If GuidemapSurfaceCreated Then
            Dim tmf As RECT
            tmf.Left = 0: tmf.Right = tmf.Left + MapWidth
            tmf.Top = 0: tmf.Bottom = tmf.Top + MapHeight
            DDS_Back.BltFast 160 - CLng(MapWidth / 2), 100 - CLng(MapHeight / 2), DDS_GuideMap, tmf, DDBLTFAST_WAIT
        End If
        DrawText "MAP NAME: " & MapName, 160 - CLng(Len("MAP NAME: " & MapName) * 8 / 2), 110 + CLng(MapHeight / 2), 0, 2
        DrawText "CREATED BY: " & MapCreator, 160 - CLng(Len("CREATED BY: " & MapCreator) * 8 / 2), 120 + CLng(MapHeight / 2), 0, 2
        DrawText "HIT SPACE TO SWITCH MAP", 160 - CLng(Len("HIT SPACE TO SWITCH MAP") * 8 / 2), 150 + CLng(MapHeight / 2), 0, 2
        DrawText "HIT ENTER TO START GAME", 160 - CLng(Len("HIT ENTER TO START GAME") * 8 / 2), 160 + CLng(MapHeight / 2), 0, 2
        
            If mintMouseX > 2 And mintMouseX < (2 + rQuit.Right) And mintMouseY > 220 And mintMouseY < 236 Then
                DDS_Back.BltFast 4, 220, DDS_MENUBUTTONS_0_0, rQuitOver, DDBLTFAST_SRCCOLORKEY
                tmpValue2 = "exit this world"
                If mblnLMouseButton And mnuClickFix = 0 Then
                    frmMain.tmr_MenuClickFix.ENABLED = True
                    mnuClickFix = mnuClickFix + 1: mblnLMouseButton = False
                    PlaySample "menu\select.mp3"
                    bQuit = True
                    bQuit2 = True
                End If
            End If
    
        
    ElseIf MENU.VisibleMenu = MNUStory Then
        DrawMap
    ElseIf MENU.VisibleMenu = MNUInstructions Then
            
    ElseIf MENU.VisibleMenu = MNULobby And NetworkStatus = SUCCESS Then
    
        DDS_Back.BltFast 0, 0, DDS_LOBBY, r, DDBLTFAST_SRCCOLORKEY
        
        Dim u As Integer
        For u = 0 To bPlayerCount
        
            tmpValue = udtPlayers(u).NickName
            DrawText UCase(tmpValue), 214, 116 + (u * 8)
            
        Next u
        
        Dim p As Integer
        For p = 0 To 23
            If ChatLine(p).chatText <> "" Then
                DrawText Mid(CStr(ChatLine(p).chatText), 1, 25), 4, (216 - 8 - (p * 8)), 0, 2
            End If
        Next p
        
        DrawText CStr(ChatPromtText & ChatPromtCursor), 4, 240 - 4 - 8
                        
        ' 32 , 32 - serverinfo
        tmpValue = ServerI.SessionName & " (" & bPlayerCount + 1 & "/" & CStr(ServerI.lMaxPlayers - 1) & ")."
        DrawText UCase(tmpValue), 4, 4
        'tmpValue = "CLIENTS: (" & CStr(bPlayerCount + 1) & "/" & CStr(ServerI.lMaxPlayers - 1) & ")."
        'DrawText UCase(tmpValue), 8, 64 + 8
                
        'tmpValue = "MAP: " & MapName & " (" & (MapWidth * 32) & ", " & (MapHeight * 32) & ") - created by " & MapCreator & "."
        'DrawText UCase(tmpValue), 8, 64 + 16
        
        DDS_Back.BltFast 320 - 4 - MapWidth, 4, DDS_GuideMap, HUD.SIZE_GUIDEMAP, DDBLTFAST_SRCCOLORKEY
        
        tmpValue = "start game"
        DrawText UCase(tmpValue), 320 - 4 - Int((Len(tmpValue) * 8)), 240 - 4 - 8, 0, 2

    ElseIf MENU.VisibleMenu = MNUMain Then
                            
            If SELECTEDMENU = MNUMultiplayer Then
                DDS_Back.BltFast 4, 40, DDS_MENUBUTTONS_0_0, rStartGameOver, DDBLTFAST_SRCCOLORKEY
                tmpValue2 = "multiplayer match of Activated Core"
            End If
            If SELECTEDMENU = MNUStory Then
                DDS_Back.BltFast 4, 58, DDS_MENUBUTTONS_0_0, rViewIntroOver, DDBLTFAST_SRCCOLORKEY
                tmpValue2 = "start new single player game"
            End If
            If SELECTEDMENU = MNUOptions Then
                DDS_Back.BltFast 4, 76, DDS_MENUBUTTONS_0_0, rOptionsOver, DDBLTFAST_SRCCOLORKEY
                tmpValue2 = "setup character and sound"
            End If
            If SELECTEDMENU = MNUMapEditor Then
                DDS_Back.BltFast 4, 94, DDS_MENUBUTTONS_0_0, rInstructionsOver, DDBLTFAST_SRCCOLORKEY
                tmpValue2 = "create or edit custom multiplayer maps"
            End If
            If SELECTEDMENU = MNUCredits Then
                DDS_Back.BltFast 4, 112, DDS_MENUBUTTONS_0_0, rCreditsOver, DDBLTFAST_SRCCOLORKEY
                tmpValue2 = "who made this?"
            End If
            If SELECTEDMENU = MNUQuit Then
                DDS_Back.BltFast 4, 220, DDS_MENUBUTTONS_0_0, rQuitOver, DDBLTFAST_SRCCOLORKEY
                tmpValue2 = "exit this world"
            End If
            
    ElseIf MENU.VisibleMenu = MNUMultiplayer Then
    
        'DDS_Back.BltFast 83, 40, DDS_MENULINES_1_1, rLines1_1, DDBLTFAST_SRCCOLORKEY
        
        'If mintMouseX > 96 And mintMouseX < (96 + rHost.Right) And mintMouseY > 38 And mintMouseY < 56 Then
        If SELECTEDMENU = MNUMultiplayerStart Then
            DDS_Back.BltFast 99, 40, DDS_MENUBUTTONS_1_1, rHostOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "start a multiplayer game of Activated Core"
        Else
            DDS_Back.BltFast 99, 40, DDS_MENUBUTTONS_1_1, rHost, DDBLTFAST_SRCCOLORKEY
        End If
        
        If SELECTEDMENU = MNUMultiplayerJoin Then
            DDS_Back.BltFast 99, 58, DDS_MENUBUTTONS_1_1, rJoinOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "join a multiplayer game of Activated Core"
        Else
            DDS_Back.BltFast 99, 58, DDS_MENUBUTTONS_1_1, rJoin, DDBLTFAST_SRCCOLORKEY
        End If
        
    ElseIf MENU.VisibleMenu = MNUMultiplayerStart Then
    
        'DDS_Back.BltFast 132, 40, DDS_MENULINES_STRAIGHT, rLinesStraight, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 148, 40, DDS_MENUSERVERNAME, rServerName, DDBLTFAST_SRCCOLORKEY
        
        DrawText UCase(ServerName), 152, 54, 0, 2
        
        'Old stuff
        'DDS_Back.BltFast 83, 40, DDS_MENULINES_1_1, rLines1_1, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 40, DDS_MENUBUTTONS_1_1, rHost, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 58, DDS_MENUBUTTONS_1_1, rJoin, DDBLTFAST_SRCCOLORKEY
    
    ElseIf MENU.VisibleMenu = MNUMultiplayerJoin Then
    
        'DDS_Back.BltFast 132, 58, DDS_MENULINES_STRAIGHT, rLinesStraight, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 148, 58, DDS_MENUJOINIP, rJoinIp, DDBLTFAST_SRCCOLORKEY
        
        DrawText UCase(JoinIpAddress), 152, 72, 0, 2
    
        'Old stuff
        'DDS_Back.BltFast 83, 40, DDS_MENULINES_1_1, rLines1_1, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 40, DDS_MENUBUTTONS_1_1, rHost, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 58, DDS_MENUBUTTONS_1_1, rJoin, DDBLTFAST_SRCCOLORKEY
        
    ElseIf MENU.VisibleMenu = MNUOptions Then
    
        'DDS_Back.BltFast 83, 76, DDS_MENULINES_2_1, rLines2_1, DDBLTFAST_SRCCOLORKEY
        
        If SELECTEDMENU = MNUEditName Then
            DDS_Back.BltFast 99, 76, DDS_MENUBUTTONS_2_1, rNameOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "set your nickname"
        Else
            DDS_Back.BltFast 99, 76, DDS_MENUBUTTONS_2_1, rName, DDBLTFAST_SRCCOLORKEY
        End If
        
        If SELECTEDMENU = MNUEditTeamName Then
            DDS_Back.BltFast 99, 94, DDS_MENUBUTTONS_2_1, rTeamOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "set your teamname"
        Else
            DDS_Back.BltFast 99, 94, DDS_MENUBUTTONS_2_1, rTeam, DDBLTFAST_SRCCOLORKEY
        End If
        
        If SELECTEDMENU = MNUSoundSettings Then
            DDS_Back.BltFast 99, 112, DDS_MENUBUTTONS_2_1, rSoundOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "select sound options"
        Else
            DDS_Back.BltFast 99, 112, DDS_MENUBUTTONS_2_1, rSound, DDBLTFAST_SRCCOLORKEY
        End If
        
        If SELECTEDMENU = MNUAimPoint Then
            DDS_Back.BltFast 99, 130, DDS_MENUAIM, rAimOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "select aim settings"
        Else
            DDS_Back.BltFast 99, 130, DDS_MENUAIM, rAim, DDBLTFAST_SRCCOLORKEY
        End If
                                
    ElseIf MENU.VisibleMenu = MNUEditName Then
    
        'DDS_Back.BltFast 139, 76, DDS_MENULINES_STRAIGHT, rLinesStraight, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 155, 76, DDS_MENUPLAYERNAME, rPlayerName, DDBLTFAST_SRCCOLORKEY
                    
        DrawText UCase(CHARACTER.name), 158, 90, 0, 2
                    
            'And old buttons;
        
        'DDS_Back.BltFast 83, 76, DDS_MENULINES_2_1, rLines2_1, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 76, DDS_MENUBUTTONS_2_1, rName, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 94, DDS_MENUBUTTONS_2_1, rTeam, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 112, DDS_MENUBUTTONS_2_1, rSound, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 130, DDS_MENUAIM, rAim, DDBLTFAST_SRCCOLORKEY
    
    ElseIf MENU.VisibleMenu = MNUEditTeamName Then
    
        'DDS_Back.BltFast 139, 94, DDS_MENULINES_STRAIGHT, rLinesStraight, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 155, 94, DDS_MENUTEAMNAME, rTeamName, DDBLTFAST_SRCCOLORKEY
                    
        DrawText UCase(CHARACTER.TeamName), 158, 108, 0, 2
                    
        'And old buttons;
        
        'DDS_Back.BltFast 83, 76, DDS_MENULINES_2_1, rLines2_1, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 76, DDS_MENUBUTTONS_2_1, rName, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 94, DDS_MENUBUTTONS_2_1, rTeam, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 112, DDS_MENUBUTTONS_2_1, rSound, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 130, DDS_MENUAIM, rAim, DDBLTFAST_SRCCOLORKEY
                                    
    ElseIf MENU.VisibleMenu = MNUSoundSettings Then
    
        'DDS_Back.BltFast 139, 112, DDS_MENULINES_STRAIGHT, rLinesStraight, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 155, 112, DDS_MENUSOUNDSETTINGS, rSoundSettings, DDBLTFAST_SRCCOLORKEY
                    
        If MusicEnabled Then
            DrawText "ON", 190, 115, 0, 2
        Else
            DrawText "OFF", 190, 115, 0, 2
        End If
        
        If SFXEnabled Then
            DrawText "ON", 190, 125, 0, 2
        Else
            DrawText "OFF", 190, 125, 0, 2
        End If
        
        If SELECTEDMENU = MNUSelectedMusic Then
            DDS_Back.BltFast 155, 112, DDS_MENUSOUNDSETTINGS, rSoundSettingsMusicOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "music on/off"
        End If
                    
        If SELECTEDMENU = MNUSelectedSound Then
            DDS_Back.BltFast 155, 112, DDS_MENUSOUNDSETTINGS, rSoundSettingsSFXOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "sound effects on/off"
        End If

        If SELECTEDMENU = MNUSelectedGameTune Then
            DDS_Back.BltFast 155, 112, DDS_MENUSOUNDSETTINGS, rSoundSettingsSelMusOver, DDBLTFAST_SRCCOLORKEY
            tmpValue2 = "select game tune, click to hear"
        End If
                    
        'And old buttons;
        
        'DDS_Back.BltFast 83, 76, DDS_MENULINES_2_1, rLines2_1, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 76, DDS_MENUBUTTONS_2_1, rName, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 94, DDS_MENUBUTTONS_2_1, rTeam, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 112, DDS_MENUBUTTONS_2_1, rSound, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 130, DDS_MENUAIM, rAim, DDBLTFAST_SRCCOLORKEY

    ElseIf MENU.VisibleMenu = MNUSelectCrosshair Then


        'DDS_Back.BltFast 139, 130, DDS_MENULINES_STRAIGHT, rLinesStraight, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 155, 130, DDS_AIMBOX, rAimBox, DDBLTFAST_SRCCOLORKEY
        
        ''''''''''''''''''''''
        Dim tmpRECT As RECT
        tmpRECT.Left = CHARACTER.CROSSHAIRNUM * 9
        tmpRECT.Right = tmpRECT.Left + 9
        '''''''''''''''''''''
        
        tmpRECT.Top = 0: tmpRECT.Bottom = tmpRECT.Top + 9
        DDS_Back.BltFast 170, 148, DDS_Crosshair, tmpRECT, DDBLTFAST_SRCCOLORKEY
        tmpRECT.Top = 9: tmpRECT.Bottom = tmpRECT.Top + 9
        DDS_Back.BltFast 180, 148, DDS_Crosshair, tmpRECT, DDBLTFAST_SRCCOLORKEY
        tmpRECT.Top = 18: tmpRECT.Bottom = tmpRECT.Top + 9
        DDS_Back.BltFast 190, 148, DDS_Crosshair, tmpRECT, DDBLTFAST_SRCCOLORKEY
        tmpRECT.Top = 27: tmpRECT.Bottom = tmpRECT.Top + 9
        DDS_Back.BltFast 200, 148, DDS_Crosshair, tmpRECT, DDBLTFAST_SRCCOLORKEY
        tmpRECT.Top = 36: tmpRECT.Bottom = tmpRECT.Top + 9
        DDS_Back.BltFast 210, 148, DDS_Crosshair, tmpRECT, DDBLTFAST_SRCCOLORKEY
        tmpRECT.Top = 45: tmpRECT.Bottom = tmpRECT.Top + 9
        DDS_Back.BltFast 220, 148, DDS_Crosshair, tmpRECT, DDBLTFAST_SRCCOLORKEY
        tmpRECT.Top = 54: tmpRECT.Bottom = tmpRECT.Top + 9
        DDS_Back.BltFast 230, 148, DDS_Crosshair, tmpRECT, DDBLTFAST_SRCCOLORKEY
        tmpRECT.Top = 63: tmpRECT.Bottom = tmpRECT.Top + 9
        DDS_Back.BltFast 240, 148, DDS_Crosshair, tmpRECT, DDBLTFAST_SRCCOLORKEY
        
        DDS_Back.SetForeColor RGB(64, 64, 128)
        DDS_Back.DrawBox (169 + (CHARACTER.CROSSHAIR * 10)), 147, (180 + (CHARACTER.CROSSHAIR * 10)), 158
                
        'And old buttons;
        
        'DDS_Back.BltFast 83, 76, DDS_MENULINES_2_1, rLines2_1, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 76, DDS_MENUBUTTONS_2_1, rName, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 94, DDS_MENUBUTTONS_2_1, rTeam, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 112, DDS_MENUBUTTONS_2_1, rSound, DDBLTFAST_SRCCOLORKEY
        DDS_Back.BltFast 99, 130, DDS_MENUAIM, rAim, DDBLTFAST_SRCCOLORKEY

    End If
        
    'DrawText UCase(tmpValue2), 4, 26, 0, 2
    
    If MENU.VisibleMenu <> MNUTitleScreen Then
        If MENU.VisibleMenu <> MNUGameOver Then
            DrawText "HIGHEST SCORE", 320 - 4 - (Len("HIGHEST SCORE") * 8), 240 - 22, 0, 2
            DrawText StoryHiPlayer & ": " & CStr(StoryHiScore), 320 - 4 - (Len(StoryHiPlayer & ": " & CStr(StoryHiScore)) * 8), 240 - 12, 0, 3
        End If
    End If
    
Exit Sub

'    If GuidemapSurfaceCreated Then
'        Dim tmf As RECT
'        tmf.Left = 0
'        tmf.Top = 0
'        tmf.Bottom = MapHeight
'        tmf.Right = MapWidth
'        DDS_Back.BltFast 160 - (MapWidth / 2), 64, DDS_GuideMap, tmf, DDBLTFAST_WAIT
'    End If
'    DrawText UCase("LOADING MAP" & MapName), 160 - ((Len("LOADING MAP" & MapName) / 2) * 8), 100 + MapHeight, 0, 2
'    DrawText UCase(CStr(LoadingCompletion / MapHeight)), 160 - ((Len(CStr(LoadingCompletion / MapHeight)) / 2) * 8), 110 + MapHeight, 0, 2
        
End If

ErrorSender:
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: ERROR IN DRAWING MENU/MENU SYSTEM"
    ShutdownNoErrorFlag = False: Shutdown
    
End Sub




Private Sub DrawMainButtons()

End Sub







Public Sub RestartMenu(Optional StoryProceed As Boolean = False)

    bQuit = False
    gSTARTED = False
    
    If StoryProceed = False Then MENU.VisibleMenu = MNUMain
    
    
    RenderMenuLoop

End Sub
















Public Sub DrawActCoreIntro()

    AnimateActCoreIntro

    Dim i As Integer
    
    i = CurrentLine
    
        If IntroLine(i).intro_Font = 0 Then
            DDS_Back.SetFont frmMain.mnuFont.Font
        ElseIf IntroLine(i).intro_Font = 2 Then
            DDS_Back.SetFont frmMain.mnuCreditFont.Font
        Else
            DDS_Back.SetFont frmMain.Font
        End If
        
            DDS_Back.SetForeColor IntroLine(i).intro_Color
        
            DDS_Back.DrawText IntroLine(i).intro_XPos, IntroLine(i).intro_YPos, UCase(IntroLine(i).intro_TEXT), False
    
    If IntroShowPressText = True Then
        
        DrawText UCase("PRESS ANY KEY TO PROCEED"), (160 - Int((Len("PRESS ANY KEY TO PROCEED") * 8) / 2)), (120), 0, 3
        
    End If
    
End Sub














Public Sub AnimateActCoreIntro()

    lTickCount9 = GetTickCount()
    
    If (lTickCount9 - lOldTickCount9) > 40 Then
        'Save the tick count
        lOldTickCount9 = GetTickCount
                
        Dim i As Integer, i2 As Integer
        
        i = CurrentLine
        If i = UBound(IntroLine) Then
            Intro_INIT
        End If
                
            IntroLine(i).intro_XPos = IntroLine(i).intro_XPos + IntroLine(i).intro_MoveFactor

                If IntroLine(i).iFix = True Then
                    If i = 0 Then
                        IntroLine(i).intro_Color = IntroLine(i).intro_Color + RGB(4, 4, 4)
                    Else
                        IntroLine(i).intro_Color = IntroLine(i).intro_Color + RGB(6, 6, 6)
                    End If
                    If IntroLine(i).intro_Color >= RGB(255, 255, 255) Then
                        IntroLine(i).intro_Color = RGB(255, 255, 255)
                        IntroLine(i).iFix = False
                    End If
                Else
                    IntroLine(i).intro_Color = IntroLine(i).intro_Color - RGB(6, 6, 6)
                    If IntroLine(i).intro_Color <= 0 Then
                        IntroLine(i).intro_Color = 0
                        If CurrentLine = MaxLines Then
                            SwitchMenu MNUTitleScreen
                        End If
                        CurrentLine = CurrentLine + 1
                    End If
                End If

    End If

End Sub

















Public Sub Intro_INIT()



CurrentLine = 0

IntroShowPressText = False

Dim i As Integer

For i = 0 To UBound(IntroLine)
    IntroLine(i).intro_TEXT = ""
    IntroLine(i).intro_Font = 0
    IntroLine(i).intro_YPos = 110
    IntroLine(i).intro_XPos = 160
    IntroLine(i).intro_Color = 0
    IntroLine(i).intro_MoveFactor = -4
    IntroLine(i).iFix = True
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("written introline nr '" & CStr(i) & "'")
    DoEvents
    
Next i
    
    

Randomize

i = 0

    IntroLine(i).intro_TEXT = "press any key to skip intro"
    IntroLine(i).intro_XPos = 16
    IntroLine(i).intro_Font = 2
    IntroLine(i).intro_YPos = 16
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
        
i = i + 1

    IntroLine(i).intro_TEXT = "jiisuki presents"
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
    
i = i + 1

    IntroLine(i).intro_TEXT = "a c t i v a t e d . c o r e"
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True

i = i + 1

    IntroLine(i).intro_TEXT = ""
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
    
i = i + 1

    IntroLine(i).intro_TEXT = "an unforgetable journey"
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
        
i = i + 1

    IntroLine(i).intro_TEXT = "to a place called home"
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
    
i = i + 1

    IntroLine(i).intro_TEXT = "with an awakened core"
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
        
i = i + 1

    IntroLine(i).intro_TEXT = ""
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
        
i = i + 1

    IntroLine(i).intro_TEXT = "this is destiny"
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
        
        
i = i + 1

    IntroLine(i).intro_TEXT = ""
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
    
    
i = i + 1

    IntroLine(i).intro_TEXT = "an original game by"
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True

        
i = i + 1

    IntroLine(i).intro_TEXT = "j i i s u k i"
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
    
i = i + 1

    IntroLine(i).intro_TEXT = ""
    IntroLine(i).intro_XPos = 160 - ((Len(IntroLine(i).intro_TEXT) * 9) / 2)
    IntroLine(i).intro_MoveFactor = 0
    IntroLine(i).iFix = True
    
            
            
MaxLines = i + 1 'to fix the logoappereance and stuff..
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("written introlines content of total '" & CStr(i) & "' lines")
    
End Sub

