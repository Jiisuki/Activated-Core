Attribute VB_Name = "mod_Network"
'Option Explicit

'Public blnMyTurn As Boolean
Private Const AppGuid = "{2E2666B3-0799-4659-ADA8-75D16D4D1F93}" 'ActCore Unique GUID
Private Const intServerPort As Integer = 5231    '//Use 5231 as serverport (we'll listen on that port)

Public ServerI As DPN_APPLICATION_DESC

Public JoinIpAddress As String

Public ObjDPClient As DirectPlay8Client         '//DP client object, for sending and lots of other stuff
Public ObjDPClientAddress As DirectPlay8Address '//Client IP Address, Port
Public ObjDPServerAddress As DirectPlay8Address '//Server IP Address, Port
Public ObjDX8 As DirectX8

Public Const bPacketChat As Byte = 1        '//constant for chat message
Public Const bPacketIdent As Byte = 2       '//constant for the message that will let the server know who we are
Public Const bPacketID As Byte = 3
Public Const bPacketPosition As Byte = 4
Public Const bPacketItem As Byte = 5
Public Const bPacketAnim As Byte = 6
Public Const bPacketAnimFrame As Byte = 7
Public Const bPacketReverseFlag As Byte = 8
Public Const bPacketMap As Byte = 10
Public bPacketMotD(0 To 2) As Byte
Public Const bPacketNotice As Byte = 14
Public Const bPacketQuit As Byte = 15        '//constant for player quit messages
Public Const bPacketGotShield As Byte = 16
Public Const bPacketHealth As Byte = 17
Public Const bPacketFrags As Byte = 18
Public Const bPacketStartGame As Byte = 19


Public PacketSpeed As Integer

Public Enum ConnectionState
    INITIALIZING = 0
    NOTCONNECTED = 1
    SUCCESS = 2
    CONNECTING = 3
End Enum

Public strPlayerName As String
Public ServerName As String
Public NetworkStatus As ConnectionState

Public bMotD0 As String, bMotD1 As String, bMotD2 As String, bMotNotice As String

Public BoardArray(0 To 8) As Byte  '//This will contain the status of our board

Public udtPlayers() As New cls_BotClient
Public bPlayerCount As Integer

Public bMyType As Byte
Public lngMyPlayerID As Long

Public Sub SendPhysicsPackets()

    lTickCount12 = GetTickCount()
    
    
    If (lTickCount12 - lOldTickCount12) > PacketSpeed Then
        'Save the tick count
        lOldTickCount12 = GetTickCount
        SendPosition CStr(CHARACTER.X), CStr(CHARACTER.Y)
        SendAnim
        SendAnimFrame
        SendRevFlag
        SendGotShield
        
    End If


End Sub


Public Sub InitClient()
    'on local error GoTo ERRORHANDLER
    
    NetworkStatus = INITIALIZING
    
    '//Purpose: Initialize DirectPlay objects
    Set ObjDX8 = New DirectX8
    Set ObjDPClient = ObjDX8.DirectPlayClientCreate              '//Create DirectPlay Client
    Set ObjDPClientAddress = ObjDX8.DirectPlayAddressCreate      '//Create Client DP address
    Set ObjDPServerAddress = ObjDX8.DirectPlayAddressCreate      '//Create Server DP address
    ObjDPClient.RegisterMessageHandler frmMain                   '//Register Server message handler, our form!
    ObjDPClientAddress.SetSP DP8SP_TCPIP                         '//Configure Client address for TCP/IP
    ObjDPServerAddress.SetSP DP8SP_TCPIP                         '//'Configure Server address for TCP/IP
    ObjDPServerAddress.AddComponentLong DPN_KEY_PORT, intServerPort '//Add the serverport to the ServerAddress
    
    Exit Sub

ERRORHANDLER:
    '//If we get an error, show where, what, and exit!
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "Error #" & Err.Number & ": " & Err.Description & "in Direct Play INIT"
    Shutdown
    
End Sub

Public Sub ClientConnect(tJoinAddress As String)
    'on local error GoTo ERRORHANDLER
    '//Purpose: Connect to the server
    
    NetworkStatus = CONNECTING
    gSTARTED = False
    bQuit = True
    
    Dim AppDesc As DPN_APPLICATION_DESC  '//Application description
    
    If Len(tJoinAddress) = 0 Then Exit Sub  '//user has entered an IP address/Host name

    ObjDPServerAddress.AddComponentString DPN_KEY_HOSTNAME, tJoinAddress '//Add this remote host to the server connection address
    AppDesc.guidApplication = AppGuid   '//This is a Guid, to indentify all your clients (for enumeration)
    
    If CHARACTER.name = "" Then CHARACTER.name = GetRandomName
    
    '//Set the player name
    SetClientName

    '//We've got everything...Connect!
    
    '//If we are connected a "connect complete" event will trigger in frmClient
    ObjDPClient.Connect AppDesc, ObjDPServerAddress, ObjDPClientAddress, 0, CHARACTER.name, Len(CHARACTER.name)
    NetworkStatus = SUCCESS
    
    For i = 0 To (UBound(ChatLine) - 1)
        ChatLine(i).chatText = ""
        DoEvents
    Next i
        
    Exit Sub

ERRORHANDLER:
    WriteEngineLOG LOGFILE, "Error #" & Err.Number & ": " & Err.Description & " in mdlDirectPlayConnect"
    Shutdown
    
End Sub

Public Sub SetClientName()
    Dim PlayerInfo As DPN_PLAYER_INFO
    '//Set up peer info
    PlayerInfo.name = CHARACTER.name
    PlayerInfo.lInfoFlags = DPNINFO_NAME
    ObjDPClient.SetClientInfo PlayerInfo, DPNOP_SYNC
End Sub

Public Sub UnloadClient()

'on local error GoTo ERRORHANDLER
    If NetworkStatus = SUCCESS Then
        SendQuit
        NetworkStatus = NOTCONNECTED
    End If
    
    Exit Sub
    
    '//Cancel all operations
    ObjDPClient.CancelAsyncOperation 0, DPNCANCEL_ALL_OPERATIONS

    '//Unregister messagehandler
    ObjDPClient.UnRegisterMessageHandler
    
    '//Close connection
    ObjDPClient.Close
    
    '//Remove clientObject from memory
    Set ObjDPClient = Nothing
    
    '//Remove clientaddress from memory
    Set ObjDPClientAddress = Nothing
    
    '//Remove DirectX from memory
    Set ObjDX8 = Nothing
    
    NetworkStatus = NOTCONNECTED
    Exit Sub
    
ERRORHANDLER:
    'Shutdown
    
End Sub

Public Sub SendChat(strMessage As String)
    
 If Not NetworkStatus = SUCCESS Then Exit Sub
    
    Dim bByteBuffer() As Byte, lngOffset As Long
    
    '//Check if there's anything usefull in the chat message
    If Len(strMessage) = 0 Then Exit Sub
    
    '//New packet
    lngOffset = NewBuffer(bByteBuffer)
    
    '//Add packet header
    Call AddDataToBuffer(bByteBuffer, bPacketChat, SIZE_BYTE, lngOffset)
    
    '//Add chat message
    Call AddStringToBuffer(bByteBuffer, CHARACTER.name & ": " & strMessage, lngOffset)

    '//Send the chat message
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_NOLOOPBACK
    DoEvents
    
End Sub

Public Sub SendStartGame()
    
If Not NetworkStatus = SUCCESS Then Exit Sub
    
    Dim bByteBuffer() As Byte, lngOffset As Long
    
    '//New packet
    lngOffset = NewBuffer(bByteBuffer)
    
    '//Add packet header
    Call AddDataToBuffer(bByteBuffer, bPacketStartGame, SIZE_BYTE, lngOffset)
    
        '//Add chat message
    Call AddStringToBuffer(bByteBuffer, CHARACTER.name & " STARTED THE GAME!", lngOffset)

    '//Send the chat message
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_NOLOOPBACK
    DoEvents
    
End Sub


Public Sub SendPosition(strX As String, strY As String)
    Dim bByteBuffer() As Byte, lngOffset As Long
    If Len(strX) = 0 Or Len(strY) = 0 Then Exit Sub
    
    lngOffset = NewBuffer(bByteBuffer)
    
    Dim tmpID As Long, i As Integer
    
    For i = 0 To UBound(udtPlayers)
        If udtPlayers(i).iPlayerID = lngMyPlayerID Then
            tmpID = i
            Exit For
        End If
    Next i
    
    Call AddDataToBuffer(bByteBuffer, bPacketPosition, SIZE_BYTE, lngOffset)
    
    Call AddStringToBuffer(bByteBuffer, CStr(tmpID) & " " & strX, lngOffset)
    Call AddStringToBuffer(bByteBuffer, CStr(tmpID) & " " & strY, lngOffset)
    
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_NOLOOPBACK
    DoEvents
    
End Sub

Public Sub SendItem(tItem As MapObjectType, tSpawned As Boolean, tItemNum As Integer)
    Dim bByteBuffer() As Byte, lngOffset As Long
    
    lngOffset = NewBuffer(bByteBuffer)
        
    Call AddDataToBuffer(bByteBuffer, bPacketItem, SIZE_BYTE, lngOffset)
    
    Call AddStringToBuffer(bByteBuffer, CStr(tItem) & " " & CStr(tSpawned), lngOffset)
    Call AddStringToBuffer(bByteBuffer, CStr(tItemNum), lngOffset)
    
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_GUARANTEED + DPNSEND_NOLOOPBACK
    DoEvents
    
End Sub

Public Sub SendUpdateItem(tItem As MapObjectType, tItemNum As Integer)
    Dim bByteBuffer() As Byte, lngOffset As Long
    
    lngOffset = NewBuffer(bByteBuffer)
        
    Call AddDataToBuffer(bByteBuffer, bPacketItem, SIZE_BYTE, lngOffset)
    
    Call AddStringToBuffer(bByteBuffer, CStr(tItem) & " " & CStr(tItemNum), lngOffset)
    
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_GUARANTEED + DPNSEND_NOLOOPBACK
    DoEvents
    
End Sub

Public Sub ReceiveItem(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    Dim tmpStr As String, aResult() As String
    Dim lngItem As MapObjectType, tmpSpawn As Boolean, tmpItem As Integer
    
    tmpSpawn = False
    tmpItem = 0
    
    tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)

    aResult = SplitString(tmpStr, " ", "\")
        
    Dim a As Integer, b As Integer
    a = LBound(aResult)
    b = UBound(aResult)
        
    lngItem = CInt(aResult(a))
    tmpSpawn = CBool(aResult(b))
    
    tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    tmpItem = CInt(tmpStr)
    
    If lngItem = tArmorShard Then
        obj_Armor(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tBatteries Then
        obj_Batteries(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tBoingers Then
        obj_Boingers(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tCapacitor Then
        obj_Cap(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tGrenades Then
        obj_GrenadesAmmo(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tHealth Then
        obj_HealthPack(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tHeartSensor Then
        obj_HeartSens(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tMegaHealth Then
        obj_MegaHealthPack(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tMines Then
        obj_MinesAmmo(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tPowerup Then
        obj_Power(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tRailgun Then
        obj_Railgun(tmpItem).Spawned = tmpSpawn
    ElseIf lngItem = tShield Then
        obj_Shield(tmpItem).Spawned = tmpSpawn
    End If
            
End Sub

Public Sub SendGotShield()
    Dim bByteBuffer() As Byte, lngOffset As Long
        
    '//New packet
    lngOffset = NewBuffer(bByteBuffer)
    
    Dim tmpID As Long, i As Integer
    
    For i = 0 To UBound(udtPlayers)
        If udtPlayers(i).iPlayerID = lngMyPlayerID Then
            tmpID = i
            Exit For
        End If
    Next i
    
    'Add packet header
    Call AddDataToBuffer(bByteBuffer, bPacketGotShield, SIZE_BYTE, lngOffset)
    Call AddStringToBuffer(bByteBuffer, CStr(tmpID) & " " & CStr(CHARACTER.GotShield), lngOffset)
    'SEND
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_NOLOOPBACK
    DoEvents
    
End Sub

Public Sub SendAnim()
    Dim bByteBuffer() As Byte, lngOffset As Long
        
    '//New packet
    lngOffset = NewBuffer(bByteBuffer)
    
    Dim tmpID As Long, i As Integer
    
    For i = 0 To UBound(udtPlayers)
        If udtPlayers(i).iPlayerID = lngMyPlayerID Then
            tmpID = i
            Exit For
        End If
    Next i
    
    'Add packet header
    Call AddDataToBuffer(bByteBuffer, bPacketAnim, SIZE_BYTE, lngOffset)
    Call AddStringToBuffer(bByteBuffer, CStr(tmpID) & " " & CStr(CHARACTER.Animation), lngOffset)
    'SEND
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_NOLOOPBACK
    DoEvents
    
    
    
End Sub

Public Sub SendAnimFrame()
    Dim bByteBuffer() As Byte, lngOffset As Long
        
    '//New packet
    lngOffset = NewBuffer(bByteBuffer)
    
    Dim tmpID As Long, i As Integer
    
    For i = 0 To UBound(udtPlayers)
        If udtPlayers(i).iPlayerID = lngMyPlayerID Then
            tmpID = i
            Exit For
        End If
    Next i
    
    
    Call AddDataToBuffer(bByteBuffer, bPacketAnimFrame, SIZE_BYTE, lngOffset)
    Call AddStringToBuffer(bByteBuffer, CStr(tmpID) & " " & CStr(CHARACTER.ANIMATIONNUM), lngOffset)
    'SEND
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_NOLOOPBACK
    DoEvents
    
    
    
End Sub

Public Sub SendRevFlag()
    Dim bByteBuffer() As Byte, lngOffset As Long
        
    '//New packet
    lngOffset = NewBuffer(bByteBuffer)
    
    Dim tmpID As Long, i As Integer
    
    For i = 0 To UBound(udtPlayers)
        If udtPlayers(i).iPlayerID = lngMyPlayerID Then
            tmpID = i
            Exit For
        End If
    Next i
    
    
    Call AddDataToBuffer(bByteBuffer, bPacketReverseFlag, SIZE_BYTE, lngOffset)
    Call AddStringToBuffer(bByteBuffer, CStr(tmpID) & " " & CStr(CInt(ReverseFlag)), lngOffset)
    'SEND
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_NOLOOPBACK
    DoEvents
    
    
End Sub

Public Sub SendQuit()
    Dim bByteBuffer() As Byte, lngOffset As Long
    
    '//Check if there's anything usefull in the chat message
    
    '//New packet
    lngOffset = NewBuffer(bByteBuffer)

    
    '//Add packet header
    Call AddDataToBuffer(bByteBuffer, bPacketQuit, SIZE_BYTE, lngOffset)
    
    '//Add chat message
    Call AddStringToBuffer(bByteBuffer, CStr(lngMyPlayerID) & " NOWAY!", lngOffset)
    
    '//Send the chat message
    ObjDPClient.Send bByteBuffer, 0, DPNSEND_GUARANTEED + DPNSEND_NOLOOPBACK
    DoEvents
    
End Sub

Public Sub ReceiveChat(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    '//Get the received chat message
    Dim strMessage As String
     
    '//Get the received chat message
    strMessage = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)

    '//Add the message to the textbox
    AddChatMessage (strMessage)
    
End Sub

Public Sub ReceiveStartGame(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    '//Get the received chat message
    Dim strMessage As String
     
    '//Get the received chat message
    strMessage = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)

    '//Add the message to the textbox
    AddChatMessage (strMessage)
    
    Start_Game

End Sub


Public Sub ReceiveMap(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    GotMapItemsArray = False
    Dim tMapItArr As String
    tMapItArr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    GotMapItemsArray = CBool(tMapItArr)

    Dim bMap As String
    bMap = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    
    Dim tmpGotMap As Boolean
    tmpGotMap = False
    Dim icMap As Integer
    If cMapCount > 0 Then
        For icMap = 0 To cMapCount - 1
            If bMap = frmMain.FilecMap.List(icMap) Then tmpGotMap = True
        Next icMap
    End If
            
    If tmpGotMap Then
        LoadMap App.Path & "\maps\" & bMap
    Else
        cCmdFeed "You don't have map: " & bMap
        UnloadClient
    End If

End Sub

Public Sub ReceiveID(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)
    
    Dim bID As Long
    Call GetDataFromBuffer(dpnotify.ReceivedData, bID, SIZE_LONG, lngOffset)
    lngMyPlayerID = bID
    
    cCmdFeed "", True
    cCmdFeed "YOUR ID: " & CStr(lngMyPlayerID), True
    
End Sub


Public Sub ReceiveMOTD0(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)
    
    bMotD0 = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    cCmdFeed "", True
    cCmdFeed bMotD0, True

End Sub

Public Sub ReceiveMOTD1(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    bMotD1 = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    cCmdFeed bMotD1, True

End Sub

Public Sub ReceiveMOTD2(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    bMotD2 = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    cCmdFeed bMotD2, True

End Sub

Public Sub ReceiveNOTICE(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    bMotNotice = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    cCmdFeed "NOTICE: " & bMotNotice, True

End Sub

Public Sub ReceiveAnim(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    Dim tmpStr As String, aResult() As String

    tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    
    Dim lngPlayer As String, tmpX As String
    
    lngPlayer = ""
    tmpX = ""
    
    If tmpStr = "" Then Exit Sub
    
    aResult = SplitString(tmpStr, " ", "\")
    
    Dim a As Integer, b As Integer
    a = LBound(aResult)
    b = UBound(aResult)
        
    lngPlayer = aResult(a)
    tmpX = aResult(b)
        
    udtPlayers(lngPlayer).Animation = CInt(tmpX)
    'ChatFeed tmpX
        
End Sub

Public Sub ReceiveGotShield(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    Dim tmpStr As String, aResult() As String

    tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    
    Dim lngPlayer As String, tmpX As String
    
    lngPlayer = ""
    tmpX = ""
    
    If tmpStr = "" Then Exit Sub
    
    aResult = SplitString(tmpStr, " ", "\")
    
    Dim a As Integer, b As Integer
    a = LBound(aResult)
    b = UBound(aResult)
        
    lngPlayer = aResult(a)
    tmpX = aResult(b)
        
    udtPlayers(lngPlayer).GotShield = CBool(tmpX)
    'ChatFeed tmpX
        
End Sub

Public Sub ReceiveAnimFrame(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    Dim tmpStr As String, aResult() As String

    tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    
    Dim lngPlayer As String, tmpX As String
    
    lngPlayer = ""
    tmpX = ""
    
    If tmpStr = "" Then Exit Sub
    
    aResult = SplitString(tmpStr, " ", "\")
    
    Dim a As Integer, b As Integer
    a = LBound(aResult)
    b = UBound(aResult)
        
    lngPlayer = aResult(a)
    tmpX = aResult(b)
        
    udtPlayers(lngPlayer).AnimationFrame = CInt(tmpX)
    'ChatFeed tmpX
        
End Sub

Public Sub ReceiveRevFlag(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    Dim tmpStr As String, aResult() As String

    tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    
    Dim lngPlayer As String, tmpX As String
    
    lngPlayer = ""
    tmpX = ""
    
    If tmpStr = "" Then Exit Sub
    
    aResult = SplitString(tmpStr, " ", "\")
    
    Dim a As Integer, b As Integer
    a = LBound(aResult)
    b = UBound(aResult)
        
    lngPlayer = aResult(a)
    tmpX = aResult(b)
        
    udtPlayers(lngPlayer).ReverseFlag = CBool(tmpX)
    'ChatFeed tmpX
        
End Sub

Public Sub ReceivePositions(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)

    Dim tmpStr As String, aResult() As String

    tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    
    Dim lngPlayer As String, tmpX As String, tmpY As String
    
    lngPlayer = ""
    tmpX = ""
    
    If tmpStr = "" Then Exit Sub
    
    aResult = SplitString(tmpStr, " ", "\")
    
    Dim a As Integer, b As Integer
    a = LBound(aResult)
    b = UBound(aResult)
        
    lngPlayer = aResult(a)
    tmpX = aResult(b)
        
    udtPlayers(lngPlayer).X = CLng(tmpX)
    
    
    
    tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    
    lngPlayer = ""
    tmpY = ""
    
    If tmpStr = "" Then Exit Sub
    
    aResult = SplitString(tmpStr, " ", "\")
    
    a = LBound(aResult)
    b = UBound(aResult)
        
    lngPlayer = aResult(a)
    tmpY = aResult(b)
        
    udtPlayers(lngPlayer).Y = CLng(tmpY)
    'ChatFeed tmpX
        
End Sub

Public Sub ReceiveQuit(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)
    Dim lngPlayerID As Long
    Dim i As Long
    '//Get the playerID of the player that went offline
    Call GetDataFromBuffer(dpnotify.ReceivedData, lngPlayerID, SIZE_LONG, lngOffset)
    
    '//Remove the player
    Call RemovePlayer(lngPlayerID)
End Sub

Public Sub ReceiveIdent(dpnotify As DxVBLibA.DPNMSG_RECEIVE, lngOffset As Long)
    
    Dim i As Long
    '//Get the player count
    Call GetDataFromBuffer(dpnotify.ReceivedData, bPlayerCount, SIZE_INTEGER, lngOffset)
    cCmdFeed "PLAYERS: " & CStr(bPlayerCount + 1), True
    ReDim udtPlayers(bPlayerCount)
    
    Dim tmpStr As String, aResult() As String
    
    For i = 0 To bPlayerCount
        tmpStr = GetStringFromBuffer(dpnotify.ReceivedData, lngOffset)
    
        Dim lngPlayer As String, tmpY As String
        
        lngPlayer = ""
        tmpY = ""
        
        If tmpStr = "" Then Exit Sub
        
        aResult = SplitString(tmpStr, " ", "\")
        
        Dim a As Integer, b As Integer
        a = LBound(aResult)
        b = UBound(aResult)
            
        lngPlayer = aResult(a)
        tmpY = aResult(b)
    
        '//Redim our array to te new number of players
        udtPlayers(i).iPlayerID = CLng(aResult(a))
        udtPlayers(i).NickName = CStr(aResult(b))

        'cCmdFeed "IDENT (" & CStr(udtPlayers(i).NickName) & ") " & CStr(udtPlayers(i).iPlayerID), True
    Next i

End Sub

Public Sub AddChatMessage(strText As String)
    
    ChatFeed strText, ""
    ShowChatSwitch = True
    frmMain.tmr_ShowChat.ENABLED = True
    
End Sub

Public Sub RemovePlayer(lngPlayerID As Long)
    Dim i As Long
    Dim NewList() As New cls_BotClient, lngCount As Long
    
    For i = 0 To UBound(udtPlayers)
        If udtPlayers(i).iPlayerID = lngPlayerID Then   '//If this is the player to be removed
            '//Don't do anything, except notifying this player went offline
            AddChatMessage udtPlayers(i).NickName & " has left"
        Else
            ReDim Preserve NewList(lngCount)
            NewList(lngCount) = udtPlayers(i) '//Copy the player to the temp array
            lngCount = lngCount + 1
        End If
    Next i

    '//Copy the new playerlist back to the real one
    udtPlayers = NewList
    
End Sub


