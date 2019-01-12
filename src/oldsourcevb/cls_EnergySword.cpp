VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cls_EnergySword"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Description = "Basic: Energy Sword"
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
Private mvarGotWeapon As Boolean 'local copy
Private mvarColorMain As Long 'local copy
Private mvarColorSecondary As Long 'local copy
Private mvarAmmoMax As Long 'local copy
Private mvarAmmoInBackpack As Long 'local copy
Private mvarAmmoCurrent As Long 'local copy
Private mvarDamageMax As Integer 'local copy
Private mvarDamageMin As Integer 'local copy
Private mvarMsgPickup As String 'local copy
Private mvarRecoilAmount As Long 'local copy
Public Property Let RecoilAmount(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.RecoilAmount = 5
    mvarRecoilAmount = vData
End Property


Public Property Get RecoilAmount() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.RecoilAmount
    RecoilAmount = mvarRecoilAmount
End Property



Public Sub Reload()
End Sub

Public Sub Fire()
Attribute Fire.VB_Description = "Fire the gun!"
End Sub

Public Property Let MsgPickup(ByVal vData As String)
Attribute MsgPickup.VB_Description = "The message displayed when picking up from map."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MsgPickup = 5
    mvarMsgPickup = vData
End Property


Public Property Get MsgPickup() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.MsgPickup
    MsgPickup = mvarMsgPickup
End Property



Public Property Let DamageMin(ByVal vData As Integer)
Attribute DamageMin.VB_Description = "The minimum damage this weapon can do on impact."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.DamageMin = 5
    mvarDamageMin = vData
End Property


Public Property Get DamageMin() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.DamageMin
    DamageMin = mvarDamageMin
End Property



Public Property Let DamageMax(ByVal vData As Integer)
Attribute DamageMax.VB_Description = "The maximum damage this weapon can do on impact."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.DamageMax = 5
    mvarDamageMax = vData
End Property


Public Property Get DamageMax() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.DamageMax
    DamageMax = mvarDamageMax
End Property



Public Property Let AmmoCurrent(ByVal vData As Long)
Attribute AmmoCurrent.VB_Description = "The amount of ammo this weapon is currently carrying in mag."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.AmmoCurrent = 5
    mvarAmmoCurrent = vData
End Property


Public Property Get AmmoCurrent() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.AmmoCurrent
    AmmoCurrent = mvarAmmoCurrent
End Property



Public Property Let AmmoInBackpack(ByVal vData As Long)
Attribute AmmoInBackpack.VB_Description = "The amount of ammo you are carrying in backpack of this type."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.AmmoInBackpack = 5
    mvarAmmoInBackpack = vData
End Property


Public Property Get AmmoInBackpack() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.AmmoInBackpack
    AmmoInBackpack = mvarAmmoInBackpack
End Property



Public Property Let AMMOMAX(ByVal vData As Long)
Attribute AMMOMAX.VB_Description = "The maximum amount of ammo this weapon can carry in mag."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.AmmoMax = 5
    mvarAmmoMax = vData
End Property


Public Property Get AMMOMAX() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.AmmoMax
    AMMOMAX = mvarAmmoMax
End Property



Public Property Let ColorSecondary(ByVal vData As Long)
Attribute ColorSecondary.VB_Description = "The secondary color of the weapon."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ColorSecondary = 5
    mvarColorSecondary = vData
End Property


Public Property Get ColorSecondary() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.ColorSecondary
    ColorSecondary = mvarColorSecondary
End Property



Public Property Let ColorMain(ByVal vData As Long)
Attribute ColorMain.VB_Description = "The main color of the weapon."
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ColorMain = 5
    mvarColorMain = vData
End Property


Public Property Get ColorMain() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.ColorMain
    ColorMain = mvarColorMain
End Property



Public Property Let GotWeapon(ByVal vData As Boolean)
Attribute GotWeapon.VB_Description = "Have you got the weapon, or not?"
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.GotWeapon = 5
    mvarGotWeapon = vData
End Property


Public Property Get GotWeapon() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.GotWeapon
    GotWeapon = mvarGotWeapon
End Property

Public Property Get ClassDebugID() As Variant
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: if enginelogenabled then WriteEngineLOG LOGFILE,  X.ClassDebugID
    If IsObject(mvarClassDebugID) Then
        Set ClassDebugID = mvarClassDebugID
    Else
        ClassDebugID = mvarClassDebugID
    End If
End Property



Private Sub Class_Initialize()

    'Ammo
        Me.AMMOMAX = 0
        Me.AmmoCurrent = 0
        Me.AmmoInBackpack = 0
        Me.RecoilAmount = 64
        
    'Colors
        Me.ColorMain = RGB(255, 0, 0)
        Me.ColorSecondary = RGB(0, 255, 0)
    
    'Damage
        Me.DamageMax = 20
        Me.DamageMin = 10
        
    'Got Weapon Init
        Me.GotWeapon = True
        
    'Pickup Msg
        Me.MsgPickup = ""

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
