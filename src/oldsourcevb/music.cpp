Attribute VB_Name = "mod_Music"
Public songHandle As Long
Public streamHandle As Long
Public streamChannel As Long
Public MusicEnabled As Boolean

Public StreamCustomAdress1 As String
Public StreamCustomAdress2 As String
Public StreamCustomAdress3 As String

Public Mp3Count As Integer
Public Mp3SongPlaying As String
Public mp3song As Integer

Public PlayingInfo As String

Public Enum MUSIC_TYPE
    TITLESCREEN = 255
    INTRO = 0
    GAME1 = 1
    GAME2 = 2
    GAME3 = 3
    GAME4 = 4
    GAME5 = 5
    GAME6 = 6
    GAME7 = 7
    GAME8 = 8
    GAME9 = 9
    CREDTIS = 10
    MNU = 11
    LOBBY = 98
    STORY = 99
    GAMEOVER = 100
End Enum
Public SelectedMusic As MUSIC_TYPE
Public PlayingMusic As MUSIC_TYPE

Public Sub StartGameMusic(song As MUSIC_TYPE)

If MusicEnabled = False Then Exit Sub

    StopMusicPlaying
    
    If song = INTRO Then
        StartMp3Music "intro.mp3"
        PlayingMusic = INTRO
    ElseIf song = CREDTIS Then
        StartMp3Music "credits.mp3", True
        PlayingMusic = CREDTIS
    ElseIf song = GAME1 Then
        StartMp3Music "loop1.mp3"
        PlayingMusic = GAME1
    ElseIf song = GAME2 Then
        StartMp3Music "loop2.mp3"
        PlayingMusic = GAME2
    ElseIf song = GAME3 Then
        StartMp3Music "loop3.mp3"
        PlayingMusic = GAME3
    ElseIf song = GAME4 Then
        StartMp3Music "loop4.mp3"
        PlayingMusic = GAME4
    ElseIf song = GAME5 Then
        StartMp3Music "loop5.mp3"
        PlayingMusic = GAME5
    ElseIf song = GAME6 Then
        StartMp3Music "loop6.mp3"
        PlayingMusic = GAME6
    ElseIf song = GAME7 Then
        StartMp3Music "loop7.mp3"
        PlayingMusic = GAME7
    ElseIf song = GAME8 Then
        StartMp3Music "loop8.mp3"
        PlayingMusic = GAME8
    ElseIf song = GAME9 Then
        StartMp3Music "loop9.mp3"
        PlayingMusic = GAME9
    ElseIf song = STORY Then
        StartMp3Music "story.mp3"
        PlayingMusic = STORY
    ElseIf song = MNU Then
        StartMp3Music "menu.mp3"
        PlayingMusic = MNU
    ElseIf song = TITLESCREEN Then
        StartMp3Music "title.mp3"
        PlayingMusic = TITLESCREEN
    ElseIf song = LOBBY Then
        StartMp3Music "lobby.mp3"
        PlayingMusic = LOBBY
    ElseIf song = GAMEOVER Then
        StartMp3Music "gameover.mp3"
        PlayingMusic = GAMEOVER
    End If
    
End Sub

Public Sub StopMusicPlaying()
    
    FSOUND_Stream_Stop streamHandle
    FSOUND_Stream_Close streamHandle
    streamChannel = 0
    streamHandle = 0
    
    StopModuleMusic

End Sub

Public Sub StartStreamMusic(sStyle As MUSIC_TYPE)
    
    Dim sAdress As String
    
    If sStyle = STREAMCHILLOUT Then
        sAdress = "http://64.236.98.50/stream/1035"
    ElseIf sStyle = STREAMSYNTHPOP Then
        sAdress = "http://160.79.128.40:7234/"
    Else
        sAdress = ""
    End If
    
    streamHandle = FSOUND_Stream_Open(sAdress, FSOUND_STREAM_NET, 0, 0)
    If streamHandle <> 0 Then
    'success
    Else
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: OPENING STREAM FOR NETRADIO"
        Exit Sub
    End If

    streamChannel = FSOUND_Stream_Play(FSOUND_FREE, streamHandle)

    If streamChannel <> 0 Then
    'Playing
    Else
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: STARTING STREAM FOR NETRADIO"
    End If
        
End Sub

Public Sub StartMp3Music(mp3song As String, Optional NoLoop As Boolean = False)
       
    If Not NoLoop Then
        streamHandle = FSOUND_Stream_Open(App.Path & "\music\" & mp3song, FSOUND_LOOP_NORMAL + FSOUND_MPEGHALFRATE, 0, 0)
    Else
        streamHandle = FSOUND_Stream_Open(App.Path & "\music\" & mp3song, FSOUND_LOOP_OFF, 0, 0)
    End If
    If streamHandle <> 0 Then
        'success
    Else
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: OPENING MP3STREAM"
        Exit Sub
    End If
    
    streamChannel = FSOUND_Stream_Play(FSOUND_FREE, streamHandle)

    If streamChannel <> 0 Then
        'Playing
    Else
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: PLAYING MP3STREAM"
    End If

End Sub

Public Sub StartModuleMusic(msong As String)
    
    songHandle = FMUSIC_LoadSong(msong)
    If songHandle <> 0 Then
        'Loading was successful
    Else
        'Something went wrong
    End If
    
    Dim result As Boolean
    result = FMUSIC_PlaySong(songHandle)

End Sub

Public Sub StopModuleMusic()

    FMUSIC_StopSong songHandle
    FMUSIC_FreeSong songHandle
    'You should manually set the handle to 0 after closing the song
    'This way, you can see if the song is loaded or not
    songHandle = 0

End Sub

Public Sub LoadMp3List()

With frmMain.FileMp3
    If (Dir(App.Path & "\music\") = "") Then Exit Sub
    .Path = App.Path & "\music\"
End With
    
    Mp3Count = frmMain.FileMp3.ListCount
    

    
    Dim i As Integer
    
    For i = 0 To Mp3Count - 1
        frmMain.ListMp3.AddItem App.Path & "\music\" & frmMain.FileMp3.List(i)
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, frmMain.ListMp3.List(i)
            
            
            
        DoEvents
            
    Next i

End Sub

Public Function CheckPlayingInfo(Optional CheckSelectedInstead As Boolean = False) As String

Dim tmpValue As String
Dim tmpValue2 As String

    If PlayingMusic = CREDTIS Then
        tmpValue = "CREDITS"
    ElseIf PlayingMusic = GAME1 Then
        tmpValue = "GAME TUNE 1"
    ElseIf PlayingMusic = GAME2 Then
        tmpValue = "GAME TUNE 2"
    ElseIf PlayingMusic = GAME3 Then
        tmpValue = "GAME TUNE 3"
    ElseIf PlayingMusic = GAME4 Then
        tmpValue = "GAME TUNE 4"
    ElseIf PlayingMusic = GAME5 Then
        tmpValue = "GAME TUNE 5"
    ElseIf PlayingMusic = GAME6 Then
        tmpValue = "GAME TUNE 6"
    ElseIf PlayingMusic = GAME7 Then
        tmpValue = "GAME TUNE 7"
    ElseIf PlayingMusic = GAME8 Then
        tmpValue = "GAME TUNE 8"
    ElseIf PlayingMusic = GAME9 Then
        tmpValue = "GAME TUNE 9"
    ElseIf PlayingMusic = INTRO Then
        tmpValue = "INTRO"
    ElseIf PlayingMusic = MNU Then
        tmpValue = "MENU MUSIC"
    ElseIf PlayingMusic = LOBBY Then
        tmpValue = "LOBBY MUSIC"
    ElseIf PlayingMusic = TITLESCREEN Then
        tmpValue = "TITLE"
    ElseIf PlayingMusic = GAMEOVER Then
        tmpValue = "GAME OVER"
    End If
    
    If CheckSelectedInstead Then
        If SelectedMusic = CREDTIS Then
            tmpValue = "CREDITS"
        ElseIf SelectedMusic = GAME1 Then
            tmpValue = "GAME TUNE 1"
        ElseIf SelectedMusic = GAME2 Then
            tmpValue = "GAME TUNE 2"
        ElseIf SelectedMusic = GAME3 Then
            tmpValue = "GAME TUNE 3"
        ElseIf SelectedMusic = GAME4 Then
            tmpValue = "GAME TUNE 4"
        ElseIf SelectedMusic = GAME5 Then
            tmpValue = "GAME TUNE 5"
        ElseIf SelectedMusic = GAME6 Then
            tmpValue = "GAME TUNE 6"
        ElseIf SelectedMusic = GAME7 Then
            tmpValue = "GAME TUNE 7"
        ElseIf SelectedMusic = GAME8 Then
            tmpValue = "GAME TUNE 8"
        ElseIf SelectedMusic = GAME9 Then
            tmpValue = "GAME TUNE 9"
        ElseIf SelectedMusic = INTRO Then
            tmpValue = "INTRO"
        ElseIf SelectedMusic = MNU Then
            tmpValue = "MENU MUSIC"
        ElseIf SelectedMusic = LOBBY Then
            tmpValue = "LOBBY MUSIC"
        ElseIf SelectedMusic = TITLESCREEN Then
            tmpValue = "TITLE"
        ElseIf SelectedMusic = GAMEOVER Then
            tmpValue = "GAME OVER"
        End If
    End If
    
    If MusicEnabled = False Then
        tmpValue = "MUSIC DISABLED!"
    End If
                    
    CheckPlayingInfo = tmpValue

End Function

