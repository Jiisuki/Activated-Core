



#define MENU_INTRO 0
#define MENU_MAIN  1
#define MENU_LOADING_MAP 2
#define MENU_SETTINGS_MAIN 3
#define MENU_INSTRUCTIONS 4
#define MENU_SETTINGS_CONTROLS 5
#define MENU_SETTINGS_CHECK_BINDS 6
#define MENU_SETTINGS_SET_BINDS 7
#define MENU_SETTINGS_SFX 8
#define MENU_SETTINGS_GFX 9
#define MENU_SELECT_LEVEL 10
#define MENU_START_LEVEL 11
#define MENU_SETUP_GAME 12

#define MENU_NUM_MENUS 13

class cls_MenuSubItem{
private:
  char ItemName[32];
public:
  const char *GetItemName();
  void SetItemName(const char *Name);
};

const char *cls_MenuSubItem::GetItemName(){
  return ItemName;
}
void cls_MenuSubItem::SetItemName(const char* Name){
  strcpy(ItemName, Name);
}

class cls_MenuScreen{
private:
  int NumItems;
  char MenuName[32];
  char OptionalInfo[64];
  cls_MenuSubItem *SubItem;
public:
  cls_MenuScreen(const char *Name, int NumSubItems);
  ~cls_MenuScreen();
  const char *GetMenuName();
  void SetMenuName(const char *Name);
  const char *GetItemName(int Item);
  void SetItemName(int Item, const char *Name);
  int GetNumItems();
  const char *GetOptionalInfo();
  void SetOptionalInfo(const char *String);
};

cls_MenuScreen::cls_MenuScreen(const char *Name, int NumSubItems){
  strcpy(MenuName, Name);
  memset(OptionalInfo,'\0',32);
  NumItems = NumSubItems;
  if( NumSubItems > 0 ){
    SubItem = (cls_MenuSubItem*) malloc( sizeof(cls_MenuSubItem)*NumSubItems );
    if( SubItem == NULL ) {
      printf("ERROR allocating memory for menu sub item!\n");
    }
  }
}
cls_MenuScreen::~cls_MenuScreen(){
  free( SubItem );
}
const char *cls_MenuScreen::GetMenuName(){
  return MenuName;
}
void cls_MenuScreen::SetMenuName(const char* Name){
  strcpy(MenuName, Name);
}
const char *cls_MenuScreen::GetItemName(int Item){
  return SubItem[Item].GetItemName();
}
void cls_MenuScreen::SetItemName(int Item, const char* Name){
  SubItem[Item].SetItemName(Name);
}
int cls_MenuScreen::GetNumItems(){
  return NumItems;
}
const char *cls_MenuScreen::GetOptionalInfo(){
  return OptionalInfo;
}
void cls_MenuScreen::SetOptionalInfo(const char *String){
  strcpy(OptionalInfo,String);
}



class cls_Menu{
private:
  int MenuSelection;
  int ItemSelection;
  cls_MenuScreen *Screen[MENU_NUM_MENUS];
public:
  char welc[32];
  int lenwelc;
  int scrm[32];
  int decode;
  unsigned int InfoDelay;
  unsigned int InfoDelayStop;
  bool ShowInfo;
  cls_Menu();
  ~cls_Menu();
  void SetMenuSelection(int NewSelection);
  void SetItemSelection(int NewSelection);
  void SetItemString(int Item, const char *String);
  int GetNumItems();
  const char *GetFreeItemName(int Item);
  int GetMenu();
  int GetItem();
  const char *GetMenuName();
  const char *GetItemName(int UML);
  void MenuUp();
  void MenuDown();
  const char *GetOptinalInfo();
  void SetOptionalText(const char *String);
  bool IsSelected(int Item);
};

void cls_Menu::MenuUp(){
  ItemSelection--;
  if( ItemSelection < 0 )
    ItemSelection = 0;
}
void cls_Menu::MenuDown(){
  ItemSelection++;
  if( ItemSelection >= Screen[MenuSelection]->GetNumItems()-1 )
    ItemSelection = Screen[MenuSelection]->GetNumItems()-1;
}

cls_Menu::cls_Menu(){
  memset(welc, '\0', 32);
  memset(scrm, 0, 32);
  lenwelc = 0;
  decode = 0;

  ShowInfo = 0;
  InfoDelay = 0;
  InfoDelayStop = 3;
  
  MenuSelection = 1;

  Screen[MENU_INTRO] = new cls_MenuScreen("Introduction",1);
  Screen[MENU_INTRO]->SetItemName(0,"");

  Screen[MENU_MAIN] = new cls_MenuScreen("Title Menu",5);
  Screen[MENU_MAIN]->SetItemName(0,"Start New Game");
  Screen[MENU_MAIN]->SetItemName(1,"Editor");
  Screen[MENU_MAIN]->SetItemName(2,"Settings");
  Screen[MENU_MAIN]->SetItemName(3,"Instructions");
  Screen[MENU_MAIN]->SetItemName(4,"Quit");

  Screen[MENU_LOADING_MAP] = new cls_MenuScreen("Loading Map",1);
  Screen[MENU_LOADING_MAP]->SetOptionalInfo("Loading Map");
  Screen[MENU_LOADING_MAP]->SetItemName(0,"Name");
  
  Screen[MENU_SETTINGS_MAIN] = new cls_MenuScreen("Settings",3);
  Screen[MENU_SETTINGS_MAIN]->SetItemName(0,"Set Controls");
  Screen[MENU_SETTINGS_MAIN]->SetItemName(1,"Sound and Music");
  Screen[MENU_SETTINGS_MAIN]->SetItemName(2,"Graphics");

  Screen[MENU_INSTRUCTIONS] = new cls_MenuScreen("Instructions",0);

  Screen[MENU_SETTINGS_CONTROLS] = new cls_MenuScreen("Set Controls",2);
  Screen[MENU_SETTINGS_CONTROLS]->SetItemName(0,"Check Current Binds");
  Screen[MENU_SETTINGS_CONTROLS]->SetItemName(1,"Set Control Bindings");

  Screen[MENU_SETTINGS_CHECK_BINDS] = new cls_MenuScreen("Check Current Binds",1);
  Screen[MENU_SETTINGS_CHECK_BINDS]->SetItemName(0,"Check Current Binds");
  
  Screen[MENU_SETTINGS_SET_BINDS] = new cls_MenuScreen("Bind Keys",CTRL_NUM_OF_CONTROL_KEYS-1); //10-1
  int i;
  for( i = 0; i < CTRL_NUM_OF_CONTROL_KEYS-1; i++ ){ // - 1 to get rid of needed escape! (no rebind)
    Screen[MENU_SETTINGS_SET_BINDS]->SetItemName(i,Control.GetKeyFcnDescription(i));
  }

  Screen[MENU_SETTINGS_SFX] = new cls_MenuScreen("Preview Music",1);
  Screen[MENU_SETTINGS_SFX]->SetOptionalInfo("Select With A or D");
  Screen[MENU_SETTINGS_SFX]->SetItemName(0,"Preview Music");

  Screen[MENU_SETTINGS_GFX] = new cls_MenuScreen("Graphics Options",3);
  Screen[MENU_SETTINGS_GFX]->SetOptionalInfo("Requires Restart!");
  Screen[MENU_SETTINGS_GFX]->SetItemName(0,"Fullscreen");
  Screen[MENU_SETTINGS_GFX]->SetItemName(1,"Resolution");
  Screen[MENU_SETTINGS_GFX]->SetItemName(2,"Aspect Ratio");

  Screen[MENU_SELECT_LEVEL] = new cls_MenuScreen("Open Level",8);
  Screen[MENU_SELECT_LEVEL]->SetOptionalInfo("Please Select Level");
  Screen[MENU_SELECT_LEVEL]->SetItemName(0,"Base Station");
  Screen[MENU_SELECT_LEVEL]->SetItemName(1,"Headquarters");
  Screen[MENU_SELECT_LEVEL]->SetItemName(2,"Laboratory");
  Screen[MENU_SELECT_LEVEL]->SetItemName(3,"Weapon Factory");
  Screen[MENU_SELECT_LEVEL]->SetItemName(4,"Unknown Territory");
  Screen[MENU_SELECT_LEVEL]->SetItemName(5,"Custom 01");
  Screen[MENU_SELECT_LEVEL]->SetItemName(6,"Custom 02");
  Screen[MENU_SELECT_LEVEL]->SetItemName(7,"Custom 03");

  Screen[MENU_START_LEVEL] = new cls_MenuScreen("Open Level",8);
  Screen[MENU_START_LEVEL]->SetOptionalInfo("Please Select Level");
  Screen[MENU_START_LEVEL]->SetItemName(0,"Base Station");
  Screen[MENU_START_LEVEL]->SetItemName(1,"Headquarters");
  Screen[MENU_START_LEVEL]->SetItemName(2,"Laboratory");
  Screen[MENU_START_LEVEL]->SetItemName(3,"Weapon Factory");
  Screen[MENU_START_LEVEL]->SetItemName(4,"Unknown Territory");
  Screen[MENU_START_LEVEL]->SetItemName(5,"Custom 01");
  Screen[MENU_START_LEVEL]->SetItemName(6,"Custom 02");
  Screen[MENU_START_LEVEL]->SetItemName(7,"Custom 03");
  
  Screen[MENU_SETUP_GAME] = new cls_MenuScreen("Setup Game",5);
  Screen[MENU_SETUP_GAME]->SetItemName(0,"Players:");
  Screen[MENU_SETUP_GAME]->SetItemName(1,"Mode:");
  Screen[MENU_SETUP_GAME]->SetItemName(2,"Score Limit:");
  Screen[MENU_SETUP_GAME]->SetItemName(3,"Time Limit:");
  Screen[MENU_SETUP_GAME]->SetItemName(4,"Select Map");
}
cls_Menu::~cls_Menu(){
  int i;
  for( i = 0; i < MENU_NUM_MENUS; i++ ){
    free(Screen[i]);
    printf("Deleted Screen %i\n",i);
  }
}
void cls_Menu::SetItemString(int Item, const char* String){
  Screen[MenuSelection]->SetItemName(Item, String);
}
void cls_Menu::SetMenuSelection(int NewSelection){
  if( NewSelection < 0 )
    return;
  if( NewSelection >= MENU_NUM_MENUS )
    return;
  ItemSelection = 0;
  MenuSelection = NewSelection;
  printf("Current Menu: %s\n",GetMenuName());
}
void cls_Menu::SetItemSelection(int NewSelection){
  if( NewSelection < 0 )
    return;
  if( NewSelection >= Screen[MenuSelection]->GetNumItems() )
    return;
  ItemSelection = NewSelection;
}
int cls_Menu::GetMenu(){
  return MenuSelection;
}
int cls_Menu::GetItem(){
  return ItemSelection;
}
const char *cls_Menu::GetMenuName(){
  return Screen[MenuSelection]->GetMenuName();
}
const char *cls_Menu::GetItemName(int UML){
  if( UML == 1 ){ //Upper
    if( ItemSelection <= 0 )
      return "";
    return Screen[MenuSelection]->GetItemName(ItemSelection-1);
  } else if( UML == 2 ){ //Lower
    if( ItemSelection >= Screen[MenuSelection]->GetNumItems()-1 )
      return "";
    return Screen[MenuSelection]->GetItemName(ItemSelection+1);
  }
  return Screen[MenuSelection]->GetItemName(ItemSelection);
}
const char *cls_Menu::GetOptinalInfo(){
  return Screen[MenuSelection]->GetOptionalInfo();
}
void cls_Menu::SetOptionalText(const char* String){
  Screen[MenuSelection]->SetOptionalInfo(String);
}
int cls_Menu::GetNumItems(){
  return Screen[MenuSelection]->GetNumItems();
}
const char *cls_Menu::GetFreeItemName(int Item){
  return Screen[MenuSelection]->GetItemName(Item);
}
bool cls_Menu::IsSelected(int Item){
  if( Item == ItemSelection )
    return 1;
  return 0;
}

cls_Menu Menu;











