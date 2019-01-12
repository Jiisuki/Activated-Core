VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cls_BotClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
'set this to 0 to disable debug code in this class
#Const DebugMode = 1


#If DebugMode Then
    'local variable to hold the serialized class ID that was created in Class_Initialize
    Private mlClassDebugID As Long
#End If
'local variable(s) to hold property value(s)
Private mvarClassDebugID As Variant 'local copy
Private mvarAnimation As STATE_ENUM    'local copy
Private mvarAnimationFrame As Integer 'local copy
Private mvarAnimationLen As Integer
Private mvarModel As String 'local copy
Private mvarX As Long 'local copy
Private mvarY As Long 'local copy
Private mvarMoveX As Integer
Private mvarNickName As String 'local copy
Private mvarTeam As TEAMTYPE  'local copy
Private mvarTeamName As String 'local copy
Private mvarHealth As Integer 'local copy
Private mvarFrags As Integer 'local copy
Private mvarDeaths As Integer 'local copy
Private mvarCurrentWeapon As SelectedWeaponEnum  'local copy
Private mvarComputerControlled As Boolean 'local copy
Private mvarStandingOnGround As Boolean
Private mvarCrouching As Boolean
Private mvarYSpeed As Integer
Private mvarJetpak As Boolean
Private mvarArmor As Integer
Private mvarArmorMax As Integer
Private mvarDead As Boolean
Private mvarFiring As Boolean
Private mvarGotJumpAssist As Boolean
Private mvarJumpAssistTime As Boolean
Private mvarGotShield As Boolean
Private mvarGotHeartSens As Boolean
Private mvarShieldTime As Integer
Private mvarGotCap As Boolean
Private mvarReverseFlag As Boolean
Private mvarAIState As BotState
Private mvarMoveDown As Boolean
Private idPlayerID As Long
Private intType As Byte

Public Sub Jump()

    If Me.StandingOnGround Then Me.YSpeed = JumpForce

End Sub

Public Sub AnimateBot()

'------------------------------------------.
'This controls the animations of the game. |
'------------------------------------------'

    '---------------------------------------------------.
    'Control the looping speed with tickcount function. |
    '---------------------------------------------------'
    lTickCount7 = GetTickCount()
    
    If (lTickCount7 - lOldTickCount7) > 500 Then
        'Save the tick count
        lOldTickCount7 = GetTickCount()
        
        '-------------------.
        'Select next frame. |
        '-------------------'
        
        If Me.MoveX < 0 Then
            If Me.ReverseFlag = False Then
                Me.Animation = RUNNING
                Me.AnimationLen = 8
                Me.AnimationFrame = Me.AnimationFrame - 1
                If Me.AnimationFrame < 0 Then Me.AnimationFrame = Me.AnimationLen - 1
            Else
                Me.Animation = RUNNING
                Me.AnimationLen = 8
                Me.AnimationFrame = Me.AnimationFrame + 1
                If Me.AnimationFrame >= Me.AnimationLen Then Me.AnimationFrame = 0
                
            End If
        ElseIf MOVERIGHT = True Then
            If ReverseFlag = False Then
                Me.Animation = RUNNING
                Me.AnimationLen = 8
                Me.AnimationFrame = Me.AnimationFrame + 1
                If Me.AnimationFrame >= Me.AnimationLen Then Me.AnimationFrame = 0
                
            Else
                Me.Animation = RUNNING
                Me.AnimationLen = 8
                Me.AnimationFrame = Me.AnimationFrame - 1
                If Me.AnimationFrame < 0 Then Me.AnimationFrame = Me.AnimationLen - 1
            End If
        Else
            Me.Animation = STANDING
            Me.AnimationLen = 6
            Me.AnimationFrame = 0
            If Me.AnimationFrame >= Me.AnimationLen Then Me.AnimationFrame = 0
        End If

    End If
        
End Sub


Public Sub Spawn()

Me.Team = rBLUE
Me.YSpeed = 0                        'Reset gravity speed
Me.Health = 250                      'Init health.
Me.Dead = False
Me.MoveDown = False
Me.AIState = SEARCHING
Me.MoveX = -5

Retry:

Randomize
Dim z As Integer

z = Int(Rnd * SPAWNPOINTS)


If GAMEMODE = MULTIPLAY_CTF Then
    If SPAWNPOINT(z).BUSY = False And SPAWNPOINT(z).Team = Me.Team Then
        Me.X = SPAWNPOINT(z).X
        Me.Y = SPAWNPOINT(z).Y
    Else
        GoTo Retry
    End If
Else
    If SPAWNPOINT(z).BUSY = False Then
        Me.X = SPAWNPOINT(z).X
        Me.Y = SPAWNPOINT(z).Y
    Else
        GoTo Retry
    End If
End If


                                'Select starting weapon

                                'Reset DEAD-flag and don't show status.

End Sub

Public Sub ClientInit(Optional Nick As String = "")


    Me.ComputerControlled = True
    If Nick <> "" Then
        Me.NickName = Nick
    Else
        Me.NickName = GetRandomName
    End If
        
    Me.TeamName = "BOT"
    Me.Frags = 0
    Me.Deaths = 0
    Me.Dead = False
    Me.Animation = STANDING
    Me.AnimationLen = 1
    Me.AnimationFrame = 0
    Me.AIState = SEARCHING
    Me.CurrentWeapon = Blaster
    Me.Health = 250
    Me.MoveDown = False
    Me.MoveX = 0
    Me.ReverseFlag = False
    Me.StandingOnGround = False
    Me.YSpeed = 0
            
    #If DebugMode Then
        'get the next available class ID, and print out
        'that the class was created successfully
        If EngineLogEnabled Then
            If Me.ComputerControlled Then
                If EngineLogEnabled Then WriteEngineLOG LOGFILE, "'" & TypeName(Me) & "' instance " & mlClassDebugID & " created as a bot with the name '" & Me.NickName & "'."
            Else
                If EngineLogEnabled Then WriteEngineLOG LOGFILE, "'" & TypeName(Me) & "' instance " & mlClassDebugID & " created as " & Me.NickName & " playing with " & Me.TeamName
            End If
        End If
    #End If

End Sub

Public Property Let iPlayerID(ByVal vData As Long)
    idPlayerID = vData
    
End Property

Public Property Get iPlayerID() As Long
    iPlayerID = idPlayerID
End Property

Public Property Let iType(ByVal vData As Byte)
    intType = vData
End Property

Public Property Get iType() As Byte
    iType = intType
End Property

Public Property Let GotShield(ByVal vData As Boolean)
    mvarGotShield = vData
End Property

Public Property Get GotShield() As Boolean
    GotShield = mvarGotShield
End Property

Public Property Let AIState(ByVal vData As BotState)
    mvarAIState = vData
    
End Property

Public Property Get AIState() As BotState
    AIState = mvarAIState
End Property

Public Property Let StandingOnGround(ByVal vData As Boolean)
    mvarStandingOnGround = vData
End Property

Public Property Get StandingOnGround() As Boolean
    StandingOnGround = mvarStandingOnGround
End Property

Public Property Let MoveDown(ByVal vData As Boolean)
    mvarMoveDown = vData
End Property

Public Property Get MoveDown() As Boolean
    MoveDown = mvarMoveDown
End Property


Public Property Let ComputerControlled(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ComputerControlled = 5
    mvarComputerControlled = vData
End Property


Public Property Get ComputerControlled() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ComputerControlled
    ComputerControlled = mvarComputerControlled
End Property

Public Property Let ReverseFlag(ByVal vData As Boolean)
    mvarReverseFlag = vData
End Property

Public Property Get ReverseFlag() As Boolean
    ReverseFlag = mvarReverseFlag
End Property

Public Property Let CurrentWeapon(ByVal vData As SelectedWeaponEnum)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.CurrentWeapon = 5
    mvarCurrentWeapon = vData
End Property

Public Property Get CurrentWeapon() As SelectedWeaponEnum
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.CurrentWeapon
    CurrentWeapon = mvarCurrentWeapon
End Property

Public Property Let Deaths(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Deaths = 5
    mvarDeaths = vData
End Property


Public Property Get Deaths() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Deaths
    Deaths = mvarDeaths
End Property

Public Property Let Dead(ByVal vData As Boolean)
    mvarDead = vData
End Property

Public Property Get Dead() As Boolean
    Dead = mvarDead
End Property


Public Property Let Frags(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Frags = 5
    mvarFrags = vData
End Property


Public Property Get Frags() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Frags
    Frags = mvarFrags
End Property



Public Property Let Health(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Health = 5
    mvarHealth = vData
End Property


Public Property Get Health() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Health
    Health = mvarHealth
End Property



Public Property Let TeamName(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.TeamName = 5
    mvarTeamName = vData
End Property


Public Property Get TeamName() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.TeamName
    TeamName = mvarTeamName
End Property



Public Property Let Team(ByVal vData As TEAMTYPE)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Team = 5
    mvarTeam = vData
End Property

Public Property Get Team() As TEAMTYPE
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Team
    Team = mvarTeam
End Property



Public Property Let NickName(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.NickName = 5
    mvarNickName = vData
End Property


Public Property Get NickName() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.NickName
    NickName = mvarNickName
End Property

Public Property Let Y(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Y = 5
    mvarY = vData
End Property


Public Property Get Y() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Y
    Y = mvarY
End Property

Public Property Let YSpeed(ByVal vData As Integer)
    mvarYSpeed = vData
End Property

Public Property Get YSpeed() As Integer
    YSpeed = mvarYSpeed
End Property


Public Property Let X(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.X = 5
    mvarX = vData
End Property


Public Property Get X() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.X
    X = mvarX
End Property

Public Property Let MoveX(ByVal vData As Integer)
    mvarMoveX = vData
End Property

Public Property Get MoveX() As Integer
    MoveX = mvarMoveX
End Property


Public Property Let Model(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Model = 5
    mvarModel = vData
End Property


Public Property Get Model() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Model
    Model = mvarModel
End Property



Public Property Let AnimationFrame(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.AnimationFrame = 5
    mvarAnimationFrame = vData
End Property


Public Property Get AnimationFrame() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.AnimationFrame
    AnimationFrame = mvarAnimationFrame
End Property



Public Property Let Animation(ByVal vData As STATE_ENUM)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Animation = 5
    mvarAnimation = vData
End Property


Public Property Get Animation() As STATE_ENUM
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Animation
    Animation = mvarAnimation
End Property

Public Property Let AnimationLen(ByVal vData As Integer)
    mvarAnimationLen = vData
End Property

Public Property Get AnimationLen() As Integer
    AnimationLen = mvarAnimationLen
End Property




Public Property Get ClassDebugID() As Variant
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ClassDebugID
    If IsObject(mvarClassDebugID) Then
        Set ClassDebugID = mvarClassDebugID
    Else
        ClassDebugID = mvarClassDebugID
    End If
End Property





Private Sub Class_Initialize()
    #If DebugMode Then
        'get the next available class ID, and print out
        'that the class was created successfully
        Debug.Print "'" & TypeName(Me) & "' instance " & mlClassDebugID & " created"
    #End If
    'cCmdFeed Me.NickName, True
End Sub


Private Sub Class_Terminate()
    'the class is being destroyed
    #If DebugMode Then
        Debug.Print "'" & TypeName(Me) & "' instance " & CStr(mlClassDebugID) & " is terminating"
    #End If
End Sub
