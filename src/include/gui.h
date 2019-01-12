

#define CONSOLE_NUMBER_OF_LINES 14
#define CONSOLE_LINE_WIDTH      128

class cls_GUI {
private:
  int i;
  struct StructOSDM{
    char  Message[64];
    bool  Show;
    float Time;
    int   ShowTime;
  }OSDM;
  struct StructConsole{
    char Console_Text[CONSOLE_LINE_WIDTH];
    bool SystemLine;
  }Console[CONSOLE_NUMBER_OF_LINES];
  char CurrentConsoleCommand[CONSOLE_LINE_WIDTH];
public:
  void OSDMessage(const char *String, int ShowTime){
    memset(OSDM.Message,'\0',64);
    strcpy(OSDM.Message,String);
    OSDM.Time = 0;
    OSDM.Show = 1;
    OSDM.ShowTime = ShowTime;
  }
  const char *ReadOSDMessage(){
    if( OSDM.Show ){
      OSDM.Time+=0.01;
      if( OSDM.Time > OSDM.ShowTime ){
        OSDM.Show = 0;
        OSDM.Time = 0;
        return "";
      }
      return OSDM.Message;
    } else {
      return "";
    }
  }
  void AddConsoleLine(const char *String, bool System){
    char tmp[CONSOLE_LINE_WIDTH] = {0};
    int i;
    for( i = 0; i < CONSOLE_NUMBER_OF_LINES-1; i++ ){
      memset(tmp,'\0',CONSOLE_LINE_WIDTH);
      memset(Console[i].Console_Text,'\0',CONSOLE_LINE_WIDTH);
      strcpy(tmp, Console[i+1].Console_Text);
      strncpy(Console[i].Console_Text, tmp, CONSOLE_LINE_WIDTH);
      Console[i].SystemLine = Console[i+1].SystemLine;
    }
    strncpy(Console[CONSOLE_NUMBER_OF_LINES-1].Console_Text, String, CONSOLE_LINE_WIDTH);
    Console[CONSOLE_NUMBER_OF_LINES-1].SystemLine = System;
    memset(CurrentConsoleCommand,'\0',CONSOLE_LINE_WIDTH);
  }
  void ClearConsole(){
    int i;
    for( i = 0; i < CONSOLE_NUMBER_OF_LINES; i++ ){
      memset(Console[i].Console_Text,'\0',CONSOLE_LINE_WIDTH);
      Console[i].SystemLine = 0;
    }
    memset(CurrentConsoleCommand,'\0',CONSOLE_LINE_WIDTH);
  }
  const char *GetConsoleLine(int Line){
    return Console[Line].Console_Text;
  }
  int IsConsoleLineSystem(int Line){
    return Console[Line].SystemLine;
  }
  void SetCurrentConsoleCommand(const char *String){
    memset(CurrentConsoleCommand,'\0',CONSOLE_LINE_WIDTH);
    strcpy(CurrentConsoleCommand,String);
  }
  const char *GetCurrentConsoleCommand(){
    return CurrentConsoleCommand;
  }
};

cls_GUI GUI;