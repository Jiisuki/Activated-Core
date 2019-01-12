/* mapitems.cpp
 *
 * This file contains all needed classes for mapobjects (pickups, teleporters, spawns etc)
 *
 */






#define ITEM_DISC       14
#define ITEM_LAUNCHER   13
#define ITEM_RAILGUN    9
#define ITEM_TRAILGUN   10
#define ITEM_CAPACITOR  11
#define ITEM_BATTERY    5
#define ITEM_ARMOR      8
#define ITEM_SHIELD     2
#define ITEM_SLUGS      4
#define ITEM_HEALTH     16
#define ITEM_GRENADES   6
#define ITEM_SENSOR     7
#define ITEM_SPAWN      1

//#define ITEM_ELEVATOR 0
//#define ITEM_TELEPORT 1
//#define ITEM_DOOR 3

#define HIGH_ITEM 16

const char *GetItemName(int item){
  switch( item ){
    case ITEM_SPAWN:
      return "SPAWN";
    case ITEM_DISC:
      return "DISC";
    case ITEM_LAUNCHER:
      return "LAUNCHER";
    case ITEM_RAILGUN:
      return "RAILGUN";
    case ITEM_TRAILGUN:
      return "TRAILGUN";
    case ITEM_CAPACITOR:
      return "CAP";
    case ITEM_BATTERY:
      return "BATTERY";
    case ITEM_ARMOR:
      return "ARMOR";
    case ITEM_SHIELD:
      return "SHIELD";
    case ITEM_SLUGS:
      return "SLUGS";
    case ITEM_HEALTH:
      return "HEALTH";
    case ITEM_GRENADES:
      return "GRENADES";
    case ITEM_SENSOR:
      return "SENSOR";
    /*case ITEM_ELEVATOR:
      return "ELEVATOR";
    case ITEM_TELEPORT:
      return "TELEPORT";
    case ITEM_DOOR:
      return "DOOR";*/
    default:
      return "UNKNOWN";
  }
}


/* cls_Spawn
 * ============================================
 * This class holds all needed information for
 * spawns on the map.
 * ============================================ */
class cls_Spawn{
private:
  int  X;
  int  Y;
  bool Busy;
  int  Team;
  int  Time;
public:
  cls_Spawn();
  void SetSpawn(int sX, int sY, bool sBusy, int sTeam, int sTime);
  int GetX();
  int GetY();
};
cls_Spawn::cls_Spawn(){
  X    = 0;
  Y    = 0;
  Busy = 0;
  Team = 0;
  Time = 0;
}
int cls_Spawn::GetX(){
  return X;
}
int cls_Spawn::GetY(){
  return Y;
}
void cls_Spawn::SetSpawn(int sX, int sY, bool sBusy, int sTeam, int sTime){
  X = sX;
  Y = sY;
  Busy = sBusy;
  Team = sTeam;
  Time = sTime;
}



/* cls_Teleport
 * ============================================
 * This class holds all needed information for
 * teleports on the map.
 * ============================================ */
class cls_Teleport{
private:
  int  X;
  int  Y;
  bool Busy;
  int  ToID;
  bool NeedKey;
  int  AnimNum;
  float AnimStep;
  int  AnimLen;
  bool SpawnLeft;
public:
  cls_Teleport();
  void SetTeleport(int sX, int sY, bool sBusy, int sToID, bool sNeedKey, int sAnimLen, bool sSpawn);
  int  GetX();
  int  GetY();
  int  GetToID();
  bool GetKeyNeeded();
  int  Animation(bool Step);
  bool GetSpawnLeft();
};
cls_Teleport::cls_Teleport(){
  X       = 0;
  Y       = 0;
  Busy    = 0;
  ToID    = 0;
  NeedKey = 0;
  AnimLen = 12;
  AnimStep = 0;
  AnimNum = 0;
}
int cls_Teleport::Animation(bool Step){
  if( Step ){
    AnimStep+=0.3;
    if( AnimStep > 1 ){
      AnimNum++;
      if( AnimNum > AnimLen-1 )
        AnimNum = 0;
      AnimStep = 0;
    }
    return AnimNum;
  } else {
    return AnimNum;
  }
}
int cls_Teleport::GetX(){
  return X;
}
int cls_Teleport::GetY(){
  return Y;
}
int cls_Teleport::GetToID(){
  return ToID;
}
bool cls_Teleport::GetKeyNeeded(){
  return NeedKey;
}
bool cls_Teleport::GetSpawnLeft(){
  return SpawnLeft;
}
void cls_Teleport::SetTeleport(int sX, int sY, bool sBusy, int sToID, bool sNeedKey, int sAnimLen, bool sSpawn){
  X = sX;
  Y = sY;
  Busy = sBusy;
  ToID = sToID;
  NeedKey = sNeedKey;
  AnimLen = sAnimLen;
  SpawnLeft = sSpawn;
}




class cls_MapExtra{
private:
  int  X;
  int  Y;
  int  W;
  int  H;
  GLuint Texture;
  char TextureFile[128];
  float AnimStep;
  int AnimLen;
  int AnimNum;
public:
  cls_MapExtra();
  ~cls_MapExtra();
  void SetMapExtra(int sX, int sY, const char *TexFile, int sAnimLen, int sW, int sH);
  int  GetX();
  int  GetY();
  int  GetW();
  int  GetH();
  int  GetAlen();
  int  Animation(bool Step);
  GLuint GetTexture();
  void DrawMapExtra();
};
cls_MapExtra::cls_MapExtra(){
  X       = 0;
  Y       = 0;
  AnimLen = 12;
  AnimStep = 0;
  AnimNum = 0;
  Texture = 0;
  memset(TextureFile,'\0',128);
}
cls_MapExtra::~cls_MapExtra(){
  glDeleteTextures(1, &Texture);
}
GLuint cls_MapExtra::GetTexture(){
  return Texture;
}
int cls_MapExtra::GetAlen(){
  return AnimLen;
}
int cls_MapExtra::Animation(bool Step){
  if( Step ){
    AnimStep+=0.3;
    if( AnimStep > 1 ){
      AnimNum++;
      if( AnimNum > AnimLen-1 )
        AnimNum = 0;
      AnimStep = 0;
    }
    return AnimNum;
  } else {
    return AnimNum;
  }
}
int cls_MapExtra::GetX(){
  return X;
}
int cls_MapExtra::GetY(){
  return Y;
}
int cls_MapExtra::GetW(){
  return W;
}
int cls_MapExtra::GetH(){
  return H;
}
void cls_MapExtra::SetMapExtra(int sX, int sY, const char *TexFile, int sAnimLen, int sW, int sH){
  X = sX;
  Y = sY;
  W = sW;
  H = sH;
  AnimLen = sAnimLen;
  strcpy(TextureFile,TexFile);
  usleep(10000);
  GFX.LoadTexture(TextureFile, &Texture);
  usleep(10000);
}
void cls_MapExtra::DrawMapExtra(){
  
}





/* cls_PickupItem
 * ============================================
 * This class holds all needed information for
 * pickup objects.
 * ============================================ */
class cls_PickupItem{
private:
  int   X;
  int   Y;
  int   Type;
  bool  Spawned;
  float SpawnTime;
  int   SpawnTimeMax;
  bool  ReSpawn;
  int   AnimGfx;
  int   AnimNum;
  float AnimStep;
  int   AnimLen;
  char  FlagStr[32];
  int   FlagInt;
public:
  cls_PickupItem();
  void SetItem(int sX, int sY, int sType, const char *sFs, int sFi, int sAnimGfx, bool sRespawn);
  int GetX();
  int GetY();
  int GetType();
  int Pickup();
  const char *GetFlagStr();
  int GetFlagInt();
  int Animation(bool Step);
  int GetAnimGfx();
  bool IsSpawned();
  void CountSpawnTime();
  void Spawn();
};

cls_PickupItem::cls_PickupItem(){

}
void cls_PickupItem::SetItem(int sX, int sY, int sType, const char *sFs, int sFi, int sAnimGfx, bool sRespawn){
  X = sX;
  Y = sY;
  Type = sType;
  Spawned = 1;
  SpawnTime = 0;
  SpawnTimeMax = 15;
  ReSpawn = sRespawn; // 0 if object will not respawn!

  strcpy(FlagStr, sFs);
  FlagInt = sFi;

  AnimGfx = sAnimGfx;
  AnimNum = 0;
  AnimLen = 8;
  AnimStep = 0;
}
void cls_PickupItem::CountSpawnTime(){
  if( ReSpawn )
    SpawnTime+=0.01;
  if( SpawnTime > SpawnTimeMax )
    Spawned = 1;
}
bool cls_PickupItem::IsSpawned(){
  return Spawned;
}
int cls_PickupItem::GetAnimGfx(){
  return AnimGfx;
}

int cls_PickupItem::Animation(bool Step){
  if( Step ){
    AnimStep+=0.3;
    if( AnimStep > 1 ){
      AnimNum++;
      if( AnimNum > AnimLen-1 )
        AnimNum = 0;
      AnimStep = 0;
    }
    return AnimNum;
  } else {
    return AnimNum;
  }
}
int cls_PickupItem::GetX(){
  return X;
}
int cls_PickupItem::GetY(){
  return Y;
}
int cls_PickupItem::GetType(){
  return Type;
}
void cls_PickupItem::Spawn(){
  Spawned = 1;
}
int cls_PickupItem::Pickup(){
  if( Spawned ){
    Spawned = 0;
    SpawnTime = 0;
    //GUI.OSDMessage(FlagStr, 1);
    Sound.PlaySfx(SFX_PICKUP);
    return Type;
  } else {
    return -1;
  }
}
int cls_PickupItem::GetFlagInt(){
  return FlagInt;
}






/* cls_PickupItem
 * ============================================
 * This class holds all needed information for
 * pickup objects.
 * ============================================ */
class cls_Elevator{
private:
  int   X;
  int   Y;
  int   Y0;
  int   AnimNum;
  float AnimStep;
  int   AnimLen;
  int   Speed;
  int   Travel;
  int   AnimDir;
public:
  cls_Elevator();
  void SetItem(int sX, int sY, int sFi, int sW);
  int GetX();
  int GetY();
  int Animation(bool Step);
  void Move();
  void ResetMove();
  void ResetAll();
};

cls_Elevator::cls_Elevator(){

}
void cls_Elevator::ResetAll(){
  Y = Y0;
}
void cls_Elevator::Move(){
  if( Y <= (Y0-Travel) ){
    Y = Y0-Travel;
    return;
  }
  Y -= Speed;
  AnimDir = 1;
  Animation(1);
}
void cls_Elevator::ResetMove(){
  if( Y >= Y0 ){
    Y = Y0;
    return;
  }
  Y += Speed;
  AnimDir = -1;
  Animation(1);
}
void cls_Elevator::SetItem(int sX, int sY, int sFi, int sW){
  X = sX;
  Y = sY;
  Y0 = sY;

  Speed = sFi;
  AnimDir = 1;
  Travel = sW-9;

  AnimNum = 0;
  AnimLen = 4;
  AnimStep = 0;
}
int cls_Elevator::Animation(bool Step){
  if( Step ){
    AnimStep+=3*abs(Speed);
    if( AnimStep > 12 ){
      if( AnimDir > 0 ){
        AnimNum++;
        if( AnimNum > AnimLen-1 )
          AnimNum = 0;
      } else {
        AnimNum--;
        if( AnimNum < 0 )
          AnimNum = AnimLen-1;
      }
      AnimStep = 0;
    }
    return AnimNum;
  } else {
    return AnimNum;
  }
}
int cls_Elevator::GetX(){
  return X;
}
int cls_Elevator::GetY(){
  return Y;
}





class cls_Door{
private:
  int   X;
  int   Y;
  int   AnimNum;
  float AnimStep;
  int   AnimLen;
  int   AnimState;
  int   Key;
  int   Travel;
  int   AnimDir;
public:
  cls_Door();
  void SetItem(int sX, int sY, int sKey);
  int GetX();
  int GetY();
  int Animation(bool Step);
  int GetState();
  void Open();
  int GetDoorKey();
  void Close();
};

cls_Door::cls_Door(){

}
int cls_Door::GetDoorKey(){
  return Key;
}
void cls_Door::Open(){
  if( (AnimState == 0) && (AnimNum == 0) ){
    AnimDir = 1;
    AnimState = 1;
  }
}
void cls_Door::Close(){
  if( (AnimState == 2) && (AnimNum == AnimLen-1) ){
    AnimDir = -1;
    AnimNum = AnimLen-1;
    AnimState = 1;
  }
}
void cls_Door::SetItem(int sX, int sY, int sKey){
  X = sX;
  Y = sY;

  AnimDir = 1;
  Key = sKey;

  AnimNum = 0;
  AnimLen = 8;
  AnimStep = 0;
  AnimState = 0;
}
int cls_Door::Animation(bool Step){
  if( Step ){
    AnimStep+=0.6;
    if( AnimStep > 1 ){
      if( AnimState == 1 ){
        AnimNum+=AnimDir;
        if( AnimNum > AnimLen-1 ){
          AnimNum = 0;
          AnimState = 2;
        }
        if( AnimNum < 0 ){
          AnimNum = AnimLen-1;
          AnimState = 0;
        }
        AnimStep = 0;
      } else {
        AnimNum+=AnimDir;
        if( AnimNum > AnimLen-1 )
          AnimNum = 0;
        if( AnimNum < 0 )
          AnimNum = AnimLen-1;
        AnimStep = 0;
      }
    }
    return AnimNum;
  } else {
    return AnimNum;
  }
}
int cls_Door::GetX(){
  return X;
}
int cls_Door::GetY(){
  return Y;
}
int cls_Door::GetState(){
  return AnimState;
}







/* cls_Terminal
 * ============================================
 * This class holds all needed information for
 * terminals on the map
 * ============================================ */
class cls_Terminal{
private:
  int  X;
  int  Y;
  int  W;
  int  H;
  bool Busy;
  int  ToID;
  int  NeedKey;
  int  AnimNum;
  float AnimStep;
  int  AnimLen;
  int  Type;
  struct StructWelcome{
    char Line[64];
  }InitText[4];
public:
  cls_Terminal();
  void SetTerminal(int sX, int sY, bool sBusy, int sToID, int sNeedKey, int sAnimLen, int sW, int sH, int sType);
  void SetInitText(int Line, const char *Text);
  const char *GetInitText(int Line);
  int  GetX();
  int  GetY();
  int  GetW();
  int  GetH();
  int  GetToID();
  int  GetType();
  int  GetKeyNeeded();
  int  Animation(bool Step);
};
cls_Terminal::cls_Terminal(){
  X       = 0;
  Y       = 0;
  W       = 0;
  H       = 0;
  Busy    = 0;
  ToID    = 0;
  NeedKey = 0;
  AnimLen = 12;
  AnimStep = 0;
  AnimNum = 0;
  Type    = 0;
}
void cls_Terminal::SetInitText(int Line, const char *Text){
  memset(InitText[Line].Line,'\0',64);
  strcpy(InitText[Line].Line,Text);
}
const char *cls_Terminal::GetInitText(int Line){
  return InitText[Line].Line;
}
int cls_Terminal::Animation(bool Step){
  if( Step ){
    AnimStep+=0.3;
    if( AnimStep > 1 ){
      AnimNum++;
      if( AnimNum > AnimLen-1 )
        AnimNum = 0;
      AnimStep = 0;
    }
    return AnimNum;
  } else {
    return AnimNum;
  }
}
int cls_Terminal::GetX(){
  return X;
}
int cls_Terminal::GetY(){
  return Y;
}
int cls_Terminal::GetW(){
  return W;
}
int cls_Terminal::GetH(){
  return H;
}
int cls_Terminal::GetToID(){
  return ToID;
}
int cls_Terminal::GetType(){
  return Type;
}
int cls_Terminal::GetKeyNeeded(){
  return NeedKey;
}
void cls_Terminal::SetTerminal(int sX, int sY, bool sBusy, int sToID, int sNeedKey, int sAnimLen, int sW, int sH, int sType){
  X = sX;
  Y = sY;
  W = sW;
  H = sH;
  Busy = sBusy;
  ToID = sToID;
  NeedKey = sNeedKey;
  AnimLen = sAnimLen;
  Type = sType;
}






/* cls_PickupItem
 * ============================================
 * This class holds all needed information for
 * pickup objects.
 * ============================================ */
class cls_Hbl{
private:
  int   X;
  int   Y;
  int   AnimNum;
  float AnimStep;
  int   AnimLen;
  int   AnimState;
  float SpawnTime;
  float SpawnTimeMax;
  bool  Spawned;
public:
  cls_Hbl();
  void SetItem(int sX, int sY, int sFi);
  int GetX();
  int GetY();
  int Animation(bool Step);
  void CountSpawnTime();
  bool IsSpawned();
  int GetState();
};

cls_Hbl::cls_Hbl(){

}
void cls_Hbl::SetItem(int sX, int sY, int sFi){
  X = sX;
  Y = sY;
  
  SpawnTimeMax = (float) sFi;
  Spawned = 1;
  SpawnTime = 0;

  AnimNum = 3;
  AnimLen = 8;
  AnimStep = 0;
  AnimState = 0;
}
int cls_Hbl::Animation(bool Step){
  if( Step ){
    if( AnimState != 1 ){
      AnimState = 1;
      AnimLen = 8;
      AnimNum = 0;
    }
    AnimStep+=0.3;
    if( AnimStep > 1 ){
      AnimNum++;
      if( AnimNum > AnimLen-1 ){
        Spawned = 0;
        AnimNum = 0;
      }
      AnimStep = 0;
    }
    return AnimNum;
  } else {
    if( AnimState == 0 ){
      if( AnimNum < 3 ){
        AnimNum++;
        if( AnimNum > AnimLen-1 ){
          AnimNum = 0;
          AnimState = 1;
        }
      }
    }
    return AnimNum;
  }
}
int cls_Hbl::GetX(){
  return X;
}
int cls_Hbl::GetY(){
  return Y;
}
int cls_Hbl::GetState(){
  return AnimState;
}
void cls_Hbl::CountSpawnTime(){
  SpawnTime+=0.01;
  if( SpawnTime > SpawnTimeMax ){
    SpawnTime = 0;
    Spawned = 1;
    AnimState = 0;
    AnimNum = 0;
    AnimLen = 4;
  }
}
bool cls_Hbl::IsSpawned(){
  return Spawned;
}








