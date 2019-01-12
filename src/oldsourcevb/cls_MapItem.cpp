VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cls_MapItem"
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
Private mvarID As String 'local copy
Private mvarFlag1 As Long 'local copy
Private mvarFlag2 As String 'local copy
Private mvarFlag3 As String 'local copy
Private mvarSpawned As Boolean 'local copy
Private mvarSpawntime As Integer 'local copy
Private mvarAnimationFrame As Integer 'local copy
Private mvarX As Long 'local copy
Private mvarY As Long 'local copy
Private mvarRect As RECT
'local variable(s) to hold property value(s)
Private mvarSpawntimeCurrent As Integer 'local copy
Public Property Let SpawntimeCurrent(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.SpawntimeCurrent = 5
    mvarSpawntimeCurrent = vData
End Property


Public Property Get SpawntimeCurrent() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.SpawntimeCurrent
    SpawntimeCurrent = mvarSpawntimeCurrent
End Property

Public Property Let Rectangle(vData As RECT)
    mvarRect = vData
End Property

Public Property Get Rectangle() As RECT
    Rectangle = mvarRect
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



Public Property Let Spawntime(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Spawntime = 5
    mvarSpawntime = vData
End Property


Public Property Get Spawntime() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Spawntime
    Spawntime = mvarSpawntime
End Property



Public Property Let Spawned(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Spawned = 5
    mvarSpawned = vData
End Property


Public Property Get Spawned() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Spawned
    Spawned = mvarSpawned
End Property



Public Property Let Flag3(ByVal vData As String)
Attribute Flag3.VB_Description = "Whatever.."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Flag3 = 5
    mvarFlag3 = vData
End Property


Public Property Get Flag3() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Flag3
    Flag3 = mvarFlag3
End Property



Public Property Let Flag2(ByVal vData As String)
Attribute Flag2.VB_Description = "Message.."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Flag2 = 5
    mvarFlag2 = vData
End Property


Public Property Get Flag2() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Flag2
    Flag2 = mvarFlag2
End Property



Public Property Let Flag1(ByVal vData As Long)
Attribute Flag1.VB_Description = "Amount of Armour, Health etc."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Flag1 = 5
    mvarFlag1 = vData
End Property


Public Property Get Flag1() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Flag1
    Flag1 = mvarFlag1
End Property



Public Property Let ID(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ID = 5
    mvarID = vData
End Property


Public Property Get ID() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ID
    ID = mvarID
End Property


Private Sub Class_Initialize()
    #If DebugMode Then
        'get the next available class ID, and print out
        'that the class was created successfully
        If EngineLogEnabled Then WriteEngineLOG LOGFILE, "'" & TypeName(Me) & "' instance " & mlClassDebugID & " created"
    #End If
End Sub


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

