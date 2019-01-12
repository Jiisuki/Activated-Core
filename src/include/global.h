
#ifndef _GLOBAL_H
#define _GLOBAL_H



#define G_MODE_TRAINING         0 /* Definition for Game Mode = Training */
#define G_MODE_DEATHMATCH       1 /* Game Mode = Free For All Deathmatch */
#define G_MODE_TEAM_DEATHMATCH  2 /* Game Mode = Team Deathmatch         */
#define G_MODE_DUEL             3 /* Game Mode = Duel                    */
#define G_MODE_RACING           4
#define G_MODE_BUMPER           5
#define G_MODE_TAG              6
#define G_MODE_CAPTURE_THE_FLAG 7 
#define G_MODE_SINGLE_STORY     8 

#define LOOP_MAIN_MENU    0
#define LOOP_IN_GAME_MENU 1
#define LOOP_GAME         2
#define LOOP_EDITOR     3

#define LOOP_MAX 3
#define LOOP_MIN 0

#define HOLD_MIN 4000
#define HOLD_MAX 80000

#define LIM_F 0
#define LIM_T 1



class cls_AC{
private:
  char Description[64];
  char Author[32];
  char Website[32];
  char Version[32];
  char Compiled[64];
  char WindowTitle[512];
  bool Initiated;
  bool FullScreen;
  int  LoopSpecify;
  bool LinScale;
  bool QuitFlag;
  int  Screen_MODE;
  int  Screen_MODE_Max;
  int  Screen_SIZE;
  int  Screen_SIZE_Max;
  char Screen_SIZE_Desc[32];
  int  Screen_Width;
  int  Screen_Height;
  int  Game_Width;
  int  Game_Height;
  int ProgSpeedCtrl;
  struct StructGameSettings{
    int  Mode;               /* Current Game Mode (See definitions on top) */
    int  NumberOfPlayers;    /* Number of BOTS allowed for this game */
    bool Started;            /* Flag to see if game is started */
    int  TimeLimit;          /* Time limit for the game */
    int  FragLimit;          /* Frag limit for the game */
    bool PowerupsEnabled;    /* Use powerups? */
    bool InstagibEnabled;    /* Instagib extra mode on? */
    bool DarknessEnabled;    /* Darkness extra mode on? */
    bool EquilibriumEnabled; /* Equilibrium extra mode on? */
    float EquilibriumStrength;
    int  Map;                /* Current Map for the game */
    int  NextMap;            /* Next map to load for the game */
    char MapFile[64];            /* Name of the current map */
    char NextMapFile[64];        /* Name of the next map */
    char MessageOfTheDay[4][32]; /* Message of the day array, 4 lines, 32 characters wide */
  } GameSettings;
public:
  double dif;
  char FPS[32];
  unsigned int FPSc;
  cls_AC();
  bool  GetEquilibrium();
  float GetEquilibriumStrength();
  void  SetEquilibriumStrength(float Strength);
  bool  GetLinScale();
  void  SetLinScale(bool On);
  void  SetGameMode(int Mode);
  const char *GetGameMode();
  const char *GetDescription();
  const char *GetAuthor();
  const char *GetWebsite();
  const char *GetVersion();
  void  ConfirmInitiated();
  bool  GetInit();
  void  SetFullscreen();
  void  SetWindowed();
  bool  GetFullscreen();
  void  PrintInformation();
  const char *GetMapFile();
  const char *GetNextMapFile();
  void  UpdateMapFile();
  void  SetNextMapFile(char *Filename);
  void  Quit();
  bool  QuitConfirmed();
  int GetScreenWidth();
  int GetHalfW();
  int GetHalfH();
  int GetScreenHeight();
  int GetGameWidth();
  int GetGameHeight();
  void SetResolution(int SIZE, int MODE);
  int GetSpecifiedLoop();
  void SpecifyLoop(int Loop);
  int GetProgramHoldTime();
  void AdjustProgramHoldTime(int Adj);
  const char *GetResolutionDesc();
  const char *GetAspectRatioDesc();
  int GetResolution(bool Max);
  int GetAspectRatio(bool Max);
  void SetAspectRatio(int MODE);
  const char *GetCompiled();
  const char *GetWindowTitle();
  int NumberOfPlayers(int inc);
  int GetSetLimits(int limit, int inc);
};

int cls_AC::GetSetLimits(int limit, int inc){
  switch( limit ){
    case LIM_F:
      GameSettings.FragLimit += inc;
      return GameSettings.FragLimit;
      break;
    case LIM_T:
      GameSettings.TimeLimit += inc;
      return GameSettings.TimeLimit;
      break;

    default:
      return 0;
  }
}
int cls_AC::NumberOfPlayers(int inc){
  if( inc > 0 ){
    if( ++GameSettings.NumberOfPlayers > 2 )
      GameSettings.NumberOfPlayers = 1;
  } else if( inc < 0 ){
    if( --GameSettings.NumberOfPlayers < 1 )
      GameSettings.NumberOfPlayers = 2;
  }
  return GameSettings.NumberOfPlayers;
}

cls_AC::cls_AC(){
  ProgSpeedCtrl = 12000;
  dif = 0;
  memset(FPS, '\0', 32);
  FPSc = 0;
  strcpy(Description,"An adventure to the depth of the earth");
  strcpy(Author,"Andre Lundkvist");
  strcpy(Website,"activate.jiisuki.net");
  strcpy(Version,"Version Alpha");
  sprintf(Compiled,"Compiled: %s %s",__DATE__,__TIME__);
  sprintf(WindowTitle,"Activated Core - %s (%s - %s)",Description,Version,Compiled);
  Initiated = 0;
  FullScreen = 0;
  LinScale = 0;
  QuitFlag = 0;
  Screen_MODE = 0;
  Screen_SIZE = 0;
  memset(Screen_SIZE_Desc,'\0',32);
  Screen_MODE_Max = 2;
  Screen_SIZE_Max = 4;
  Screen_Width = 1280;
  Screen_Height = 960;
  Game_Width = 1280;
  Game_Height = 960;
  LoopSpecify = LOOP_MAIN_MENU;
  GameSettings.Mode = G_MODE_DEATHMATCH;
  GameSettings.DarknessEnabled = 0;
  GameSettings.EquilibriumEnabled = 1;
  GameSettings.EquilibriumStrength = 30;
  GameSettings.FragLimit = 0;
  GameSettings.InstagibEnabled = 0;
  GameSettings.Map = 1;
  GameSettings.NextMap = 2;
  strcpy(GameSettings.MapFile, "maps/story/level01/map");
  strcpy(GameSettings.NextMapFile, "maps/story/level01/map");
  GameSettings.NumberOfPlayers = 1;
  GameSettings.PowerupsEnabled = 1;
  GameSettings.Started = 0;
  GameSettings.TimeLimit = 0;
}
void cls_AC::UpdateMapFile(){
  strcpy(GameSettings.MapFile, GameSettings.NextMapFile);
  printf("Current Map Updated to: %s\n\n",GameSettings.MapFile);
}
void cls_AC::SetNextMapFile(char *Filename){
  strcpy(GameSettings.NextMapFile, Filename);
  printf("Next Map Updated to: %s\n\n",GameSettings.NextMapFile);
}
const char *cls_AC::GetCompiled(){
  return Compiled;
}
bool cls_AC::GetEquilibrium(){
  return GameSettings.EquilibriumEnabled;
}
float cls_AC::GetEquilibriumStrength(){
  return GameSettings.EquilibriumStrength;
}
void cls_AC::SetEquilibriumStrength(float Strength){
  GameSettings.EquilibriumStrength = Strength;
}
bool cls_AC::GetLinScale(){
  return LinScale;
}
void cls_AC::SetLinScale(bool On){
  LinScale = On;
}
void cls_AC::SetGameMode(int Mode){
  if( Mode > 0 ){
    if( ++GameSettings.Mode > G_MODE_SINGLE_STORY )
      GameSettings.Mode = 0;
  } else if( Mode < 0 ){
    if( --GameSettings.Mode < 0 )
      GameSettings.Mode = G_MODE_SINGLE_STORY;
  }
}
const char *cls_AC::GetGameMode(){
  switch( GameSettings.Mode ){
    case 0: return "Training";
    case 1: return "Deathmatch";
    case 2: return "Team Deathmatch";
    case 3: return "Two Player Duel";
    case 4: return "Race to the Line";
    case 5: return "Bumper Kill";
    case 6: return "Tag";
    case 7: return "Capture the Flag";
    case 8: return "Single Player CTF";
  } return "Unknown Gamemode. Consider restarting Activated Core!";
}
const char *cls_AC::GetDescription(){
  return Description;
}
const char *cls_AC::GetAuthor(){
  return Author;
}
const char *cls_AC::GetWebsite(){
  return Website;
}
const char *cls_AC::GetVersion(){
  return Version;
}
void cls_AC::ConfirmInitiated(){
  Initiated = 1;
}
bool cls_AC::GetInit(){
  return Initiated;
}
void cls_AC::SetFullscreen(){
  FullScreen = 1;
}
void cls_AC::SetWindowed(){
  FullScreen = 0;
}
bool cls_AC::GetFullscreen(){
  return FullScreen;
}
void cls_AC::PrintInformation(){
  printf("Description:\n  %s\n",Description);
  printf("Author:\n  %s\n",Author);
  printf("Website:\n  %s\n",Website);
  printf("Version:\n  %s\n",Version);
  printf("Running in Fullscreen: %i\n",FullScreen);
  // ADD MORE
}
const char *cls_AC::GetMapFile(){
  return GameSettings.MapFile;
}
const char *cls_AC::GetNextMapFile(){
  return GameSettings.NextMapFile;
}
void cls_AC::Quit(){
  QuitFlag = 1;
}
bool cls_AC::QuitConfirmed(){
  return QuitFlag;
}
int cls_AC::GetScreenWidth(){
  return Screen_Width;
}
int cls_AC::GetScreenHeight(){
  return Screen_Height;
}
int cls_AC::GetHalfW(){
  return Screen_Width/2;
}
int cls_AC::GetHalfH(){
  return Screen_Height/2;
}
int cls_AC::GetGameWidth(){
  return Game_Width;
}
int cls_AC::GetGameHeight(){
  return Game_Height;
}
void cls_AC::SetResolution(int SIZE, int MODE){
   // SIZE     WIDTH     MODE    ASPECT
   // 0        640       0       4:3
   // 1        1024      1       16:9
   // 2        1280      2       16:10
  int k = 2;

  int SX, SY, SXG, SYG;
  switch( MODE ){
    case 0:
      SXG = 1280;
      SYG = 960;
      break;
    case 1:
      SXG = 1280;
      SYG = 720;
      break;
    case 2:
      SXG = 1280;
      SYG = 800;
      break;
    default:
      SXG = 1280;
      SYG = 960;
  }
  SXG = SXG/k;
  SYG = SYG/k;

//  switch( MODE ){
//    case 0:
//      SXG = 640;
//      SYG = 480;
//      break;
//    case 1:
//      SXG = 640;
//      SYG = 360;
//      break;
//    case 2:
//      SXG = 640;
//      SYG = 400;
//      break;
//    default:
//      SXG = 640;
//      SYG = 480;
//  }
  switch( SIZE ){
    case 0:
      if( MODE == 0 ){
        SX = 320;
        SY = 240;}
      if( MODE == 1 ){
        SX = 320;
        SY = 180;}
      if( MODE == 2 ){
        SX = 320;
        SY = 200;}
      break;
    case 1:
      if( MODE == 0 ){
        SX = 640;
        SY = 480;}
      if( MODE == 1 ){
        SX = 640;
        SY = 360;}
      if( MODE == 2 ){
        SX = 640;
        SY = 400;}
      break;
    case 2:
      if( MODE == 0 ){
        SX = 800;
        SY = 600;}
      if( MODE == 1 ){
        SX = 800;
        SY = 450;}
      if( MODE == 2 ){
        SX = 800;
        SY = 500;}
      break;
    case 3:
      if( MODE == 0 ){
        SX = 1024;
        SY = 768;}
      if( MODE == 1 ){
        SX = 1024;
        SY = 576;}
      if( MODE == 2 ){
        SX = 1024;
        SY = 640;}
      break;
    case 4:
      if( MODE == 0 ){
        SX = 1280;
        SY = 960;}
      if( MODE == 1 ){
        SX = 1280;
        SY = 720;}
      if( MODE == 2 ){
        SX = 1280;
        SY = 800;}
      break;
    default:
      SX = 640;
      SY = 480;
      break;
  }
  Screen_Width = SXG;
  Screen_Height = SYG;
  Game_Width = SX;
  Game_Height = SY;
//
//  if( Initiated )
//    ReSizeGLScene(Game_Width,Game_Height);

  Screen_MODE = MODE;
  Screen_SIZE = SIZE;
  
//  printf("Screen Resolution is Set to: %s\n",GetResolutionDesc());
}
const char *cls_AC::GetResolutionDesc(){
  int SX, SY;
  
  switch( Screen_SIZE ){
    case 0:
      if( Screen_MODE == 0 ){
        SX = 320;
        SY = 240;}
      if( Screen_MODE == 1 ){
        SX = 320;
        SY = 180;}
      if( Screen_MODE == 2 ){
        SX = 320;
        SY = 200;}
      break;
    case 1:
      if( Screen_MODE == 0 ){
        SX = 640;
        SY = 480;}
      if( Screen_MODE == 1 ){
        SX = 640;
        SY = 360;}
      if( Screen_MODE == 2 ){
        SX = 640;
        SY = 400;}
      break;
    case 2:
      if( Screen_MODE == 0 ){
        SX = 800;
        SY = 600;}
      if( Screen_MODE == 1 ){
        SX = 800;
        SY = 450;}
      if( Screen_MODE == 2 ){
        SX = 800;
        SY = 500;}
      break;
    case 3:
      if( Screen_MODE == 0 ){
        SX = 1024;
        SY = 768;}
      if( Screen_MODE == 1 ){
        SX = 1024;
        SY = 576;}
      if( Screen_MODE == 2 ){
        SX = 1024;
        SY = 640;}
      break;
    case 4:
      if( Screen_MODE == 0 ){
        SX = 1280;
        SY = 960;}
      if( Screen_MODE == 1 ){
        SX = 1280;
        SY = 720;}
      if( Screen_MODE == 2 ){
        SX = 1280;
        SY = 800;}
      break;
    default:
      SX = 640;
      SY = 480;
      break;
  }
  sprintf(Screen_SIZE_Desc,"%i x %i (%s)",SX,SY,GetAspectRatioDesc());
  return Screen_SIZE_Desc;
}
const char *cls_AC::GetAspectRatioDesc(){
  switch( Screen_MODE ){
    case 0:
      return "4:3";
      break;
    case 1:
      return "16:9";
      break;
    case 2:
      return "16:10";
      break;
    default:
      return "4:3";
  }
}
void cls_AC::SetAspectRatio(int MODE){
  Screen_MODE = MODE;
}
int cls_AC::GetResolution(bool Max){
  if( Max )
    return Screen_SIZE_Max;
  return Screen_SIZE;
}
int cls_AC::GetAspectRatio(bool Max){
  if( Max )
    return Screen_MODE_Max;
  return Screen_MODE;
}
int cls_AC::GetSpecifiedLoop(){
  return LoopSpecify;
}
void cls_AC::SpecifyLoop(int Loop){
  if( Loop >= LOOP_MIN && Loop <= LOOP_MAX )
    LoopSpecify = Loop;
}
int cls_AC::GetProgramHoldTime(){
  return ProgSpeedCtrl;
}
void cls_AC::AdjustProgramHoldTime(int Adj){
  ProgSpeedCtrl+=Adj;
  if( ProgSpeedCtrl < HOLD_MIN )
    ProgSpeedCtrl = HOLD_MIN;
  if( ProgSpeedCtrl > HOLD_MAX )
    ProgSpeedCtrl = HOLD_MAX;
}
const char *cls_AC::GetWindowTitle(){
  return WindowTitle;
}


class cls_System {
public:
  void SysMessage(const char *String);
  void NewSection(const char *String);
};
void cls_System::SysMessage(const char *String){
  printf("%s\n",String);
}
void cls_System::NewSection(const char *String){
  printf("\n======================================================\n");
  printf("  %s\n",String);
  printf("======================================================\n");
}


cls_AC AC;
cls_System SYSTEM;


#endif

