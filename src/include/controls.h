
/* Control Settings */
#define CTRL_KEY_UP                     0
#define CTRL_KEY_DOWN                   1
#define CTRL_KEY_LEFT                   2
#define CTRL_KEY_RIGHT                  3
#define CTRL_KEY_JETPAK                 4
#define CTRL_KEY_SWITCH_WEAPON          5
#define CTRL_KEY_ACTION_1               6
#define CTRL_KEY_ACTION_2               7
#define CTRL_KEY_CONFIRM_OPTION         8
#define CTRL_KEY_TEMPORARY_DEBUG_USAGE  9
#define CTRL_KEY_ESCAPE                 10
#define CTRL_KEY_INC_EQ 11
#define CTRL_KEY_DEC_EQ 12
#define CTRL_NUM_OF_CONTROL_KEYS       11

class cls_Ctrl{
private:
  unsigned char ControlKey[CTRL_NUM_OF_CONTROL_KEYS];
  char StrK[16];
  char BoundStr[64];
public:
  cls_Ctrl();
  const char *GetKeyFcnDescription(int KeyFunc);
  unsigned char GetBoundKey(int KeyFunc);
  const char *GetBoundKeyName(unsigned char Key);
  void CheckBinds();
  int BindKey(int KeyFunc, unsigned char Key);
  const char *GetBoundString(int KeyFunc);
};

cls_Ctrl::cls_Ctrl(){
  ControlKey[CTRL_KEY_UP]       = 119; // w
  ControlKey[CTRL_KEY_DOWN]     = 115; // s
  ControlKey[CTRL_KEY_LEFT]     =  97; // a
  ControlKey[CTRL_KEY_RIGHT]    = 100; // d
  ControlKey[CTRL_KEY_JETPAK]   = 112; // p
  ControlKey[CTRL_KEY_SWITCH_WEAPON] = 32; // space
  ControlKey[CTRL_KEY_ACTION_1] = 107; // k
  ControlKey[CTRL_KEY_ACTION_2] = 108; // l
  ControlKey[CTRL_KEY_TEMPORARY_DEBUG_USAGE]    = 103; // g
  ControlKey[CTRL_KEY_CONFIRM_OPTION]  =  13; // return
  ControlKey[CTRL_KEY_ESCAPE] = 27;
}

const char *cls_Ctrl::GetBoundString(int KeyFunc){
  sprintf(BoundStr,"%s : %s",GetKeyFcnDescription(KeyFunc),GetBoundKeyName(ControlKey[KeyFunc]));
  return BoundStr;
}

int cls_Ctrl::BindKey(int KeyFunc, unsigned char Key){
  if( KeyFunc < 0 || KeyFunc > CTRL_NUM_OF_CONTROL_KEYS )
    return 1;
  if( Key < 0 || Key > 255 )
    return 1;
  ControlKey[KeyFunc] = Key;
  return 0;
}

unsigned char cls_Ctrl::GetBoundKey(int KeyFunc){
  if( KeyFunc < 0 || KeyFunc >= CTRL_NUM_OF_CONTROL_KEYS )
    return 0;
  return ControlKey[KeyFunc];
}

const char *cls_Ctrl::GetKeyFcnDescription(int KeyFunc){
  if( KeyFunc == CTRL_KEY_UP )
    return "Up      ";
  if( KeyFunc == CTRL_KEY_DOWN )
    return "Down    ";
  if( KeyFunc == CTRL_KEY_LEFT )
    return "Left    ";
  if( KeyFunc == CTRL_KEY_RIGHT )
    return "Right   ";
  if( KeyFunc == CTRL_KEY_JETPAK )
    return "Jetpack ";
  if( KeyFunc == CTRL_KEY_SWITCH_WEAPON )
    return "Weapon  ";
  if( KeyFunc == CTRL_KEY_ACTION_1 )
    return "Action 1";
  if( KeyFunc == CTRL_KEY_ACTION_2 )
    return "Action 2";
  if( KeyFunc == CTRL_KEY_CONFIRM_OPTION )
    return "Confirm ";
  if( KeyFunc == CTRL_KEY_TEMPORARY_DEBUG_USAGE )
    return "Debug   ";
  if( KeyFunc == CTRL_KEY_ESCAPE )
    return "Quit    ";
  
  return "Not a Valid Function!";
}
void cls_Ctrl::CheckBinds(){
  int i;
//  printf("Displaying Control Bind Table:\n");
  for( i = 0; i < CTRL_NUM_OF_CONTROL_KEYS; i++ ){
    printf("Action '%s' is bound to %s\n",GetKeyFcnDescription(i),GetBoundKeyName(ControlKey[i]));
  }
}
const char *cls_Ctrl::GetBoundKeyName(unsigned char Key){
  
  if( isalnum(Key) ){
    memset(StrK,'\0',16);
    sprintf(StrK,"%c     ",toupper(Key));
    return StrK;
  } else {
    
    switch( Key ){
      case 13:
        return "Return";
      case 27:
        return "Escape";
      case 32:
        return "Space ";
      default:
        return "Inval ";
    }
  }
}








cls_Ctrl Control;



