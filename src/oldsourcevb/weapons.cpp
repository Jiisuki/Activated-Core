Attribute VB_Name = "mod_Weapons"
    
    
    Public WeaponReloadTime As Long
    Public WeaponRecoilAmount As Long
        
    Public Enum ProjAnims
        MA_Idle = 0
        MA_Placing = 1
        MA_Explode = 2
    End Enum
    
    Public Enum SelectedWeaponEnum
        Blaster = 1
        EnergySword = 0
        Boingers = 2
        Mines = 3
        Railgun = 4
        None = 99
    End Enum
    Public SelectedWeapon As SelectedWeaponEnum
    
    'BASIC WEAPONS:
    Public WeapBlaster As New cls_Blaster
    Public WeapEnergySword As New cls_EnergySword

    'ADVANCED WEAPONS:
    Public WeapBoingers As New cls_Boingers                 'Boingers
    Public WeapMines As New cls_MinesProxy             'Proxy Mines
    Public WeapRailgun As New cls_Railgun                   'Railgun

    'PROJECTILES
    Public BlasterBullets() As New cls_ProjectileBase
    Public Grenades() As New cls_ProjectileBase
    Public Rail() As New cls_ProjectileBase
    Public Mine() As New cls_ProjectileBase
    
    Public BBIndex As Integer
    Public BBInactiveIndex As Integer, BBFoundInActive As Boolean
    
    Public GrenadesIndex As Integer
    Public GrenadesInactiveIndex As Integer, GrenadesFoundInActive As Boolean
    
    Public RailIndex As Integer
    Public RailInactiveIndex As Integer, RailFoundInActive As Boolean
    
    Public MineIndex As Integer
    Public MineInactiveIndex As Integer, MineFoundInActive As Boolean
    
Public Sub FireWeapon()

If SelectedWeapon = Blaster Then
    If Not WeapBlaster.AmmoCurrent <= 0 Then
        CHARACTER.ANIMATIONNUM = 0
        CHARACTER.FIRING = True
        BlasterFire
        WeapBlaster.AmmoCurrent = WeapBlaster.AmmoCurrent - 1
        If WeapBlaster.AmmoCurrent < 0 Then WeapBlaster.AmmoCurrent = 0
        If ReverseFlag Then
            MoveX = MoveX + WeapBlaster.RecoilAmount
        Else
            MoveX = MoveX - WeapBlaster.RecoilAmount
        End If
    End If
ElseIf SelectedWeapon = Railgun Then
    If Not WeapBlaster.AmmoCurrent < 5 Then
        CHARACTER.ANIMATIONNUM = 0
        CHARACTER.FIRING = True
        RailgunFire
        WeapBlaster.AmmoCurrent = WeapBlaster.AmmoCurrent - 5
        If WeapBlaster.AmmoCurrent < 0 Then WeapBlaster.AmmoCurrent = 0
        If ReverseFlag Then
            MoveX = MoveX + WeapRailgun.RecoilAmount
        Else
            MoveX = MoveX - WeapRailgun.RecoilAmount
        End If
    Else
        If Not WeapBlaster.AmmoCurrent <= 0 Then
            SwitchWeapon Blaster
            CHARACTER.ANIMATIONNUM = 0
            CHARACTER.FIRING = True
            BlasterFire
            WeapBlaster.AmmoCurrent = WeapBlaster.AmmoCurrent - 1
            If WeapBlaster.AmmoCurrent < 0 Then WeapBlaster.AmmoCurrent = 0
            If ReverseFlag Then
                MoveX = MoveX + WeapBlaster.RecoilAmount
            Else
                MoveX = MoveX - WeapBlaster.RecoilAmount
            End If
        End If
    End If
ElseIf SelectedWeapon = Boingers Then
    If Not WeapBoingers.AmmoCurrent <= 0 Then
        CHARACTER.ANIMATIONNUM = 0
        CHARACTER.FIRING = True
        GrenadesFire
        WeapBoingers.AmmoCurrent = WeapBoingers.AmmoCurrent - 1
        If WeapBoingers.AmmoCurrent < 0 Then WeapBoingers.AmmoCurrent = 0
        If ReverseFlag Then
            MoveX = MoveX + WeapBoingers.RecoilAmount
        Else
            MoveX = MoveX - WeapBoingers.RecoilAmount
        End If
    Else
        If Not WeapBlaster.AmmoCurrent <= 0 Then
            If WeapRailgun.GotWeapon And WeapBlaster.AmmoCurrent >= 5 Then
                SwitchWeapon Railgun
                CHARACTER.ANIMATIONNUM = 0
                CHARACTER.FIRING = True
                RailgunFire
                WeapBlaster.AmmoCurrent = WeapBlaster.AmmoCurrent - 5
                If ReverseFlag Then
                    MoveX = MoveX + WeapRailgun.RecoilAmount
                Else
                    MoveX = MoveX - WeapRailgun.RecoilAmount
                End If
            Else
                SwitchWeapon Blaster
                CHARACTER.ANIMATIONNUM = 0
                CHARACTER.FIRING = True
                BlasterFire
                WeapBlaster.AmmoCurrent = WeapBlaster.AmmoCurrent - 1
                If ReverseFlag Then
                    MoveX = MoveX + WeapBlaster.RecoilAmount
                Else
                    MoveX = MoveX - WeapBlaster.RecoilAmount
                End If
            End If
            If WeapBlaster.AmmoCurrent < 0 Then WeapBlaster.AmmoCurrent = 0
        End If
    End If
ElseIf SelectedWeapon = Mines Then
    If Not WeapMines.AmmoCurrent <= 0 Then
        CHARACTER.PLACINGMineFlag = True
    End If
        
End If

End Sub
    
Public Sub PlaceMine()

    
    PlaySample "menu\click.mp3"
    

    'Advance blasterbullet array
    Dim p As Integer
    
    'Reset boolean variable
    MineFoundInActive = False
    
    If MineIndex = 0 Then 'if we just started
    
        MineIndex = MineIndex + 1
        
    Else 'Look for inactive bullets
    
        'Cycle through the bullets
        For p = 0 To UBound(Mine)
            If Mine(p).Active = False Then
                MineInactiveIndex = p
                MineFoundInActive = True
            End If
            
            DoEvents
            
        Next
        
        'if we didn't find any inactive bullets add
        'a new element to the array
        If MineFoundInActive = False Then
            MineIndex = MineIndex + 1
        End If
        
    End If
    
    'redimension the array holding our bullet info
    ReDim Preserve Mine(MineIndex)
    
    'If we are adding a completely new bullet then:
    If MineFoundInActive = False Then
        Mine(MineIndex).XSpeed = 0
        Mine(MineIndex).YSpeed = 1
        Mine(MineIndex).TrailAngle = 0
        Mine(MineIndex).CoorX = CHARACTER.X + 12
        Mine(MineIndex).CoorY = CHARACTER.Y
        Mine(MineIndex).ProjectileColor = RGB(16, 16, 16)
        Mine(MineIndex).Active = True
        Mine(MineIndex).Animation = MA_Placing
        Mine(MineIndex).AnimationFrame = 0
        Mine(MineIndex).Countdown = 3
    Else
        'Add a laser to where a previous missle that
        'is now inactive is located
        Mine(MineInactiveIndex).XSpeed = 0
        Mine(MineInactiveIndex).YSpeed = 1
        Mine(MineInactiveIndex).TrailAngle = 0
        Mine(MineInactiveIndex).CoorX = CHARACTER.X + 12
        Mine(MineInactiveIndex).CoorY = CHARACTER.Y
        Mine(MineInactiveIndex).ProjectileColor = RGB(16, 16, 16)
        Mine(MineInactiveIndex).Active = True
        Mine(MineInactiveIndex).Animation = MA_Placing
        Mine(MineInactiveIndex).AnimationFrame = 0
        Mine(MineInactiveIndex).Countdown = 3
    End If

End Sub

    Public Sub DrawPlacedMines()

    If MineIndex > 0 Then

        Dim i As Integer, k As Integer, a As RECT
        For i = 0 To MineIndex
            'don't draw anything if the current missle is
            'not active
            If Mine(i).Active = True Then
                
                'advance the laser coordinates
                'LOCK!!!
                Dim NewY As Long
                NewY = Mine(i).CoorY + Mine(i).YSpeed
                
                DDS_COLLISIONMAP.Lock rMAPCUT, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
                While DDS_COLLISIONMAP.GetLockedPixel(Mine(i).CoorX + 4, NewY + 7) = cWhite
                    NewY = NewY - 1
                    Mine(i).YSpeed = 0
                Wend
                Mine(i).CoorY = NewY
                DDS_COLLISIONMAP.Unlock rMAPCUT
                
                With a
                    .Left = CLng(Mine(i).CoorX - (CHARACTER.X - 144))
                    .Right = .Left + 8
                    .Top = CLng(Mine(i).CoorY - (CHARACTER.Y - 104))
                    .Bottom = .Top + 8
                End With
                
                
                Mine(i).ProjectileColor = Mine(i).ProjectileColor + RGB(1, 1, 1)
                If Mine(i).ProjectileColor >= RGB(222, 222, 222) Then
                    Mine(i).ProjectileColor = RGB(222, 222, 222)
                    Mine(i).TrailAngle = 1
                    Mine(i).Animation = MA_Idle
                Else
                    Mine(i).TrailAngle = 0
                End If
                
                Dim rMine As RECT
                With rMine
                    .Left = Mine(i).AnimationFrame * 8
                    .Right = .Left + 8
                    .Top = Mine(i).Animation * 8
                    .Bottom = .Top + 8
                End With
                
                If a.Left > 0 And a.Right < 320 And a.Top > 0 And a.Bottom < 240 Then
                'draw the bullet
                DDS_Back.Blt a, DDS_WEAP, rMine, DDBLT_KEYSRC
                End If
                  
                'check all of our missles and see if they are active or not
                CheckIfMineStillActive
            
            End If
            
            DoEvents
            
        Next
        
    End If

End Sub
    
Public Sub RailgunFire()

    
    PlaySample "weapon\blaster\blaster1.mp3"
    

    'Advance blasterbullet array
    Dim p As Integer
    
    'Reset boolean variable
    RailFoundInActive = False
    
    If RailIndex = 0 Then 'if we just started
    
        RailIndex = RailIndex + 1
        
    Else 'Look for inactive bullets
    
        'Cycle through the bullets
        For p = 0 To UBound(Rail)
            If Rail(p).Active = False Then
                RailInactiveIndex = p
                RailFoundInActive = True
            End If
            
            DoEvents
            
        Next
        
        'if we didn't find any inactive bullets add
        'a new element to the array
        If RailFoundInActive = False Then
            RailIndex = RailIndex + 1
        End If
        
    End If
    
    'redimension the array holding our bullet info
    ReDim Preserve Rail(RailIndex)
    
    'If we are adding a completely new bullet then:
    If RailFoundInActive = False Then
        Rail(RailIndex).CoorX = CHARACTER.X + 32
        Rail(RailIndex).XSpeed = (Cos(mintMouseAngle) * 20)
        Rail(RailIndex).YSpeed = (Sin(mintMouseAngle) * 20)
        Rail(RailIndex).TrailAngle = mintMouseAngle
        If Rail(RailIndex).XSpeed > 0 Then
            Rail(RailIndex).CoorX = CHARACTER.X + 32 + Rail(RailIndex).XSpeed
        Else
            Rail(RailIndex).CoorX = CHARACTER.X - 2 - Rail(RailIndex).XSpeed
        End If
        Rail(RailIndex).CoorY = CHARACTER.Y + 10
        Rail(RailIndex).ProjectileColor = RGB(255, 0, 0)
        Rail(RailIndex).Active = True
    Else
        'Add a laser to where a previous missle that
        'is now inactive is located
        Rail(RailInactiveIndex).XSpeed = (Cos(mintMouseAngle) * 20)
        Rail(RailInactiveIndex).YSpeed = (Sin(mintMouseAngle) * 20)
        Rail(RailInactiveIndex).TrailAngle = mintMouseAngle
        If Rail(RailInactiveIndex).XSpeed > 0 Then
            Rail(RailInactiveIndex).CoorX = CHARACTER.X + 32 + Rail(RailInactiveIndex).XSpeed
        Else
            Rail(RailInactiveIndex).CoorX = CHARACTER.X - 2 - Rail(RailInactiveIndex).XSpeed
        End If
        Rail(RailInactiveIndex).CoorY = CHARACTER.Y + 10
        Rail(RailInactiveIndex).ProjectileColor = RGB(255, 0, 0)
        Rail(RailInactiveIndex).Active = True
    End If

End Sub

Public Sub DrawRail()

    If RailIndex > 0 Then

        Dim i As Integer, k As Integer, a As RECT, Trail(0 To 64) As RECT, tmpYY As Single
        For i = 0 To RailIndex
            'don't draw anything if the current missle is
            'not active
            If Rail(i).Active = True Then
                
                'advance the laser coordinates
                With Rail(i)
                    .CoorY = .CoorY + .YSpeed
                    .CoorX = .CoorX + .XSpeed
                End With
                            
                
                With a
                    .Left = CLng(Rail(i).CoorX - (CHARACTER.X - 144))
                    .Right = .Left + 2
                    .Top = CLng(Rail(i).CoorY - (CHARACTER.Y - 104))
                    .Bottom = .Top + 2
                End With
                
                For k = 0 To UBound(Trail)
                    Randomize
                    With Trail(k)
                        Dim tLine As Single
                        tLine = CInt(Rnd * 32)
                        .Left = CLng(a.Left + (32 * (Cos(Rail(i).TrailAngle))) - (tLine * (Cos(Rail(i).TrailAngle))))
                        .Right = .Left + 1
                        .Top = CLng(a.Top + (64 * (Sin(Rail(i).TrailAngle))) - (tLine * (Sin(Rail(i).TrailAngle))))
                        .Bottom = .Top + 1
                    End With
                Next k
                        
                For k = 0 To UBound(Trail)
                    If Trail(k).Left > 0 And Trail(k).Right < 320 And Trail(k).Top > 0 And Trail(k).Bottom < 240 Then
                        Randomize
                        DDS_Back.BltColorFill Trail(k), RGB(Rnd * 64 + 191, Rnd * 64, Rnd * 32)
                    End If
                Next k
                
                'If a.Left > 0 And a.Right < 320 And a.Top > 0 And a.Bottom < 240 Then
                ''draw the bullet
                'DDS_Back.BltColorFill a, Rail(i).ProjectileColor
                'End If
                
                
                
                'check all of our missles and see if they are active or not
                CheckIfRailStillActive
            
            End If
            
            DoEvents
            
        Next
        
    End If

End Sub

Private Sub CheckIfRailStillActive()
    'This function checks whether a missle is still active.
    'For this application our criteria is when it goes offscreen
    
    'We pass the laser array to this function and it sets the
    'laser to either true (active) or false (inactive)
    Dim t As Integer
    
    For t = 0 To UBound(Rail)
        'we make missles inactive when they are slightly
        'offscreen
        DDS_COLLISIONMAP.Lock rTOTMAP, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
        If DDS_COLLISIONMAP.GetLockedPixel(Rail(t).CoorX, Rail(t).CoorY) = cWhite Then
            Rail(t).Active = False
        End If
        If Rail(t).CoorX < 0 Or Rail(t).CoorX > MapWidth * 32 Or Rail(t).CoorY < 0 Or Rail(t).CoorY > MapHeight * 32 Then Rail(t).Active = False
        DDS_COLLISIONMAP.Unlock rTOTMAP
        DoEvents
    
    Next
End Sub

Private Sub CheckIfMineStillActive()
    'This function checks whether a missle is still active.
    'For this application our criteria is when it goes offscreen
    
    'We pass the laser array to this function and it sets the
    'laser to either true (active) or false (inactive)
    Dim t As Integer
    
    For t = 0 To UBound(Mine)
        'we make missles inactive when they are slightly
        'offscreen
        If CHARACTER.X + 32 > Mine(t).CoorX And CHARACTER.X < Mine(t).CoorX + 4 And CHARACTER.Y < Mine(t).CoorY And CHARACTER.Y + 32 + 16 > Mine(t).CoorY Then
            If Mine(t).Active Then
                Mine(t).Animation = MA_Explode
                If Mine(t).TrailAngle <> 0 Then
                    Mine(t).Active = False
                    If CHARACTER.Health > 0 Then
                        CHARACTER.Health = CHARACTER.Health - Int(Rnd(150) + 100)
                    End If
                    PlaySample "char/pain/instagib.mp3"
                End If
            End If
        End If
        DoEvents
    Next
End Sub
    

Public Sub BlasterFire()

    
    PlaySample "weapon\blaster\blaster1.mp3"
    

    'Advance blasterbullet array
    Dim p As Integer
    
    'Reset boolean variable
    BBFoundInActive = False
    
    If BBIndex = 0 Then 'if we just started
    
        BBIndex = BBIndex + 1
        
    Else 'Look for inactive bullets
    
        'Cycle through the bullets
        For p = 0 To UBound(BlasterBullets)
            If BlasterBullets(p).Active = False Then
                BBInactiveIndex = p
                BBFoundInActive = True
            End If
            
            DoEvents
            
        Next
        
        'if we didn't find any inactive bullets add
        'a new element to the array
        If BBFoundInActive = False Then
            BBIndex = BBIndex + 1
        End If
        
    End If
    
    'redimension the array holding our bullet info
    ReDim Preserve BlasterBullets(BBIndex)
    
    'If we are adding a completely new bullet then:
    If BBFoundInActive = False Then
        BlasterBullets(BBIndex).CoorX = CHARACTER.X + 32
        BlasterBullets(BBIndex).XSpeed = (Cos(mintMouseAngle) * 5)
        BlasterBullets(BBIndex).YSpeed = (Sin(mintMouseAngle) * 5)
        BlasterBullets(BBIndex).TrailAngle = mintMouseAngle
        If BlasterBullets(BBIndex).XSpeed > 0 Then
            BlasterBullets(BBIndex).CoorX = CHARACTER.X + 32 + BlasterBullets(BBIndex).XSpeed
        Else
            BlasterBullets(BBIndex).CoorX = CHARACTER.X - 2 - BlasterBullets(BBIndex).XSpeed
        End If
        BlasterBullets(BBIndex).CoorY = CHARACTER.Y + 10
        BlasterBullets(BBIndex).ProjectileColor = RGB(0, 0, 255)
        BlasterBullets(BBIndex).Active = True
    Else
        'Add a laser to where a previous missle that
        'is now inactive is located
        BlasterBullets(BBInactiveIndex).XSpeed = (Cos(mintMouseAngle) * 5)
        BlasterBullets(BBInactiveIndex).YSpeed = (Sin(mintMouseAngle) * 5)
        BlasterBullets(BBInactiveIndex).TrailAngle = mintMouseAngle
        If BlasterBullets(BBInactiveIndex).XSpeed > 0 Then
            BlasterBullets(BBInactiveIndex).CoorX = CHARACTER.X + 32 + BlasterBullets(BBInactiveIndex).XSpeed
        Else
            BlasterBullets(BBInactiveIndex).CoorX = CHARACTER.X - 2 - BlasterBullets(BBInactiveIndex).XSpeed
        End If
        BlasterBullets(BBInactiveIndex).CoorY = CHARACTER.Y + 10
        BlasterBullets(BBInactiveIndex).ProjectileColor = RGB(0, 0, 255)
        BlasterBullets(BBInactiveIndex).Active = True
    End If

End Sub

Public Sub DrawBlasterBullets()

    If BBIndex > 0 Then

        Dim i As Integer, k As Integer, a As RECT, Trail(0 To 4) As RECT, tmpYY As Single
        For i = 0 To BBIndex
            'don't draw anything if the current missle is
            'not active
            If BlasterBullets(i).Active = True Then
                
                'advance the laser coordinates
                With BlasterBullets(i)
                    .CoorY = .CoorY + .YSpeed
                    .CoorX = .CoorX + .XSpeed
                End With
                            
                With a
                    .Left = CLng(BlasterBullets(i).CoorX - (CHARACTER.X - 144))
                    .Right = .Left + 1
                    .Top = CLng(BlasterBullets(i).CoorY - (CHARACTER.Y - 104))
                    .Bottom = .Top + 1
                End With
                
                For k = 0 To UBound(Trail)
                    Randomize
                    Dim tLine As Single
                    tLine = CInt(Rnd * 8)
                    With Trail(k)
                        .Left = CLng(a.Left - 8 * (Cos(BlasterBullets(i).TrailAngle)) + (tLine * (Cos(BlasterBullets(i).TrailAngle))))
                        .Right = .Left + 1
                        .Top = CLng(a.Top - 8 * (0.2) + (tLine * (0.4)))
                        .Bottom = .Top + 1
                    End With
                Next k
                        
                For k = 0 To UBound(Trail)
                    If Trail(k).Left > 0 And Trail(k).Right < 320 And Trail(k).Top > 0 And Trail(k).Bottom < 240 Then
                        DDS_Back.BltColorFill Trail(k), RGB(128, 128, 128)
                    End If
                Next k
                
                If a.Left > 0 And a.Right < 320 And a.Top > 0 And a.Bottom < 240 Then
                'draw the bullet
                DDS_Back.BltColorFill a, BlasterBullets(i).ProjectileColor
                End If
                
                
                
                'check all of our missles and see if they are active or not
                CheckIfbbStillActive
            
            End If
            
            DoEvents
            
        Next
        
    End If

End Sub

Private Sub CheckIfbbStillActive()
    'This function checks whether a missle is still active.
    'For this application our criteria is when it goes offscreen
    
    'We pass the laser array to this function and it sets the
    'laser to either true (active) or false (inactive)
    Dim t As Integer, i As Integer
    
    For t = 0 To UBound(BlasterBullets)
        'we make missles inactive when they are slightly
        'offscreen
        DDS_COLLISIONMAP.Lock rTOTMAP, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
        If DDS_COLLISIONMAP.GetLockedPixel(BlasterBullets(t).CoorX, BlasterBullets(t).CoorY) = cWhite Then
            BlasterBullets(t).Active = False
        End If
        
        For i = LBound(BotClient) To UBound(BotClient)
            If BlasterBullets(t).CoorX > BotClient(i).X And BlasterBullets(t).CoorX < BotClient(i).X + 32 And BlasterBullets(t).CoorY > BotClient(i).Y And BlasterBullets(t).CoorY < BotClient(i).Y + 32 Then
                BlasterBullets(t).Active = False
                BotClient(i).Health = BotClient(i).Health - 100
                If BotClient(i).Health <= 0 Then CHARACTER.Frags = CHARACTER.Frags + 1
            End If
        Next i
            
        If BlasterBullets(t).CoorX < 0 Or BlasterBullets(t).CoorX > MapWidth * 32 Or BlasterBullets(t).CoorY < 0 Or BlasterBullets(t).CoorY > MapHeight * 32 Then BlasterBullets(t).Active = False
        DDS_COLLISIONMAP.Unlock rTOTMAP
        DoEvents
    
    Next
End Sub

Public Sub GrenadesFire()

    PlaySample "weapon\grenades\grenades1.wav"
    'Advance blasterbullet array
    Dim p As Integer
    
    'Reset boolean variable
    GrenadesFoundInActive = False
    
    If GrenadesIndex = 0 Then 'if we just started
    
        GrenadesIndex = GrenadesIndex + 1
        
    Else 'Look for inactive bullets
    
        'Cycle through the bullets
        For p = 0 To UBound(Grenades)
            If Grenades(p).Active = False Then
                GrenadesInactiveIndex = p
                GrenadesFoundInActive = True
            End If
            
            DoEvents
            
        Next
        
        'if we didn't find any inactive bullets add
        'a new element to the array
        If GrenadesFoundInActive = False Then
            GrenadesIndex = GrenadesIndex + 1
        End If
        
    End If
    
    'redimension the array holding our bullet info
    ReDim Preserve Grenades(GrenadesIndex)
    
    'If we are adding a completely new bullet then:
    If GrenadesFoundInActive = False Then
        Grenades(GrenadesIndex).TimeLeft = 0
        Grenades(GrenadesIndex).CoorX = CHARACTER.X + 32
        Grenades(GrenadesIndex).XSpeed = (Cos(mintMouseAngle) * 1)
        Grenades(GrenadesIndex).YSpeed = (Sin(mintMouseAngle) * 1)
        Grenades(GrenadesIndex).TrailAngle = mintMouseAngle
        If Grenades(GrenadesIndex).XSpeed > 0 Then
            Grenades(GrenadesIndex).CoorX = CHARACTER.X + 32 + Grenades(GrenadesIndex).XSpeed
        Else
            Grenades(GrenadesIndex).CoorX = CHARACTER.X - 2 - Grenades(GrenadesIndex).XSpeed
        End If
        Grenades(GrenadesIndex).CoorY = CHARACTER.Y + 10
        Grenades(GrenadesIndex).ProjectileColor = RGB(0, 255, 255)
        Grenades(GrenadesIndex).Active = True
    Else
        'Add a laser to where a previous missle that
        'is now inactive is located
        Grenades(GrenadesInactiveIndex).TimeLeft = 0
        Grenades(GrenadesInactiveIndex).CoorX = CHARACTER.X + 32
        Grenades(GrenadesInactiveIndex).XSpeed = (Cos(mintMouseAngle) * 1)
        Grenades(GrenadesInactiveIndex).YSpeed = (Sin(mintMouseAngle) * 1)
        Grenades(GrenadesInactiveIndex).TrailAngle = mintMouseAngle
        If Grenades(GrenadesInactiveIndex).XSpeed > 0 Then
            Grenades(GrenadesInactiveIndex).CoorX = CHARACTER.X + 32 + Grenades(GrenadesInactiveIndex).XSpeed
        Else
            Grenades(GrenadesInactiveIndex).CoorX = CHARACTER.X - 2 - Grenades(GrenadesInactiveIndex).XSpeed
        End If
        Grenades(GrenadesInactiveIndex).CoorY = CHARACTER.Y + 10
        Grenades(GrenadesInactiveIndex).ProjectileColor = RGB(0, 255, 255)
        Grenades(GrenadesInactiveIndex).Active = True
    End If

End Sub

Public Sub DrawGrenades()

    If GrenadesIndex > 0 Then

        Dim i As Integer, k As Integer, a As RECT, Trail(0 To 16) As RECT
        For i = 0 To GrenadesIndex
            'don't draw anything if the current missle is
            'not active
            If Grenades(i).Active = True Then
                'advance the laser coordinates
                Dim tmpYY As Single
                With Grenades(i)
                    .CoorY = .CoorY + (.YSpeed * (.TimeLeft / 2))
                    .CoorX = .CoorX + (.XSpeed * (.TimeLeft / 2))
                    If .TimeLeft < 10 Then .TimeLeft = .TimeLeft + 1
                End With
                
                
                With a
                    .Left = CLng(Grenades(i).CoorX - (CHARACTER.X - 144))
                    .Right = .Left + 2
                    .Top = CLng(Grenades(i).CoorY - (CHARACTER.Y - 104))
                    .Bottom = .Top + 2
                End With
                
                For k = 0 To UBound(Trail)
                    Randomize
                    Dim tLine As Single
                    tLine = CInt(Rnd * 16)
                    With Trail(k)
                        .Left = CLng(a.Left - 16 * (Cos(Grenades(i).TrailAngle)) + (tLine * (Cos(Grenades(i).TrailAngle))))
                        .Right = .Left + 1
                        .Top = CLng(a.Top - 16 * (Sin(Grenades(i).TrailAngle)) + (tLine * (Sin(Grenades(i).TrailAngle))))
                        .Bottom = .Top + 1
                    End With
                Next k
                
                For k = 0 To UBound(Trail)
                    If Trail(k).Left > 0 And Trail(k).Right < 320 And Trail(k).Top > 0 And Trail(k).Bottom < 240 Then
                        DDS_Back.BltColorFill Trail(k), RGB(128, 128, 128)
                    End If
                Next k
                                
                If a.Left > 0 And a.Right < 320 And a.Top > 0 And a.Bottom < 240 Then
                'draw the bullet
                DDS_Back.BltColorFill a, Grenades(i).ProjectileColor
                End If

                'check all of our missles and see if they are active or not
                CheckIfGrenadesStillActive
            
            End If
            
            DoEvents
            
        Next
        
    End If

End Sub

Private Sub CheckIfGrenadesStillActive()
    'This function checks whether a missle is still active.
    'For this application our criteria is when it goes offscreen
    
    'We pass the laser array to this function and it sets the
    'laser to either true (active) or false (inactive)
    Dim t As Integer
    
    For t = 0 To UBound(Grenades)
        'we make missles inactive when they are slightly
        'offscreen
        DDS_COLLISIONMAP.Lock rTOTMAP, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
        If DDS_COLLISIONMAP.GetLockedPixel(Grenades(t).CoorX, Grenades(t).CoorY) = cWhite Then
            Grenades(t).Active = False
        End If
        
        For i = LBound(BotClient) To UBound(BotClient)
            If Grenades(t).CoorX > BotClient(i).X And Grenades(t).CoorX < BotClient(i).X + 32 And Grenades(t).CoorY > BotClient(i).Y And Grenades(t).CoorY < BotClient(i).Y + 32 Then
                Grenades(t).Active = False
                BotClient(i).Health = BotClient(i).Health - 100
                If BotClient(i).Health <= 0 Then CHARACTER.Frags = CHARACTER.Frags + 1
            End If
        Next i
            
        If Grenades(t).CoorX < 0 Or Grenades(t).CoorX > MapWidth * 32 Or Grenades(t).CoorY < 0 Or Grenades(t).CoorY > MapHeight * 32 Then Grenades(t).Active = False
        DDS_COLLISIONMAP.Unlock rTOTMAP
        DoEvents
    
    Next
    
End Sub
 
Public Sub DrawProjectiles()

    DrawBlasterBullets
    DrawGrenades
    DrawRail
    DrawPlacedMines

End Sub























Public Sub CheckForFireWeapon()
    If CHARACTER.Dead Then
        'CharacterSpawn
    Else
        lTickCount11 = GetTickCount()
        If (lTickCount11 - lOldTickCount11) > WeaponReloadTime Then
            If Not CHARACTER.FIRING Then
            'Save the tick count
                FireWeapon
            End If
            lTickCount11 = GetTickCount()
        Else
        End If
    End If
End Sub

Public Sub WeapInit()

    WeapBlaster.Reload
    WeapEnergySword.Reload
    WeapBoingers.Reload
    WeapMines.Reload
    WeapRailgun.Reload

End Sub

Public Sub SwitchWeapon(cWeapon As SelectedWeaponEnum)

    If SelectedWeapon <> cWeapon Then
        PlaySample "weapon\reload.mp3"
    End If

    If cWeapon = Blaster Then
        'If SelectedWeapon = Blaster Then Exit Sub
        ChatFeed "Blaster selected"
        SelectedWeapon = Blaster
    ElseIf cWeapon = Boingers Then
        'If SelectedWeapon = Boingers Then Exit Sub
        If WeapBoingers.GotWeapon = False Then
            ChatFeed "You don't have that weapon"
            Exit Sub
        ElseIf WeapBoingers.AmmoCurrent <= 0 Then
            ChatFeed "You don't have any rockets"
            Exit Sub
        End If
        ChatFeed "Rockets selected"
        SelectedWeapon = Boingers
    ElseIf cWeapon = EnergySword Then
        'If SelectedWeapon = EnergySword Then Exit Sub
        ChatFeed "Energy Sword selected"
        SelectedWeapon = EnergySword
    ElseIf cWeapon = Mines Then
        'If SelectedWeapon = Mines Then Exit Sub
        If WeapMines.GotWeapon = False Then
            ChatFeed "You don't have that weapon"
            Exit Sub
        ElseIf WeapMines.AmmoCurrent <= 0 Then
            ChatFeed "You don't have any mines"
            Exit Sub
        End If
        ChatFeed "Mines selected"
        SelectedWeapon = Mines
    ElseIf cWeapon = Railgun Then
        'If SelectedWeapon = Railgun Then Exit Sub
        If WeapRailgun.GotWeapon = False Then
            ChatFeed "You don't have that weapon"
            Exit Sub
        ElseIf WeapBlaster.AmmoCurrent <= 0 Then
            ChatFeed "You don't have any batteries"
            Exit Sub
        End If
        ChatFeed "Railgun selected"
        SelectedWeapon = Railgun
    Else
        SelectedWeapon = None
    End If

End Sub
