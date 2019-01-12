VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cls_Client"
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
Private mvarAnimation As Integer 'local copy
Private mvarAnimationFrame As Integer 'local copy
Private mvarModel As String 'local copy
Private mvarX As Long 'local copy
Private mvarY As Long 'local copy
Private mvarNickName As String 'local copy
Private mvarTeam As Variant 'local copy
Private mvarTeamName As String 'local copy
Private mvarHealth As Integer 'local copy
Private mvarFrags As Integer 'local copy
Private mvarDeaths As Integer 'local copy
Private mvarCurrentWeapon As Integer 'local copy
Private mvarComputerControlled As Boolean 'local copy
Public Sub ClientInit()



End Sub

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



Public Property Let CurrentWeapon(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.CurrentWeapon = 5
    mvarCurrentWeapon = vData
End Property


Public Property Get CurrentWeapon() As Integer
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



Public Property Let Team(ByVal vData As Variant)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Team = 5
    mvarTeam = vData
End Property


Public Property Set Team(ByVal vData As Variant)
'used when assigning an Object to the property, on the left side of a Set statement.
'Syntax: Set x.Team = Form1
    Set mvarTeam = vData
End Property


Public Property Get Team() As Variant
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Team
    If IsObject(mvarTeam) Then
        Set Team = mvarTeam
    Else
        Team = mvarTeam
    End If
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



Public Property Let Animation(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Animation = 5
    mvarAnimation = vData
End Property


Public Property Get Animation() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Animation
    Animation = mvarAnimation
End Property

Private Sub Class_Terminate()
    'the class is being destroyed
    #If DebugMode Then
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "'" & TypeName(Me) & "' instance " & CStr(mlClassDebugID) & " is terminating"
    #End If
End Sub


#If DebugMode Then
    Public Property Get ClassDebugID()
        'if we are in debug mode, surface this property that consumers can query
        ClassDebugID = mlClassDebugID
    End Property
#End If

