Attribute VB_Name = "mod_CFGCtrl"
'Var = ReadCFG(filename, key) & WriteCFG filename, key, value
'To write header tags just leave the [value] out of WriteCFG and the [Key] is the heading (wrote to file in order used)
Public CFGFile As String
Public CTRLCFGFILE As String
Public LOGFILE As String

Public cR As Integer, cG As Integer, cB As Integer

Public EngineLogEnabled As Boolean

Public Function ReadCFG(File As String, Key As String) As String

    Dim fnum As Integer, Data As String

    If (Dir(File) = "") Then Exit Function

    fnum = FreeFile
    Open File For Input As fnum
        Do While Not EOF(fnum)
            Line Input #fnum, Data
            If (Left(LCase(Data), Len(Key)) = LCase(Key)) Then
                ReadCFG = Trim(Right(Data, Len(Data) - Len(Key) - 1))
                Exit Do
            End If
            
            DoEvents
            
        Loop
    Close fnum

End Function

Public Sub WriteCFG(File As String, Key As String, Optional Value As String = "@~")

    On Local Error GoTo Shut
    
    Dim fn1 As Integer, fn2 As Integer, Data As String, File2 As String
    Dim Found As Boolean, NewFile As Boolean
 
    fn1 = FreeFile
 
    If (Dir(File) = "") Then Open File For Output As #fn1: Close fn1: NewFile = True

    fn2 = fn1 + 1
    File2 = Left(File, Len(File) - 4) & ".tmp"
    Open File For Input As fn1
        Open File2 For Output As fn2
            Do While Not EOF(fn1)
                Line Input #fn1, Data
                If (Value = "@~") Then
                    If (Left(LCase(Data), Len(Key) + 2) = "[" & LCase(Key) & "]") Then
                        Print #fn2, Data: Found = True
                    Else: Print #fn2, Data
                    End If
                Else
                    If (Left(LCase(Data), Len(Key) + 1) = LCase(Key) & "=") Then
                        Print #fn2, Key & "=" & Value: Found = True
                    Else: Print #fn2, Data
                    End If
                End If
            Loop
        If Not Found Then
            If (Value = "@~") Then
                If Not NewFile Then Print #fn2,
                    Print #fn2, "[" & Key & "]"
                Else
                    Print #fn2, Key & "=" & Value
                End If
            End If
        Close fn1, fn2

    FileCopy File2, File
    Kill File2
    
    Exit Sub
    
Shut:

End Sub

Public Sub WriteEngineLOG(File As String, Key As String)

    Dim fn1 As Integer, fn2 As Integer, Data As String, File2 As String
    Dim Found As Boolean, NewFile As Boolean
 
    fn1 = FreeFile
 
    If (Dir(File) = "") Then Open File For Output As #fn1: Close fn1: NewFile = True
 
    fn2 = fn1 + 1
    File2 = Left(File, Len(File) - 4) & ".tmp"
    Open File For Input As fn1
        Open File2 For Output As fn2
        
            Do While Not EOF(fn1)
            
                Line Input #fn1, Data
                Print #fn2, Data: Found = True

            Loop
            
            Print #fn2, Time & ": " & Key
            
        Close fn1, fn2

    FileCopy File2, File
    Kill File2

End Sub


Public Sub CFG_INIT()

    Dim aResult() As String, i As Long, i2 As Long
    Dim aVar1 As String, aVar2 As String, aVar3 As String

'on local error GoTo ErrOut


    
    Dim tmpValue As String
    
    Character.Name = UCase(ReadCFG(CFGFile, "NAME"))
        ''Dialog.PB2.Value = Dialog.PB2.Value + 1
        ''Dialog.Refresh
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("character.name '" & Character.Name & "'")
        If Character.Name = "" Then
            Character.Name = GetRandomName
        End If
            
    Character.TeamName = UCase(ReadCFG(CFGFile, "TEAMNAME"))
        ''Dialog.PB2.Value = Dialog.PB2.Value + 1
        ''Dialog.Refresh
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("character.teamname '" & Character.TeamName & "'")
        If Character.TeamName = "" Then
            Character.TeamName = GetRandomName
            If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("set character.teamname to '" & Character.TeamName & "'")
        End If
        
    StoryHiPlayer = UCase(ReadCFG(CFGFile, "HIPLAYER"))
    If StoryHiPlayer = "" Then StoryHiPlayer = "TEAM EB3K"
    tmpValue = ReadCFG(CFGFile, "HISCORE")
    If tmpValue = "" Then
        StoryHiScore = 500
    Else
        StoryHiScore = CLng(tmpValue)
    End If
    
    tmpValue = ReadCFG(CFGFile, "CROSSHAIR")
    If tmpValue = "" Then
        Character.Crosshair = 0
    Else
        Character.Crosshair = CInt(tmpValue)
    End If
        ''Dialog.PB2.Value = Dialog.PB2.Value + 1
        ''Dialog.Refresh
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("character.crosshair '" & Character.Crosshair & "'")
    
    tmpValue = ReadCFG(CFGFile, "USEVIDEOMEM")
    If tmpValue = "0" Then
        UseVideoMem = False
    ElseIf tmpValue = "1" Then
        UseVideoMem = True
    Else
        UseVideoMem = True
    End If
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("video memory '" & CStr(UseVideoMem) & "'")
    
    tmpValue = ReadCFG(CFGFile, "FULLSCREEN")
    If tmpValue = "" Then tmpValue = "1"
    ScreenMode = CInt(tmpValue)
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("video memory '" & CStr(UseVideoMem) & "'")

    tmpValue = ReadCFG(CFGFile, "STARFIELD")
    If tmpValue = "0" Then
        Starfield.On = False
    Else
        Starfield.On = True
    End If
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
            
    tmpValue = ReadCFG(CFGFile, "C_TRANSPARENT")
    If tmpValue = "1" Then
        cTransparent = True
    Else
        cTransparent = False
    End If
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh

    tmpValue = ReadCFG(CFGFile, "MUSIC")
    If tmpValue = "0" Then
        MusicEnabled = False
    Else
        MusicEnabled = True
    End If
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
            
        
    tmpValue = ReadCFG(CFGFile, "GAMETUNE")
    If tmpValue = "" Then
        SelectedMusic = GAME2
    Else
        SelectedMusic = CInt(tmpValue)
    End If
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
        
    tmpValue = ReadCFG(CFGFile, "SFX")
    If tmpValue = "0" Then
        SFXEnabled = False
    Else
        SFXEnabled = True
    End If
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
    
    
    tmpValue = ReadCFG(CFGFile, "SHOWINTRO")
    If tmpValue <> "" Then
        ShowIntro = CBool(tmpValue)
    Else
        ShowIntro = True
    End If
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
        
    INIT_DefaultKeys
        
    'Dim ik As Integer
    'For ik = 0 To 20
    '    tmpValue = ReadCFG(CFGFile, BoundKeyType(ik))
    '    BoundKey(ik) = KeyInt(tmpValue)
    'Next
    
    tmpValue = ReadCFG(CFGFile, "PACKETSPEED")
    If tmpValue <> "" Then
        PacketSpeed = CInt(tmpValue)
    Else
        PacketSpeed = 25
    End If
    
    CFG_WRITE CFGFile
    
    Exit Sub
    
ErrOut:
    
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: READING CFG"
    ShutdownNoErrorFlag = False: Shutdown
        
End Sub

Public Sub CFG_WRITE(CFGFile As String)

    WriteCFG CFGFile, "GENERATED BY ACTIVATED.CORE", "DO NOT MODIFY!"
    WriteCFG CFGFile, "EDIT ON OWN RISK", "BUT DON'T MODIFY!"
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
    
    WriteCFG CFGFile, "PLAYER SETTINGS"
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
    WriteCFG CFGFile, "NAME", Character.Name
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
    WriteCFG CFGFile, "TEAMNAME", Character.TeamName
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
    WriteCFG CFGFile, "CROSSHAIR", CStr(Character.Crosshair)
        'Dialog.PB2.Value = Dialog.PB2.Value + 1
        'Dialog.Refresh
    
    WriteCFG CFGFile, "SCREEN SETTINGS"

    If UseVideoMem = True Then
        WriteCFG CFGFile, "USEVIDEOMEM", 1
    Else
        WriteCFG CFGFile, "USEVIDEOMEM", 0
    End If
    
    WriteCFG CFGFile, "FULLSCREEN", CStr(ScreenMode)
    
    If Starfield.On = False Then
        WriteCFG CFGFile, "STARFIELD", 0
    Else
        WriteCFG CFGFile, "STARFIELD", 1
    End If
        
    WriteCFG CFGFile, "SOUND SETTINGS"
    If MusicEnabled Then
        WriteCFG CFGFile, "MUSIC", 1
    Else
        WriteCFG CFGFile, "MUSIC", 0
    End If
    WriteCFG CFGFile, "GAMETUNE", CStr(SelectedMusic)
    If SFXEnabled Then
        WriteCFG CFGFile, "SFX", 1
    Else
        WriteCFG CFGFile, "SFX", 0
    End If
        
    WriteCFG CFGFile, "OTHER"
    WriteCFG CFGFile, "SHOWINTRO", CStr(ShowIntro)
    WriteCFG CFGFile, "ENGINELOG", CStr(EngineLogEnabled)
    WriteCFG CFGFile, "PACKETSPEED", CStr(PacketSpeed)
        
    WriteCFG CFGFile, "KEY BINDINGS"
    Dim ik As Integer
    For ik = 0 To 20
        WriteCFG CFGFile, BoundKeyType(ik), KeyNames(BoundKey(ik))
    Next
    
    WriteCFG CFGFile, "HIGHSCORE"

End Sub

Public Sub ExecCFG(Optional ByVal Filename As String = "autoexec.cfg")

'on local error GoTo NOTFOUND

If (Dir(Filename) = "") Then Exit Sub

Dim tstr As String

Open Filename For Input As 1
        
    Do Until EOF(1)
    
        Line Input #1, tstr
        If Not Mid(UCase(tstr), 1, 1) = "#" Then
            cCmdFeed tstr, False, True
        End If

    Loop

Close

'cCmdFeed "CFG_WRITE", , True

Exit Sub

NOTFOUND:

    cCmdFeed "COULD NOT FIND CFG", True

End Sub

Public Sub LoadCTRL()

    Dim tmpValue As String
    
    tmpValue = ReadCFG(CTRLCFGFILE, "MOVELEFT")
    If tmpValue = "" Then
        CTRL_MOVELEFT = 30
    Else
        CTRL_MOVELEFT = Int(tmpValue)
    End If
    
    tmpValue = ReadCFG(CTRLCFGFILE, "MOVERIGHT")
    If tmpValue = "" Then
        CTRL_MOVERIGHT = 32
    Else
        CTRL_MOVERIGHT = Int(tmpValue)
    End If
    
    tmpValue = ReadCFG(CTRLCFGFILE, "JUMP")
    If tmpValue = "" Then
        CTRL_JUMP = 17
    Else
        CTRL_JUMP = Int(tmpValue)
    End If
    
    tmpValue = ReadCFG(CTRLCFGFILE, "CROUCH")
    If tmpValue = "" Then
        CTRL_CROUCH = 31
    Else
        CTRL_CROUCH = Int(tmpValue)
    End If
    
    tmpValue = ReadCFG(CTRLCFGFILE, "TOGGLECONSOLE")
    If tmpValue = "" Then
        CTRL_TOGGLECONSOLE = 41
    Else
        CTRL_TOGGLECONSOLE = Int(tmpValue)
    End If
    
    tmpValue = ReadCFG(CFGFile, "SHOWGAMESTATS")
    If tmpValue = "" Then
        CTRL_SHOWGAMESTATS = 15
    Else
        CTRL_SHOWGAMESTATS = Int(tmpValue)
    End If
    
    tmpValue = ReadCFG(CTRLCFGFILE, "KILL")
    If tmpValue = "" Then
        CTRL_KILL = 37
    Else
        CTRL_KILL = Int(tmpValue)
    End If

End Sub

