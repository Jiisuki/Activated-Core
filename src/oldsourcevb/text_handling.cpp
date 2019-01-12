Attribute VB_Name = "mod_Texthandling"
Private CharXCord As Long
Private CharYCord As Long
Private rChar As RECT
Private tX As Long
Private tY As Long

Public SelectedCharmap As Integer

Public BITFONTS As Boolean

Public Sub DrawText(Txt As String, X As Single, Y As Single, Optional ByVal tMod As Integer = 0, Optional CharmapOverride As Integer = 1)

If Txt = "" Then Exit Sub

If SelectedCharmap < LBound(DDS_Charmap) Or SelectedCharmap > UBound(DDS_Charmap) Then
    SelectedCharmap = LBound(DDS_Charmap)
End If

If CharmapOverride < LBound(DDS_Charmap) Or CharmapOverride > UBound(DDS_Charmap) Then
    CharmapOverride = LBound(DDS_Charmap)
End If
    
    For i = 0 To Len(Txt)
        GetChar Mid(Txt, i + 1, 1)
        If Mid(Txt, i + 1, 1) <> " " Then
            If tMod = 0 Then
                DDS_Back.BltFast (X + (i * 8)), Y, DDS_Charmap(CharmapOverride), rChar, DDBLTFAST_SRCCOLORKEY
            Else
                DDS_ConsoleBuffer.BltFast (X + (i * 8)), Y, DDS_Charmap(CharmapOverride), rChar, DDBLTFAST_SRCCOLORKEY
            End If
        End If
        
        DoEvents
        
    Next i
        
End Sub

Private Sub GetChar(InputChar As String)

  Select Case InputChar
    Case "!": tX = 1: tY = 2
    Case "#": tX = 3: tY = 2
    Case "$": tX = 4: tY = 2
    Case "%": tX = 5: tY = 2
    Case "&": tX = 6: tY = 2
    Case "'": tX = 7: tY = 2
    Case "(": tX = 8: tY = 2
    Case ")": tX = 9: tY = 2
    Case "*": tX = 10: tY = 2
    Case "+": tX = 11: tY = 2
    Case ",": tX = 12: tY = 2
    Case "-": tX = 13: tY = 2
    Case ".": tX = 14: tY = 2
    Case "/": tX = 15: tY = 2
    Case "0": tX = 0: tY = 3
    Case "1": tX = 1: tY = 3
    Case "2": tX = 2: tY = 3
    Case "3": tX = 3: tY = 3
    Case "4": tX = 4: tY = 3
    Case "5": tX = 5: tY = 3
    Case "6": tX = 6: tY = 3
    Case "7": tX = 7: tY = 3
    Case "8": tX = 8: tY = 3
    Case "9": tX = 9: tY = 3
    Case ":": tX = 10: tY = 3
    Case ";": tX = 11: tY = 3
    Case "<": tX = 12: tY = 3
    Case "=": tX = 13: tY = 3
    Case ">": tX = 14: tY = 3
    Case "?": tX = 15: tY = 3
    Case "@": tX = 0: tY = 4
    Case "A": tX = 1: tY = 4
    Case "B": tX = 2: tY = 4
    Case "C": tX = 3: tY = 4
    Case "D": tX = 4: tY = 4
    Case "E": tX = 5: tY = 4
    Case "F": tX = 6: tY = 4
    Case "G": tX = 7: tY = 4
    Case "H": tX = 8: tY = 4
    Case "I": tX = 9: tY = 4
    Case "J": tX = 10: tY = 4
    Case "K": tX = 11: tY = 4
    Case "L": tX = 12: tY = 4
    Case "M": tX = 13: tY = 4
    Case "N": tX = 14: tY = 4
    Case "O": tX = 15: tY = 4
    Case "P": tX = 0: tY = 5
    Case "Q": tX = 1: tY = 5
    Case "R": tX = 2: tY = 5
    Case "S": tX = 3: tY = 5
    Case "T": tX = 4: tY = 5
    Case "U": tX = 5: tY = 5
    Case "V": tX = 6: tY = 5
    Case "W": tX = 7: tY = 5
    Case "X": tX = 8: tY = 5
    Case "Y": tX = 9: tY = 5
    Case "Z": tX = 10: tY = 5
    Case "[": tX = 11: tY = 5
    Case "\": tX = 12: tY = 5
    Case "]": tX = 13: tY = 5
    Case "^": tX = 14: tY = 5
    Case "_": tX = 15: tY = 5
    Case "`": tX = 0: tY = 6
    Case "a": tX = 1: tY = 6
    Case "b": tX = 2: tY = 6
    Case "c": tX = 3: tY = 6
    Case "d": tX = 4: tY = 6
    Case "e": tX = 5: tY = 6
    Case "f": tX = 6: tY = 6
    Case "g": tX = 7: tY = 6
    Case "h": tX = 8: tY = 6
    Case "i": tX = 9: tY = 6
    Case "j": tX = 10: tY = 6
    Case "k": tX = 11: tY = 6
    Case "l": tX = 12: tY = 6
    Case "m": tX = 13: tY = 6
    Case "n": tX = 14: tY = 6
    Case "o": tX = 15: tY = 6
    Case "p": tX = 0: tY = 7
    Case "q": tX = 1: tY = 7
    Case "r": tX = 2: tY = 7
    Case "s": tX = 3: tY = 7
    Case "t": tX = 4: tY = 7
    Case "u": tX = 5: tY = 7
    Case "v": tX = 6: tY = 7
    Case "w": tX = 7: tY = 7
    Case "x": tX = 8: tY = 7
    Case "y": tX = 9: tY = 7
    Case "z": tX = 10: tY = 7
    Case "{": tX = 11: tY = 7
    Case "|": tX = 12: tY = 7
    Case "}": tX = 13: tY = 7
    Case "~": tX = 14: tY = 7
    Case Else: tX = 0: tY = 2
  End Select
  
  rChar.Left = tX * 8
  rChar.Right = rChar.Left + 8
  rChar.Top = tY * 8
  rChar.Bottom = rChar.Top + 8
    
End Sub
