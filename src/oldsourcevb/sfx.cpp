Attribute VB_Name = "mod_SFX"
Public sampleHandle As Long
Public sampleChannel As Long
Public SFXEnabled As Boolean
Public SampleFreq As Long

Public Type SFXRayBase
    xPos As Single
    XSpeed As Single
    yPos As Single
    YSpeed As Single
    Power(0 To 5) As Single
    HitWindow() As Single
End Type
Public SFXRay() As SFXRayBase

Public RayTraceStep As Integer
Public RayTraceThreshold As Single
Public RayTraceRaynum As Integer
Public RayTraceMaxResolution As Double
Public RayTraceHS As Single
Public RayMaxSpeed As Integer
Public RayHitWindowSize As Integer
Public RayTraceMaxDivs As Integer
Public RayTracePropagationLoss As Single
Public RayTraceHSLoss As Single
Public RayTraceMaxReverbTime As Single

Public SFXImpulseLeft() As Single
Public SFXImpulseRight() As Single

Public Sub InitRayTraceEngine()
    
    'Initial values and engine environment.
    RayTraceMaxReverbTime = 0.5                                 'Maximum reverberation time in seconds.
    RayTraceThreshold = 0.1                                     'Ray power threshold for ALIVE status.
    RayTraceRaynum = 512                                        'Number of rays.
    RayTraceMaxResolution = RayTraceMaxReverbTime * SampleFreq  'Size of the impulse response.
    RayTraceHS = 0.4                                            'Head shadow damping.
    RayMaxSpeed = 32                                            'Maximum speed of each ray.
    RayHitWindowSize = 128                                      'Hit peak size.
    RayTraceMaxDivs = 0.01 * SampleFreq                         'Maximum separation allowed.
    RayTracePropagationLoss = 0.0001                            'Propagation loss.
    RayTraceStep = CInt(RayTraceMaxDivs / 2)                    'Iteration step.
    RayTraceHSLoss = 0.4                                        'Head Shadow loss.
    
    
    
    'Setup the Window (Values from Matlab).
    Dim WindowShape(0 To 128) As Single
    WindowShape(0) = 0
    WindowShape(RayHitWindowSize) = 0
    
    'Allocate Memory.
    ReDim SFXRay(0 To RayTraceRaynum)
    ReDim SFXImpulseLeft(0 To RayTraceMaxResolution)
    ReDim SFXImpulseRight(0 To RayTraceMaxResolution)
    
    'Initial values for the rays.
    For i = 0 To RayTraceRaynum
        With SFXRay(i)
            .Power(0) = 1
            .xPos = 32
            .yPos = 32
            .XSpeed = 0
            .YSpeed = 0
            ReDim .HitWindow(0 To RayHitWindowSize)
            'Set each ray peak shape, used for adding to the impulse response.
            'By initilizing them here instead of using pure random in the raytracing,
            'speed is optimized. This will be more psuedo-random, and make the sound
            'actually more equal between different raytracings.
            For j = 0 To RayHitWindowSize
                .HitWindow(j) = CSng(Rnd * WindowShape(j))
            Next j
        End With
    Next i
    
End Sub

Public Sub RayTrace(SourceX As Integer, SourceY As Integer, TargetX1 As Integer, TargetX2 As Integer, TargetY1 As Integer, TargetY2 As Integer)
    'Set up random directions and defined positions
    For i = 0 To RayTraceRaynum
        Dim tmpAng As Single
        tmpAng = Int(Rnd * 360)
        With SFXRay(i)
            .XSpeed = Cos(tmpAng) * RayMaxSpeed
            .YSpeed = Sin(tmpAng) * RayMaxSpeed
            .xPos = SourceX
            .yPos = SourceY
            .Power(0) = 1
        End With
    Next i
    
    'Clear impulse responses and allocate memory.
    ReDim SFXImpulseLeft(0)
    ReDim SFXImpulseLeft(0 To RayTraceMaxResolution)
    ReDim SFXImpulseRight(0)
    ReDim SFXImpulseRight(0 To RayTraceMaxResolution)
    
    'Start raytracing
    Dim n As Integer
    Dim tmpX As Single, tmpY As Single
    Dim Hits As Integer
    
    Hits = 0
    n = 0
    Do
        For i = 0 To RayTraceRaynum
            'Update new sound particle position
            With SFXRay(i)
                If .Power(0) > RayTraceThreshold Then
                    tmpX = .xPos + .XSpeed
                    tmpY = .yPos + .YSpeed
                    
                    DDS_COLLISIONMAP.Lock rMAPCUT, DDSD_COLLISIONMAP, DDLOCK_READONLY, 0
                    If DDS_COLLISIONMAP.GetLockedPixel(Round(tmpX), Round(tmpY)) = cWhite Then
                        If .YSpeed > 0 Then
                            .YSpeed = -1 * .YSpeed
                            While DDS_COLLISIONMAP.GetLockedPixel(Round(tmpX), Round(tmpY)) = cWhite
                                tmpY = tmpY - 1
                            Wend
                            .Power(0) = .Power(0) * 0.9
                        ElseIf .YSpeed < 0 Then
                            .YSpeed = -1 * .YSpeed
                            While DDS_COLLISIONMAP.GetLockedPixel(Round(tmpX), Round(tmpY)) = cWhite
                                tmpY = tmpY + 1
                            Wend
                            .Power(0) = .Power(0) * 0.9
                        End If
                        If .XSpeed > 0 Then
                            .XSpeed = -1 * .XSpeed
                            While DDS_COLLISIONMAP.GetLockedPixel(Round(tmpX), Round(tmpY)) = cWhite
                                tmpX = tmpX - 1
                            Wend
                            .Power(0) = .Power(0) * 0.9
                        ElseIf .XSpeed < 0 Then
                            .XSpeed = -1 * .XSpeed
                            While DDS_COLLISIONMAP.GetLockedPixel(Round(tmpX), Round(tmpY)) = cWhite
                                tmpX = tmpX + 1
                            Wend
                            .Power(0) = .Power(0) * 0.9
                        End If
                    End If
                    
                    .xPos = tmpX
                    .yPos = tmpY
                    DDS_COLLISIONMAP.Unlock rMAPCUT
                
                    'Check if outside level:
                    If .xPos < 1 Or .xPos > MapWidth * 32 Or .yPos < 1 Or .yPos > MapHeight * 32 Then
                        .Power(0) = 0
                    End If
                    
                    'Check for arrival:
                    If .xPos > TargetX1 And .xPos < TargetX2 And .yPos > TargetY1 And .yPos < TargetY2 Then
                        If .XSpeed > 0 Then
                            SFXImpulseLeft(CDbl(n * RayTraceStep)) = .Power(0)
                        Else
                            SFXImpulseRight(CDbl(n * RayTraceStep)) = .Power(0)
                        End If
                        .Power(0) = 0 '.Power(0) * RayTraceHS
                        Hits = Hits + 1
                    End If
                End If
            End With
        Next i
        
        n = n + 1
        DoEvents
    Loop While n < CDbl(RayTraceMaxResolution / RayTraceStep)
    ChatFeed "Raytracing Completed (" & CStr(Hits) & ")", "SFX"

End Sub


Public Sub PlaySample(SampleFile As String, Optional fPickup As Boolean = False)

    If SFXEnabled = False Then Exit Sub
    Dim fs As Long
    fs = FSOUND_FREE
    If fs = 1 Then fs = 2
    
    If fPickup Then
        sampleHandle = FSOUND_Sample_Load(fs, App.Path & "\sfx\" & SampleFile, FSOUND_LOOP_OFF, 0, 0)
    Else
        sampleHandle = FSOUND_Sample_Load(FSOUND_FREE, App.Path & "\sfx\" & SampleFile, FSOUND_LOOP_OFF, 0, 0)
    End If
    
    If sampleHandle <> 0 Then
        'Loading was successful
    Else
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: LOADING SFX-SAMPLE"
        Exit Sub
    End If

    'You should always use FSOUND_FREE as the first paramter
    'This lets fmod choose a free channel and play the sample in it
    'Each sample can be played more than once if necessary
    'If you need to keep track of each sample that is playing,
    'You will need as much variables as times you want to play the sample
    'to store the sample channels in'
    If fPickup Then
        sampleChannel = FSOUND_PlaySound(fs, sampleHandle)
    Else
        sampleChannel = FSOUND_PlaySound(FSOUND_FREE, sampleHandle)
    End If

    If sampleChannel <> 0 Then
        'Playing
    Else
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "ERROR: PLAYING SFX-SAMPLE"
    End If

End Sub

Public Sub CloseSoundFX()

    FSOUND_Sample_Free sampleHandle
        'You should manually set the handle to 0 after closing the song
        'This way, you can see if the song is loaded or not
    sampleHandle = 0

End Sub

