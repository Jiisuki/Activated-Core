Attribute VB_Name = "mod_HUD"
Public CrosshairSize As Integer
Public DrawFPS As Boolean

Public Type HUDSETTINGS
    SIZE_GUIDEMAP As RECT
    SIZE_GUIDEMAP2 As RECT
    SIZE_TOPMAIN As RECT
    SIZE_BOTTOMMAIN As RECT
    SIZE_ARMOR As RECT
    SIZE_LIFE As RECT
    SIZE_AMMO As RECT
    ENABLED As Boolean
    HUDCOLOR_R As Integer
    HUDCOLOR_G As Integer
    HUDCOLOR_B As Integer
End Type
Public HUD As HUDSETTINGS

Public Type WEAPONBAR_TYPE
    SIZE_FILE As RECT
End Type
Public WEAPONBAR As WEAPONBAR_TYPE

Public Sub DRAWGAMESTATS()

    Dim rGSTATS As RECT
    rGSTATS.Left = 32: rGSTATS.Right = 320 - 32
    rGSTATS.Top = 32: rGSTATS.Bottom = 240 - 32
    
    DDS_Back.BltColorFill rGSTATS, RGB(0, 0, 0)
    DDS_Back.SetForeColor RGB(255, 255, 255)
    DDS_Back.DrawBox 32, 32, 320 - 32, 240 - 32
    
    DrawText UCase("GAMESTATUS"), 160 - (CInt(Len("GAMESTATUS") / 2) * 8), 48, 0, 3
    DrawText UCase("PLAYER"), 48, 64, 0, 2
    DrawText UCase("FRAGS"), 164, 64, 0, 2
    DrawText UCase("DEATHS"), 224, 64, 0, 2
    
    Dim i As Integer
    
    If GAMEMODE = TRAINING_BOTPLAY Then
        DrawText UCase(CHARACTER.name), 48, 72, 0
        DrawText UCase(CHARACTER.Frags), 164, 72, 0
        DrawText UCase(CHARACTER.DEATH), 224, 72, 0
        
        For i = 0 To UBound(BotClient)
            DrawText UCase(BotClient(i).NickName), 48, 80 + (8 * i), 0
            DrawText UCase(BotClient(i).Frags), 164, 80 + (8 * i), 0
            DrawText UCase(BotClient(i).Deaths), 224, 80 + (8 * i), 0
        Next i
    End If
    
    If NetworkStatus = SUCCESS Then
        For i = 0 To UBound(udtPlayers)
            DrawText UCase(udtPlayers(i).NickName), 48, 80 + (8 * i), 0
            DrawText UCase(udtPlayers(i).Frags), 164, 80 + (8 * i), 0
            DrawText UCase(udtPlayers(i).Deaths), 224, 80 + (8 * i), 0
        Next i
    Else
        DrawText UCase(CHARACTER.name), 48, 72, 0
        DrawText UCase(CHARACTER.Frags), 164, 72, 0
        DrawText UCase(CHARACTER.DEATH), 224, 72, 0
    End If
    
End Sub

Public Sub HUD_INIT()
    
    HUD.HUDCOLOR_R = 0
    HUD.HUDCOLOR_G = 128
    HUD.HUDCOLOR_B = 255
    
    HUD.SIZE_TOPMAIN.Left = 0
    HUD.SIZE_TOPMAIN.Right = 320
    HUD.SIZE_TOPMAIN.Top = 0
    HUD.SIZE_TOPMAIN.Bottom = 32
    
    HUD.SIZE_BOTTOMMAIN.Left = 0
    HUD.SIZE_BOTTOMMAIN.Right = 320
    HUD.SIZE_BOTTOMMAIN.Top = 0
    HUD.SIZE_BOTTOMMAIN.Bottom = 33
            
    HUD.SIZE_ARMOR.Left = 0
    HUD.SIZE_ARMOR.Right = 23
    HUD.SIZE_ARMOR.Top = 0
    HUD.SIZE_ARMOR.Bottom = 3
    
    HUD.SIZE_LIFE.Left = 0
    HUD.SIZE_LIFE.Right = 23
    HUD.SIZE_LIFE.Top = 0
    HUD.SIZE_LIFE.Bottom = 3
    
    HUD.SIZE_AMMO.Left = 0
    HUD.SIZE_AMMO.Right = 23
    HUD.SIZE_AMMO.Top = 0
    HUD.SIZE_AMMO.Bottom = 3
    
End Sub

Public Sub DRAWGUIDEMAP()

    Dim tmf As RECT
    tmf.Left = 0
    tmf.Top = 0
    tmf.Bottom = MapHeight
    tmf.Right = MapWidth
    DDS_Back.BltFast 320 - MapWidth, 0, DDS_GuideMap, tmf, DDBLTFAST_WAIT
    
    DDS_Back.SetForeColor RGB(255, 255, 255)
    DDS_Back.DrawBox 320 - MapWidth, 0, 320, MapHeight

End Sub

Public Sub DrawHUD()
   
    Dim rGP As RECT
    
    rGP.Left = 0
    rGP.Right = 320
    rGP.Top = 207
    rGP.Bottom = 240
    DDS_Back.BltColorFill rGP, RGB(0, 0, 0)
    
    DDS_Back.BltFast 0, 207, DDS_HUDBottomMain, HUD.SIZE_BOTTOMMAIN, DDBLTFAST_SRCCOLORKEY
    
    DDS_Back.BltFast 0, 0, DDS_HUDTopMain, HUD.SIZE_TOPMAIN, DDBLTFAST_SRCCOLORKEY
    
    Dim rP As RECT
    rP.Left = 32 * 8
    rP.Right = rP.Left + 32
    rP.Top = 0
    rP.Bottom = 32
    DDS_Back.BltFast 120, 4, DDS_Character1, rP, DDBLTFAST_SRCCOLORKEY
    
    'SET BARS
    If CHARACTER.Health > 0 Then
        HUD.SIZE_LIFE.Right = 22 * (CHARACTER.Health / 1000) + 1
        If CHARACTER.Health >= 1000 Then HUD.SIZE_LIFE.Right = 23
    Else
        HUD.SIZE_LIFE.Right = 1
    End If
    
    If CHARACTER.ARMOR > 0 And CHARACTER.ARMOR <= CHARACTER.ARMORMAX Then
        HUD.SIZE_ARMOR.Right = 22 * (CHARACTER.ARMOR / CHARACTER.ARMORMAX) + 1
    Else
        HUD.SIZE_ARMOR.Right = 1
    End If
    
    
    If CHARACTER.GOTHEARTSENS Then
        rGP.Top = 192
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        DDS_Back.BltFast 288, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    If CHARACTER.GOTCAP Then
        rGP.Top = 320
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        DDS_Back.BltFast 256, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    If CHARACTER.GotShield Then
        rGP.Top = 32
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        If CHARACTER.SHIELDFLASH = False Then DDS_Back.BltFast 224, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    If CHARACTER.GOTJUMPASSIST Then
        rGP.Top = 64
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        If CHARACTER.JUMPASSISTFLASH = False Then DDS_Back.BltFast 192, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    If WeapEnergySword.GotWeapon Then
        rGP.Top = 352
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        DDS_Back.BltFast 0, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    If WeapBlaster.GotWeapon And WeapBlaster.AmmoCurrent > 0 Then
        rGP.Top = 384
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        DDS_Back.BltFast 32, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    If WeapBoingers.GotWeapon And WeapBoingers.AmmoCurrent > 0 Then
        rGP.Top = 288
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        DDS_Back.BltFast 64, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    If WeapRailgun.GotWeapon And WeapBlaster.AmmoCurrent > 0 Then
        rGP.Top = 256
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        DDS_Back.BltFast 96, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    If WeapMines.GotWeapon And WeapMines.AmmoCurrent > 0 Then
        rGP.Top = 160
        rGP.Bottom = rGP.Top + 32
        rGP.Left = ObjectAnimationFrame
        rGP.Right = rGP.Left + 32
        DDS_Back.BltFast 128, 208, DDS_Objects, rGP, DDBLTFAST_SRCCOLORKEY
    End If
    
    DDS_Back.SetForeColor RGB(230, 140, 0)
    
    Dim tmpX As Integer
    tmpX = 0
    If SelectedWeapon = Blaster Then
        HUD.SIZE_AMMO.Right = 22 * (WeapBlaster.AmmoCurrent / WeapBlaster.AMMOMAX) + 1
        tmpX = 32
        'DrawText "AMMO:   " & Str(WeapBlaster.AmmoCurrent), 8, 32, 0, 2
    ElseIf SelectedWeapon = Boingers Then
        HUD.SIZE_AMMO.Right = 22 * (WeapBoingers.AmmoCurrent / WeapBoingers.AMMOMAX) + 1
        tmpX = 64
        'DrawText "AMMO:   " & Str(WeapBoingers.AmmoCurrent), 8, 32, 0, 2
    ElseIf SelectedWeapon = EnergySword Then
        HUD.SIZE_AMMO.Right = 23
        tmpX = 0
        'DrawText "AMMO:   UNLIMITED", 8, 32, 0, 2
    ElseIf SelectedWeapon = Mines Then
        HUD.SIZE_AMMO.Right = 22 * (WeapMines.AmmoCurrent / WeapMines.AMMOMAX) + 1
        tmpX = 128
        'DrawText "AMMO:   " & Str(WeapMines.AmmoCurrent), 8, 32, 0, 2
    ElseIf SelectedWeapon = Railgun Then
        HUD.SIZE_AMMO.Right = 22 * (WeapBlaster.AmmoCurrent / WeapBlaster.AMMOMAX) + 1
        tmpX = 96
        'DrawText "AMMO:   " & Str(WeapBlaster.AmmoCurrent), 8, 32, 0, 2
    End If
        
    DDS_Back.DrawBox tmpX, 207, tmpX + 32, 241

    DDS_Back.BltFast 11, 5, DDS_HUDTopEnergyBar, HUD.SIZE_LIFE, DDBLTFAST_SRCCOLORKEY
    DDS_Back.BltFast 46, 5, DDS_HUDTopArmorBar, HUD.SIZE_ARMOR, DDBLTFAST_SRCCOLORKEY
    DDS_Back.BltFast 81, 5, DDS_HUDTopAmmoBar, HUD.SIZE_AMMO, DDBLTFAST_SRCCOLORKEY
        
    'Dim i As Integer
    'For i = 0 To UBound(udtPlayers)
    '    DrawText CStr(udtPlayers(i).X) & "," & CStr(udtPlayers(i).Y), 64, 64 + (8 * i), 0, 3
    'Next i
    If DrawFPS Then DrawText "FPS: " & CStr(FPS), 8, 64, 0, 3
    If GAMEMODE = STORYMODE Then
        DrawText "SCORE: " & CStr(StoryPlayerPoints), 4, 194, 0, 2
        If StoryPlayerLives = 1 Then
            DrawText CStr(StoryPlayerLives) & " CONTINUE", 316 - (Len(CStr(StoryPlayerLives) & " CONTINUE") * 8), 194, 0, 2
        Else
            DrawText CStr(StoryPlayerLives) & " CONTINUES", 316 - (Len(CStr(StoryPlayerLives) & " CONTINUES") * 8), 194, 0, 2
        End If
    End If
    
    If CHARACTER.GOTHEARTSENS Then
        DRAWGUIDEMAP
        DrawGuideMapPlayers
    End If

    If ChatPromt Then DrawText CStr(ChatPromtText) & ChatPromtCursor, 160 - ((Len(ChatPromtText & ChatPromtCursor) * 8) / 2), 150, 0, 3
    
    'CROSSHAIR?
    DrawCrosshair
       
    'draw motd
    If ShowMotDSwitch = True And Not GAMEMODE = STORYMODE Then
        DrawText UCase(mod_Network.bMotD0), (160 - Int((Len(mod_Network.bMotD0) * 8) / 2)), (80), 0, 2
        DrawText UCase(mod_Network.bMotD1), (160 - Int((Len(mod_Network.bMotD1) * 8) / 2)), (90), 0, 2
        DrawText UCase(mod_Network.bMotD2), (160 - Int((Len(mod_Network.bMotD2) * 8) / 2)), (100), 0, 2
        'DrawText UCase(mod_Network.bMotNotice), (160 - Int((Len(mod_Network.bMotNotice) * 8) / 2)), (110), 0, 2
    End If
    
    If ShowChatSwitch = True Then
        DrawText UCase(ChatLine(0).chatText), (160 - Int((Len(ChatLine(0).chatText) * 8) / 2)), 142, 0, 2
    End If
    
    If CHARACTER.PLACINGMineFlag Then
        DrawText "PLACING MINE", (160 - Int((Len("PLACING MINE") * 8) / 2)), 142, 0, 2
    End If
    
    'STORY MODE INFORMATION TEXTS.
    If GAMEMODE = STORYMODE And Not CHARACTER.Dead Then
        Dim tmpValue As String, tmpValue2 As String, tmpValue3 As String
        
        If StoryStatus = 1 Then
            If InstructionsPage = 1 And Not InstructionsPageFlagged(2) = True Then
                tmpValue = "the ship is going down!"
                tmpValue2 = "find the storage room"
                tmpValue3 = "to get the important data"
            ElseIf InstructionsPage = 1 And InstructionsPageFlagged(2) = True Then
                tmpValue = "the ship is going down!"
                tmpValue2 = "you have to get out"
                tmpValue3 = ""
            ElseIf InstructionsPage = 2 Then
                tmpValue = "grab the data by"
                tmpValue2 = "walking over it"
            ElseIf InstructionsPage = 3 Then
                tmpValue = "great, now find the"
                tmpValue2 = "escape pod"
            ElseIf InstructionsPage = 4 And Not InstructionsPageFlagged(2) = True Then
                tmpValue = "you can't leave"
                tmpValue2 = "without the data!"
            ElseIf InstructionsPage = 4 And InstructionsPageFlagged(2) = True Then
                tmpValue = "drop down here"
                tmpValue2 = "to proceed"
            ElseIf InstructionsPage = 5 And Not InstructionsPageFlagged(2) = True Then
                tmpValue = "enjoying the view?"
                tmpValue2 = "better than nothing"
            ElseIf InstructionsPage = 5 And InstructionsPageFlagged(2) = True Then
                tmpValue = "enjoying the view?"
                tmpValue2 = "you don't have time!"
            End If
        ElseIf StoryStatus = 2 Then
            If InstructionsPage = 1 Then
                tmpValue = "bzzt *#.@"
                tmpValue2 = "heeeelp!!"
                tmpValue3 = "aaaaaaaaaahrghh"
            ElseIf InstructionsPage = 2 Then
                tmpValue = "this is main ammo"
                tmpValue2 = "to power the blaster"
                tmpValue3 = "and it's powerups"
            ElseIf InstructionsPage = 3 Then
                tmpValue = ""
                tmpValue2 = ""
                tmpValue3 = ""
            ElseIf InstructionsPage = 4 Then
                tmpValue = ""
                tmpValue2 = ""
                tmpValue3 = ""
            ElseIf InstructionsPage = 5 Then
                tmpValue = ""
                tmpValue2 = ""
                tmpValue3 = ""
            End If
        End If
    End If
    
    If GAMEMODE = STORYMODE Then
        If InstructionsPage <> 0 And Not InstructionsPageFlagged(InstructionsPage) = True Then DrawText UCase(tmpValue), (160 - Int((Len(tmpValue) * 8) / 2)), 60, 0, 1
        If InstructionsPage <> 0 And Not InstructionsPageFlagged(InstructionsPage) = True Then DrawText UCase(tmpValue2), (160 - Int((Len(tmpValue2) * 8) / 2)), 70, 0, 1
        If InstructionsPage <> 0 And Not InstructionsPageFlagged(InstructionsPage) = True Then DrawText UCase(tmpValue3), (160 - Int((Len(tmpValue3) * 8) / 2)), 80, 0, 1
    End If
    
End Sub

Public Sub DrawCrosshair(Optional pFlag As Boolean = False)

    



    AnimateCrosshair    'animate crosshair.

    Dim mbltfx As DDBLTFX
    Dim r As RECT, r2 As RECT
    
    CrosshairSize = 1
    r.Top = mintMouseY - (3) ' * CrosshairSize)
    r.Bottom = mintMouseY + (6) ' * CrosshairSize)
    r.Left = mintMouseX - (3) ' * CrosshairSize)
    r.Right = mintMouseX + (6) ' * CrosshairSize)
    
    
    
    If r.Top < 0 Then
        r.Top = 0
        r.Bottom = 9 * CrosshairSize
    ElseIf r.Bottom > SCRHeight Then
        r.Top = SCRHeight - (9 * CrosshairSize)
        r.Bottom = SCRHeight
    End If
    If r.Left < 0 Then
        r.Left = 0
        r.Right = 9 * CrosshairSize
    ElseIf r.Right > SCRWidth Then
        r.Left = SCRWidth - (9 * CrosshairSize)
        r.Right = SCRWidth
    End If
        
    If pFlag Then
        r2.Top = 90
    Else
        r2.Top = CHARACTER.CROSSHAIR * 9
    End If
        r2.Bottom = r2.Top + 9
        r2.Left = CHARACTER.CROSSHAIRNUM * 9
        r2.Right = r2.Left + 9
            
        DDS_Back.Blt r, DDS_Crosshair, r2, DDBLT_WAIT Or DDBLT_KEYSRC
           
End Sub

Public Sub DrawGuideMapPlayers()

    Dim X As Long, Y As Long, r2 As RECT

    X = 320 - MapWidth + (Int((CHARACTER.X + 10) / 32))
    Y = Int((CHARACTER.Y + 12) / 32)

    r2.Left = X
    r2.Right = X + 1
    r2.Top = Y
    r2.Bottom = Y + 1

    DDS_Back.BltColorFill r2, RGB(0, 255, 0)
 
Dim i As Integer
If GAMEMODE = TRAINING_BOTPLAY Then
    
    For i = 0 To UBound(BotClient)
                
        X = 320 - MapWidth + (Int((BotClient(i).X + 10) / 32))
        Y = Int((BotClient(i).Y + 12) / 32)
    
        r2.Left = X
        r2.Right = X + 1
        r2.Top = Y
        r2.Bottom = Y + 1
    
        DDS_Back.BltColorFill r2, RGB(0, 255, 0)
    
    Next i
End If

If NetworkStatus = SUCCESS Then
    For i = 0 To UBound(udtPlayers)
                
        X = 320 - MapWidth + (Int((udtPlayers(i).X + 10) / 32))
        Y = Int((udtPlayers(i).Y + 12) / 32)
    
        r2.Left = X
        r2.Right = X + 1
        r2.Top = Y
        r2.Bottom = Y + 1
    
        DDS_Back.BltColorFill r2, RGB(0, 255, 0)
    
    Next i
End If

End Sub
