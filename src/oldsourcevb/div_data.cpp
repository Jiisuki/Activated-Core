Attribute VB_Name = "mod_DivData"
Public Type cType
    Name As String
    TeamName As String
    Crosshair As Integer
End Type
Public Character As cType

Public StoryHiPlayer As String
Public StoryHiScore As Long
Public UseVideoMem As Boolean
Public ScreenMode As Integer
Public cTransparent As Boolean
Public MusicEnabled As Boolean
Public SFXEnabled As Boolean

Public Enum MusicType
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
Public SelectedMusic As MusicType

Public Type StrF
    On As Boolean
End Type
Public StarfieldEnabled As StrF

Public ShowIntro As Boolean
Public PacketSpeed As Integer

