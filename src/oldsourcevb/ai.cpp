Attribute VB_Name = "mod_AI"
Public Enum BotState
    SEARCHING = 0
    GETHEALTH = 1
    AGRESSIVEATTACK = 2
    DEFENSIVEATTACK = 3
    GETARMOR = 4
    GETSHIELD = 5
End Enum

Public BotClient() As New cls_BotClient
Public StoryEnemy(0 To 255) As New cls_StoryEnemy
Public StoryEnemyCount(8) As Integer

Public Sub SwitchStateOfMind(iBot As Integer)

    If iBot < LBound(BotClient) Or iBot > UBound(BotClient) Then Exit Sub
    If BotClient(iBot).Dead Then Exit Sub
    
    Randomize
    Dim tState As Integer
    tState = CInt(Rnd * 5)
    
    BotClient(iBot).AIState = SEARCHING
    If BotClient(iBot).MoveX <> 0 Then
        BotClient(iBot).MoveX = -BotClient(iBot).MoveX
    Else
        BotClient(iBot).MoveX = 5
    End If

End Sub

Public Sub DoBotState()

Dim iBot As Integer
For iBot = 0 To UBound(BotClient)

If BotClient(iBot).AIState = SEARCHING Then
    'LOCK!!!
    DDS_COLLISIONMAP.Lock rTOTMAP, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0

    If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 2, BotClient(iBot).Y + 20) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 34, BotClient(iBot).Y + 20) = cWhite Then
        BotClient(iBot).MoveX = -BotClient(iBot).MoveX
    End If
    
    
    If BotClient(iBot).MoveX > 0 Then
        If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 64 + 16, BotClient(iBot).Y + 16) = cWhite And DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 64 + 16, BotClient(iBot).Y - 64 - 16) <> cWhite Then
            If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, BotClient(iBot).Y - 16) <> cWhite Then BotClient(iBot).Jump
        ElseIf DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 34, BotClient(iBot).Y + 36) = cBlack Then
            If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 192 + 16, BotClient(iBot).Y + 32 + 16) = cWhite Then 'And DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 192 + 16, BotClient(iBot).Y - 32 - 16) <> cWhite Then
                BotClient(iBot).Jump
            ElseIf DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 64 + 16, BotClient(iBot).Y - 16) = cWhite And DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 64 + 16, BotClient(iBot).Y - 32 - 16) = cBlack Then ' Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 64 + 16, BotClient(iBot).Y - 16 - 32) = cWhite Then
                BotClient(iBot).Jump
            ElseIf DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 + 16, BotClient(iBot).Y + 36 + 64) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 + 16, BotClient(iBot).Y + 36 + 32) <> cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 + 16, BotClient(iBot).Y + 36 + 96) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 32 + 16, BotClient(iBot).Y + 36 + 128) = cWhite Then
                
            Else
                BotClient(iBot).MoveX = -BotClient(iBot).MoveX
            End If
        End If
    ElseIf BotClient(iBot).MoveX < 0 Then
        If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 64 + 16, BotClient(iBot).Y + 16) = cWhite And DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 64 + 16, BotClient(iBot).Y - 64 - 16) <> cWhite Then
            If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X + 16, BotClient(iBot).Y - 16) <> cWhite Then BotClient(iBot).Jump
        ElseIf DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 2, BotClient(iBot).Y + 36) = cBlack Then
            If DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 192 + 16, BotClient(iBot).Y + 32 + 16) = cWhite Then 'And DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 192 + 16, BotClient(iBot).Y - 32 - 16) <> cWhite Then
                BotClient(iBot).Jump
            ElseIf DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 64 - 16, BotClient(iBot).Y - 16) = cWhite And DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 64 - 16, BotClient(iBot).Y - 32 - 16) = cBlack Then ' Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 64 - 16, BotClient(iBot).Y - 16 - 32) = cWhite Then
                BotClient(iBot).Jump
            ElseIf DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 32 + 16, BotClient(iBot).Y + 36 + 64) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 32 + 16, BotClient(iBot).Y + 36 + 32) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 32 + 16, BotClient(iBot).Y + 36 + 96) = cWhite Or DDS_COLLISIONMAP.GetLockedPixel(BotClient(iBot).X - 32 + 16, BotClient(iBot).Y + 36 + 128) = cWhite Then
            
            Else
                BotClient(iBot).MoveX = -BotClient(iBot).MoveX
            End If
        End If
    End If
    'UNLOCK!!
    DDS_COLLISIONMAP.Unlock rTOTMAP
Else
End If






If BotClient(iBot).MoveX <> 0 Then
    If BotClient(iBot).MoveX < 0 Then
        BotClient(iBot).ReverseFlag = True
    Else
        BotClient(iBot).ReverseFlag = False
    End If
    
    BotClient(iBot).Animation = RUNNING
    BotClient(iBot).AnimationFrame = CHARACTER.ANIMATIONNUM
Else
    BotClient(iBot).Animation = STANDING
End If

Next iBot
End Sub












Public Sub CreateBots(Optional Nick As String = "")

Dim i As Integer

On Local Error GoTo FIRSTBOT

Dim tmpBots As Integer
tmpBots = UBound(BotClient)
ReDim BotClient(tmpBots + 1)

    
    
    For i = tmpBots To UBound(BotClient)
        BotClient(i).ClientInit Nick
        BotClient(i).Animation = STANDING
        BotClient(i).AnimationFrame = 0
        BotClient(i).AnimationLen = 1
        
        DoEvents
        
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("written bot nr '" & CStr(i) & "'")
        
    Next i

Exit Sub

FIRSTBOT:

ReDim BotClient(0)

    For i = 0 To UBound(BotClient)
        BotClient(i).ClientInit Nick
        
        
        
        BotClient(i).Animation = STANDING
        BotClient(i).AnimationFrame = 0
        BotClient(i).AnimationLen = 1
        
        DoEvents
        
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("written bot nr '" & CStr(i) & "'")
        
    Next i

End Sub

Public Sub TerminateBots()

'on local error Resume Next



    Dim i As Integer
    
    For i = LBound(BotClient) To UBound(BotClient)
        Set BotClient(i) = Nothing
        
        DoEvents
        
        
        
    Next i

End Sub
