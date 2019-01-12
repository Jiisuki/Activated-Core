Attribute VB_Name = "mod_Credits"
Public Type CreditText
    Crd_TEXT As String
    Crd_YPos As Long
    Crd_Font As Integer
    Crd_Color As Long
End Type
Public Crd_Line(128 - 1) As CreditText

Public LastCreditLine As Integer
Private LastHold As Long
Private LastHoldMax As Long
Private tmpNull As Boolean
Public tmpFire As Boolean

Public bTile As Integer

Public Sub Credits_INIT()
Dim i As Integer
LastHold = 0
LastHoldMax = 2000
tmpNull = False
tmpFire = False



    i = 0
    Crd_Line(i).Crd_TEXT = "CREDITS"
    Crd_Line(i).Crd_Font = 2            'HeaderMain
    Crd_Line(i).Crd_YPos = 300          'Init pos
    Crd_Line(i).Crd_Color = 0
        
        
                            
              
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "ORIGINAL GAMEPLAY CONCEPT"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
        

        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre 'Jiisuki' Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Smeghead"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 10
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "J1mb0"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 10
    Crd_Line(i).Crd_Color = 0
        
        
        
            i = i + 1
    Crd_Line(i).Crd_TEXT = "STORY"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "MENU DESIGN"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
        

        

    i = i + 1
    Crd_Line(i).Crd_TEXT = "INTRO and CREDITS"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
    
    i = i + 1
    Crd_Line(i).Crd_TEXT = "PROGRAMMING"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
    
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "SOUND ENGINE"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "FMOD"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "(www.fmod.org)"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "MAPPING"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
              
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
    
    i = i + 1
    Crd_Line(i).Crd_TEXT = "ORIGINAL SOUNDTRACK"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
        
        i = i + 1
    Crd_Line(i).Crd_TEXT = "SOUND EFFECTS"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
    
    i = i + 1
    Crd_Line(i).Crd_TEXT = "GRAPHICS"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
    
    i = i + 1
    Crd_Line(i).Crd_TEXT = "Andre Lundkvist"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "SPECIAL THANKS"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "old eb3k team"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "for all the effort and dedication"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 10
    Crd_Line(i).Crd_Color = 0
        
        
                
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "thanks to everyone enjoying"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 24
    Crd_Line(i).Crd_Color = 0
        
        
        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "and supporting my work"
    Crd_Line(i).Crd_Font = 1
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 10
    Crd_Line(i).Crd_Color = 0
        
        
        
        
        

    
                        
    i = i + 1
    Crd_Line(i).Crd_TEXT = "THANK YOU FOR PLAYING!"
    Crd_Line(i).Crd_Font = 0
    Crd_Line(i).Crd_YPos = Crd_Line(i - 1).Crd_YPos + 180
    Crd_Line(i).Crd_Color = 0
        
        
    
    i = i + 1


        
    LastCreditLine = i
        
    If EngineLogEnabled Then WriteEngineLOG LOGFILE, UCase("creditlines '" & CStr(i) & "'")
            
End Sub

Public Sub DrawCredit()
    
CreditPosUpdate
    
Dim i As Integer
    
    For i = 0 To UBound(Crd_Line)
    
        If Crd_Line(i).Crd_YPos > 0 And Crd_Line(i).Crd_YPos < 480 Then
        
            DDS_Back.SetForeColor Crd_Line(i).Crd_Color
        
            If Crd_Line(i).Crd_Font = 0 Then
                DDS_Back.SetFont frmMain.mnuFont.Font
                DDS_Back.DrawText (160 - Int((Len(Crd_Line(i).Crd_TEXT) * 9) / 2)), Crd_Line(i).Crd_YPos, UCase(Crd_Line(i).Crd_TEXT), False
            ElseIf Crd_Line(i).Crd_Font = 2 Then
                DDS_Back.SetFont frmMain.mnuFont.Font
                DDS_Back.DrawText (160 - Int((Len(Crd_Line(i).Crd_TEXT) * 9) / 2)), Crd_Line(i).Crd_YPos, UCase(Crd_Line(i).Crd_TEXT), False
            Else
                DDS_Back.SetFont frmMain.Font
                DDS_Back.DrawText (160 - Int((Len(Crd_Line(i).Crd_TEXT) * 4) / 2)), Crd_Line(i).Crd_YPos, UCase(Crd_Line(i).Crd_TEXT), False
            End If
        End If
    
        DoEvents
    
    Next i
    
    ReverseFlag = False
    
    If tmpNull = False Then
        AnimateCharacter True
        UpdateBTile
    ElseIf tmpNull = True And tmpFire <> True Then
        AnimateCharacter True, True
    Else
        CHARACTER.Animation = STANDING
        CHARACTER.ANIMATIONNUM = 0
    End If
    
    Dim tB As RECT, tB2 As RECT
    tB.Left = 96 + bTile
    tB.Right = tB.Left + 32
    tB.Top = 352
    tB.Bottom = tB.Top + 32
    
    tB2.Left = bTile
    tB2.Right = bTile + 32
    tB2.Top = 352
    tB2.Bottom = tB2.Top + 32
    
    For i = 0 To 10
        DDS_Back.BltFast i * 32, 240 - 32, DDS_MAPTILES, tB, DDBLTFAST_SRCCOLORKEY
    Next i
    
    Dim r3 As RECT, r4 As RECT
    
    r3.Bottom = 240 - 32
    r3.Top = r3.Bottom - 32
    r3.Left = 32
    r3.Right = r3.Left + 32

    r4.Top = CHARACTER.Animation * 32
    r4.Bottom = r4.Top + 32
    r4.Left = CHARACTER.ANIMATIONNUM * 32
    r4.Right = r4.Left + 32
    
    DDS_Back.Blt r3, DDS_Character1, r4, DDBLT_KEYSRC
    
    For i = 0 To 10
        DDS_Back.BltFast i * 32, 240 - 64, DDS_MAPTILES, tB2, DDBLTFAST_SRCCOLORKEY
    Next i
    
End Sub



Public Sub UpdateBTile()

lTickCount4 = GetTickCount()
    
If (lTickCount4 - lOldTickCount4) > 35 Then
    lOldTickCount4 = GetTickCount

    If MENU.VisibleMenu = MNUCredits Then
        bTile = bTile + 2
        If bTile >= 32 Then bTile = 0
    End If
    
End If

End Sub
    
Public Sub CreditPosUpdate()

lTickCount6 = GetTickCount()
    
    If (lTickCount6 - lOldTickCount6) > 45 Then
        lOldTickCount6 = GetTickCount
        
        For i = 0 To UBound(Crd_Line)
            Crd_Line(i).Crd_YPos = Crd_Line(i).Crd_YPos - 1
            If Crd_Line(i).Crd_Font <> 2 Then
                If Crd_Line(i).Crd_YPos < 230 And Crd_Line(i).Crd_YPos > 120 Then
                    Crd_Line(i).Crd_Color = Crd_Line(i).Crd_Color + RGB(2, 2, 2)
                    If Crd_Line(i).Crd_Color > RGB(255, 255, 255) Then Crd_Line(i).Crd_Color = RGB(255, 255, 255)
                ElseIf Crd_Line(i).Crd_YPos < 140 Then
                    Crd_Line(i).Crd_Color = Crd_Line(i).Crd_Color - RGB(2, 2, 2)
                    If Crd_Line(i).Crd_Color < 0 Then Crd_Line(i).Crd_Color = 0
                End If
            Else
                If Crd_Line(i).Crd_YPos < 230 And Crd_Line(i).Crd_YPos > 120 Then
                    Crd_Line(i).Crd_Color = Crd_Line(i).Crd_Color + RGB(2, 2, 2)
                    If Crd_Line(i).Crd_Color > RGB(255, 255, 255) Then Crd_Line(i).Crd_Color = RGB(255, 255, 255)
                ElseIf Crd_Line(i).Crd_YPos < 140 Then
                    Crd_Line(i).Crd_Color = Crd_Line(i).Crd_Color - RGB(2, 2, 2)
                    If Crd_Line(i).Crd_Color < 0 Then Crd_Line(i).Crd_Color = 0
                End If
            End If
            
            DoEvents
            
        Next i
        
        If Crd_Line(LastCreditLine - 1).Crd_YPos <= 120 And Crd_Line(LastCreditLine - 1).Crd_Color > RGB(1, 1, 1) Then
            LastHold = LastHold + 1
            If LastHold >= LastHoldMax Then
                LastHold = LastHoldMax
                Crd_Line(LastCreditLine - 1).Crd_Color = Crd_Line(LastCre < ditLine - 1).Crd_Color - RGB(1, 1, 1)
            End If
            Crd_Line(LastCreditLine - 1).Crd_YPos = 120
        End If
        
        If Crd_Line(LastCreditLine - 1).Crd_YPos <= 140 Then
            If tmpNull <> True Then
                CHARACTER.ANIMATIONNUM = 0
                tmpNull = True
            End If
        End If
        
    End If
    
    If Crd_Line(LastCreditLine - 1).Crd_YPos < 0 Then Credits_INIT

End Sub

