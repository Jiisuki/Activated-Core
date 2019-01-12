Attribute VB_Name = "mod_Physics"
Global JumperSpeed As Integer
Global MaxYSpeed As Integer
Global MinYSpeed As Integer
Global JumpForce As Integer
Global JetpakForce As Integer

Public Sub Init_Physics()

    JumpForce = -12
    JetpakForce = -16
    
    JumperSpeed = -20
    'If MapName = "TUTORIAL" Then JumperSpeed = -18
    
    MaxYSpeed = 7
    MinYSpeed = JumperSpeed

End Sub

Public Sub CharacterMovement()

'-----------------------------------------------.
'This moves the character due to user controls. |
'-----------------------------------------------'
    If MoveDown Then
        CHARACTER.CROUCHING = True
    Else
        DDS_COLLISIONMAP.Lock rMAPCUT, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X, CHARACTER.Y + 10) <> cWhite And DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 32, CHARACTER.Y + 10) <> cWhite And DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, CHARACTER.Y + 10) <> cWhite Then
            CHARACTER.CROUCHING = False
        End If
        DDS_COLLISIONMAP.Unlock rMAPCUT
    End If
    
    If MoveLeft Then
        If CHARACTER.CROUCHING Then
            MoveX = -2
        Else
            MoveX = MoveX - 1
            If MoveX <= -5 Then MoveX = -5
            'MoveX = -5
        End If
    ElseIf MoveRight Then
        If CHARACTER.CROUCHING Then
            MoveX = 2
        Else
            'MoveX = 5
            MoveX = MoveX + 1
            If MoveX >= 5 Then MoveX = 5
        End If
    Else
        If MoveX > 0 Then
            MoveX = MoveX - 1
            If MoveX <= 0 Then MoveX = 0
        Else
            MoveX = MoveX + 1
            If MoveX >= 0 Then MoveX = 0
        End If
    End If
         
End Sub

Public Sub CheckMaxSpeeds()

    If CHARACTER.YSpeed < JumperSpeed Then CHARACTER.YSpeed = JumperSpeed
    If CHARACTER.YSpeed > MaxYSpeed Then CHARACTER.YSpeed = MaxYSpeed
    
    Dim i As Integer
    For i = 0 To UBound(BotClient)
        If BotClient(i).YSpeed < JumperSpeed Then BotClient(i).YSpeed = JumperSpeed
        If BotClient(i).YSpeed > MaxYSpeed Then BotClient(i).YSpeed = MaxYSpeed
    Next i

End Sub

Public Sub Physics()

On Local Error Resume Next

CharacterMovement   'move the char upon user request.


''MINE-TMP
If CHARACTER.PLACINGMineFlag Then
    CHARACTER.PLACINGMineTime = CHARACTER.PLACINGMineTime + 1
    MoveX = 0
    If CHARACTER.PLACINGMineTime >= CHARACTER.PLACINGMineTimeMax Then
        CHARACTER.PLACINGMineTime = 0
        CHARACTER.PLACINGMineFlag = False
        PlaceMine
        WeapMines.AmmoCurrent = WeapMines.AmmoCurrent - 1
        If WeapMines.AmmoCurrent < 0 Then WeapMines.AmmoCurrent = 0
    End If
Else
    CHARACTER.PLACINGMineTime = 0
End If

'-----------------------------------------.
'This is our basic physics sub.           |
'To handle falling and basic collision.   |
'-----------------------------------------'

lTickCount3 = GetTickCount()
    
If (lTickCount3 - lOldTickCount3) > 15 Then
        
    lOldTickCount3 = GetTickCount
    
    Dim NewX As Long
    Dim NewY As Long
    
'LOCK!!!
    DDS_COLLISIONMAP.Lock rMAPCUT, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
    
    NewX = CHARACTER.X + MoveX
    
    'Movement in X if not against a wall.
    If Not CHARACTER.CROUCHING Then
        If MoveX < 0 Then
            While DDS_COLLISIONMAP.GetLockedPixel(NewX, CHARACTER.Y + 10) = cWhite
                NewX = NewX + 1
                'MoveX = 0
            Wend
        ElseIf MoveX > 0 Then
            While DDS_COLLISIONMAP.GetLockedPixel(NewX + 32, CHARACTER.Y + 10) = cWhite
                NewX = NewX - 1
                'MoveX = 0
            Wend
        End If
    Else
        If MoveX < 0 Then
            While DDS_COLLISIONMAP.GetLockedPixel(NewX, CHARACTER.Y + 25) = cWhite
                NewX = NewX + 1
                'MoveX = 0
            Wend
        ElseIf MoveX > 0 Then
            While DDS_COLLISIONMAP.GetLockedPixel(NewX + 32, CHARACTER.Y + 25) = cWhite
                NewX = NewX - 1
                'MoveX = 0
            Wend
        End If
    End If
    CHARACTER.X = NewX
    
    
                   
'-----------------------.
'Movement in Y-led.     |
'-----------------------'
    
    
    
    
    'Gravity
    CHARACTER.YSpeed = CHARACTER.YSpeed + 1
    NewY = CHARACTER.Y + CHARACTER.YSpeed
    

    CHARACTER.StandingOnGround = False
    

            
    'Check floor collsion
    While DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 6, NewY + 31) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 32 - 6, NewY + 31) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 31) = cWhite
        NewY = NewY - 1
        CHARACTER.YSpeed = 0
    Wend
    
    'Check roof collision
    If CHARACTER.CROUCHING Then
        While DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 6, NewY + 16) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 32 - 6, NewY + 16) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = cWhite
            NewY = NewY + 1
            CHARACTER.YSpeed = 0
        Wend
    Else
        While DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 6, NewY + 1) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 32 - 6, NewY + 1) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 1) = cWhite
            NewY = NewY + 1
            CHARACTER.YSpeed = 0
        Wend
    End If
    'Floor tags
    If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 6, NewY + 32) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 32 - 6, NewY + 32) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 32) = cWhite Then
        CHARACTER.StandingOnGround = True
        If YSpeed > 0 Then
            CHARACTER.YSpeed = 0
        End If
    End If
    
    'Airshafts
    If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = cGreen Then
        CHARACTER.StandingOnGround = False
        'CHARACTER.Animation = STANDING
        If MoveUp And Not DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY) = cWhite Then
            If CHARACTER.YSpeed > -4 Then CHARACTER.YSpeed = CHARACTER.YSpeed - 2
        End If
    End If
    
    'Jetpak
    If CHARACTER.JETPAK Then
        CHARACTER.StandingOnGround = False
        CHARACTER.CROUCHING = False
        CHARACTER.YSpeed = CHARACTER.YSpeed - 2
        If CHARACTER.YSpeed <= CHARACTER.YSpeed + CInt((3 * JumpForce) / 2) Then
            CHARACTER.YSpeed = CHARACTER.YSpeed + CInt((3 * JumpForce) / 2)
            CHARACTER.JUMPASSISTREADY = False
            CHARACTER.JETPAK = False
        End If
    End If
    
    'Roof tags
    If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 6, NewY) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 32 - 6, NewY) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY) = cWhite Then
        If YSpeed < 0 Then
            CHARACTER.YSpeed = 0
        End If
    End If
    
    'HealthZone
    'If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(128, 128, 128) Then
    '    If CHARACTER.Health < 500 Then CHARACTER.Health = CHARACTER.Health + 1
    'End If
    
    InstructionsPage = 0
    
    If MapName = "MISSION BEGINS" And GAMEMODE = STORYMODE Then
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(67, 99, 153) Then InstructionsPage = 1
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(67, 131, 153) Then InstructionsPage = 2
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(67, 153, 143) Then InstructionsPage = 3
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(67, 153, 110) Then InstructionsPage = 4
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(67, 153, 78) Then InstructionsPage = 5
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(88, 153, 67) Then InstructionsPage = 6
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(120, 153, 67) Then InstructionsPage = 7
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(153, 153, 67) Then InstructionsPage = 8
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(153, 121, 67) Then InstructionsPage = 9
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(153, 89, 67) Then InstructionsPage = 10
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(153, 67, 77) Then InstructionsPage = 11
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(153, 67, 109) Then InstructionsPage = 12
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(153, 67, 141) Then InstructionsPage = 13
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(133, 67, 153) Then InstructionsPage = 14
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(100, 67, 153) Then InstructionsPage = 15
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(68, 67, 153) Then InstructionsPage = 16
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(1, 41, 109) Then InstructionsPage = 17
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(109, 29, 1) Then InstructionsPage = 18
        If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 16) = RGB(255, 0, 255) Then 'Finished level
            If Not InstructionsPageFlagged(2) = True Then
                CHARACTER.Health = -1
            Else
                FinishLevel 1
            End If
        End If
    End If

'-----------------------.
'CHECK MAP DATA         |
'-----------------------.

    'Check if character is in the air, ie not standing on the ground.
    If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 6, NewY + 32) = cBlack And DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 32 - 6, NewY + 32) = cBlack And DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 32) = cBlack Then
        CHARACTER.StandingOnGround = False
        CHARACTER.JETPAK = False
    End If
    
    
    
    
                    
    'Check if standing on a jumperpad
    If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 16, NewY + 32) = cBlue Then
        CHARACTER.StandingOnGround = False
        CHARACTER.YSpeed = JumperSpeed
        CHARACTER.JETPAK = False
        PlaySample "char\jumping\human1.wav"
    End If
                    
    'Out of map or spikes or whatever.
    If DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X, NewY + 32) = cRed Or DDS_COLLISIONMAP.GetLockedPixel(CHARACTER.X + 32, NewY + 32) = cRed Then
        CHARACTER.Health = CHARACTER.Health - 10000
        PlaySample "char\pain\instagib.mp3"
    End If
    
    CHARACTER.Y = NewY

    

'UNLOCK!!!
    DDS_COLLISIONMAP.Unlock rMAPCUT


'-----------.
'Objects    |
'-----------'

    Dim i As Integer
    
    For i = 0 To obj_Count(0) - 1
        If obj_HealthPack(i).Spawned Then
            If CHARACTER.Health < 500 Then
                If CHARACTER.X + 16 >= obj_HealthPack(i).X And CHARACTER.X + 16 <= obj_HealthPack(i).X + 32 And CHARACTER.Y + 16 >= obj_HealthPack(i).Y And CHARACTER.Y + 16 <= obj_HealthPack(i).Y + 32 Then
                    obj_HealthPack(i).Spawned = False
                    If CHARACTER.Health < 500 Then CHARACTER.Health = CHARACTER.Health + obj_HealthPack(i).Flag1
                    If CHARACTER.Health > 500 Then CHARACTER.Health = 500
                    ChatFeed obj_HealthPack(i).Flag2
                    PlaySample "items\hpickup.wav", True
                    If NetworkStatus = SUCCESS Then SendItem tHealth, False, i
                End If
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(1) - 1
        If obj_MegaHealthPack(i).Spawned Then
            If CHARACTER.Health < 1000 Then
                If CHARACTER.X + 16 >= obj_MegaHealthPack(i).X And CHARACTER.X + 16 <= obj_MegaHealthPack(i).X + 32 And CHARACTER.Y + 16 >= obj_MegaHealthPack(i).Y And CHARACTER.Y + 16 <= obj_MegaHealthPack(i).Y + 32 Then
                    obj_MegaHealthPack(i).Spawned = False
                    CHARACTER.Health = CHARACTER.Health + obj_MegaHealthPack(i).Flag1
                    If CHARACTER.Health > 1000 Then CHARACTER.Health = 1000
                    ChatFeed obj_MegaHealthPack(i).Flag2
                    PlaySample "items\mhpickup.wav", True
                    If NetworkStatus = SUCCESS Then SendItem tMegaHealth, False, i
                End If
            End If
        End If
        DoEvents
    Next i
    
'Ammo Objects
    
    For i = 0 To obj_Count(5) - 1
        If obj_Batteries(i).Spawned Then
            If WeapBlaster.AmmoCurrent < WeapBlaster.AMMOMAX Then
                If CHARACTER.X + 16 >= obj_Batteries(i).X And CHARACTER.X + 16 <= obj_Batteries(i).X + 32 And CHARACTER.Y + 16 >= obj_Batteries(i).Y And CHARACTER.Y + 16 <= obj_Batteries(i).Y + 32 Then
                    obj_Batteries(i).Spawned = False
                    WeapBlaster.AmmoCurrent = WeapBlaster.AmmoCurrent + obj_Batteries(i).Flag1
                    If WeapBlaster.AmmoCurrent > WeapBlaster.AMMOMAX Then WeapBlaster.AmmoCurrent = WeapBlaster.AMMOMAX
                    ChatFeed obj_Batteries(i).Flag2
                    PlaySample "items\pickup.wav", True
                    If NetworkStatus = SUCCESS Then SendItem tBatteries, False, i
                End If
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(4) - 1
        If obj_GrenadesAmmo(i).Spawned Then
        
            If WeapBoingers.AmmoCurrent < WeapBoingers.AMMOMAX Then
                If CHARACTER.X + 16 >= obj_GrenadesAmmo(i).X And CHARACTER.X + 16 <= obj_GrenadesAmmo(i).X + 32 And CHARACTER.Y + 16 >= obj_GrenadesAmmo(i).Y And CHARACTER.Y + 16 <= obj_GrenadesAmmo(i).Y + 32 Then
                    obj_GrenadesAmmo(i).Spawned = False
                    WeapBoingers.AmmoCurrent = WeapBoingers.AmmoCurrent + obj_GrenadesAmmo(i).Flag1
                    If WeapBoingers.AmmoCurrent > WeapBoingers.AMMOMAX Then WeapBoingers.AmmoCurrent = WeapBoingers.AMMOMAX
                    ChatFeed obj_GrenadesAmmo(i).Flag2
                    PlaySample "items\pickup.wav", True
                    If NetworkStatus = SUCCESS Then SendItem tGrenades, False, i
                End If
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(6) - 1
        If obj_MinesAmmo(i).Spawned Then
        
            If WeapMines.AmmoCurrent < WeapMines.AMMOMAX Then
            
                If CHARACTER.X + 16 >= obj_MinesAmmo(i).X And CHARACTER.X + 16 <= obj_MinesAmmo(i).X + 32 And CHARACTER.Y + 16 >= obj_MinesAmmo(i).Y And CHARACTER.Y + 16 <= obj_MinesAmmo(i).Y + 32 Then
                    obj_MinesAmmo(i).Spawned = False
                    WeapMines.GotWeapon = True
                    WeapMines.AmmoCurrent = WeapMines.AmmoCurrent + obj_MinesAmmo(i).Flag1
                    If WeapMines.AmmoCurrent > WeapMines.AMMOMAX Then WeapMines.AmmoCurrent = WeapMines.AMMOMAX
                    ChatFeed obj_MinesAmmo(i).Flag2
                    PlaySample "items\pickup.wav", True
                    If NetworkStatus = SUCCESS Then SendItem tMines, False, i
                End If
            End If
        End If
        DoEvents
    Next i
    
'Weapon Objects

    For i = 0 To obj_Count(9) - 1
        If obj_Railgun(i).Spawned Then
            If CHARACTER.X + 16 >= obj_Railgun(i).X And CHARACTER.X + 16 <= obj_Railgun(i).X + 32 And CHARACTER.Y + 16 >= obj_Railgun(i).Y And CHARACTER.Y + 16 <= obj_Railgun(i).Y + 32 Then
                obj_Railgun(i).Spawned = False
                WeapRailgun.GotWeapon = True
                WeapBlaster.AmmoCurrent = WeapBlaster.AmmoCurrent + obj_Railgun(i).Flag1
                If WeapBlaster.AmmoCurrent >= WeapBlaster.AMMOMAX Then WeapBlaster.AmmoCurrent = WeapBlaster.AMMOMAX
                ChatFeed obj_Railgun(i).Flag2
                PlaySample "items\pickup.wav", True
                If NetworkStatus = SUCCESS Then SendItem tRailgun, False, i
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(10) - 1
        If obj_Boingers(i).Spawned Then
            If CHARACTER.X + 16 >= obj_Boingers(i).X And CHARACTER.X + 16 <= obj_Boingers(i).X + 32 And CHARACTER.Y + 16 >= obj_Boingers(i).Y And CHARACTER.Y + 16 <= obj_Boingers(i).Y + 16 Then
                obj_Boingers(i).Spawned = False
                WeapBoingers.GotWeapon = True
                If WeapBoingers.AmmoCurrent <= 5 Then WeapBoingers.AmmoCurrent = 5
                ChatFeed obj_Boingers(i).Flag2
                PlaySample "items\pickup.wav", True
                If NetworkStatus = SUCCESS Then SendItem tBoingers, False, i
            End If
        End If
        DoEvents
    Next i
    
'Other Objects
    For i = 0 To obj_Count(2) - 1
        If obj_Shield(i).Spawned Then
            If CHARACTER.X + 16 >= obj_Shield(i).X And CHARACTER.X + 16 <= obj_Shield(i).X + 32 And CHARACTER.Y + 16 >= obj_Shield(i).Y And CHARACTER.Y + 16 <= obj_Shield(i).Y + 32 Then
                obj_Shield(i).Spawned = False
                CHARACTER.GotShield = True
                CHARACTER.SHIELDTIME = obj_Shield(i).Flag1
                CHARACTER.SHIELDFLASH = False
                ChatFeed obj_Shield(i).Flag2
                PlaySample "items\pickup.wav", True
                If NetworkStatus = SUCCESS Then SendItem tShield, False, i
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(3) - 1
        If obj_Power(i).Spawned Then
            If CHARACTER.X + 16 >= obj_Power(i).X And CHARACTER.X + 16 <= obj_Power(i).X + 32 And CHARACTER.Y + 16 >= obj_Power(i).Y And CHARACTER.Y + 16 <= obj_Power(i).Y + 32 Then
                If Not CHARACTER.GOTJUMPASSIST Then
                    obj_Power(i).Spawned = False
                    CHARACTER.GOTJUMPASSIST = True
                    CHARACTER.JUMPASSISTTIME = obj_Power(i).Flag1
                    CHARACTER.JUMPASSISTFLASH = False
                    ChatFeed obj_Power(i).Flag2
                    PlaySample "items\pickup.wav", True
                    
                    'FIRST LEVEL FIX
                    'If GAMEMODE = STORYMODE Then
                    '    InstructionsPageFlagged(2) = True
                    '    StoryPlayerPoints = StoryPlayerPoints + 5000
                    'End If
                    
                    If NetworkStatus = SUCCESS Then SendItem tPowerup, False, i
                End If
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(13) - 1
        If obj_Suit(i).Spawned Then
            If CHARACTER.X + 16 >= obj_Suit(i).X And CHARACTER.X + 16 <= obj_Suit(i).X + 32 And CHARACTER.Y + 16 >= obj_Suit(i).Y And CHARACTER.Y + 16 <= obj_Suit(i).Y + 32 Then
                obj_Suit(i).Spawned = False
                ChatFeed obj_Suit(i).Flag2
                PlaySample "items\pickup.wav", True
                
                'FIRST LEVEL FIX
                If GAMEMODE = STORYMODE Then
                    InstructionsPageFlagged(2) = True
                    StoryPlayerPoints = StoryPlayerPoints + 5000
                    CHARACTER.GOTSUIT = True
                End If
                
                If NetworkStatus = SUCCESS Then SendItem tSuit, False, i
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(7) - 1
        If obj_HeartSens(i).Spawned Then
            If CHARACTER.X + 16 >= obj_HeartSens(i).X And CHARACTER.X + 16 <= obj_HeartSens(i).X + 32 And CHARACTER.Y + 16 >= obj_HeartSens(i).Y And CHARACTER.Y + 16 <= obj_HeartSens(i).Y + 32 Then
                If Not CHARACTER.GOTHEARTSENS Then
                    obj_HeartSens(i).Spawned = False
                    CHARACTER.GOTHEARTSENS = True
                    ChatFeed obj_HeartSens(i).Flag2
                    PlaySample "items\pickup.wav", True
                    If NetworkStatus = SUCCESS Then SendItem tHeartSensor, False, i
                End If
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(8) - 1
        If obj_Armor(i).Spawned Then
            If CHARACTER.X + 16 >= obj_Armor(i).X And CHARACTER.X + 16 <= obj_Armor(i).X + 32 And CHARACTER.Y + 16 >= obj_Armor(i).Y And CHARACTER.Y + 16 <= obj_Armor(i).Y + 32 Then
                If CHARACTER.ARMOR < CHARACTER.ARMORMAX Then
                    obj_Armor(i).Spawned = False
                    CHARACTER.ARMOR = CHARACTER.ARMOR + obj_Armor(i).Flag1
                    If CHARACTER.ARMOR > CHARACTER.ARMORMAX Then CHARACTER.ARMOR = CHARACTER.ARMORMAX
                    ChatFeed obj_Armor(i).Flag2
                    PlaySample "items\pickup.wav", True
                    If NetworkStatus = SUCCESS Then SendItem tArmorShard, False, i
                End If
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(11) - 1
        If obj_Cap(i).Spawned Then
            If CHARACTER.X + 16 >= obj_Cap(i).X And CHARACTER.X + 16 <= obj_Cap(i).X + 32 And CHARACTER.Y + 16 >= obj_Cap(i).Y And CHARACTER.Y + 16 <= obj_Cap(i).Y + 32 Then
                obj_Cap(i).Spawned = False
                CHARACTER.GOTCAP = True
                WeapBlaster.AMMOMAX = WeapBlaster.AMMOMAX + obj_Cap(i).Flag1
                ChatFeed obj_Cap(i).Flag2 & CStr(WeapBlaster.AMMOMAX) & "!"
                PlaySample "items\pickup.wav", True
                If NetworkStatus = SUCCESS Then SendItem tCapacitor, False, i
            End If
        End If
        DoEvents
    Next i
    
    
    
    'TELEPORT!!
    For i = 0 To obj_Count(12) - 1
        If obj_Teleport(i).Spawned Then
            If CHARACTER.X + 16 >= obj_Teleport(i).X And CHARACTER.X + 16 <= obj_Teleport(i).X + 32 And CHARACTER.Y + 16 >= obj_Teleport(i).Y And CHARACTER.Y + 16 <= obj_Teleport(i).Y + 32 Then
                Dim tTele As Integer
                tTele = CInt(Rnd * (obj_Count(12) - 1))
                While tTele = i And obj_Count(12) > 1
                    tTele = CInt(Rnd * (obj_Count(12) - 1))
                Wend
                obj_Teleport(tTele).Spawned = False
                Teleport tTele, i
            End If
        End If
        DoEvents
    Next i
    
End If

CheckPlayerStatus
CheckMaxSpeeds

End Sub


Public Sub CheckPlayerStatus()

    If CHARACTER.X < 0 Or CHARACTER.X > MapWidth * 32 Or CHARACTER.Y < 0 Or CHARACTER.Y > MapHeight * 32 Then CHARACTER.Health = -10000

    If CHARACTER.Health <= 0 Then
        If GAMEMODE = STORYMODE Then
            StoryPlayerLives = StoryPlayerLives - 1
            StoryPlayerPoints = StoryPlayerPoints - 1000
            If StoryPlayerPoints < 0 Then StoryPlayerPoints = 0
            If StoryPlayerLives < 0 Then
                Game_Over
            End If
        Else
            CHARACTER.DEATH = CHARACTER.DEATH + 1
            ShowGameStats = True
        End If
        RESPAWNTIMER = 0
        CHARACTER.Dead = True
        ChatFeed GetRandomDeathMsg
        Exit Sub
        
    End If

End Sub

Public Sub CheckBotStatus(iBot As Integer)

    If BotClient(iBot).Health <= 0 Then
        BotClient(iBot).Deaths = BotClient(iBot).Deaths + 1
        BotClient(iBot).Spawn
    End If
    
    If BotClient(iBot).X < 0 Or BotClient(iBot).X > MapWidth * 32 Or BotClient(iBot).Y < 0 Or BotClient(iBot).Y > MapHeight * 32 Then BotClient(iBot).Health = -1000

End Sub



Public Sub CharacterSpawn()

CHARACTER.Team = tRED

'--------------.
'Set char pos. |
'--------------'

Retry:

Randomize
Dim z As Integer

z = Int(Rnd * (SPAWNPOINTS))

If GAMEMODE = MULTIPLAY_CTF Then
    If SPAWNPOINT(z).BUSY = False And SPAWNPOINT(z).Team = CHARACTER.Team Then
        CHARACTER.X = SPAWNPOINT(z).X
        CHARACTER.Y = SPAWNPOINT(z).Y
    Else
        GoTo Retry
    End If
Else
    If SPAWNPOINT(z).BUSY = False Then
        CHARACTER.X = SPAWNPOINT(z).X
        CHARACTER.Y = SPAWNPOINT(z).Y
    Else
        GoTo Retry
    End If
End If

CHARACTER.YSpeed = 0                        'Reset gravity speed
CHARACTER.GOTJUMPASSIST = False             'Init jet
CHARACTER.JUMPASSISTREADY = False
CHARACTER.GotShield = False                 'Init Shield
CHARACTER.GOTSUIT = True                    'Use the Suit
CHARACTER.GOTHEARTSENS = False              'Init HS
CHARACTER.GOTCAP = False                    'Init Cap
CHARACTER.ARMOR = 0                         'Init start armor
CHARACTER.ARMORMAX = 500                    'Init MAX armor
CHARACTER.Health = 250                      'Init health.
CHARACTER.SHIELDFLASH = False               'Flag for flashing of shield
CHARACTER.JUMPASSISTFLASH = False           'Flag for flashing of jetpak
CHARACTER.FLASHTIME = 7                     'Flash for how meny seconds?
frmMain.tmr_PowerupFlasher.Interval = 100   '20 * CHARACTER.FLASHTIME  'Flashing speed in ms.
CHARACTER.PLACINGMineFlag = False
CHARACTER.PLACINGMineTime = 0
CHARACTER.PLACINGMineTimeMax = 20

mintMouseXTarg = 160 + 64 'to fix bug with crosshair
ReverseFlag = False

Init_Physics

                                'Init starting weapons
WeapRailgun.GotWeapon = False
WeapRailgun.AmmoCurrent = 0
WeapBoingers.GotWeapon = False
WeapBoingers.AmmoCurrent = 0
WeapMines.GotWeapon = False
WeapMines.AmmoCurrent = 0
WeapEnergySword.GotWeapon = True
WeapBlaster.GotWeapon = True

                                'Init starting AMMO
If StoryStatus = 1 And GAMEMODE = STORYMODE Then
    WeapBlaster.AmmoCurrent = 0
    WeapBlaster.GotWeapon = False
    SelectedWeapon = EnergySword
    CHARACTER.GOTSUIT = False
ElseIf StoryStatus = 2 And GAMEMODE = STORYMODE Then
    WeapBlaster.AmmoCurrent = 0
    WeapBlaster.GotWeapon = False
    SelectedWeapon = EnergySword
Else
    WeapBlaster.AMMOMAX = 100
    WeapBlaster.AmmoCurrent = CLng(WeapBlaster.AMMOMAX / 2)
    SelectedWeapon = Blaster
End If

If GAMEMODE = STORYMODE Then
    Dim tmpinst As Integer
    For tmpinst = 0 To UBound(InstructionsPageFlagged)
        InstructionsPageFlagged(tmpinst) = False
    Next tmpinst
End If

                                'Select starting weapon



                                'Reset DEAD-flag and don't show status.
CHARACTER.Dead = False
ShowGameStats = False

End Sub

Public Sub BotPhysics()

Dim iBot As Integer
For iBot = 0 To UBound(BotClient)
'-----------------------------------------.
'This is our basic physics sub.           |
'To handle falling and basic collision.   |
'-----------------------------------------'

lTickCount10 = GetTickCount()
    
If (lTickCount10 - lOldTickCount10) > 15 Then
        
    lOldTickCount10 = GetTickCount()
    
    Dim NewX As Long
    Dim NewY As Long
    
    
'LOCK!!!
    DDS_COLLISIONMAP.Lock rMAPCUT, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
    
    NewX = BotClient(iBot).X + BotClient(iBot).MoveX
    
    'Movement in X if not against a wall.
    If BotClient(iBot).MoveX < 0 Then
        While DDS_COLLISIONMAP.GetLockedPixel(NewX, BotClient(iBot).Y + 20) = cWhite
            NewX = NewX + 1
        Wend
    ElseIf BotClient(iBot).MoveX > 0 Then
        While DDS_COLLISIONMAP.GetLockedPixel(NewX + 32, BotClient(iBot).Y + 20) = cWhite
            NewX = NewX - 1
        Wend
    End If
    BotClient(iBot).X = NewX
    
    
                   
'-----------------------.
'Movement in Y-led.     |
'-----------------------'
    
    
    
    
    'Gravity
    BotClient(iBot).YSpeed = BotClient(iBot).YSpeed + 1
    NewY = BotClient(iBot).Y + BotClient(iBot).YSpeed
    

    BotClient(iBot).StandingOnGround = False
    

            
    'Check floor collsion
    While DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 6, NewY + 31) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 - 6, NewY + 31) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, NewY + 31) = cWhite
        NewY = NewY - 1
        BotClient(iBot).YSpeed = 0
    Wend
    
    'Check roof collision
    While DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 6, NewY + 1) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 - 6, NewY + 1) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, NewY + 1) = cWhite
        NewY = NewY + 1
        BotClient(iBot).YSpeed = 0
    Wend
    
    'Floor tags
    If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 6, NewY + 32) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 - 6, NewY + 32) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, NewY + 32) = cWhite Then
        BotClient(iBot).StandingOnGround = True
        If YSpeed > 0 Then
            BotClient(iBot).YSpeed = 0
        End If
    End If
    
    'Airshafts
    If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, NewY + 16) = cGreen Then
        BotClient(iBot).StandingOnGround = False
        If Not BotClient(iBot).MoveDown And Not DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, NewY) = cWhite Then
            If BotClient(iBot).YSpeed > -4 Then BotClient(iBot).YSpeed = BotClient(iBot).YSpeed - 2
        End If
    End If
    
    'Roof tags
    If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 6, NewY) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 - 6, NewY) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, NewY) = cWhite Then
        If YSpeed < 0 Then
            BotClient(iBot).YSpeed = 0
        End If
    End If
        
'-----------------------.
'CHECK MAP DATA         |
'-----------------------.

    'Check if character is in the air, ie not standing on the ground.
    If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 6, NewY + 32) = cBlack And DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 - 6, NewY + 32) = cBlack And DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, NewY + 32) = cBlack Then
        BotClient(iBot).StandingOnGround = False
    End If
                    
    'Check if standing on a jumperpad
    If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, NewY + 32) = cBlue Then
        BotClient(iBot).StandingOnGround = False
        BotClient(iBot).YSpeed = JumperSpeed
        PlaySample "char\jumping\tech1.wav"
    End If
                    
    'Out of map or spikes or whatever.
    If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X, NewY + 32) = cRed Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32, NewY + 32) = cRed Then
        CHARACTER.Health = -1
        PlaySample "char\pain\instagib.mp3"
    End If
    
    BotClient(iBot).Y = NewY

    

'UNLOCK!!!
    DDS_COLLISIONMAP.Unlock rMAPCUT


'-----------.
'Objects    |
'-----------'

    Dim i As Integer
    
    For i = 0 To obj_Count(0) - 1
        If obj_HealthPack(i).Spawned Then
            If BotClient(iBot).Health < 500 Then
                If BotClient(iBot).X + 16 >= obj_HealthPack(i).X And BotClient(iBot).X + 16 <= obj_HealthPack(i).X + 32 And BotClient(iBot).Y + 16 >= obj_HealthPack(i).Y And BotClient(iBot).Y + 16 <= obj_HealthPack(i).Y + 32 Then
                    obj_HealthPack(i).Spawned = False
                    If BotClient(iBot).Health < 500 Then BotClient(iBot).Health = BotClient(iBot).Health + obj_HealthPack(i).Flag1
                    If BotClient(iBot).Health > 500 Then BotClient(iBot).Health = 500
                    ChatFeed obj_HealthPack(i).Flag2
                    PlaySample "items\hpickup.wav", True
                End If
            End If
        End If
        DoEvents
    Next i
    For i = 0 To obj_Count(1) - 1
        If obj_MegaHealthPack(i).Spawned Then
            If BotClient(iBot).Health < 1000 Then
                If BotClient(iBot).X + 16 >= obj_MegaHealthPack(i).X And BotClient(iBot).X + 16 <= obj_MegaHealthPack(i).X + 32 And BotClient(iBot).Y + 16 >= obj_MegaHealthPack(i).Y And BotClient(iBot).Y + 16 <= obj_MegaHealthPack(i).Y + 32 Then
                    obj_MegaHealthPack(i).Spawned = False
                    BotClient(iBot).Health = BotClient(iBot).Health + obj_MegaHealthPack(i).Flag1
                    If BotClient(iBot).Health > 500 Then BotClient(iBot).Health = 500
                    ChatFeed obj_MegaHealthPack(i).Flag2
                    PlaySample "items\mhpickup.wav", True
                End If
            End If
        End If
        DoEvents
    Next i
    
'Ammo Objects

    
    
    
    'TELEPORT!!
    For i = 0 To obj_Count(12) - 1
        If obj_Teleport(i).Spawned Then
            If BotClient(iBot).X + 16 >= obj_Teleport(i).X And BotClient(iBot).X + 16 <= obj_Teleport(i).X + 32 And BotClient(iBot).Y + 16 >= obj_Teleport(i).Y And BotClient(iBot).Y + 16 <= obj_Teleport(i).Y + 32 Then
                Dim tTele As Integer
                tTele = i + 1
                If tTele >= obj_Count(12) Then tTele = 0
                obj_Teleport(tTele).Spawned = False
                BotClient(iBot).X = obj_Teleport(tTele).X
                BotClient(iBot).Y = obj_Teleport(tTele).Y
                ChatFeed "TELEPORTED FROM " & CStr(i) & " TO " & CStr(tTele)
                PlaySample "items\pickup.wav", True
            End If
        End If
        DoEvents
    Next i

    
    
End If

CheckBotStatus iBot
CheckMaxSpeeds
Next iBot

End Sub







Public Sub Teleport(cObj As Integer, iFrom As Integer)

DDS_COLLISIONMAP.Lock rMAPCUT, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0

    If DDS_COLLISIONMAP.GetLockedPixel(obj_Teleport(cObj).X - 16, obj_Teleport(cObj).Y + 16) = cWhite And DDS_COLLISIONMAP.GetLockedPixel(obj_Teleport(cObj).X + 32 + 16, obj_Teleport(cObj).Y + 16) <> cWhite Then
        CHARACTER.X = obj_Teleport(cObj).X + 32
        CHARACTER.Y = obj_Teleport(cObj).Y
    ElseIf DDS_COLLISIONMAP.GetLockedPixel(obj_Teleport(cObj).X + 32 + 16, obj_Teleport(cObj).Y + 16) = cWhite And DDS_COLLISIONMAP.GetLockedPixel(obj_Teleport(cObj).X - 16, obj_Teleport(cObj).Y + 16) <> cWhite Then
        CHARACTER.X = obj_Teleport(cObj).X - 32
        CHARACTER.Y = obj_Teleport(cObj).Y
    ElseIf DDS_COLLISIONMAP.GetLockedPixel(obj_Teleport(cObj).X - 16, obj_Teleport(cObj).Y + 16) = cWhite And DDS_COLLISIONMAP.GetLockedPixel(obj_Teleport(cObj).X + 32 + 16, obj_Teleport(cObj).Y + 16) = cWhite Then
        CHARACTER.X = obj_Teleport(cObj).X
        CHARACTER.Y = obj_Teleport(cObj).Y
    Else
        CHARACTER.X = obj_Teleport(cObj).X + 32
        CHARACTER.Y = obj_Teleport(cObj).Y
    End If

DDS_COLLISIONMAP.Unlock rMAPCUT

ChatFeed "TELEPORTED FROM LOC " & CStr(iFrom) & " TO " & CStr(cObj)
PlaySample "other\teleport.wav", True

End Sub

