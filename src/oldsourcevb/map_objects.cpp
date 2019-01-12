Attribute VB_Name = "mod_MapObjects"
Private Type DOORTYPE
    X As Long
    Y As Long
    Y_Open As Long
    Y_Closed As Long
    PASSKEY As Long
    WAITTIME As Integer
    HOLDTIME As Integer
    ACTUALTIME As Integer
    OPENING As Boolean
End Type
Public obj_Door(0 To 64) As DOORTYPE
Public DoorCount As Integer

Public Enum MapObjectType
    tHealth = 0
    tMegaHealth = 1
    tShield = 2
    tPowerup = 3
    tGrenades = 4
    tBatteries = 5
    tMines = 6
    tHeartSensor = 7
    tArmorShard = 8
    tRailgun = 9
    tBoingers = 10
    tCapacitor = 11
    tSuit = 12
    tACK = 99
End Enum
Public obj_Type As MapObjectType

Public GotMapItemsArray As Boolean

Public obj_Teleport(0 To 255) As New cls_MapItem

Public ObjectAnimationFrame As Long
'---------------.
' O b j e c t s |
'---------------'

'Health
Public obj_HealthPack(0 To 255) As New cls_MapItem
Public obj_MegaHealthPack(0 To 255) As New cls_MapItem

'Ammo
Public obj_Batteries(0 To 255) As New cls_MapItem
Public obj_GrenadesAmmo(0 To 255) As New cls_MapItem

'Weapons
Public obj_MinesAmmo(0 To 255) As New cls_MapItem
Public obj_Railgun(0 To 32) As New cls_MapItem
Public obj_Boingers(0 To 32) As New cls_MapItem

'Flags
Public obj_FlagBlue As New cls_MapItem
Public obj_FlagRed As New cls_MapItem

'Extras
Public obj_Shield(0 To 255) As New cls_MapItem
Public obj_Power(0 To 255) As New cls_MapItem
Public obj_HeartSens(0 To 255) As New cls_MapItem
Public obj_Armor(0 To 255) As New cls_MapItem
Public obj_Cap(0 To 255) As New cls_MapItem
Public obj_Suit(0 To 32) As New cls_MapItem

Public obj_Count(0 To 13) As Integer

Public Sub ResetMapObjects()

Dim i As Integer
For i = 0 To UBound(obj_Count)
    obj_Count(i) = 0
Next i
DoorCount = 0
For i = 0 To UBound(obj_Door)
    With obj_Door(i)
        .ACTUALTIME = 0
        .HOLDTIME = 0
        .PASSKEY = 0
        .WAITTIME = 0
        .X = 0
        .Y = 0
        .Y_Open = 0
    End With
Next i
    
obj_FlagBlue.Flag1 = 0 '100 points for score.
obj_FlagBlue.Flag2 = "YOU GOT THE FLAG!"
obj_FlagBlue.ID = "f"
obj_FlagBlue.Spawned = False
obj_FlagBlue.Spawntime = 0 'seconds
obj_FlagBlue.SpawntimeCurrent = 0
obj_FlagBlue.X = 0
obj_FlagBlue.Y = 0
            
obj_FlagRed.Flag1 = 0 '100 points for score.
obj_FlagRed.Flag2 = "YOU GOT THE FLAG!"
obj_FlagRed.ID = "f"
obj_FlagRed.Spawned = False
obj_FlagRed.Spawntime = 0 'seconds
obj_FlagRed.SpawntimeCurrent = 0
obj_FlagRed.X = 0
obj_FlagRed.Y = 0

End Sub

Public Sub CreateMapObject(sType As String, q As Long, w As Long)

Randomize

If sType = "x" Then
                
    obj_FlagBlue.Flag1 = 100 '100 points for score.
    obj_FlagBlue.Flag2 = "YOU GOT THE FLAG!"
    obj_FlagBlue.ID = "x"
    obj_FlagBlue.Spawned = True
    obj_FlagBlue.Spawntime = 0 'seconds
    obj_FlagBlue.SpawntimeCurrent = 0
    obj_FlagBlue.X = q
    obj_FlagBlue.Y = w
    
ElseIf sType = "y" Then
                
    obj_FlagRed.Flag1 = 100 '100 points for score.
    obj_FlagRed.Flag2 = "YOU GOT THE FLAG!"
    obj_FlagRed.ID = "y"
    obj_FlagRed.Spawned = True
    obj_FlagRed.Spawntime = 0 'seconds
    obj_FlagRed.SpawntimeCurrent = 0
    obj_FlagRed.X = q
    obj_FlagRed.Y = w
                                
ElseIf sType = "a" Then
            
    'Create a new instance of the healthpak
    Randomize
                
    obj_HealthPack(obj_Count(0)).Flag1 = (Int(Rnd * 100) + 50) '50-150 in health
    obj_HealthPack(obj_Count(0)).Flag2 = "YOU GOT MEDPACK WORTH " & CStr(obj_HealthPack(obj_Count(0)).Flag1)
    obj_HealthPack(obj_Count(0)).ID = "a"
    obj_HealthPack(obj_Count(0)).Spawned = True
    obj_HealthPack(obj_Count(0)).Spawntime = 30 'seconds
    obj_HealthPack(obj_Count(0)).SpawntimeCurrent = 0
    obj_HealthPack(obj_Count(0)).X = q
    obj_HealthPack(obj_Count(0)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tHealth, True, obj_Count(0)
    
    obj_Count(0) = obj_Count(0) + 1
    
ElseIf sType = "l" Then
                
    Randomize
                
    obj_MegaHealthPack(obj_Count(1)).Flag1 = 1000 '500 in health
    obj_MegaHealthPack(obj_Count(1)).Flag2 = "MEGA HEALTH!"
    obj_MegaHealthPack(obj_Count(1)).ID = "l"
    obj_MegaHealthPack(obj_Count(1)).Spawned = False
    obj_MegaHealthPack(obj_Count(1)).Spawntime = 120 'seconds
    obj_MegaHealthPack(obj_Count(1)).SpawntimeCurrent = 0
    obj_MegaHealthPack(obj_Count(1)).X = q
    obj_MegaHealthPack(obj_Count(1)).Y = w
                
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tMegaHealth, True, obj_Count(1)
    
    obj_Count(1) = obj_Count(1) + 1

ElseIf sType = "e" Then

    Randomize
                
    obj_Batteries(obj_Count(5)).Flag1 = (Int(Rnd * 10) + 10) '10 - 20
    obj_Batteries(obj_Count(5)).Flag2 = "YOU GOT " & CStr(obj_Batteries(obj_BatteriesCount).Flag1) & " BATTERIES!"
    obj_Batteries(obj_Count(5)).ID = "e"
    obj_Batteries(obj_Count(5)).Spawned = True
    obj_Batteries(obj_Count(5)).Spawntime = 15 'seconds
    obj_Batteries(obj_Count(5)).SpawntimeCurrent = 0
    obj_Batteries(obj_Count(5)).X = q
    obj_Batteries(obj_Count(5)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tBatteries, True, obj_Count(5)
                
    obj_Count(5) = obj_Count(5) + 1
    
ElseIf sType = "d" Then
                       
    Randomize
                
    obj_GrenadesAmmo(obj_Count(4)).Flag1 = (Int(Rnd * 8) + 2)
    obj_GrenadesAmmo(obj_Count(4)).Flag2 = "YOU GOT " & CStr(obj_GrenadesAmmo(obj_GrenadesAmmoCount).Flag1) & " ROCKETS!"
    obj_GrenadesAmmo(obj_Count(4)).ID = "d"
    obj_GrenadesAmmo(obj_Count(4)).Spawned = True
    obj_GrenadesAmmo(obj_Count(4)).Spawntime = 30 'seconds
    obj_GrenadesAmmo(obj_Count(4)).SpawntimeCurrent = 0
    obj_GrenadesAmmo(obj_Count(4)).X = q
    obj_GrenadesAmmo(obj_Count(4)).Y = w
                
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tGrenades, True, obj_Count(4)
    
    obj_Count(4) = obj_Count(4) + 1
    
ElseIf sType = "f" Then
                
    Randomize
                
    obj_MinesAmmo(obj_Count(6)).Flag1 = (Int(Rnd * 5) + 1)
    If obj_MinesAmmo(obj_Count(6)).Flag1 = 1 Then
        obj_MinesAmmo(obj_Count(6)).Flag2 = "YOU GOT " & CStr(obj_MinesAmmo(obj_MinesAmmoCount).Flag1) & " MINE!"
    Else
        obj_MinesAmmo(obj_Count(6)).Flag2 = "YOU GOT " & CStr(obj_MinesAmmo(obj_MinesAmmoCount).Flag1) & " MINES!"
    End If
    obj_MinesAmmo(obj_Count(6)).ID = "f"
    obj_MinesAmmo(obj_Count(6)).Spawned = True
    obj_MinesAmmo(obj_Count(6)).Spawntime = 120 'seconds
    obj_MinesAmmo(obj_Count(6)).SpawntimeCurrent = 0
    obj_MinesAmmo(obj_Count(6)).X = q
    obj_MinesAmmo(obj_Count(6)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tMines, True, obj_Count(6)
                
    obj_Count(6) = obj_Count(6) + 1
    

ElseIf sType = "i" Then
            
    obj_Railgun(obj_Count(9)).Flag1 = 50
    obj_Railgun(obj_Count(9)).Flag2 = WeapRailgun.MsgPickup
    obj_Railgun(obj_Count(9)).ID = "i"
    obj_Railgun(obj_Count(9)).Spawned = True
    obj_Railgun(obj_Count(9)).Spawntime = 30 'seconds
    obj_Railgun(obj_Count(9)).SpawntimeCurrent = 0
    obj_Railgun(obj_Count(9)).X = q
    obj_Railgun(obj_Count(9)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tRailgun, True, obj_Count(9)
    
    obj_Count(9) = obj_Count(9) + 1
    
ElseIf sType = "j" Then
            
    obj_Boingers(obj_Count(10)).Flag1 = WeapBoingers.AmmoCurrent
    obj_Boingers(obj_Count(10)).Flag2 = WeapBoingers.MsgPickup
    obj_Boingers(obj_Count(10)).ID = "j"
    obj_Boingers(obj_Count(10)).Spawned = True
    obj_Boingers(obj_Count(10)).Spawntime = 30 'seconds
    obj_Boingers(obj_Count(10)).SpawntimeCurrent = 0
    obj_Boingers(obj_Count(10)).X = q
    obj_Boingers(obj_Count(10)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tBoingers, True, obj_Count(10)
    
    obj_Count(10) = obj_Count(10) + 1
    
ElseIf sType = "b" Then
            
    obj_Shield(obj_Count(2)).Flag1 = 30
    obj_Shield(obj_Count(2)).Flag2 = "YOU GOT THE SHIELD!"
    obj_Shield(obj_Count(2)).ID = "b"
    obj_Shield(obj_Count(2)).Spawned = False
    obj_Shield(obj_Count(2)).Spawntime = 60 'seconds
    obj_Shield(obj_Count(2)).SpawntimeCurrent = 0
    obj_Shield(obj_Count(2)).X = q
    obj_Shield(obj_Count(2)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tShield, True, obj_Count(2)
    
    obj_Count(2) = obj_Count(2) + 1
                        
ElseIf sType = "c" Then
            
    obj_Power(obj_Count(3)).Flag1 = 3
    obj_Power(obj_Count(3)).Flag2 = "YOU GOT THE JUMP PACK!"
    obj_Power(obj_Count(3)).ID = "c"
    obj_Power(obj_Count(3)).Spawned = True
    obj_Power(obj_Count(3)).Spawntime = 120 'seconds
    obj_Power(obj_Count(3)).SpawntimeCurrent = 0
    obj_Power(obj_Count(3)).X = q
    obj_Power(obj_Count(3)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tPowerup, True, obj_Count(3)
    
    obj_Count(3) = obj_Count(3) + 1
    
ElseIf sType = "g" Then
            
    obj_HeartSens(obj_Count(7)).Flag1 = 0
    obj_HeartSens(obj_Count(7)).Flag2 = "YOU GOT THE HEARTBEAT SENSOR!"
    obj_HeartSens(obj_Count(7)).ID = "g"
    obj_HeartSens(obj_Count(7)).Spawned = True
    obj_HeartSens(obj_Count(7)).Spawntime = 60 'seconds
    obj_HeartSens(obj_Count(7)).SpawntimeCurrent = 0
    obj_HeartSens(obj_Count(7)).X = q
    obj_HeartSens(obj_Count(7)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tHeartSensor, True, obj_Count(7)
    
    obj_Count(7) = obj_Count(7) + 1
    
ElseIf sType = "h" Then

    Randomize
    obj_Armor(obj_Count(8)).Flag1 = Int((Rnd * 40) + 20)
    obj_Armor(obj_Count(8)).Flag2 = "YOU GOT " & CStr(obj_Armor(obj_Count(8)).Flag1) & " ARMOR SHARDS!"
    obj_Armor(obj_Count(8)).ID = "h"
    obj_Armor(obj_Count(8)).Spawned = True
    obj_Armor(obj_Count(8)).Spawntime = 30 'seconds
    obj_Armor(obj_Count(8)).SpawntimeCurrent = 0
    obj_Armor(obj_Count(8)).X = q
    obj_Armor(obj_Count(8)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tArmorShard, True, obj_Count(8)
    
    obj_Count(8) = obj_Count(8) + 1
    
ElseIf sType = "k" Then

    obj_Cap(obj_Count(11)).Flag1 = 100
    obj_Cap(obj_Count(11)).Flag2 = "MAX BATTERIES INCREASED TO "
    obj_Cap(obj_Count(11)).ID = "k"
    obj_Cap(obj_Count(11)).Spawned = True
    obj_Cap(obj_Count(11)).Spawntime = 240 'seconds
    obj_Cap(obj_Count(11)).SpawntimeCurrent = 0
    obj_Cap(obj_Count(11)).X = q
    obj_Cap(obj_Count(11)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tCapacitor, True, obj_Count(11)
    
    obj_Count(11) = obj_Count(11) + 1
    
ElseIf sType = "Z" Then

    obj_Teleport(obj_Count(12)).Flag1 = 0
    obj_Teleport(obj_Count(12)).Flag2 = ""
    obj_Teleport(obj_Count(12)).ID = "Z"
    obj_Teleport(obj_Count(12)).Spawned = True
    obj_Teleport(obj_Count(12)).Spawntime = 2 'seconds
    obj_Teleport(obj_Count(12)).SpawntimeCurrent = 0
    obj_Teleport(obj_Count(12)).X = q
    obj_Teleport(obj_Count(12)).Y = w
    
    obj_Count(12) = obj_Count(12) + 1
    
ElseIf sType = "¤" Then
            
    obj_Suit(obj_Count(13)).Flag1 = 0
    obj_Suit(obj_Count(13)).Flag2 = "YOU GOT THE DATA!"
    obj_Suit(obj_Count(13)).ID = "¤"
    obj_Suit(obj_Count(13)).Spawned = True
    obj_Suit(obj_Count(13)).Spawntime = 999 'seconds
    obj_Suit(obj_Count(13)).SpawntimeCurrent = 0
    obj_Suit(obj_Count(13)).X = q
    obj_Suit(obj_Count(13)).Y = w
    
    If NetworkStatus = SUCCESS And Not GotMapItemsArray Then SendItem tSuit, True, obj_Count(13)
    
    obj_Count(13) = obj_Count(13) + 1

ElseIf sType = "/" Then
    With obj_Door(DoorCount)
        .ACTUALTIME = 0
        .HOLDTIME = 30
        .WAITTIME = 0
        .PASSKEY = 0
        .X = q
        .Y = w - 64
        .Y_Open = .Y - 90
        .Y_Closed = .Y
        .OPENING = False
    End With
    DoorCount = DoorCount + 1
End If

End Sub


Public Sub DrawMapObject(tObject As MapObjectType)

    Dim RBAPACK As RECT
    Dim rBAPack2 As RECT
    
    Dim q As Long, w As Long, i As Integer
        
        Dim tSpawn As Boolean
        
        For i = 0 To obj_Count(tObject) - 1
            tSpawn = False
            If tObject = tHealth Then
                If obj_HealthPack(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 0
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_HealthPack(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_HealthPack(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tShield Then
                If obj_Shield(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 32
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_Shield(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_Shield(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tPowerup Then
                If obj_Power(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 64
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_Power(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_Power(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tSuit Then
                If obj_Suit(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 416
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_Suit(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_Suit(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tGrenades Then
                If obj_GrenadesAmmo(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 96
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_GrenadesAmmo(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_GrenadesAmmo(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tBatteries Then
                If obj_Batteries(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 128
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_Batteries(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_Batteries(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tMines Then
                If obj_MinesAmmo(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 160
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_MinesAmmo(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_MinesAmmo(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tHeartSensor Then
                If obj_HeartSens(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 192
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_HeartSens(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_HeartSens(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tArmorShard Then
                If obj_Armor(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 224
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_Armor(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_Armor(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tRailgun Then
                If obj_Railgun(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 256
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_Railgun(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_Railgun(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tBoingers Then
                If obj_Boingers(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 288
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_Boingers(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_Boingers(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tCapacitor Then
                If obj_Cap(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 320
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_Cap(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_Cap(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            ElseIf tObject = tMegaHealth Then
                If obj_MegaHealthPack(i).Spawned Then
                    rBAPack2.Left = ObjectAnimationFrame
                    rBAPack2.Right = rBAPack2.Left + 32
                    rBAPack2.Top = 480
                    rBAPack2.Bottom = rBAPack2.Top + 32
                    RBAPACK.Left = obj_MegaHealthPack(i).X - (CHARACTER.X - 144)
                    RBAPACK.Right = RBAPACK.Left + 32
                    RBAPACK.Top = obj_MegaHealthPack(i).Y - (CHARACTER.Y - 104)
                    RBAPACK.Bottom = RBAPACK.Top + 32
                    tSpawn = True
                End If
            End If
            
            Dim tmpCutL As Integer, tmpCutR As Integer, tmpCutT As Integer, tmpCutB As Integer
            
            'If rBAPack.Left < 0 Then
            '    tmpCutL = 0 - rBAPack.Left
            '    rBAPack.Left = 0
            'End If
            'If rBAPack.Right > 320 Then
            '    tmpCutR = 320 - rBAPack.Right
            '    rBAPack.Right = 320
            'End If
            'If rBAPack.Top < 0 Then
            '    tmpCutT = 0 - rBAPack.Top
            '    rBAPack.Top = 0
            'End If
            'If rBAPack.Bottom > 240 Then
            '    tmpCutB = 240 - rBAPack.Bottom
            '    rBAPack.Bottom = 240
            'End If
            

                
            If tSpawn Then DDS_Back.BltFast RBAPACK.Left, RBAPACK.Top, DDS_Objects, rBAPack2, DDBLTFAST_SRCCOLORKEY
            
            
            DoEvents
            
        Next i

        
            

End Sub
