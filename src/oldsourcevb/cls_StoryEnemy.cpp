VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cls_StoryEnemy"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'local variable(s) to hold property value(s)
Private mvarSpawned As Boolean 'local copy
Private mvarEnemyType As typeEnemyType
Private mvarPosX As Long
Private mvarPosY As Long
Private mvarSpeedX As Integer
Private mvarSpeedY As Integer
Private mvarMoveL As Boolean
Private mvarJump As Boolean
Private mvarState As BotState

Public Property Let PosX(ByVal vData As Long)
    mvarPosX = vData
End Property

Public Property Get PosX() As Long
    PosX = mvarPosX
End Property

Public Property Let PosY(ByVal vData As Long)
    mvarPosY = vData
End Property

Public Property Get PosY() As Long
    PosY = mvarPosY
End Property

Public Property Let EnemyType(ByVal vData As typeEnemyType)
    mvarEnemyType = vData
End Property

Public Property Get EnemyType() As typeEnemyType
    EnemyType = mvarEnemyType
End Property

Public Property Let Spawned(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.RecoilAmount = 5
    mvarSpawned = vData
End Property


Public Property Get Spawned() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.RecoilAmount
    Spawned = mvarSpawned
End Property

Private Sub Class_Initialize()

    Me.Spawned = True
    Me.EnemyType = Lurker
    Me.PosX = 0
    Me.PosY = 0

    
    
End Sub

Private Sub Class_Terminate()
    'the class is being destroyed
    
End Sub
