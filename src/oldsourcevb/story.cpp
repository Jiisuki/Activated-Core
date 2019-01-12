Attribute VB_Name = "mod_Story"
Public InstructionsPageFlagged(0 To 50) As Boolean  'This is used to flag certain on screen
                                                    'messages to the player. When flagged,
                                                    'the message is not shown.
                                                    
Public Enum typeEnemyType
    Lurker = 0
    Mole = 1
End Enum

Public Type CutSceneType
    Surf As DirectDrawSurface7          'This holds the surface of the cutscene (i.e. image)
    SurfDesc As DDSURFACEDESC2          'This is the description of the image
    SurfSourceRect As RECT              'This is information about the size of the image to cut from
    SurfBltFastX As Integer             'X-position on the screen where it's suppose to go
    SurfBltFastY As Integer             'Y-pos
    SurfMovementX As Integer            'Movement of the image on the screen (for effects)
    SurfMovementY As Integer            'Same as above, but in Y-coord.
    TextLineText(0 To 3) As String      'The narration text line. 4 lines/cutscreen
    TextLineCharmap(0 To 3) As Integer  'Which character map to use for the screen
    TextLinePosX(0 To 3) As Integer     'Position in X for the textline (1/4)
    TextLinePosY(0 To 3) As Integer     'Position in Y for the textline
    TextLineEffect(0 To 3) As Integer   'This is the effect integer, used for typewriter action
    TextLineEffectLine As Integer       'This holds which textline to manipulate
    FrameLength As Long                 'Number of "frames" to show the screen. It's not related to 60 fps, it's an own counter
    FrameCurrent As Long                'Current "frame"-number
End Type

Public CutScene(0 To 64) As CutSceneType    'The cutscene-array holds every single cutscene in the game
Public CutSceneCurrent As Integer           'Holds which cutscreen that should be shown

Public StoryStatus As Integer       'Some variables for the storymode, this is which level player is at. Controls many things.
Public StoryMapFinish As Boolean    'A flag for making sure that the player finishes the level.
Public StoryPlayerLives As Integer  'Player continues
Public StoryPlayerPoints As Long    'Player points
Public StoryHiScore As Long         'Current Hiscore
Public StoryHiPlayer As String      'Current Hiscore-Signature

Public Sub Game_Over()              'Procedure when all continues are out.
    Story_INIT 1                    'Reset the game
    StoryMapFinish = True           'Make sure the player is not still playing the map
    StoryStatus = 1                 'Reset to level 1.
    MENU.VisibleMenu = MNUGameOver  'Show the game over screen.
    StartGameMusic GAMEOVER         'Start the game over music.
    gSTARTED = False                'Stop the game-flag
    OverlayMenu = False             'This is for security to just show the real menu.
    bQuit = True                    'Stop the renderloop to return to menu.
End Sub

Public Sub FinishLevel(StoryLevel As Integer)           'Procedure to exit a level.

    If StoryLevel = 1 Then                              'The rutine for level one.
        StoryPlayerPoints = StoryPlayerPoints + 10000   'Player gains 10000 points upon completion.
        StoryStatus = 2                                 'Set next map to level two.
        Story_INIT 2                                    'Init the cutscenes for level 2.
        StoryMapFinish = True                           'Finish-flag
        MENU.VisibleMenu = MNUStory                     'Show the cutscene menu
        StartGameMusic STORY                            'Start the cutscene music
        gSTARTED = False                                'End the game (playing mode)
        OverlayMenu = False                             'Don't show a fake menu
        bQuit = True                                    'Exit to the real menu
    ElseIf StoryLevel = 2 Then
        StoryPlayerPoints = StoryPlayerPoints + 10000   'Gain 10000 points upon completion.
        Story_INIT 3                                    'Set up cuts for level 3.
        StoryStatus = 3                                 'Set next map to level 3.
        StoryMapFinish = True                           'Finish-flag
        MENU.VisibleMenu = MNUMain                      'etc.
        StartGameMusic TITLESCREEN
        gSTARTED = False
        OverlayMenu = False
        bQuit = True
    End If

End Sub


Public Sub Story_INIT(Optional StoryChapter As Integer = 1)
'This procedure initializes the cutscenes.
'The images is already loaded in the LoadSurfaces subroutine.
'This basically sets the texts for every scene.
'It takes an optional StoryChapter flag. This isn't really
'important, because the StoryStatus is set before this sub is
'inited. Will be changed later.

Dim i As Integer, tmpT As Integer

'INIT STORY LINES
    If StoryChapter = 1 Then
    
        StoryStatus = 1         'This is already set, but set again for sec in alpha version.
        StoryPlayerLives = 0    'Set initial conts.
        CutSceneCurrent = 0     'Set current cutscene (to separate between levels)
        
        With CutScene(0)
            .TextLineText(0) = "Many years ago, Sarah Anderson"     'Text line one
            .TextLineText(1) = "was given a mission to seek"        'Text line two
            .TextLineText(2) = "alien life forms in outer space"    'Text line three
            .TextLineText(3) = ""                                   'Text line four
            .FrameLength = 0                                        'Extra frame length, used mainly for the last scene.
        End With
    
        With CutScene(1)
            .TextLineText(0) = "But during her absense"
            .TextLineText(1) = "several comets infected "
            .TextLineText(2) = "with alien hybrids struck"
            .TextLineText(3) = "Earth. The devastation was total"
            .FrameLength = 0
        End With
        
        With CutScene(2)
            .TextLineText(0) = "After her mission was over"
            .TextLineText(1) = "she returned home. The aliens"
            .TextLineText(2) = "had infected the earth atmosphere"
            .TextLineText(3) = "making the lack of oxygen obsolete"
            .FrameLength = 0
        End With
        
        With CutScene(3)
            .TextLineText(0) = "She gathered a lot of data"
            .TextLineText(1) = "from the atmosphere of earth"
            .TextLineText(2) = "This data could probably be"
            .TextLineText(3) = "the rescue for earth"
            .FrameLength = 0
        End With
        
        With CutScene(4)
            .TextLineText(0) = "Though the laboratory on"
            .TextLineText(1) = "the ship was not enough"
            .TextLineText(2) = "to analyze this data."
            .TextLineText(3) = "She had to get to her HQ"
            .FrameLength = 0
        End With
        
        With CutScene(5)
            .TextLineText(0) = "On the way through"
            .TextLineText(1) = "the earth atmosphere"
            .TextLineText(2) = "she experienced strong"
            .TextLineText(3) = "problems with the ship..."
            .FrameLength = 50 'This will give a few seconds longer hold-time
        End With
    
    ElseIf StoryChapter = 2 Then
    
        StoryStatus = 2
        CutSceneCurrent = 6
        
        With CutScene(6)
            .TextLineText(0) = "Analyzing the data"
            .TextLineText(1) = "gave important information"
            .TextLineText(2) = "about the structure of"
            .TextLineText(3) = "the alien hybrid."
            .FrameLength = 0
        End With
        
        With CutScene(7)
            .TextLineText(0) = "She constructs a bomb"
            .TextLineText(1) = "that will take out the"
            .TextLineText(2) = "hybrid. The only problem"
            .TextLineText(3) = "is to get to the core."
            .FrameLength = 0
        End With
        
        With CutScene(8)
            .TextLineText(0) = "The aliens has rebuilt"
            .TextLineText(1) = "the core of the earth"
            .TextLineText(2) = "to a machine that controls"
            .TextLineText(3) = "every organism on the planet."
            .FrameLength = 0
        End With
        
        With CutScene(9)
            .TextLineText(0) = "It seems like her suit"
            .TextLineText(1) = "is the only thing keeping"
            .TextLineText(2) = "her alive. If it get destroyed"
            .TextLineText(3) = "it will all be over."
            .FrameLength = 0
        End With
        
        With CutScene(10)
            .TextLineText(0) = "What's up?"
            .TextLineText(1) = ""
            .TextLineText(2) = "Check out"
            .TextLineText(3) = "www.jiisuki.net"
            .FrameLength = 50
        End With
        
    End If
    
    'This sets the standard options for all scenes
    For i = 0 To UBound(CutScene)
        With CutScene(i)
            .SurfSourceRect.Left = 0        'The size of the cutscenes
            .SurfSourceRect.Right = 90
            .SurfSourceRect.Top = 0
            .SurfSourceRect.Bottom = 60
            .SurfBltFastX = 115             'Blitting position of the image
            .SurfBltFastY = 60
            .SurfMovementX = 0              'Image movement factor
            .SurfMovementY = 0
            If i = 5 Or i = 10 Then
                .TextLineCharmap(0) = 5         'Character map
                .TextLineCharmap(1) = 5
                .TextLineCharmap(2) = 5
                .TextLineCharmap(3) = 5
            ElseIf i >= 32 Then
                .TextLineCharmap(0) = 1         'Character map
                .TextLineCharmap(1) = 1
                .TextLineCharmap(2) = 1
                .TextLineCharmap(3) = 1
            Else
                .TextLineCharmap(0) = 4         'Character map
                .TextLineCharmap(1) = 4
                .TextLineCharmap(2) = 4
                .TextLineCharmap(3) = 4
            End If
            For tmpT = 0 To 3
                .TextLinePosX(tmpT) = 160 - ((Len(.TextLineText(tmpT)) / 2) * 8)    'Center text
                .TextLinePosY(tmpT) = 130 + (tmpT * 10)                             'Rows under image
                .TextLineEffect(tmpT) = 0                                           'Reset all effects
                .FrameLength = .FrameLength + Len(CutScene(0).TextLineText(tmpT))   'Set timing for the scene
            Next tmpT
            .TextLineEffectLine = 0             'Reset effect line
            .FrameLength = .FrameLength + 70    'Add extra units to the framelen.
            .FrameCurrent = 0                   'Reset the frame counter
        End With
    Next i
                
End Sub

Public Sub DrawStory()
    
'Update the current screen.
StoryPosUpdate

'Blit current cutscene
DDS_Back.BltFast CutScene(CutSceneCurrent).SurfBltFastX, CutScene(CutSceneCurrent).SurfBltFastY, CutScene(CutSceneCurrent).Surf, CutScene(CutSceneCurrent).SurfSourceRect, DDBLTFAST_WAIT
    
'Draw every textline in the current cutscene
Dim i As Integer
For i = 0 To UBound(CutScene(CutSceneCurrent).TextLineText)
    
    'The use of the Mid() gives an effect of a typewriter.
    DrawText UCase(Mid(CutScene(CutSceneCurrent).TextLineText(i), 1, CutScene(CutSceneCurrent).TextLineEffect(i))), CSng(CutScene(CutSceneCurrent).TextLinePosX(i)), CSng(CutScene(CutSceneCurrent).TextLinePosY(i)), 0, CutScene(CutSceneCurrent).TextLineCharmap(i)
    'Don't lock the system while blitting
    DoEvents

Next i
        
End Sub
    
Public Sub StoryPosUpdate()

'This is the timing for the updating
'A lower number for the ticks will be faster.
'If set low, remember to change the framelengths of the scenes.

lTickCount6 = GetTickCount()
    
    If (lTickCount6 - lOldTickCount6) > 40 Then
        lOldTickCount6 = GetTickCount
        
        'Count the frames to show current scene
        CutScene(CutSceneCurrent).FrameCurrent = CutScene(CutSceneCurrent).FrameCurrent + 1
        'If the frame is out, switch to the next one.
        If CutScene(CutSceneCurrent).FrameCurrent >= CutScene(CutSceneCurrent).FrameLength Then
            
            CutSceneCurrent = CutSceneCurrent + 1
            PlaySample "menu\select.mp3"
            
            'Check if the total amount of screens has been shown, if so, proceed to the playing
            If StoryStatus = 1 Then
                If CutSceneCurrent > 5 Then LoadMap App.Path & "\MAPS\STORY\STORY01"
            ElseIf StoryStatus = 2 Then
                If CutSceneCurrent > 10 Then LoadMap App.Path & "\MAPS\STORY\STORY02"
            Else 'Like the first level
                If CutSceneCurrent > 5 Then LoadMap App.Path & "\MAPS\STORY\STORY01"
            End If
        End If
        
        'Write the text like a machine
        If CutScene(CutSceneCurrent).TextLineEffect(CutScene(CutSceneCurrent).TextLineEffectLine) < Len(CutScene(CutSceneCurrent).TextLineText(CutScene(CutSceneCurrent).TextLineEffectLine)) Then
            CutScene(CutSceneCurrent).TextLineEffect(CutScene(CutSceneCurrent).TextLineEffectLine) = CutScene(CutSceneCurrent).TextLineEffect(CutScene(CutSceneCurrent).TextLineEffectLine) + 1
            PlaySample "brief\typew.wav"
        End If
        
        If Not CutScene(CutSceneCurrent).TextLineEffectLine >= 3 Then
            If CutScene(CutSceneCurrent).TextLineEffect(CutScene(CutSceneCurrent).TextLineEffectLine) >= Len(CutScene(CutSceneCurrent).TextLineText(CutScene(CutSceneCurrent).TextLineEffectLine)) Then
                CutScene(CutSceneCurrent).TextLineEffectLine = CutScene(CutSceneCurrent).TextLineEffectLine + 1
            End If
        End If
    
    End If

End Sub
