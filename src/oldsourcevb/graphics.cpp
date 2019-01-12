Attribute VB_Name = "mod_Graphics"
'------------------------------------.
' This is the module that handle all |
' painting operations in directx and |
' our game.                          |
'------------------------------------'
Public DD As DirectDraw7 'ddraw object.
Public D3D As Direct3D7  'd3d object.

Public D3DDevice As Direct3DDevice7

Public DXBitDepth As Integer
Public SCRWidth As Long
Public SCRHeight As Long

Public GammaControler As DirectDrawGammaControl    'The object that gets/sets gamma ramps
Public GammaRamp As DDGAMMARAMP                    'The gamma ramp we'll use to alter the screen state
Public OriginalRamp As DDGAMMARAMP                 'The gamma ramp we'll use to store the original screen state
Public LavaGammaRamp As DDGAMMARAMP

Public GammaValue As Integer

Public cBlack As Long
Public cWhite As Long
Public cRed As Long
Public cBlue As Long
Public cGreen As Long

Public rMAPCUT As RECT
Public rTOTMAP As RECT
'----------------------.
' Surface Declarations |
'----------------------'

'these surfaces hold the window
'primary and backbuffer.
Public DDS_Primary As DirectDrawSurface7
Public DDSD_Primary As DDSURFACEDESC2
Public DDS_Back As DirectDrawSurface7
Public DDSD_Back As DDSURFACEDESC2

Public DDS_BackFX As DirectDrawSurface7
Public DDSD_BackFX As DDSURFACEDESC2

Public D3DD As Direct3DDevice7

'a clipper for windowed mode.
Public ddClipper As DirectDrawClipper

Public DDS_Character1 As DirectDrawSurface7 'char.
Public DDSD_Character1 As DDSURFACEDESC2
Public DDS_Character2 As DirectDrawSurface7 'char.
Public DDSD_Character2 As DDSURFACEDESC2

Public DDS_WEAP As DirectDrawSurface7 'mines and stuff
Public DDSD_WEAP As DDSURFACEDESC2

Public DDS_MAPTILES As DirectDrawSurface7
Public DDSD_MAPTILES As DDSURFACEDESC2
Public DDS_COLTILES As DirectDrawSurface7
Public DDSD_COLTILES As DDSURFACEDESC2

Public DDS_MAP As DirectDrawSurface7 'the mapskin.
Public DDSD_MAP As DDSURFACEDESC2
Public DDS_MAP2 As DirectDrawSurface7 'the map backgrounds
Public DDSD_MAP2 As DDSURFACEDESC2
Public DDS_MAP3 As DirectDrawSurface7 ' the map foregrounds
Public DDSD_MAP3 As DDSURFACEDESC2
Public DDS_COLLISIONMAP As DirectDrawSurface7 'the collision skin.
Public DDSD_COLLISIONMAP As DDSURFACEDESC2

Public DDS_GuideMap As DirectDrawSurface7 'the guidemap.
Public DDSD_GuideMap As DDSURFACEDESC2
Public GuidemapSurfaceCreated As Boolean

Public DDS_Crosshair As DirectDrawSurface7 'crosshairs.
Public DDSD_Crosshair As DDSURFACEDESC2

Public DDS_Guide As DirectDrawSurface7 'guidemap.
Public DDSD_Guide As DDSURFACEDESC2

Public DDS_Console As DirectDrawSurface7 'console
Public DDSD_Console As DDSURFACEDESC2
Public DDS_ConsoleBuffer As DirectDrawSurface7 'console
Public DDSD_ConsoleBuffer As DDSURFACEDESC2

Public DDS_Charmap(1 To 13) As DirectDrawSurface7 'bitmap fontmap
Public DDSD_Charmap(1 To 13) As DDSURFACEDESC2

Public DDS_CharmapAlpha As DirectDrawSurface7
Public DDSD_CharmapAlpha As DDSURFACEDESC2

Public DDS_Objects As DirectDrawSurface7
Public DDSD_Objects As DDSURFACEDESC2
Public DDS_MapObjects As DirectDrawSurface7
Public DDSD_MapObjects As DDSURFACEDESC2

Public DDS_Lava As DirectDrawSurface7 'lava.
Public DDSD_Lava As DDSURFACEDESC2

Public DDS_DOOR As DirectDrawSurface7
Public DDSD_DOOR As DDSURFACEDESC2


Public DDS_HUDTopMain As DirectDrawSurface7
Public DDSD_HUDTopMain As DDSURFACEDESC2
Public DDS_HUDBottomMain As DirectDrawSurface7
Public DDSD_HUDBottomMain As DDSURFACEDESC2
Public DDS_HUDTopEnergyBar As DirectDrawSurface7
Public DDSD_HUDTopEnergyBar As DDSURFACEDESC2
Public DDS_HUDTopAmmoBar As DirectDrawSurface7
Public DDSD_HUDTopAmmoBar As DDSURFACEDESC2
Public DDS_HUDTopArmorBar As DirectDrawSurface7
Public DDSD_HUDTopArmorBar As DDSURFACEDESC2
Public DDS_HUDTopStandingsPoint As DirectDrawSurface7
Public DDSD_HUDTopStandingsPoint As DDSURFACEDESC2

Public DDSD_LOBBY As DDSURFACEDESC2
Public DDS_LOBBY As DirectDrawSurface7

Public DDSD_WEAPONBLASTERBULLET As DDSURFACEDESC2
Public DDS_WEAPONBLASTERBULLET As DirectDrawSurface7

'Menu surfaces, buttons etc.
Public DDSD_MENUBUTTONS_0_0 As DDSURFACEDESC2
Public DDS_MENUBUTTONS_0_0 As DirectDrawSurface7
Public DDSD_MENUBUTTONS_1_1 As DDSURFACEDESC2
Public DDS_MENUBUTTONS_1_1 As DirectDrawSurface7
Public DDSD_MENUBUTTONS_2_1 As DDSURFACEDESC2
Public DDS_MENUBUTTONS_2_1 As DirectDrawSurface7
Public DDSD_MENUBUTTON_GO As DDSURFACEDESC2
Public DDS_MENUBUTTON_GO As DirectDrawSurface7
Public DDSD_MENUHEADER As DDSURFACEDESC2
Public DDS_MENUHEADER As DirectDrawSurface7
Public DDSD_MENULINES_1_1 As DDSURFACEDESC2
Public DDS_MENULINES_1_1 As DirectDrawSurface7
Public DDSD_MENULINES_2_1 As DDSURFACEDESC2
Public DDS_MENULINES_2_1 As DirectDrawSurface7
Public DDSD_MENULINES_STRAIGHT As DDSURFACEDESC2
Public DDS_MENULINES_STRAIGHT As DirectDrawSurface7
Public DDSD_MENUPLAYERNAME As DDSURFACEDESC2
Public DDS_MENUPLAYERNAME As DirectDrawSurface7
Public DDSD_MENUSERVERNAME As DDSURFACEDESC2
Public DDS_MENUSERVERNAME As DirectDrawSurface7
Public DDSD_MENUTEAMNAME As DDSURFACEDESC2
Public DDS_MENUTEAMNAME As DirectDrawSurface7
Public DDSD_MENUSOUNDSETTINGS As DDSURFACEDESC2
Public DDS_MENUSOUNDSETTINGS As DirectDrawSurface7
Public DDSD_MENUINSTRUCTIONBOX As DDSURFACEDESC2
Public DDS_MENUINSTRUCTIONBOX As DirectDrawSurface7
Public DDSD_MENUJOINIP As DDSURFACEDESC2
Public DDS_MENUJOINIP As DirectDrawSurface7
Public DDSD_MENUAIM As DDSURFACEDESC2
Public DDS_MENUAIM As DirectDrawSurface7
Public DDSD_AIMBOX As DDSURFACEDESC2
Public DDS_AIMBOX As DirectDrawSurface7

Public DDSD_LIGHTMAP As DDSURFACEDESC2
Public DDS_LIGHTMAP As DirectDrawSurface7

'Cuts
Public DDSD_TITLESCREEN As DDSURFACEDESC2
Public DDS_TITLESCREEN As DirectDrawSurface7

'Extra Items
Public DDSD_EXTRAITEM(0 To 32) As DDSURFACEDESC2
Public DDS_EXTRAITEM(0 To 32) As DirectDrawSurface7

'Menu Rectangle Definitions
Public rStartGame As RECT
Public rViewIntro As RECT
Public rOptions As RECT
Public rInstructions As RECT
Public rCredits As RECT
Public rQuit As RECT
Public rStartGameOver As RECT
Public rViewIntroOver As RECT
Public rOptionsOver As RECT
Public rInstructionsOver As RECT
Public rCreditsOver As RECT
Public rQuitOver As RECT

Public rHost As RECT
Public rJoin As RECT
Public rHostOver As RECT
Public rJoinOver As RECT

Public rName As RECT
Public rTeam As RECT
Public rSound As RECT
Public rNameOver As RECT
Public rTeamOver As RECT
Public rSoundOver As RECT
Public rAim As RECT
Public rAimOver As RECT

Public rGo As RECT
Public rGoOver As RECT

Public rPlayerName As RECT
Public rTeamName As RECT

Public rLines1_1 As RECT
Public rLines2_1 As RECT
Public rLinesStraight As RECT

Public rSoundSettings As RECT
Public rSoundSettingsMusicOver As RECT
Public rSoundSettingsSFXOver As RECT
Public rSoundSettingsSelMusOver As RECT

Public rInstructionsBox As RECT
Public rServerName As RECT
Public rJoinIp As RECT

Public rAimBox As RECT
Public rCutsScreen As RECT

'-------------------.
'Other Declatations |
'-------------------'
Public r As RECT 'usefull 640 by 480 rect, used in windowed mode.
Public ClientVidMode As Integer

'hold the current screen mode
Public SMode As Integer
Public ScreenMode As Integer

'hold the quit flag to shut down engine when program stops.
Public bQuit
Public bQuit2

Public LAVACYCLENUM As Integer
Public LAVACYCLEMOVEVALUE As Integer
Public JUMPERCYCLENUM As Integer
Public FLAGCYCLENUM As Integer
Public TELEPORTANIMNUM As Integer

Public ShowGameStats As Boolean

Public Declare Function timeGetTime Lib "winmm.dll" () As Long
Public FirstTime As Long, SecondTime As Long
Public NumLoops As Integer, FPS As Long

Public Declare Function vbDABLalphablend16 Lib "vbDABL" (ByVal iMode As Integer, ByVal bColorKey As Integer, _
     ByRef sptr As Any, ByRef dPtr As Any, ByVal iAlphaVal As Integer, ByVal iWidth As Integer, ByVal iHeight As Integer, _
     ByVal isPitch As Integer, ByVal idPitch As Integer, ByVal iColorKey As Integer) As Integer

Public Declare Function vbDABLcolorblend16555 Lib "vbDABL" (ByRef sptr As Any, ByRef dPtr As Any, ByVal alpha_val%, _
     ByVal Width%, ByVal Height%, ByVal sPitch%, ByVal dPitch%, ByVal rVal%, ByVal gVal%, ByVal bVal%) As Long

Public Declare Function vbDABLcolorblend16565 Lib "vbDABL" (ByRef sptr As Any, ByRef dPtr As Any, ByVal alpha_val%, _
     ByVal Width%, ByVal Height%, ByVal sPitch%, ByVal dPitch%, ByVal rVal%, ByVal gVal%, ByVal bVal%) As Long

Public Declare Function vbDABLcolorblend16555ck Lib "vbDABL" (ByRef sptr As Any, ByRef dPtr As Any, ByVal alpha_val%, _
     ByVal Width%, ByVal Height%, ByVal sPitch%, ByVal dPitch%, ByVal rVal%, ByVal gVal%, ByVal bVal%) As Long

Public Declare Function vbDABLcolorblend16565ck Lib "vbDABL" (ByRef sptr As Any, ByRef dPtr As Any, ByVal alpha_val%, _
     ByVal Width%, ByVal Height%, ByVal sPitch%, ByVal dPitch%, ByVal rVal%, ByVal gVal%, ByVal bVal%) As Long

Public Sub DrawLightMap()
    '* iMode: The only possible values for this parameter are '555' or '565'.
        'It specifies how each pixel is formatted in memory. In 16-bit mode,
        'there are two possible ways: 555, where there are 5 red bits, 5 green bits,
        'and 5 blue bits, and 565 where there are 5 red bits, 6 green bits, and 5 blue bits.
        'I'll show you how to detect this a little bit later...
    '* bColorKey: This parameter tells vbDABL whether to use colorkeying (a transparent color
        'which will not be copied) or not. If this is a '0' (zero), colorkying will NOT be used,
        'any other number will enable colorkeying.
    '* sPtr As Any: The 'pointer' to, or memory address of, the DirectDraw surface to be used
        'as the source for the alpha blending. It is passed 'ByRef', so what you actually pass
        'as the parameter is NOT a pointer, but what truly gets to the function IS. I'll explain
        'how this works in more detail later...
    '* dPtr As Any: The pointer to the DirectDraw surface to be used as the destination for the
        'alpha blending. All the comments about sPtr apply to this parameter as well.
    '* iAlphaVal: This is the 'alpha' value to use for the blend. Basically, it is a number between
        '0 and 255, with 0 making the resulting pixels (which end up on the destination surface)
        'equal to the destination pixels, so there is no change at all, and 255 making the resulting
        'pixels equal to the source pixels, essentially a plain blit from source to destination.
        'Therefore, the closer you get to 255, the more the resulting pixel resembles the source
        'pixel rather than the destination pixel. This may become clearer to you after I discuss
        'the algorithm used for the blending later.
    '* iWidth: The width (in pixels) of the area you want to blend.
    '* iHeight: The height (once again, in pixels) of the area you want to blend.
    '* isPitch: This is the 'pitch' of the source surface, as defined by DirectDraw. Basically
        'it's the number of bytes per row of pixels in memory. There is a better definition and
        'explanation in DirectX SDK documentation. All you need to know is that you can get it out
        'of the DDSURFACEDESC2 structure filled out for you when you lock your surface.
    '* idPitch: The pitch of the destination surface... All the isPitch stuff applies here as well.
    '* iColorKey: Hmm, similar to the 'bColorKey' parameter, except that this one starts with an 'i'.
        'The way I named many of the parameters is to use the first letter of the variable type as the
        'first letter of the parameter; thus bColorKey is treated as a boolean (even though it's actually
        'an integer...), and this one is a true integer. It is only used if bColorKey is not 0,
        'therefore only if colorkeying is enabled. It is the numerical value of the color that you want
        'to be transparent in your blend (if you aren't using colorkeying, just leave it as 0 or something,
        'it really doesn't matter). It behaves the same way as a colorkey in a normal DirectDraw blit.

'Dim dArray() As Byte, sArray() As Byte

'DDS_Back.Lock r, DDSD_Back, DDLOCK_WAIT, 0
'dds_maplightmap.Lock rMAPCUT, ddsd_maplightmap, DDLOCK_WAIT, 0

'DDS_Back.GetLockedArray dArray()
'dds_maplightmap.GetLockedArray sArray()

'Call vbDABLalphablend16(clientvideomode, 0, sArray(SX + SX, SY), dArray(DX + DX, dY), 200, 320, 240, ddsd_maplightmap.lPitch, ddsd_back.lPitch, 0)

'DDS_Back.Unlock r
'dds_maplightmap.Unlock rMAPCUT

End Sub



Public Sub DrawShield()

    Dim r As RECT, r2 As RECT, ShieldAng As Single, SX As Integer, SY As Integer
    Dim i As Integer, o As Integer
    For i = 0 To Int(CHARACTER.SHIELDTIME * 4)
    
        Randomize
        o = 1
        ShieldAng = CSng(Rnd * PI * 2)
        SX = 160 + Int((Cos(ShieldAng) * 20))
        If Not CHARACTER.CROUCHING Then
            SY = 120 + Int((Sin(ShieldAng) * 20))
        Else
            SY = 132 + Int((Sin(ShieldAng) * 20))
        End If
    
        r.Top = SY - 3 + Int(Rnd * 4) + 1
        r.Bottom = r.Top + 1
        r.Left = SX - 3 + Int(Rnd * 4) + 1 ' * CrosshairSize)
        r.Right = r.Left + 1  ' * CrosshairSize)
    
        If o = 0 Then
            DDS_Back.BltColorFill r, RGB(144, 226, 80)
        ElseIf o = 1 Then
            DDS_Back.BltColorFill r, RGB(93, 175, 29)
        Else
            DDS_Back.BltColorFill r, RGB(68, 127, 21)
        End If
        
    
    Next i
    

End Sub

Public Sub DrawClientShield(k As Integer)

    Dim r As RECT, r2 As RECT, ShieldAng As Single, SX As Integer, SY As Integer
    Dim i As Integer, o As Integer

    For i = 0 To 16
    
        Randomize
        o = 1
        ShieldAng = CSng(Rnd * PI * 2)
        SX = udtPlayers(k).X - (CHARACTER.X - 144) + 16 + Int((Cos(ShieldAng) * 20))
        If udtPlayers(k).Animation = CROUCHING Then
            SY = udtPlayers(k).Y - (CHARACTER.Y - 104) + 16 + Int((Sin(ShieldAng) * 20))
        Else
            SY = udtPlayers(k).Y - (CHARACTER.Y - 92) + 16 + Int((Sin(ShieldAng) * 20))
        End If
    
        r.Top = SY - 3 + Int(Rnd * 4) + 1
        r.Bottom = r.Top + 1
        r.Left = SX - 3 + Int(Rnd * 4) + 1 ' * CrosshairSize)
        r.Right = r.Left + 1  ' * CrosshairSize)
    
        If o = 0 Then
            DDS_Back.BltColorFill r, RGB(144, 226, 80)
        ElseIf o = 1 Then
            DDS_Back.BltColorFill r, RGB(93, 175, 29)
        Else
            DDS_Back.BltColorFill r, RGB(68, 127, 21)
        End If
        
    
    Next i
    

End Sub





Public Sub Renderloop()

'on local error GoTo Shutdowner

'------------------------------------------.
'This sub is the main renderloop.          |
'This flips the backbuffer so we can se it |
'on the primary screen buffer..            |
'------------------------------------------'

'the rectangles for windowed mode
    Dim r2 As RECT
    
'--------------------.
'Lets start the loop |
'--------------------'

FPS = 0

    Do
    
        FirstTime = timeGetTime
    
        '-------------------------.
        'Draw current game screen |
        '-------------------------'
        DrawFrame
                
        '----------------------------------.
        'Flip the double buffered surfaces |
        'This is where the magic happens!  |
        '----------------------------------'
                
        If SMode = 0 Then 'Windowed mode
            DDS_Back.SetForeColor RGB(32, 32, 32)
            'DDS_Back.DrawBox 0, 0, 320, 240
            DX.GetWindowRect frmMain.hwnd, r2
            r2.Top = r2.Top
            r2.Bottom = r2.Top + WindowedResY
            DDS_Primary.Blt r2, DDS_Back, r, DDBLTFAST_NOCOLORKEY + DDBLTFAST_WAIT
            
        Else   'Full-Screen
        
            DDS_Primary.Flip Nothing, DDFLIP_WAIT

        End If
    
    '-----------------------------.
    'Now we make time for windows |
    'to do other things           |
    '-----------------------------'
    
        'NumLoops = NumLoops + 1
        'If NumLoops = 9 Then
        '    SecondTime = timeGetTime
        '    If (SecondTime - FirstTime) > 0 Then
        '
        '    End If
        '    FirstTime = timeGetTime
        '    NumLoops = 0
        'End If
        Do Until timeGetTime >= FirstTime + 8
        Loop
        FPS = (1000 / (timeGetTime - FirstTime))
        
        DoEvents
        
        
    '--------------------------.
    'Loop until we say stop ;) |
    '--------------------------'
    
    Loop Until bQuit
    
    '-------------------.
    'Shutdown Procedure |
    '-------------------'
    If StoryMapFinish = True Then
        RestartMenu True
    Else
        RestartMenu False
    End If
    
Exit Sub
    
Shutdowner:
    
    ShutdownNoErrorFlag = False
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: GAME RENDERLOOP"
    Shutdown
    

End Sub


Public Sub DrawFrame()

'on local error GoTo Shutdowner

'----------------------------.
'This sub draws every frame  |
'Character, map, objects and |
'everything. Hell yeah!      |
'----------------------------'
        
    Dim mbltfx As DDBLTFX
    
    '-------------------------------------.
    'The above statement is if we want to |
    'use any dx effects when we paint..   |
    '-------------------------------------'
        
    '----------------------------.
    'Colour the background black |
    '----------------------------'
    If Not OverlayMenu And Not mLOADING Then
        DDS_Back.BltColorFill r, RGB(0, 0, 0)
    
        '-------------------.
        'Draw moving stars. |
        '-------------------'
        If Starfield.ON Then
            StarPhysics
            DrawStars
        End If
        
        '-------------------------------------.
        'These is calls to other subs.        |
        'This because I want it easy to edit. |
        '-------------------------------------'
        AnimateStuff
        
        
        If Not CHARACTER.Dead Then
            DrawMap         'Draw maplayer
            If ExtraItems >= 1 Then
                Dim tmpI As Integer
                For tmpI = 0 To ExtraItems - 1
                    DrawExtraItems tmpI
                Next tmpI
            End If
            DrawJumpers     'Draw jumpers
        
            If obj_FlagBlue.Flag1 <> 0 And obj_FlagRed.Flag1 <> 0 Then DrawFlags
 
            'This draws items, weapons and other pickups.
            If obj_Count(0) > 0 Then DrawMapObject tHealth
            If obj_Count(1) > 0 Then DrawMapObject tMegaHealth
            If obj_Count(2) > 0 Then DrawMapObject tShield
            If obj_Count(3) > 0 Then DrawMapObject tPowerup
            If obj_Count(4) > 0 Then DrawMapObject tGrenades
            If obj_Count(5) > 0 Then DrawMapObject tBatteries
            If obj_Count(6) > 0 Then DrawMapObject tMines
            If obj_Count(7) > 0 Then DrawMapObject tHeartSensor
            If obj_Count(8) > 0 Then DrawMapObject tArmorShard
            If obj_Count(9) > 0 Then DrawMapObject tRailgun
            If obj_Count(10) > 0 Then DrawMapObject tBoingers
            If obj_Count(11) > 0 Then DrawMapObject tCapacitor
            If obj_Count(13) > 0 Then DrawMapObject tSuit   'Actually it has been changed to a data
                                                            'disk in the story mode, but the code is
                                                            'still the same as the firs idea, the suit.
        End If
        
        If NetworkStatus = SUCCESS And Not CHARACTER.Dead Then
            Dim tPc As Integer
            For tPc = 0 To bPlayerCount
                If Not udtPlayers(tPc).iPlayerID = lngMyPlayerID Then
                    DrawClient tPc
                    If udtPlayers(tPc).GotShield Then DrawClientShield tPc
                End If
            Next tPc
            SendPhysicsPackets
        End If
        
        If Not CHARACTER.Dead Then
            DrawCharacter
            If CHARACTER.GotShield Then DrawShield
            DrawProjectiles
        End If
        
        If GAMEMODE = TRAINING_BOTPLAY Then
            Dim i As Integer
            For i = 0 To UBound(BotClient)
                If Not BotClient(i).Dead And GAMEMODE = TRAINING_BOTPLAY Then
                    If Not CHARACTER.Dead Then DrawOpponents
                    DoBotState
                    BotPhysics
                End If
            Next i
        End If
        
        If Not CHARACTER.Dead Then
            DrawTelePort
            DrawHUD
            DrawCrosshair
        End If
    
    '---------------------------------------------------.
    'This doesnt have anything to do with the painting  |
    'but this is so we update everything we paint for   |
    'the next frame. Move the char, select next picture |
    'in animations etc.                                 |
    '---------------------------------------------------'
    
        CheckMouse
        CheckKeyboard
        If Not CHARACTER.Dead Then
            Physics    'falling etc.
        End If
        
        If ShowGameStats And GAMEMODE <> STORYMODE Then DRAWGAMESTATS
        
        If GAMEMODE = STORYMODE And CHARACTER.Dead Then
            If StoryPlayerLives >= 2 Then
                DrawText "CONTINUES LEFT: " & CStr(StoryPlayerLives), 160 - (CInt(Len("CONTINUES LEFT: " & CStr(StoryPlayerLives)) / 2) * 8), 116, 0, 2
            Else
                DrawText "CONTINUES LEFT: " & CStr(StoryPlayerLives), 160 - (CInt(Len("CONTINUES LEFT: " & CStr(StoryPlayerLives)) / 2) * 8), 116, 0, 3
            End If
        End If
            
        If cEnabled Then
            cDrawConsole
        End If
        
    Else
    
        CheckMouse
        DrawMenuFrame
        
    End If

    Exit Sub
    
Shutdowner:
    
    ShutdownNoErrorFlag = False
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: DRAWING FRAME"
    Shutdown
    
End Sub

Public Sub DrawShadow()


End Sub

Public Sub DrawClient(i As Integer)

    AnimateCharacter    'animate character.

'----------------------------------------------.
'This draws the character onto the backbuffer. |
'----------------------------------------------'

    Dim r3 As RECT, r4 As RECT
    Dim mbltfx As DDBLTFX
    
    '--------------------------------------------.
    'This sets the rectangle so we paint the guy |
    'in the middle of the screen.                |
    '--------------------------------------------'
    r3.Top = udtPlayers(i).Y - (CHARACTER.Y - 104)    'character.y
    r3.Bottom = r3.Top + 32
    r3.Left = udtPlayers(i).X - (CHARACTER.X - 144)   'Character.X
    r3.Right = r3.Left + 32
            
    '---------------------------------------------------.
    'Copy the current frame (cyclenum) from the bitmap. |
    '---------------------------------------------------'
    r4.Top = udtPlayers(i).Animation * 32
    r4.Bottom = r4.Top + 32
    r4.Left = udtPlayers(i).AnimationFrame * 32
    r4.Right = r4.Left + 32

    If udtPlayers(i).ReverseFlag Then
        mbltfx.lDDFX = DDBLTFX_MIRRORLEFTRIGHT
        DDS_Back.BltFx r3, DDS_Character1, r4, DDBLT_KEYSRC Or DDBLT_DDFX, mbltfx
    Else '(i.e. facing right)
        DDS_Back.Blt r3, DDS_Character1, r4, DDBLT_KEYSRC
    End If

End Sub


Public Sub DrawCharacter()

    AnimateCharacter    'animate character.

'----------------------------------------------.
'This draws the character onto the backbuffer. |
'----------------------------------------------'

    Dim r3 As RECT, r4 As RECT
    Dim mbltfx As DDBLTFX
    
    '--------------------------------------------.
    'This sets the rectangle so we paint the guy |
    'in the middle of the screen.                |
    '--------------------------------------------'
    
    r3.Bottom = 120 + 16
    r3.Top = r3.Bottom - 32
    r3.Left = 160 - 16
    r3.Right = r3.Left + 32

    r4.Top = CHARACTER.Animation * 32
    r4.Bottom = r4.Top + 32
    r4.Left = CHARACTER.ANIMATIONNUM * 32
    r4.Right = r4.Left + 32
    
    '-------------------.
    'Paint the bastard! |
    '-------------------'
    If CHARACTER.GOTSUIT Then
        If ReverseFlag Then
            mbltfx.lDDFX = DDBLTFX_MIRRORLEFTRIGHT
            DDS_Back.BltFx r3, DDS_Character1, r4, DDBLT_KEYSRC Or DDBLT_DDFX, mbltfx
        Else '(i.e. facing right)
            DDS_Back.Blt r3, DDS_Character1, r4, DDBLT_KEYSRC
            
        End If
    Else
        If ReverseFlag Then
            mbltfx.lDDFX = DDBLTFX_MIRRORLEFTRIGHT
            DDS_Back.BltFx r3, DDS_Character1, r4, DDBLT_KEYSRC Or DDBLT_DDFX, mbltfx
        Else '(i.e. facing right)
            DDS_Back.Blt r3, DDS_Character1, r4, DDBLT_KEYSRC
            
        End If
    End If
    
End Sub

Public Sub DrawOpponents()


'----------------------------------------------.
'This draws the character onto the backbuffer. |
'----------------------------------------------'

    Dim r3 As RECT, r4 As RECT
    Dim mbltfx As DDBLTFX
    
    Dim i As Integer
    
    For i = 0 To UBound(BotClient)
    
        BotClient(i).AnimateBot
    
        '--------------------------------------------.
        'This sets the rectangle so we paint the guy |
        'in the middle of the screen.                |
        '--------------------------------------------'
        r3.Top = BotClient(i).Y - (CHARACTER.Y - 104)    'character.y
        r3.Bottom = r3.Top + 32
        r3.Left = BotClient(i).X - (CHARACTER.X - 144)   'Character.X
        r3.Right = r3.Left + 32
        '---------------------------------------------------.
        'Copy the current frame (cyclenum) from the bitmap. |
        '---------------------------------------------------'
        r4.Top = BotClient(i).Animation * 32
        r4.Bottom = r4.Top + 32
        r4.Left = BotClient(i).AnimationFrame * 32
        r4.Right = r4.Left + 32
    
        If BotClient(i).ReverseFlag Then
            mbltfx.lDDFX = DDBLTFX_MIRRORLEFTRIGHT
            DDS_Back.BltFx r3, DDS_Character1, r4, DDBLT_KEYSRC Or DDBLT_DDFX, mbltfx
        Else '(i.e. facing right)
            DDS_Back.Blt r3, DDS_Character1, r4, DDBLT_KEYSRC
        End If
        
    Next i

End Sub

Public Sub DrawLava()

    
    
    Dim rLava As RECT
    Dim rLava2 As RECT
    
    Dim X As Integer, Y As Integer, q As Long, w As Long
    
    Randomize
    
    rLava2.Top = 0
    rLava2.Bottom = 32
    
    DDS_COLLISIONMAP.Lock rTOTMAP, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
    
    For X = Int((CHARACTER.X - 144) / (32)) To Int((CHARACTER.X + 176) / (32))
    
        For Y = Int((CHARACTER.Y - 104) / (32)) To Int((CHARACTER.Y + 136) / (32))
        
            q = X * 32
            w = Y * 32
                    
            If DDS_COLLISIONMAP.GetLockedPixel(q, w) = cRed Then
            
                rLava2.Left = LAVACYCLENUM
                rLava2.Right = rLava2.Left + 32
            
                rLava.Left = q - (CHARACTER.X - 144)
                rLava.Right = rLava.Left + 32
                rLava.Top = w - (CHARACTER.Y - 104)
                rLava.Bottom = rLava.Top + 32
                
                If rLava.Left < 0 Then rLava.Left = 0
                If rLava.Right > SCRWidth Then rLava.Right = SCRWidth
                If rLava.Top < 0 Then rLava.Top = 0
                If rLava.Bottom > SCRHeight Then rLava.Bottom = SCRHeight
            
                DDS_Back.Blt rLava, DDS_Lava, rLava2, DDBLT_KEYSRC
                    
            End If
            
            DoEvents
                        
        Next Y
        
    Next X
    
    DDS_COLLISIONMAP.Unlock rTOTMAP

End Sub

Public Sub DrawJumpers()

    Dim rJ As RECT
    Dim rJ2 As RECT
    
    Dim X As Integer, Y As Integer, q As Long, w As Long
    
    Randomize
    
    rJ2.Top = 64
    rJ2.Bottom = rJ2.Top + 32
    
    DDS_COLLISIONMAP.Lock rTOTMAP, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0

    For X = Int((CHARACTER.X - 200) / (32)) To Int((CHARACTER.X + 232) / (32))
    
        For Y = Int((CHARACTER.Y - 160) / (32)) To Int((CHARACTER.Y + 192) / (32))
        
            q = X * 32
            w = Y * 32
            If X < MapWidth And X > 0 Then
                If Y < MapHeight And Y > 0 Then
                    If DDS_COLLISIONMAP.GetLockedPixel(q, w) = cBlue Then
                    
                        rJ2.Left = JUMPERCYCLENUM
                        rJ2.Right = rJ2.Left + 32
                    
                        rJ.Left = q - (CHARACTER.X - 144)
                        rJ.Right = rJ.Left + 32
                        rJ.Top = w - (CHARACTER.Y - 104)
                        rJ.Bottom = rJ.Top + 32
                        
                        Dim tmpCutL As Integer, tmpCutR As Integer, tmpCutT As Integer, tmpCutB As Integer
                        
                        'If rJ.Left < 0 Then
                        '    tmpCutL = 0 - rJ.Left
                        '    rJ.Left = 0
                        'End If
                        'If rJ.Right > 320 Then
                        '    tmpCutR = 320 - rJ.Right
                        '    rJ.Right = 320
                        'End If
                        'If rJ.Top < 0 Then
                        '    tmpCutT = 0 - rJ.Top
                        '    rJ.Top = 0
                        'End If
                        'If rJ.Bottom > 240 Then
                        '    tmpCutB = 240 - rJ.Bottom
                        '    rJ.Bottom = 240
                        'End If
                        'rJ2.Left = rJ2.Left + tmpCutL
                        'rJ2.Right = rJ2.Right + tmpCutR
                        'rJ2.Top = rJ2.Top + tmpCutT
                        'rJ2.Bottom = rJ2.Bottom + tmpCutB
                    
                        DDS_Back.Blt rJ, DDS_MapObjects, rJ2, DDBLT_KEYSRC
                            
                    End If
                    
                    DoEvents
                End If
            End If
                        
        Next Y
        
    Next X
    
    DDS_COLLISIONMAP.Unlock rTOTMAP

End Sub

Public Sub DrawExtraItems(tmpC As Integer)
            
    Dim rJ As RECT
    Dim rJ2 As RECT
    Dim X As Integer, Y As Integer, q As Long, w As Long
    
    Dim tmpCutL As Integer, tmpCutR As Integer, tmpCutT As Integer, tmpCutB As Integer

    rJ2.Top = 0
    rJ2.Bottom = rJ2.Top + ExtraItem(tmpC).itAnimHeight
    rJ2.Left = ExtraItem(tmpC).itAnimPos * ExtraItem(tmpC).itAnimWidth
    rJ2.Right = rJ2.Left + ExtraItem(tmpC).itAnimWidth

    rJ.Left = ExtraItem(tmpC).itX - (CHARACTER.X - 144)
    rJ.Right = rJ.Left + ExtraItem(tmpC).itAnimWidth
    rJ.Top = ExtraItem(tmpC).itY - (CHARACTER.Y - 104)
    rJ.Bottom = rJ.Top + ExtraItem(tmpC).itAnimHeight
                    
    If rJ.Left < 0 Then
        tmpCutL = -rJ.Left
        rJ.Left = 0
    End If
    If rJ.Right > SCRWidth Then
        tmpCutR = SCRWidth - rJ.Right
        rJ.Right = SCRWidth
    End If
    If rJ.Top < 0 Then
        tmpCutT = -rJ.Top
        rJ.Top = 0
    End If
    If rJ.Bottom > SCRHeight Then
        tmpCutB = SCRHeight - rJ.Bottom
        rJ.Bottom = SCRHeight
    End If
    rJ2.Left = rJ2.Left + tmpCutL
    rJ2.Right = rJ2.Right + tmpCutR
    rJ2.Top = rJ2.Top + tmpCutT
    rJ2.Bottom = rJ2.Bottom + tmpCutB

    DDS_Back.Blt rJ, DDS_EXTRAITEM(ExtraItem(tmpC).itType), rJ2, DDBLT_KEYSRC
    'DoEvents

End Sub

Public Sub DrawFlags()

    Dim RBAPACK As RECT
    Dim rBAPack2 As RECT
    
    Dim q As Long, w As Long, i As Integer
                                
        'blue
            rBAPack2.Top = 32
            rBAPack2.Bottom = rBAPack2.Top + 32
                  
            If obj_FlagBlue.Spawned Then
            
                rBAPack2.Left = obj_FlagBlue.AnimationFrame
                rBAPack2.Right = rBAPack2.Left + 32
            
                RBAPACK.Left = obj_FlagBlue.X - (CHARACTER.X - 144)
                RBAPACK.Right = RBAPACK.Left + 32
                RBAPACK.Top = obj_FlagBlue.Y - (CHARACTER.Y - 104)
                RBAPACK.Bottom = RBAPACK.Top + 32
            
                DDS_Back.Blt RBAPACK, DDS_MapObjects, rBAPack2, DDBLT_KEYSRC

            End If
            
        'red
            rBAPack2.Top = 0
            rBAPack2.Bottom = rBAPack2.Top + 32
                  
            If obj_FlagRed.Spawned Then
            
                rBAPack2.Left = obj_FlagRed.AnimationFrame
                rBAPack2.Right = rBAPack2.Left + 32
            
                RBAPACK.Left = obj_FlagRed.X - (CHARACTER.X - 144)
                RBAPACK.Right = RBAPACK.Left + 32
                RBAPACK.Top = obj_FlagRed.Y - (CHARACTER.Y - 104)
                RBAPACK.Bottom = RBAPACK.Top + 32
            
                DDS_Back.Blt RBAPACK, DDS_MapObjects, rBAPack2, DDBLT_KEYSRC

            End If
            
            DoEvents
            
End Sub




Public Sub DrawHealthPack()
    
    Dim rHPack As RECT
    Dim rHPack2 As RECT
    
    Dim q As Long, w As Long, i As Integer
        
    rHPack2.Top = 0
    rHPack2.Bottom = 32
                        
        For i = 0 To obj_HealthPackCount - 1
                  
            If obj_HealthPack(i).Spawned Then
            
                rHPack2.Left = obj_HealthPack(i).AnimationFrame
                rHPack2.Right = rHPack2.Left + 32
            
                rHPack.Left = obj_HealthPack(i).X - (CHARACTER.X - 144)
                rHPack.Right = rHPack.Left + 32
                rHPack.Top = obj_HealthPack(i).Y - (CHARACTER.Y - 104)
                rHPack.Bottom = rHPack.Top + 32
            
                DDS_Back.Blt rHPack, DDS_Objects, rHPack2, DDBLT_KEYSRC

            End If
            
            DoEvents
            
        Next i
                        
End Sub

Public Sub DrawMegaHealthPack()
    
    Dim rHPack As RECT
    Dim rHPack2 As RECT
    
    Dim q As Long, w As Long, i As Integer
        
    rHPack2.Top = 480
    rHPack2.Bottom = rHPack2.Top + 32
                        
        For i = 0 To obj_MegaHealthPackCount - 1
                  
            If obj_MegaHealthPack(i).Spawned Then
            
                rHPack2.Left = obj_MegaHealthPack(i).AnimationFrame
                rHPack2.Right = rHPack2.Left + 32
            
                rHPack.Left = obj_MegaHealthPack(i).X - (CHARACTER.X - 144)
                rHPack.Right = rHPack.Left + 32
                rHPack.Top = obj_MegaHealthPack(i).Y - (CHARACTER.Y - 104)
                rHPack.Bottom = rHPack.Top + 32
            
                DDS_Back.Blt rHPack, DDS_Objects, rHPack2, DDBLT_KEYSRC

            End If
            
            DoEvents
            
        Next i
                        
End Sub

Public Sub DrawBlasterAmmoPack()
    
                        
End Sub


Public Sub DrawGrenadesAmmoPack()
    
    Dim RBAPACK As RECT
    Dim rBAPack2 As RECT
    
    Dim q As Long, w As Long, i As Integer
        
    rBAPack2.Top = 96
    rBAPack2.Bottom = rBAPack2.Top + 32
                        
        For i = 0 To obj_GrenadesAmmoCount - 1
                  
            If obj_GrenadesAmmo(i).Spawned Then
            
                rBAPack2.Left = obj_GrenadesAmmo(i).AnimationFrame
                rBAPack2.Right = rBAPack2.Left + 32
            
                RBAPACK.Left = obj_GrenadesAmmo(i).X - (CHARACTER.X - 144)
                RBAPACK.Right = RBAPACK.Left + 32
                RBAPACK.Top = obj_GrenadesAmmo(i).Y - (CHARACTER.Y - 104)
                RBAPACK.Bottom = RBAPACK.Top + 32
            
                DDS_Back.Blt RBAPACK, DDS_Objects, rBAPack2, DDBLT_KEYSRC

            End If
            
            DoEvents
            
        Next i
                        
End Sub

Public Sub DrawMinesAmmoPack()
    
    Dim RBAPACK As RECT
    Dim rBAPack2 As RECT
    
    Dim q As Long, w As Long, i As Integer
        
    rBAPack2.Top = 160
    rBAPack2.Bottom = rBAPack2.Top + 32
                        
        For i = 0 To obj_MinesAmmoCount - 1
                  
            If obj_MinesAmmo(i).Spawned Then
            
                rBAPack2.Left = obj_MinesAmmo(i).AnimationFrame
                rBAPack2.Right = rBAPack2.Left + 32
            
                RBAPACK.Left = obj_MinesAmmo(i).X - (CHARACTER.X - 144)
                RBAPACK.Right = RBAPACK.Left + 32
                RBAPACK.Top = obj_MinesAmmo(i).Y - (CHARACTER.Y - 104)
                RBAPACK.Bottom = RBAPACK.Top + 32
            
                DDS_Back.Blt RBAPACK, DDS_Objects, rBAPack2, DDBLT_KEYSRC

            End If
            
            DoEvents
            
        Next i
                        
End Sub

Public Sub DrawRailgunPack()
    
    Dim RBAPACK As RECT
    Dim rBAPack2 As RECT
    
    Dim q As Long, w As Long, i As Integer
        
    rBAPack2.Top = 288
    rBAPack2.Bottom = rBAPack2.Top + 32
                        
        For i = 0 To obj_RailgunCount - 1
                  
            If obj_Railgun(i).Spawned Then
            
                rBAPack2.Left = obj_Railgun(i).AnimationFrame
                rBAPack2.Right = rBAPack2.Left + 32
            
                RBAPACK.Left = obj_Railgun(i).X - (CHARACTER.X - 144)
                RBAPACK.Right = RBAPACK.Left + 32
                RBAPACK.Top = obj_Railgun(i).Y - (CHARACTER.Y - 104)
                RBAPACK.Bottom = RBAPACK.Top + 32
            
                DDS_Back.Blt RBAPACK, DDS_Objects, rBAPack2, DDBLT_KEYSRC

            End If
            
            DoEvents
            
        Next i
                        
End Sub

Public Sub DrawTelePort()

'on local error Resume Next
    
    Dim rJ As RECT
    Dim rJ2 As RECT
    
    Dim X As Integer, Y As Integer, q As Long, w As Long
    
    Randomize
    
    rJ2.Top = 96
    rJ2.Bottom = rJ2.Top + 32
    
    DDS_COLLISIONMAP.Lock rTOTMAP, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0

    For X = Int((CHARACTER.X - 200) / (32)) To Int((CHARACTER.X + 232) / (32))
    
        For Y = Int((CHARACTER.Y - 160) / (32)) To Int((CHARACTER.Y + 192) / (32))
        
            q = X * 32
            w = Y * 32
            If X < MapWidth And X > 0 Then
                If Y < MapHeight And Y > 0 Then
                    If DDS_COLLISIONMAP.GetLockedPixel(q, w) = RGB(128, 128, 128) Then
                    
                        rJ2.Left = TELEPORTANIMNUM
                        rJ2.Right = rJ2.Left + 32
                    
                        rJ.Left = q - (CHARACTER.X - 144)
                        rJ.Right = rJ.Left + 32
                        rJ.Top = w - (CHARACTER.Y - 104)
                        rJ.Bottom = rJ.Top + 32
                        
                        If rJ.Left < 0 Then rJ.Left = 0
                        If rJ.Right > SCRWidth Then rJ.Right = SCRWidth
                        If rJ.Top < 0 Then rJ.Top = 0
                        If rJ.Bottom > SCRHeight Then rJ.Bottom = SCRHeight
                    
                        DDS_Back.Blt rJ, DDS_MapObjects, rJ2, DDBLT_KEYSRC
                            
                    End If
                    
                    DoEvents
                End If
            End If
                        
        Next Y
        
    Next X
    
    DDS_COLLISIONMAP.Unlock rTOTMAP

End Sub



Public Sub AnimateStuff()

    lTickCount8 = GetTickCount()
    
    If (lTickCount8 - lOldTickCount8) > 50 Then
        'Save the tick count
        lOldTickCount8 = GetTickCount
        
        JUMPERCYCLENUM = JUMPERCYCLENUM + 32
        If JUMPERCYCLENUM >= 128 Then
            JUMPERCYCLENUM = 0
        End If
        TELEPORTANIMNUM = TELEPORTANIMNUM + 32
        If TELEPORTANIMNUM >= 416 Then
            TELEPORTANIMNUM = 0
        End If
        
        obj_FlagBlue.AnimationFrame = obj_FlagBlue.AnimationFrame + 32
        If obj_FlagBlue.AnimationFrame >= 256 Then obj_FlagBlue.AnimationFrame = 0
        obj_FlagRed.AnimationFrame = obj_FlagRed.AnimationFrame + 32
        If obj_FlagRed.AnimationFrame >= 256 Then obj_FlagRed.AnimationFrame = 0
        
        If ExtraItems >= 1 Then
            Dim tmpE As Integer
            For tmpE = 0 To ExtraItems - 1
                ExtraItem(tmpE).itAnimPos = ExtraItem(tmpE).itAnimPos + 1
                If ExtraItem(tmpE).itAnimPos >= ExtraItem(tmpE).itAnimLen Then ExtraItem(tmpE).itAnimPos = 0
            Next tmpE
        End If
        
        ObjectAnimationFrame = ObjectAnimationFrame + 32
        If ObjectAnimationFrame >= 256 Then ObjectAnimationFrame = 0
        
        Dim i As Integer
        If MineIndex > 0 Then
            For i = 0 To MineIndex
                Mine(i).AnimationFrame = Mine(i).AnimationFrame + 1
                If Mine(i).AnimationFrame >= 32 Then Mine(i).AnimationFrame = 0
            Next i
        End If
        
    End If

End Sub

Public Sub AnimateCharacter(Optional inCredits As Boolean = False, Optional inCreditsFire As Boolean = False)

'------------------------------------------.
'This controls the animations of the game. |
'------------------------------------------'

    '---------------------------------------------------.
    'Control the looping speed with tickcount function. |
    '---------------------------------------------------'
    lTickCount = GetTickCount()
    
    Dim tmpslow As Integer
    If CHARACTER.FIRING = True Then
        tmpslow = 50
    Else
        tmpslow = 50
    End If
    
    If (lTickCount - lOldTickCount) > tmpslow Then
        'Save the tick count
        lOldTickCount = GetTickCount
        
        'IN CREDITS -------------------------------------------------------------------------------------#
        If inCredits Then                                                                               '#
            If inCreditsFire Then                                                                       '#
                CHARACTER.Animation = FIRING                                                            '#
                CHARACTER.ANIMATIONLENGTH = 7                                                           '#
                CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1                                     '#
                If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then                             '#
                    CHARACTER.Animation = STANDING                                                      '#
                    CHARACTER.ANIMATIONNUM = 0                                                          '#
                    tmpFire = True                                                                      '#
                End If                                                                                  '#
            Else                                                                                        '#
                CHARACTER.Animation = RUNNING                                                           '#
                CHARACTER.ANIMATIONLENGTH = 8                                                           '#
                CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1                                     '#
                If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then CHARACTER.ANIMATIONNUM = 0  '#
            End If                                                                                      '#
        Else  '------------------------------------------------------------------------------------------#
        
        'NOT CREDITS --->
        If MoveLeft = True Then
            If ReverseFlag = False Then
                If CHARACTER.FIRING = False Then
                    If CHARACTER.CROUCHING Then
                        CHARACTER.Animation = CROUCHING
                        CHARACTER.ANIMATIONLENGTH = 9
                        CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                        If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then CHARACTER.ANIMATIONNUM = 0
                    Else
                        CHARACTER.Animation = RUNNING
                        CHARACTER.ANIMATIONLENGTH = 8
                        CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM - 1
                        If CHARACTER.ANIMATIONNUM < 0 Then CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONLENGTH - 1
                    End If
                ElseIf CHARACTER.FIRING = True Then
                    CHARACTER.Animation = FIRINGRUNNINGBACKWARDS
                    CHARACTER.ANIMATIONLENGTH = 8
                    CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                    
                    If SelectedWeapon = Blaster Then
                        If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH / 2 Then CHARACTER.FIRING = False
                    End If
                    
                    If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then
                        CHARACTER.FIRING = False
                        CHARACTER.ANIMATIONNUM = 0
                    End If
                End If
            Else
                If CHARACTER.FIRING = False Then
                    If CHARACTER.CROUCHING Then
                        CHARACTER.Animation = CROUCHING
                        CHARACTER.ANIMATIONLENGTH = 9
                        CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM - 1
                        If CHARACTER.ANIMATIONNUM < 0 Then CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONLENGTH - 1
                    Else
                        CHARACTER.Animation = RUNNING
                        CHARACTER.ANIMATIONLENGTH = 8
                        CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                        If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then CHARACTER.ANIMATIONNUM = 0
                    End If
                ElseIf CHARACTER.FIRING = True Then
                    'If mintMouseAngle > CSng(PI / 6) Then
                    '    CHARACTER.Animation = FIRINGRUNNING
                    'ElseIf mintMouseAngle > CSng(PI / 4) Then
                    '    CHARACTER.Animation = FIRINGRUNNING
                    'ElseIf mintMouseAngle > CSng(PI / 3) Then
                    '    CHARACTER.Animation = FIRINGRUNNING90
                    'Else
                        CHARACTER.Animation = FIRINGRUNNING
                    'End If
                    CHARACTER.ANIMATIONLENGTH = 8
                    CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                    
                    If SelectedWeapon = Blaster Then
                        If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH / 2 Then CHARACTER.FIRING = False
                    End If
                    
                    If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then
                        CHARACTER.FIRING = False
                        CHARACTER.ANIMATIONNUM = 0
                    End If
                End If
            End If
        ElseIf MoveRight = True Then
            If ReverseFlag = False Then
                If CHARACTER.FIRING = False Then
                    If CHARACTER.CROUCHING Then
                        CHARACTER.Animation = CROUCHING
                        CHARACTER.ANIMATIONLENGTH = 9
                        CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                        If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then CHARACTER.ANIMATIONNUM = 0
                    Else
                        CHARACTER.Animation = RUNNING
                        CHARACTER.ANIMATIONLENGTH = 8
                        CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                        If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then CHARACTER.ANIMATIONNUM = 0
                    End If
                ElseIf CHARACTER.FIRING = True Then
                    'If mintMouseAngle > CSng(PI / 6) Then
                    '    CHARACTER.Animation = FIRINGRUNNING
                    'ElseIf mintMouseAngle > CSng(PI / 4) Then
                    '    CHARACTER.Animation = FIRINGRUNNING
                    'ElseIf mintMouseAngle < CSng(PI / 3) Then
                    '    CHARACTER.Animation = FIRINGRUNNING90
                    'Else
                        CHARACTER.Animation = FIRINGRUNNING
                    'End If
                    CHARACTER.ANIMATIONLENGTH = 8
                    CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                    
                    If SelectedWeapon = Blaster Then
                        If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH / 2 Then CHARACTER.FIRING = False
                    End If
                
                    If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then
                        CHARACTER.FIRING = False
                        CHARACTER.ANIMATIONNUM = 0
                    End If
                End If
            Else
                If CHARACTER.FIRING = False Then
                    If CHARACTER.CROUCHING Then
                        CHARACTER.Animation = CROUCHING
                        CHARACTER.ANIMATIONLENGTH = 9
                        CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM - 1
                        If CHARACTER.ANIMATIONNUM < 0 Then CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONLENGTH - 1
                    Else
                        CHARACTER.Animation = RUNNING
                        CHARACTER.ANIMATIONLENGTH = 8
                        CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM - 1
                        If CHARACTER.ANIMATIONNUM < 0 Then CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONLENGTH - 1
                    End If
                ElseIf CHARACTER.FIRING = True Then
                    CHARACTER.Animation = FIRINGRUNNINGBACKWARDS
                    CHARACTER.ANIMATIONLENGTH = 8
                    CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                    
                    If SelectedWeapon = Blaster Then
                        If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH / 2 Then CHARACTER.FIRING = False
                    End If
                    
                    If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then
                        CHARACTER.FIRING = False
                        CHARACTER.ANIMATIONNUM = 0
                    End If
                End If
            End If
        Else
            If CHARACTER.FIRING = True Then
                CHARACTER.Animation = FIRING
                CHARACTER.ANIMATIONLENGTH = 6
                CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                If SelectedWeapon = Blaster Then
                    If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH / 2 Then CHARACTER.FIRING = False
                End If
                If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then
                    CHARACTER.ANIMATIONNUM = 0
                    CHARACTER.FIRING = False
                End If
            ElseIf CHARACTER.CROUCHING Then
                    CHARACTER.Animation = CROUCHING
                    CHARACTER.ANIMATIONLENGTH = 9
                    CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM
                    If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then CHARACTER.ANIMATIONNUM = 0
            Else
                CHARACTER.Animation = STANDING
                CHARACTER.ANIMATIONLENGTH = 6
                CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
                If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then CHARACTER.ANIMATIONNUM = 0
            End If
        End If
        
            
        
        End If
        
        'CHARACTER.ANIMATIONNUM = CHARACTER.ANIMATIONNUM + 1
        
        '----------------------------.
        'If character is not moving, |
        'the frame will be 0.        |
        '----------------------------'
        'CHARACTER.Animation = RUNNING    'running model
        'CHARACTER.ANIMATIONLENGTH = 10   '10 frames
        
        'If CHARACTER.ANIMATIONNUM >= CHARACTER.ANIMATIONLENGTH Then CHARACTER.ANIMATIONNUM = 0
            
    End If
        
End Sub



Public Sub AnimateCrosshair()

'------------------------------------------.
'This controls the animations of the game. |
'------------------------------------------'

    '---------------------------------------------------.
    'Control the looping speed with tickcount function. |
    '---------------------------------------------------'
    lTickCount5 = GetTickCount()
    
    If (lTickCount5 - lOldTickCount5) > 70 Then
        'Save the tick count
        lOldTickCount5 = GetTickCount
        
        '-------------------.
        'Select next frame. |
        '-------------------'
        
        CHARACTER.CROSSHAIRNUM = CHARACTER.CROSSHAIRNUM + 1
        
        If CHARACTER.CROSSHAIR = 0 Or CHARACTER.CROSSHAIR = 3 Then
            If CHARACTER.CROSSHAIRNUM >= 7 Then CHARACTER.CROSSHAIRNUM = 0
        Else
            If CHARACTER.CROSSHAIRNUM >= 8 Then CHARACTER.CROSSHAIRNUM = 0
        End If

    End If
        
End Sub

Public Sub DrawMap()

'--------------------------------------------------.
'This procedure draws the map onto the backbuffer. |
'--------------------------------------------------'

    '-----------------------------------------.
    'Some necessary variables and rectangles. |
    '-----------------------------------------'
    Dim q As Long, w As Long, Q2 As Long, W2 As Long
    Dim qfix As Long, wfix As Long, qfix2 As Long, wfix2 As Long
    
    Dim r As RECT, r2 As RECT, r3 As RECT
        
    q = CHARACTER.X - (160 - 16)
    w = CHARACTER.Y - (120 - 16)
    Q2 = CHARACTER.X + (160 + 16)
    W2 = CHARACTER.Y + (120 + 16)
    
    If q < 0 Then
        qfix = -q
    Else
        qfix = 0
    End If
    If Q2 > (MapWidth * 32) Then
        qfix2 = 320 - (Q2 - (MapWidth * 32))
    Else
        qfix2 = 320
    End If
    
    If w < 0 Then
        wfix = -w
    Else
        wfix = 0
    End If
    If W2 > (MapHeight * 32) Then
        wfix2 = 240 - (W2 - (MapHeight * 32))
    Else
        wfix2 = 240
    End If
        
            '----------------------------.
            'Where the heck will it go?! |
            '----------------------------'
            r.Left = qfix
            r.Top = wfix
            r.Right = qfix2
            r.Bottom = wfix2
            
            If r.Top < 0 Then r.Top = 0
            If r.Right > SCRWidth Then r.Right = SCRWidth
            If r.Left < 0 Then r.Left = 0
            If r.Bottom > SCRHeight Then r.Bottom = SCRHeight
                
            '--------------.
            'What to grab. |
            '--------------'
            rMAPCUT.Left = q
            rMAPCUT.Top = w
            rMAPCUT.Right = Q2
            rMAPCUT.Bottom = W2
            
            If rMAPCUT.Bottom > (MapHeight * 32) Then rMAPCUT.Bottom = (MapHeight * 32)
            If rMAPCUT.Right > (MapWidth * 32) Then rMAPCUT.Right = (MapWidth * 32)
            If rMAPCUT.Left < 0 Then rMAPCUT.Left = 0
            If rMAPCUT.Top < 0 Then rMAPCUT.Top = 0
            
            '-------.
            'Paint. |
            '-------'
            DDS_Back.Blt r, DDS_MAP, rMAPCUT, DDBLT_KEYSRC

End Sub

Public Sub CreateGuidemapSurface()
        
    Dim ddckey As DDCOLORKEY

    'Now let's set the surface description
    Set DDS_GuideMap = Nothing
    
    DDSD_GuideMap.lFlags = DDSD_CAPS Or DDSD_WIDTH Or DDSD_HEIGHT
    DDSD_GuideMap.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    DDSD_GuideMap.lWidth = MapWidth
    DDSD_GuideMap.lHeight = MapHeight
    'now create the other off-screen surface
    Set DDS_GuideMap = DD.CreateSurface(DDSD_GuideMap)
    ddckey.low = 0: ddckey.high = 0
    DDS_GuideMap.SetColorKey DDCKEY_SRCBLT, ddckey
    
    HUD.SIZE_GUIDEMAP.Left = 0
    HUD.SIZE_GUIDEMAP.Right = MapWidth
    HUD.SIZE_GUIDEMAP.Top = 0
    HUD.SIZE_GUIDEMAP.Bottom = MapHeight
        
    HUD.SIZE_GUIDEMAP2.Left = 320 - (MapWidth * 2)
    HUD.SIZE_GUIDEMAP2.Right = 320
    HUD.SIZE_GUIDEMAP2.Top = 0
    HUD.SIZE_GUIDEMAP2.Bottom = MapHeight * 2
        
    GuidemapSurfaceCreated = True

End Sub

Public Sub CreateGuideMap(cx As Long, cy As Long)

'on local error GoTo Shutdowner

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
        
    DDS_COLLISIONMAP.Unlock rTOTMAP
        
    GuidemapSurfaceCreated = True
                        
Exit Sub

Shutdowner:
    
    ShutdownNoErrorFlag = False
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: CREATING GUIDEMAP"
    Shutdown
    
End Sub

Public Sub SaveScreenDump()

    Set frmScreenshot.Picture = Nothing
    
    Dim r As RECT, r2 As RECT
    r.Left = 0
    r.Right = 320
    r.Top = 0
    r.Bottom = 240
    r2.Left = 0
    r2.Right = 320
    r2.Top = 0
    r2.Bottom = 240
    
    frmScreenshot.tmpPic.Width = 320
    frmScreenshot.tmpPic.Height = 240
    
    SSCount = SSCount + 1
    
    Dim tmpSPCR As String
    tmpSPCR = "00000"
    If SSCount > 9 Then tmpSPCR = Left(tmpSPCR, 4)
    If SSCount > 99 Then tmpSPCR = Left(tmpSPCR, 3)
    If SSCount > 999 Then tmpSPCR = Left(tmpSPCR, 2)
    If SSCount > 9999 Then tmpSPCR = Left(tmpSPCR, 1)
    
    DDS_Primary.BltToDC frmScreenshot.tmpPic.hDC, r, r2
    SavePicture frmScreenshot.tmpPic.Image, App.Path & "\screenshots\" & tmpSPCR & SSCount & ".bmp"
    
    cCmdFeed "SCREENSHOT WRITTEN TO \SCREENSHOTS\" & tmpSPCR & SSCount & ".bmp", True

End Sub

Public Sub SetCrosshairColor(cRed As Integer, cGreen As Integer, cBlue As Integer)

Dim a As Long, b As Long, tmp As Long, tmpr As RECT

tmpr.Left = 0
tmpr.Right = 72
tmpr.Top = 0
tmpr.Bottom = 90

    DDS_Crosshair.Lock tmpr, DDSD_Crosshair, DDLOCK_WAIT, 0
    For a = 0 To 72
        For b = 0 To 90
            tmp = DDS_Crosshair.GetLockedPixel(a, b)
            If tmp <> 0 Then
                DDS_Crosshair.SetLockedPixel a, b, RGB(cBlue, cGreen, cRed)
            End If
            
            DoEvents
            
        Next b
        
        DoEvents
        
    Next a
    DDS_Crosshair.Unlock tmpr

End Sub


'For Gamma Support:
Public Function ConvToSignedValue(lngValue As Long) As Integer

    'Cheezy method for converting to signed integer
    If lngValue <= 32767 Then
        ConvToSignedValue = CInt(lngValue)
        Exit Function
    End If
    
    ConvToSignedValue = CInt(lngValue - 65535)

End Function

Public Function ConvToUnSignedValue(intValue As Integer) As Long

    'Cheezy method for converting to unsigned integer
    If intValue >= 0 Then
        ConvToUnSignedValue = intValue
        Exit Function
    End If
    
    ConvToUnSignedValue = intValue + 65535

End Function

Public Sub SetGamma(intRed As Integer, intGreen As Integer, intBlue As Integer)

Dim i As Integer

    'Alter the gamma ramp to the percent given by comparing to original state
    'A value of zero ("0") for intRed, intGreen, or intBlue will result in the
    'gamma level being set back to the original levels. Anything ABOVE zero will
    'fade towards FULL colour, anything below zero will fade towards NO colour
    For i = 0 To 255
        If intRed < 0 Then GammaRamp.red(i) = ConvToSignedValue(ConvToUnSignedValue(OriginalRamp.red(i)) * (100 - Abs(intRed)) / 100)
        If intRed = 0 Then GammaRamp.red(i) = OriginalRamp.red(i)
        If intRed > 0 Then GammaRamp.red(i) = ConvToSignedValue(65535 - ((65535 - ConvToUnSignedValue(OriginalRamp.red(i))) * (100 - intRed) / 100))
        If intGreen < 0 Then GammaRamp.green(i) = ConvToSignedValue(ConvToUnSignedValue(OriginalRamp.green(i)) * (100 - Abs(intGreen)) / 100)
        If intGreen = 0 Then GammaRamp.green(i) = OriginalRamp.green(i)
        If intGreen > 0 Then GammaRamp.green(i) = ConvToSignedValue(65535 - ((65535 - ConvToUnSignedValue(OriginalRamp.green(i))) * (100 - intGreen) / 100))
        If intBlue < 0 Then GammaRamp.blue(i) = ConvToSignedValue(ConvToUnSignedValue(OriginalRamp.blue(i)) * (100 - Abs(intBlue)) / 100)
        If intBlue = 0 Then GammaRamp.blue(i) = OriginalRamp.blue(i)
        If intBlue > 0 Then GammaRamp.blue(i) = ConvToSignedValue(65535 - ((65535 - ConvToUnSignedValue(OriginalRamp.blue(i))) * (100 - intBlue) / 100))
        
        DoEvents
        
    Next
    GammaControler.SetGammaRamp DDSGR_DEFAULT, GammaRamp

End Sub

Public Sub Gamma_INIT()

    'Make a new gamma controler
    Set GammaControler = DDS_Primary.GetDirectDrawGammaControl
    'Fill out the original gamma ramps
    GammaControler.GetGammaRamp DDSGR_DEFAULT, OriginalRamp

End Sub

Public Sub LoadSurfaces()

    Dim ddckey As DDCOLORKEY
    
    
'---------------.
'DOOR SURFACE!! |
'---------------'
    'Now let's set the surface description
    DDSD_WEAP.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_WEAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_WEAP.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_WEAP = DD.CreateSurfaceFromFile(App.Path & "\gfx\models\weapon\various.bmp", DDSD_WEAP)
    ddckey.low = 0: ddckey.high = 0
    DDS_WEAP.SetColorKey DDCKEY_SRCBLT, ddckey
    
'-------------------.
'MAPTILES SURFACE!! |
'-------------------'
    'Now let's set the surface description
    DDSD_MAPTILES.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MAPTILES.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MAPTILES.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_MAPTILES = DD.CreateSurfaceFromFile(App.Path & "\gfx\models\maptiles.bmp", DDSD_MAPTILES)
    ddckey.low = 0: ddckey.high = 0
    DDS_MAPTILES.SetColorKey DDCKEY_SRCBLT, ddckey
    
'-------------------.
'COLTILES SURFACE!! |
'-------------------'
    'Now let's set the surface description
    DDSD_COLTILES.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_COLTILES.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_COLTILES.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_COLTILES = DD.CreateSurfaceFromFile(App.Path & "\gfx\models\coltiles.bmp", DDSD_COLTILES)
    ddckey.low = 0: ddckey.high = 0
    DDS_COLTILES.SetColorKey DDCKEY_SRCBLT, ddckey
                                      
'-------------------.
'GUIDEMAP SURFACE!! |
'-------------------'
    'Now let's set the surface description
    DDSD_Guide.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_Guide.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_Guide.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_Guide = DD.CreateSurfaceFromFile(App.Path & "\gfx\map\guide.bmp", DDSD_Guide)
    ddckey.low = 0: ddckey.high = 0
    DDS_Guide.SetColorKey DDCKEY_SRCBLT, ddckey
            
'----------------------.
'CHARACTER 1 SURFACE!! |
'----------------------'
    'Now let's set the surface description
    DDSD_Character1.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_Character1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_Character1.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_Character1 = DD.CreateSurfaceFromFile(App.Path & "\gfx\models\character1.bmp", DDSD_Character1)
    ddckey.low = 0: ddckey.high = 0
    DDS_Character1.SetColorKey DDCKEY_SRCBLT, ddckey
    
'----------------------.
'CHARACTER 2 SURFACE!! |
'----------------------'
    'Now let's set the surface description
    DDSD_Character2.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_Character2.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_Character2.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_Character2 = DD.CreateSurfaceFromFile(App.Path & "\gfx\models\character2.bmp", DDSD_Character2)
    ddckey.low = 0: ddckey.high = 0
    DDS_Character2.SetColorKey DDCKEY_SRCBLT, ddckey
    

    
    
    
    
    
    

    
    
'--------------------.
'LAVA SURFACE!!!!!!! |
'--------------------'
    'Now let's set the surface description
    DDSD_Lava.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_Lava.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_Lava.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_Lava = DD.CreateSurfaceFromFile(App.Path & "\gfx\map\lava.bmp", DDSD_Lava)
    ddckey.low = 0: ddckey.high = 0
    DDS_Lava.SetColorKey DDCKEY_SRCBLT, ddckey
    LAVACYCLEMOVEVALUE = 32
    
'----------------------.
'OBJECT SURFACE!!!!!!! |
'----------------------'
    'Now let's set the surface description
    DDSD_Objects.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_Objects.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_Objects.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_Objects = DD.CreateSurfaceFromFile(App.Path & "\gfx\models\objects.bmp", DDSD_Objects)
    ddckey.low = 0: ddckey.high = 0
    DDS_Objects.SetColorKey DDCKEY_SRCBLT, ddckey


'-------------------------.
'MAPOBJECT SURFACE!!!!!!! |
'-------------------------'
    'Now let's set the surface description
    DDSD_MapObjects.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_MapObjects.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_MapObjects.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_MapObjects = DD.CreateSurfaceFromFile(App.Path & "\gfx\models\mapobjects.bmp", DDSD_MapObjects)
    ddckey.low = 0: ddckey.high = 0
    DDS_MapObjects.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
'-------------.
'HUD SURFACES |
'-------------'

    'Now let's set the surface description
    DDSD_HUDTopMain.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_HUDTopMain.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_HUDTopMain.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_HUDTopMain = DD.CreateSurfaceFromFile(App.Path & "\gfx\hud\topmain.bmp", DDSD_HUDTopMain)
    ddckey.low = 0: ddckey.high = 0
    DDS_HUDTopMain.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    'Now let's set the surface description
    DDSD_HUDBottomMain.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_HUDBottomMain.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_HUDBottomMain.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_HUDBottomMain = DD.CreateSurfaceFromFile(App.Path & "\gfx\hud\bottommain.bmp", DDSD_HUDBottomMain)
    ddckey.low = 0: ddckey.high = 0
    DDS_HUDBottomMain.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    DDSD_HUDTopEnergyBar.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_HUDTopEnergyBar.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_HUDTopEnergyBar.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_HUDTopEnergyBar = DD.CreateSurfaceFromFile(App.Path & "\gfx\hud\energybar.bmp", DDSD_HUDTopEnergyBar)
    ddckey.low = 0: ddckey.high = 0
    DDS_HUDTopEnergyBar.SetColorKey DDCKEY_SRCBLT, ddckey
    
    DDSD_HUDTopAmmoBar.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_HUDTopAmmoBar.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_HUDTopAmmoBar.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_HUDTopAmmoBar = DD.CreateSurfaceFromFile(App.Path & "\gfx\hud\ammobar.bmp", DDSD_HUDTopAmmoBar)
    ddckey.low = 0: ddckey.high = 0
    DDS_HUDTopAmmoBar.SetColorKey DDCKEY_SRCBLT, ddckey
    
    DDSD_HUDTopArmorBar.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_HUDTopArmorBar.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_HUDTopArmorBar.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_HUDTopArmorBar = DD.CreateSurfaceFromFile(App.Path & "\gfx\hud\armorbar.bmp", DDSD_HUDTopArmorBar)
    ddckey.low = 0: ddckey.high = 0
    DDS_HUDTopArmorBar.SetColorKey DDCKEY_SRCBLT, ddckey
    
    DDSD_HUDTopStandingsPoint.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_HUDTopStandingsPoint.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_HUDTopStandingsPoint.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_HUDTopStandingsPoint = DD.CreateSurfaceFromFile(App.Path & "\gfx\hud\standingspoint.bmp", DDSD_HUDTopStandingsPoint)
    ddckey.low = 0: ddckey.high = 0
    DDS_HUDTopStandingsPoint.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
'----------------.
'WEAPON SURFACES |
'----------------'

    'Now let's set the surface description
    DDSD_WEAPONBLASTERBULLET.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_WEAPONBLASTERBULLET.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_WEAPONBLASTERBULLET.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_WEAPONBLASTERBULLET = DD.CreateSurfaceFromFile(App.Path & "\gfx\models\weapon\projectiles\blaster.bmp", DDSD_WEAPONBLASTERBULLET)
    ddckey.low = 0: ddckey.high = 0
    DDS_WEAPONBLASTERBULLET.SetColorKey DDCKEY_SRCBLT, ddckey
    
    
    
    
    
'CUTS
'====

    'Now let's set the surface description
    DDSD_TITLESCREEN.lFlags = DDSD_CAPS
    If UseVideoMem Then
        DDSD_TITLESCREEN.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_TITLESCREEN.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_TITLESCREEN = DD.CreateSurfaceFromFile(App.Path & "\gfx\cuts\title.bmp", DDSD_TITLESCREEN)
    ddckey.low = 0: ddckey.high = 0
    DDS_TITLESCREEN.SetColorKey DDCKEY_SRCBLT, ddckey




'Lets load all cutscenes into their screenarray.
Dim TT As Integer
For TT = 0 To 10
    'Now let's set the surface description
    CutScene(TT).SurfDesc.lFlags = DDSD_CAPS
    If UseVideoMem Then
        CutScene(TT).SurfDesc.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        CutScene(TT).SurfDesc.ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set CutScene(TT).Surf = DD.CreateSurfaceFromFile(App.Path & "\gfx\cuts\cutscene" & CStr(TT) & ".bmp", CutScene(TT).SurfDesc)
    ddckey.low = 0: ddckey.high = 0
    CutScene(TT).Surf.SetColorKey DDCKEY_SRCBLT, ddckey
Next TT


'Extra Items
For TT = 0 To 1
    'Now let's set the surface description
    DDSD_EXTRAITEM(TT).lFlags = DDSD_CAPS

    If UseVideoMem Then
        DDSD_EXTRAITEM(TT).ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN Or DDSCAPS_VIDEOMEMORY
    Else
        DDSD_EXTRAITEM(TT).ddsCaps.lCaps = DDSCAPS_OFFSCREENPLAIN
    End If
    'now create the other off-screen surface
    Set DDS_EXTRAITEM(TT) = DD.CreateSurfaceFromFile(App.Path & "\gfx\map\extra" & CStr(TT) & ".bmp", DDSD_EXTRAITEM(TT))
    ddckey.low = 0: ddckey.high = 0
    DDS_EXTRAITEM(TT).SetColorKey DDCKEY_SRCBLT, ddckey
Next TT



    rCutsScreen.Left = 0
    rCutsScreen.Right = 640
    rCutsScreen.Top = 0
    rCutsScreen.Bottom = 480
    

End Sub
