VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cls_ProjectileBase"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"


'local variable(s) to hold property value(s)
Private mvarCoorX As Single 'local copy
Private mvarCoorY As Single 'local copy
Private mvarActive As Boolean 'local copy
'local variable(s) to hold property value(s)
Private mvarXSpeed As Single  'local copy
Private mvarYSpeed As Single  'local copy
Private mvarTrailAngle As Single
Private mvarPCol As Long
'local variable(s) to hold property value(s)
Private mvarTimeLeft As Integer 'local copy
Private mvarAnimation As ProjAnims
Private mvarAnimationFrame As Integer
Private mvarCountdown As Integer

Public Property Let Countdown(ByVal vData As Integer)
    mvarCountdown = vData
End Property
Public Property Get Countdown() As Integer
    Countdown = mvarCountdown
End Property

Public Property Let Animation(ByVal vData As ProjAnims)
    mvarAnimation = vData
End Property
Public Property Get Animation() As ProjAnims
    Animation = mvarAnimation
End Property

Public Property Let AnimationFrame(ByVal vData As Integer)
    mvarAnimationFrame = vData
End Property
Public Property Get AnimationFrame() As Integer
    AnimationFrame = mvarAnimationFrame
End Property

Public Property Let TimeLeft(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.TimeLeft = 5
    mvarTimeLeft = vData
End Property

Public Sub Blow()

    Me.Active = False

End Sub

Public Property Get TimeLeft() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.TimeLeft
    TimeLeft = mvarTimeLeft
End Property

Public Property Let ProjectileColor(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.YSpeed = 5
    mvarPCol = vData
End Property


Public Property Get ProjectileColor() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.YSpeed
    ProjectileColor = mvarPCol
End Property

Public Property Let TrailAngle(ByVal vData As Single)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.YSpeed = 5
    mvarTrailAngle = vData
End Property


Public Property Get TrailAngle() As Single
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.YSpeed
    TrailAngle = mvarTrailAngle
End Property

Public Property Let YSpeed(ByVal vData As Single)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.YSpeed = 5
    mvarYSpeed = vData
End Property


Public Property Get YSpeed() As Single
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.YSpeed
    YSpeed = mvarYSpeed
End Property



Public Property Let XSpeed(ByVal vData As Single)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.XSpeed = 5
    mvarXSpeed = vData
End Property


Public Property Get XSpeed() As Single
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.XSpeed
    XSpeed = mvarXSpeed
End Property



Public Property Let Active(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Active = 5
    mvarActive = vData
End Property


Public Property Get Active() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Active
    Active = mvarActive
End Property



Public Property Let CoorY(ByVal vData As Single)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.CoorY = 5
    mvarCoorY = vData
End Property


Public Property Get CoorY() As Single
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.CoorY
    CoorY = mvarCoorY
End Property



Public Property Let CoorX(ByVal vData As Single)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.CoorX = 5
    mvarCoorX = vData
End Property


Public Property Get CoorX() As Single
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.CoorX
    CoorX = mvarCoorX
End Property



