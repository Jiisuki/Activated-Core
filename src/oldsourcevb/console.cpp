Attribute VB_Name = "mod_Console"
Public Type ConsoleLine_Type
    cText As String
    cAltText As Boolean
End Type
Public cLine(38 - 1) As ConsoleLine_Type

Public cUsrCmd As String
Public tmpCmd As Integer
Public cPrevCmd As String
Public cEnabled As Boolean
Public cTransparent As Boolean

'For the hacking parts
Public Type HackLine_Type
    HackText As String
    HackAltText As Boolean
End Type
Public HackLine(32 - 1) As HackLine_Type
Public HackUsrCmd As String
Public HackTmpCmd As Integer
Public HackPrevCmd As String
Public HackEnabled As Boolean
Public HackDirLevel(0 To 32) As Integer

Private Declare Function StrCSpnI Lib "shlwapi" Alias "StrCSpnIA" (ByVal StringSearched As String, ByVal Characters As String) As Long

Public Sub Console_INIT()

On Local Error GoTo ErrShut

    Dim i As Integer
    For i = 0 To UBound(cLine)
        cLine(i).cText = ""
        
        DoEvents
        
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("written consoleline nr '" & CStr(i) & "'")
        
    Next i
    
    cCmdFeed "CLS"
    'cCmdFeed "#============================#", True
    'cCmdFeed "#                            #", True
    'cCmdFeed "# WELCOME TO Activated Core! #", True
    'cCmdFeed "#                            #", True
    'cCmdFeed "#============================#", True
    'cCmdFeed "", True
    
    Dim tmpG As String
    tmpG = ""
    For i = 0 To UBound(BotClient)
        If i = 0 Then
            tmpG = BotClient(i).NickName
        Else
            tmpG = tmpG & " and " & BotClient(i).NickName
        End If
    Next i
    cCmdFeed tmpG & " says welcome!", True
        
    cEnabled = False
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("written welcome message")
    
        'Load Commandlist
        frmMain.cCMDLIST.AddItem "CLS"
        frmMain.cCMDLIST.AddItem "SYS_VERSION"
        frmMain.cCMDLIST.AddItem "EXEC"
        frmMain.cCMDLIST.AddItem "TIME"
        frmMain.cCMDLIST.AddItem "QUIT"
        frmMain.cCMDLIST.AddItem "DIR"
        frmMain.cCMDLIST.AddItem "CROSSHAIR"
        frmMain.cCMDLIST.AddItem "NAME"
        frmMain.cCMDLIST.AddItem "TEAM"
        frmMain.cCMDLIST.AddItem "GAMETUNE"
        frmMain.cCMDLIST.AddItem "INTRO"
        frmMain.cCMDLIST.AddItem "MAP"
        frmMain.cCMDLIST.AddItem "MAPLIST"
        frmMain.cCMDLIST.AddItem "BIND"
        frmMain.cCMDLIST.AddItem "SHOWBINDS1"
        frmMain.cCMDLIST.AddItem "SHOWBINDS2"
        frmMain.cCMDLIST.AddItem "DEBUGINFO"
        frmMain.cCMDLIST.AddItem "MAPEDITOR"
        frmMain.cCMDLIST.AddItem "SAY"
        frmMain.cCMDLIST.AddItem "EXEC"
        frmMain.cCMDLIST.AddItem "SAVECFG"
        frmMain.cCMDLIST.AddItem "ADDBOT"
        frmMain.cCMDLIST.AddItem "DISCONNECT"
        frmMain.cCMDLIST.AddItem "CONNECT"
        frmMain.cCMDLIST.AddItem "PACKETSPEED"
        frmMain.cCMDLIST.AddItem "FPS"
        frmMain.cCMDLIST.AddItem "TESTRAY"
        
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("written console commands of total '" & CStr(frmMain.cCMDLIST.ListCount) & "'")
        
        Exit Sub
        
ErrShut:
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "Error in Console Init"

End Sub

Public Sub cCmdFeed(cStringFeed As String, Optional ByVal cSys As Boolean = False, Optional ByVal cInvis As Boolean = False)
    
On Local Error GoTo ErrShut:
    
    Dim i As Integer, i2 As Integer
        
    If Not cInvis Then
    
        For i = 0 To (UBound(cLine) - 2)
        i2 = (UBound(cLine) - 2) - i
        cLine(i2 + 1).cText = cLine(i2).cText
        DoEvents
        Next i
        
        If Not cSys Then
            cLine(0).cText = cStringFeed
        Else
            cLine(0).cText = ">> " & cStringFeed
        End If
    End If
    
    If Not cSys Then
        cCheckCommands UCase(cStringFeed)
    End If
        
    cUsrCmd = ""
    Exit Sub
    
ErrShut:
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "Error in Console Feed"

End Sub

Public Sub cUpdateConsoleBuffer()

On Local Error GoTo ErrShut

    Dim i As Integer, i2 As Integer, i3 As Single, rConsoleBuf As RECT
    
    rConsoleBuf.Left = 0
    rConsoleBuf.Right = 320
    rConsoleBuf.Top = 0
    rConsoleBuf.Bottom = 160
    
    DDS_ConsoleBuffer.BltFast 0, 0, DDS_Console, rConsoleBuf, DDBLTFAST_WAIT

    For i = 0 To (UBound(cLine) - 1)
    
        i2 = (UBound(cLine) - 1) - i
        i3 = 130 - (i2 * 10)
            
        If i3 > 0 Then
            
                DrawText UCase(cLine(i2).cText), 2, i3, 1
                DrawText UCase(ActCore_VERSION), (310 - Int((Len(ActCore_VERSION) * 8))), 150, 1, 2
                                            
        End If
        
        DoEvents
        
    Next i
    Exit Sub
    
ErrShut:
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "Error in Updating Console Buffer"

End Sub

Public Sub cDrawConsole()

On Local Error GoTo ErrShut

    Dim rConsole As RECT
    
    rConsole.Left = 0
    rConsole.Right = 320
    rConsole.Top = 0
    rConsole.Bottom = 160
    
    DDS_Back.BltFast 0, 0, DDS_ConsoleBuffer, rConsole, DDBLTFAST_WAIT
                
    DrawText cUsrCmd & "*", 2, 150, 0, 3
    

    'DDS_Back.SetForeColor RGB(255, 255, 255)
    'DDS_Back.DrawText 8, 310, cUsrCmd & "_", False

ErrShut:
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "Error Drawing Console"

End Sub

Public Sub cCheckCommands(cString As String)

On Local Error GoTo ERRORHANDLER
    
    Dim aResult() As String, i As Long, i2 As Long, m As Integer
    Dim aCMD As String, aVar1 As String, aVar2 As String, aVar3 As String
    
    aCMD = ""
    aVar1 = ""
    aVar2 = ""
    aVar3 = ""
    
    If cString = "" Then Exit Sub
    
    aResult = SplitString(cString, " ", "\")
    
    i = LBound(aResult)
    i2 = UBound(aResult)
    
    aCMD = aResult(i)
    If i + 1 <= i2 Then
        aVar1 = aResult(i + 1)
    End If
    If i + 2 <= i2 Then
        aVar2 = aResult(i + 2)
    End If
    If i + 3 <= i2 Then
        aVar3 = aResult(i + 3)
    End If
    
    Dim tmpL As Long
    
    tmpL = Len(aCMD)
    If Mid(aCMD, tmpL, 1) = Chr(0) Then
        aCMD = Mid(aCMD, 1, tmpL - 1)
    End If
    
    tmpL = Len(aVar1)
    If tmpL > 0 Then
        If Mid(aVar1, tmpL, 1) = Chr(0) Then
            aVar1 = Mid(aVar1, 1, tmpL - 1)
        End If
    End If
        
    tmpL = Len(aVar2)
    If tmpL > 0 Then
        If Mid(aVar2, tmpL, 1) = Chr(0) Then
            aVar2 = Mid(aVar2, 1, tmpL - 1)
        End If
    End If
    
    tmpL = Len(aVar3)
    If tmpL > 0 Then
        If Mid(aVar3, tmpL, 1) = Chr(0) Then
            aVar3 = Mid(aVar3, 1, tmpL - 1)
        End If
    End If
    
    
    
    
    If aCMD = "MAP" Or aCMD = "SAY" Then
    
        aVar1 = ""
        
        For m = (i + 1) To i2 'left bound + 1 (only vars) to right bound
            If m > (i + 1) Then
            
                tmpL = Len(aResult(m))
                If tmpL > 0 Then
                    If Mid(aResult(m), tmpL, 1) = Chr(0) Then
                        aResult(m) = Mid(aResult(m), 1, tmpL - 1)
                    End If
                End If
                
                aVar1 = aVar1 & " " & aResult(m)
                
            Else
            
                aVar1 = aResult(m)
                
            End If
        Next m
        
        aVar1 = Mid(aVar1, 1, 44)
                
    End If
    
        
        
    
    If aCMD = "QUIT" Then
    
        ShutdownNoErrorFlag = True: Shutdown
        
    ElseIf aCMD = "TESTRAY" Then
        RayTrace CInt(CHARACTER.X + 16), CInt(CHARACTER.Y - 64), CInt(CHARACTER.X), CInt(CHARACTER.X + 32), CInt(CHARACTER.Y), CInt(CHARACTER.Y + 32)
        
    ElseIf aCMD = "GOD" Then
    
        CHARACTER.ARMOR = CHARACTER.ARMORMAX
        CHARACTER.GOTCAP = True
        CHARACTER.GOTHEARTSENS = True
        CHARACTER.GOTJUMPASSIST = True
        CHARACTER.GOTSUIT = True
        CHARACTER.JUMPASSISTREADY = True
        CHARACTER.JUMPASSISTTIME = 0
        WeapBlaster.GotWeapon = True
        WeapBlaster.AmmoCurrent = WeapBlaster.AMMOMAX
        WeapRailgun.GotWeapon = True
        WeapBoingers.GotWeapon = True
        WeapBoingers.AmmoCurrent = WeapBoingers.AMMOMAX
        WeapMines.GotWeapon = True
        WeapMines.AmmoCurrent = WeapMines.AMMOMAX
        
    ElseIf aCMD = "DISCONNECT" Then
    
        If NetworkStatus = SUCCESS Then
            UnloadClient
            gSTARTED = False
            bQuit = True
            StartGameMusic TITLESCREEN
        End If
    
    ElseIf aCMD = "PACKETSPEED" Then
        If aVar1 <> "" Then
            PacketSpeed = CInt(aVar1)
            WriteCFG CFGFile, "PACKETSPEED", CStr(PacketSpeed)
        Else
            cCmdFeed CStr(PacketSpeed), True
        End If
        
    ElseIf aCMD = "FPS" Then
        If DrawFPS = False Then
            DrawFPS = True
        Else
            DrawFPS = False
        End If
        
    ElseIf aCMD = "CONNECT" Then
        
        If NetworkStatus = SUCCESS Then UnloadClient
        NetworkStatus = INITIALIZING
        mod_Network.InitClient
        mod_Network.ClientConnect aVar1
        PlaySample "menu\select.mp3"
        MENU.VisibleMenu = MNUMultiplayer
        
    ElseIf aCMD = "DEBUGINFO" Then
        cCmdFeed CStr(MoveDown) & ":" & CStr(CHARACTER.CROUCHING), True
        
    ElseIf aCMD = "MAPEDITOR" Then
        If aVar1 <> "" Then
            MAPFILENAME = aVar1
            INIT_MAPEDITOR MAPFILENAME
        Else
            INIT_MAPEDITOR
        End If
        
    ElseIf aCMD = "BIND" Then
        If aVar1 <> "" Then
            If aVar2 <> "" Then
                Dim iTMP As Integer
                iTMP = BoundKeys(aVar1)
                BoundKey(iTMP) = KeyInt(aVar2)
            Else
                cCmdFeed "JUMP BOUND TO: " & KeyNames(&H11), True
            End If
        End If
        
    ElseIf aCMD = "EXEC" Then
        ExecCFG App.Path & aVar1
    
    ElseIf aCMD = "SAVECFG" Then
        If aVar1 = "" Then
            CFG_WRITE CFGFile
        Else
            CFG_WRITE App.Path & aVar1
        End If
        
    ElseIf aCMD = "ADDBOT" Then
        GAMEMODE = TRAINING_BOTPLAY
        CreateBots aVar1
        
    ElseIf aCMD = "SHOWBINDS1" Then
        Dim tC As Integer
        For tC = 0 To 10
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, CStr(tC) & ": " & BoundKeyType(tC) & " BOUND TO " & KeyNames(BoundKey(tC))
            cCmdFeed CStr(tC) & ": " & BoundKeyType(tC) & " BOUND TO " & KeyNames(BoundKey(tC)), True
        Next tC
    ElseIf aCMD = "SHOWBINDS2" Then
        Dim tC2 As Integer
        For tC2 = 11 To 20
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, CStr(tC2) & ": " & BoundKeyType(tC2) & " BOUND TO " & KeyNames(BoundKey(tC2))
            cCmdFeed CStr(tC2) & ": " & BoundKeyType(tC2) & " BOUND TO " & KeyNames(BoundKey(tC2)), True
        Next tC2
        
    ElseIf aCMD = "GAMETUNE" Then
        
        If aVar1 = "" Then
            cCmdFeed "SELECTED GAMETUNE: " & CheckPlayingInfo(True), True
        Else
            If Int(aVar1) > 8 Or Int(aVar1) < 1 Then
                SelectedMusic = GAME1
            ElseIf Int(aVar1) = 1 Then
                SelectedMusic = GAME1
            ElseIf Int(aVar1) = 2 Then
                SelectedMusic = GAME2
            ElseIf Int(aVar1) = 3 Then
                SelectedMusic = GAME3
            ElseIf Int(aVar1) = 4 Then
                SelectedMusic = GAME4
            ElseIf Int(aVar1) = 5 Then
                SelectedMusic = GAME5
            ElseIf Int(aVar1) = 6 Then
                SelectedMusic = GAME6
            ElseIf Int(aVar1) = 7 Then
                SelectedMusic = GAME7
            ElseIf Int(aVar1) = 8 Then
                SelectedMusic = GAME8
            End If
            StartGameMusic SelectedMusic
            WriteCFG CFGFile, "GAMETUNE", CStr(SelectedMusic)
        End If
        
    ElseIf aCMD = "INTRO" Then
        Intro_INIT
        StartGameMusic INTRO
        MENU.VisibleMenu = MNUIntro
        cEnabled = False
        
    ElseIf aCMD = "CROSSHAIR" Then
        
        If aVar1 <> "" Then
            If Int(aVar1) > 0 And Int(aVar1) < 7 Then
                CHARACTER.CROSSHAIR = Int(aVar1)
            Else
                CHARACTER.CROSSHAIR = 0
            End If
            WriteCFG CFGFile, "CROSSHAIR", CStr(CHARACTER.CROSSHAIR)
        Else
            cCmdFeed "YOUR CROSSHAIR IS: " & CStr(CHARACTER.CROSSHAIR), True
        End If
        
        
    ElseIf aCMD = "CTRANS" Then
    
        If aVar1 = "1" Then
            cTransparent = True
        Else
            cTransparent = False
        End If
        
        
    ElseIf aCMD = "NAME" Then
    
        If aVar1 = "" Then
            cCmdFeed "YOUR NAME IS: " & CHARACTER.name, True
        Else
            CHARACTER.name = aVar1
            WriteCFG CFGFile, "NAME", CHARACTER.name
        End If
                
      
    ElseIf aCMD = "TEAM" Then
    
        If aVar1 = "" Then
            cCmdFeed "YOUR TEAM NAME IS: " & CHARACTER.TeamName, True
        Else
            CHARACTER.name = aVar1
            WriteCFG CFGFile, "TEAMNAME", CHARACTER.TeamName
        End If
                
                
    ElseIf aCMD = "CLS" Then
        
        Dim i3 As Integer
        For i3 = 0 To UBound(cLine)
            cLine(i3).cText = ""
            DoEvents
        Next i3
                            
                            
                            
    ElseIf aCMD = "MAP" Then
        If aVar1 = "" Then
            cCmdFeed "MAPLIST", , True
        Else
            If Right(aVar1, 1) = " " Then
                Dim ttt As Integer
                ttt = Len(aVar1)
                aVar1 = Left(aVar1, ttt - 1)
            End If
            'If Right(aVar1, 4) <> ".MAP" Then
            '    aVar1 = aVar1 & ".MAP"
            'End If
            LoadMap App.Path & "\maps\" & aVar1
        End If
        
        
    ElseIf aCMD = "MAPLIST" Then
        Dim icMap As Integer
        If cMapCount > 0 Then
            For icMap = 0 To cMapCount - 1
                cCmdFeed frmMain.FilecMap.List(icMap), True
                DoEvents
            Next icMap
        Else
            cCmdFeed "NO CUSTOM MAPS IN MAPDIR" & ".", True
        End If
        
        
                
    ElseIf aCMD = "SYS_VERSION" Then
        cCmdFeed ActCore_VERSION, True, False
    
    
    
    ElseIf aCMD = "EXEC" Then
    
        ExecCFG aVar1
        
        
        
    ElseIf aCMD = "TIME" Then
        
        cCmdFeed Time, True, False
        

    ElseIf aCMD = "SAY" Then
        
        ChatFeed aVar1 & aVar2 & aVar3, CHARACTER.name
        
        
        
                
    ElseIf aCMD = "DIR" Then
    
        Dim X As Integer, Y As Integer, t As String
    
        cCmdFeed "CLS"
        
        Dim tmpMaxLen As Long
        
        For X = 0 To frmMain.cCMDLIST.ListCount - 1
        
            t = "              "
            For Y = 0 To Len(frmMain.cCMDLIST.List(X))
                t = Mid(t, 1, Len(t) - 1)
            Next Y

            cCmdFeed frmMain.cCMDLIST.List(X) & t & frmMain.cCMDLIST.List(X + 1), True
            X = X + 1
            
            DoEvents
            
        Next X
        
        
            
    Else
        cCmdFeed "UNRECOGNIZED COMMAND.", True, False
        cCmdFeed "TYPE 'DIR' FOR LIST OF COMMANDS!", True
        
    End If
    
    If ActCore_INITED Then
        cUpdateConsoleBuffer
    End If
    
    Exit Sub
    
ERRORHANDLER:

    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: CONSOLE COMMANDCHECK"

End Sub

Public Sub CheckAvailableCmds(cString As String)

    If cString = "" Then Exit Sub
    
    frmMain.cCMDLISTtmp.Clear
    
'dim some necessary variables. maybe not all is nec, but it's made easy this way.
Dim X As Integer, x2 As Integer, Y As Integer
Dim z As Integer, t As Integer, strTmp As String

'clear the lengthholder for text
t = 0

'this adds all the matching commands into a templist from the maincommandlist
For X = 0 To frmMain.cCMDLIST.ListCount
    
    strTmp = frmMain.cCMDLIST.List(X)
    If Left$(strTmp, Len(cString)) = cString Then
        frmMain.cCMDLISTtmp.AddItem frmMain.cCMDLIST.List(X)
    End If
    
    DoEvents
    
Next X

'this clears screen and then shows all matching commands
cCmdFeed "CLS"
For X = 0 To frmMain.cCMDLISTtmp.ListCount - 1
    cCmdFeed frmMain.cCMDLISTtmp.List(X), True
    
    DoEvents
    
Next X

'this will decide how much to extend the command written by user
'to complete as long as possible.
For X = 0 To frmMain.cCMDLISTtmp.ListCount - 1
    
    z = 0
    For Y = 1 To Len(frmMain.cCMDLISTtmp.List(0))

        If frmMain.cCMDLISTtmp.ListCount > 1 Then
            If X = 0 Then
                X = X + 1
                If X > frmMain.cCMDLISTtmp.ListCount Then X = frmMain.cCMDLISTtmp.ListCount
            End If
        End If
        
        If Mid(frmMain.cCMDLISTtmp.List(0), Y, 1) = Mid(frmMain.cCMDLISTtmp.List(X), Y, 1) Then
            z = z + 1
        End If
    
    Next Y
    
    If z > t Then
        t = z
        'update the command written by user.
        cUsrCmd = Mid(frmMain.cCMDLISTtmp.List(X), 1, t)
    End If
    
    cUsrCmd = cUsrCmd & " "
    
    DoEvents
    
Next X

'update buffer
If ActCore_INITED Then
    cUpdateConsoleBuffer
End If
    
End Sub

Public Function SplitString(ByVal toSplit As String, _
    Optional ByVal SplitChars As String = " ", _
    Optional ByVal EscapeChar As String = "\", _
    Optional ByVal TrimStrings As Boolean = True) _
    As String()

'--------------------------------------------------------------------------------------------------
' Arguments :
'
' toSplit               - String to be Splitted
' SplitChars            - Delimiters that are used for Splitting the String (Default : Space)
' EscapeChar            - The Escape Character (if precedes a Split Character, the Split
'                         Character is recognized as a literal) (Default : Back Slash)
' TrimStrings           - If True, trims the returned Strings in the Array, else the spaces are
'                         returned as-is.
'
' Returns   : The Splitted String Array
'
'
' Notes     :  This function is slower than the Split() counterpart. It's slows down as the length of the
'              string increases. But, it provides you two things that Split() does not provide.
'              1. It allows multiple delimiters (called SplitChars here)
'              2. What if you want to represent the delimiter itself ? For e.g., if you have
'                 - as the delimiter and you want to pass A-B as an argument ?. For this, this function
'                allows you to have one Escape Character. Instead of passing A-B, you pass the argument as
'               A\-B in this case.
'
'--------------------------------------------------------------------------------------------------

Dim retArray() As String        ' The returned array of results
Dim tempString As String        ' The Temporary Buffer
Dim arrLength As Long           ' No. Of Splitted Parts
Dim isEscapeChar As Boolean     ' Was a Escape Character found ?
Dim FoundPos As Long            ' The position at which the Split Character was found

ReDim retArray(0 To 0)          ' Hmm.. Looks like bad example of Initializing an array
arrLength = -1                  ' No of split parts - 1

If EscapeChar <> "" Then
    EscapeChar = Left$(EscapeChar, 1)   ' Only one character can be allowed as the EscapeCharacter
End If

If Len(toSplit) = 0 Then       ' No String, nothing to do ...
    SplitString = retArray
    Exit Function
End If

If Len(SplitChars) = 0 Then     ' No Splitting to be done
    SplitString = retArray
    Exit Function
End If

'
' To avoid Redimensioning Array many times within the loop, we dimension the array to the
' maximum possible extent and waste some memory
'
ReDim retArray(0 To 10)

toSplit = toSplit & Chr$(0)
SplitChars = SplitChars & Chr$(0)

Do
    ' Use the SHLWAPI function to search for String matches
    FoundPos = StrCSpnI(toSplit, SplitChars)
    
    '
    ' The String before the Split Character (if any) should be "splitted"
    ' unless there is a Escape Character preceding the Split Character
    '
    FoundPos = FoundPos + 1     ' Remember ? C Strings start with a Zero Index
    
    Select Case FoundPos
    Case Len(toSplit), 0
        arrLength = arrLength + 1
        
        If arrLength > UBound(retArray) Then
            ReDim Preserve retArray(arrLength + 5)  ' Pre-Allocate more memory
        End If
        
        If isEscapeChar Then
            retArray(arrLength) = tempString & toSplit ' Whatever is remaining
        Else
            retArray(arrLength) = toSplit
        End If
        
        If TrimStrings Then retArray(arrLength) = Trim$(retArray(arrLength))
        Exit Do
        
    Case Is > 1
        ' Check for Escape Character
        If Mid$(toSplit, FoundPos - 1, 1) = EscapeChar Then
            ' The Split Character is intepreted as an ordinary literal.
            isEscapeChar = True
            
            ' Remove everything before the Escape Character for temporary storage
            If Len(toSplit) > 2 Then
                tempString = Left$(toSplit, FoundPos - 2) & Mid$(toSplit, FoundPos, 1)
            Else        ' The Escape Character is the First Character
                tempString = Mid$(toSplit, FoundPos)
            End If
            
            ' To avoid "finding" the Escaped Split Character again, we rip that part
            If Len(toSplit) > FoundPos + 1 Then
                toSplit = Mid$(toSplit, FoundPos + 1)
            Else
                ' The String has ended with the Escaped Split Character. Now
                ' this is the last part of the string that must be stored in the
                ' Split Array. Just do that !
                arrLength = arrLength + 1
        
                If arrLength > UBound(retArray) Then
                    ReDim Preserve retArray(arrLength + 5)  ' Pre-Allocate more memory
                End If
                        
                retArray(arrLength) = tempString
                If TrimStrings Then retArray(arrLength) = Trim$(retArray(arrLength))
                Exit Do
           End If
           
        Else        ' No Escape Character
            arrLength = arrLength + 1
                    
            If arrLength > UBound(retArray) Then
                ReDim Preserve retArray(arrLength + 5)  ' Pre-Allocate more memory
            End If
        
            ' We might have left-overs of an Escaped Split Character
            If isEscapeChar Then
                retArray(arrLength) = tempString & Left$(toSplit, FoundPos - 1)
                isEscapeChar = False
            Else
                retArray(arrLength) = Left$(toSplit, FoundPos - 1)
            End If
            
            If TrimStrings Then retArray(arrLength) = Trim$(retArray(arrLength))
            
            ' Remove that Part
            If Len(toSplit) > FoundPos + 1 Then
                toSplit = Mid$(toSplit, FoundPos + 1)
            Else
                ' No more string to be splitted. Re-dimenstion the array.
                Exit Do
           End If
        End If
        
    Case 1
        ' The Split Character is at the First Position
        If Len(toSplit) > 1 Then
            toSplit = Mid$(toSplit, 2)
        Else
            Exit Do
        End If
    End Select
Loop

ReDim Preserve retArray(arrLength)
toSplit = ""

SplitString = retArray
        
End Function


Public Sub HackConsole_INIT()

On Local Error GoTo ErrShut

    Dim i As Integer
    For i = 0 To UBound(HackLine)
        HackLine(i).HackText = ""
        DoEvents
    Next i
    
    For i = 0 To UBound(HackDirLevel)
        HackDirLevel(i) = 0
        DoEvents
    Next i
        
    HackEnabled = False
    
        'Load Commandlist
        frmMain.hackCMDLIST.AddItem "CLS"
        frmMain.hackCMDLIST.AddItem "SYS_VERSION"
        frmMain.hackCMDLIST.AddItem "EXEC"
        frmMain.hackCMDLIST.AddItem "TIME"
        frmMain.hackCMDLIST.AddItem "QUIT"
        
    Exit Sub
        
ErrShut:
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "Error in Console Init"

End Sub

Public Sub InitTerminals(HackTerminal As Integer)

    If HackTerminal = 1 Then
        HackFeed "", True
        HackFeed "Welcome to Terminal 1", True
        HackFeed "", True
    End If
    
End Sub

Public Sub HackFeed(HackStringFeed As String, Optional ByVal hackSys As Boolean = False)
    
On Local Error GoTo ErrShut:
    
    Dim i As Integer, i2 As Integer
        
        For i = 0 To (UBound(HackLine) - 2)
        i2 = (UBound(HackLine) - 2) - i
        HackLine(i2 + 1).HackText = HackLine(i2).HackText
        DoEvents
        Next i
        
        HackLine(0).HackText = HackStringFeed
    
    If Not hackSys Then
        HackCheckCommands UCase(HackStringFeed)
    End If
        
    cUsrCmd = ""
    Exit Sub
    
ErrShut:
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "Error in Console Feed"

End Sub

Public Sub HackCheckCommands(cString As String, HackTerm As Integer)

On Local Error GoTo ERRORHANDLER
    
    Dim aResult() As String, i As Long, i2 As Long, m As Integer
    Dim aCMD As String, aVar1 As String, aVar2 As String, aVar3 As String
    
    aCMD = ""
    aVar1 = ""
    aVar2 = ""
    aVar3 = ""
    
    If cString = "" Then Exit Sub
    
    aResult = SplitString(cString, " ", "\")
    
    i = LBound(aResult)
    i2 = UBound(aResult)
    
    aCMD = aResult(i)
    If i + 1 <= i2 Then
        aVar1 = aResult(i + 1)
    End If
    If i + 2 <= i2 Then
        aVar2 = aResult(i + 2)
    End If
    If i + 3 <= i2 Then
        aVar3 = aResult(i + 3)
    End If
    
    Dim tmpL As Long
    
    tmpL = Len(aCMD)
    If Mid(aCMD, tmpL, 1) = Chr(0) Then
        aCMD = Mid(aCMD, 1, tmpL - 1)
    End If
    
    tmpL = Len(aVar1)
    If tmpL > 0 Then
        If Mid(aVar1, tmpL, 1) = Chr(0) Then
            aVar1 = Mid(aVar1, 1, tmpL - 1)
        End If
    End If
        
    tmpL = Len(aVar2)
    If tmpL > 0 Then
        If Mid(aVar2, tmpL, 1) = Chr(0) Then
            aVar2 = Mid(aVar2, 1, tmpL - 1)
        End If
    End If
    
    tmpL = Len(aVar3)
    If tmpL > 0 Then
        If Mid(aVar3, tmpL, 1) = Chr(0) Then
            aVar3 = Mid(aVar3, 1, tmpL - 1)
        End If
    End If
    
    If aCMD = "QUIT" Then
        HackEnabled = False
        
    ElseIf aCMD = "EXIT" Then
        HackEnabled = False
        
    ElseIf aCMD = "CD" Then
        If HackTerm = 1 Then
            If HackDirLevel(1) = 0 Then
                If aVar1 = "LOGS" Then
                    HackDirLevel(1) = 1
                ElseIf aVar1 = "SYS" Then
                    HackDirLevel(1) = 2
                End If
            End If
        End If
        
    ElseIf aCMD = "LS" Then
        If HackTerm = 1 Then
            If HackDirLevel(1) = 0 Then
                HackFeed "", True
                HackFeed "LISTING FOR /", True
                HackFeed "", True
                HackFeed "LOGS   [DIRECTORY]", True
                HackFeed "SYS    [DIRECTORY]", True
                HackFeed "", True
            ElseIf HackDirLevel(1) = 1 Then
                HackFeed "", True
                HackFeed "LISTING FOR /LOGS/", True
                HackFeed "", True
                HackFeed "ATMOSPHERE DATA", True
                HackFeed "SECURITY LOG", True
                HackFeed "CRASH LOG", True
                HackFeed "", True
            ElseIf HackDirLevel(1) = 2 Then
                HackFeed "", True
                HackFeed "LISTING FOR /SYS/", True
                HackFeed "", True
                HackFeed "", True
                HackFeed "", True
            End If
        End If
            
    Else
        HackFeed "UNRECOGNIZED COMMAND.", True
        HackFeed "TYPE 'DIR' FOR LIST OF COMMANDS!", True
        
    End If
    
    If ActCore_INITED Then
        cUpdateConsoleBuffer
    End If
    
    Exit Sub
    
ERRORHANDLER:

    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: CONSOLE COMMANDCHECK"

End Sub
