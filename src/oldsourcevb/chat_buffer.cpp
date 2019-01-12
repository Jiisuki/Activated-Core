struct ChatLine_Type{
  
}

struct ChatLine_Type ChatLine[24];
bool ChatPrompt;
char *ChatPromptText;
char ChatPromptCursor;
bool ShowChatSwitch;

int ChatFeed(char *chatString, char *chatAuthor){
  int i, j;
  for( i = 0; i < ChatLine_MaxLines - 2; i++ ){
    j = ChatLine_Maxlines - 2 - i;
    ChatLine[j+1].ChatText = ChatLine[j].ChatText;
  }
  if( strcmp(ChatAuthor, "") != 0 ){
    ChatLine[0].ChatText =

        If chatAuthor <> "" Then
            ChatLine(0).chatText = chatAuthor & ": " & chatString
        Else
            ChatLine(0).chatText = chatString
        End If
    
    ShowChatSwitch = True
    frmMain.tmr_ShowChat.ENABLED = True
    PlaySample "menu\click.mp3"

End Sub
