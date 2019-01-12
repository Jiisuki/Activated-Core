
#ifndef _MAP_H
#define _MAP_H


#include "mapitems.h"
#include "mapdata.h"
#include "global.h"
//#include "graphics.h"


int GetTileX(int t){
    return (t%TILES_RES);
}
int GetTileY(int t){
    return floor(t/TILES_RES);
}



struct StructMapExtraTexture{
  char Type;              /* Which graphics to display */
  int  X;                  /* Position X */
  int  Y;                  /* Position Y */
  char AnimationLength;   /* Length of Animation */
  char AnimationPosition; /* Current Animation Frame */
  char AnimationHeight;   /* Height of the Animation Frames */
  char AnimationWidth;    /* Width of the Animation Frames */
};



/* Create the main mapsettings. */
class cls_Map{
private:
  unsigned char PreviewMapIndex;    // Index for the Preview Map Function
  unsigned int  MapCount;           // Number of maps available
  unsigned int  SelectedMap;        // Number of the selected map
  bool Loaded;
  struct StructMapSettings{
    char       Name[64];     // Name of the map
    char       Author[32];   // Name of the author/creator
    char       File_Tex_Gfx[128];
    char       File_Tex_LM[128];
    char       File_Tex_Ovr[128];
    char       File_Tex_Col[128];
    char       File_Extra_Map[128];
    TGAImg     ColmapTmp;
    unsigned char *Colmap;
    GLuint     Tex_Gfx; // Graphical representation texture
    GLuint     Tex_LM;  // Lightmap
    GLuint     Tex_Ovr; // Overlay graphics
    StructSurf Rect;         // Size of the Map
    int        Width;
    int        Height;
    int        Music;        // Musical tune
  }Data;
  
  GLuint EnbarTex;
  char EnbarTexFile[128];
  
  struct StructPickups{
    cls_PickupItem *Item;
    int NumItems;
    GLuint Tex;
    char TexFile[128];
  }PickupObject;
  cls_MapExtra *ExtraMapAnimation;
  int NumExtraMapAnimations;
  int Env;
  
  struct StructElevator{
    cls_Elevator *Item;
    int NumItems;
    GLuint Tex;
    char TexFile[128];
  }Elevator;
  
  struct StructDoor{
    cls_Door *Item;
    int NumItems;
    GLuint Tex;
    char TexFile[128];
  }Door;
  
  struct StructHbl{
    cls_Hbl *Item;
    int NumItems;
    GLuint Tex;
    char TexFile[128];
  }Hbl;
 
  
public:
struct StructMapObjects{
    GLuint Tex; // Map objects (teleport, jumper)
    char   TexFile[128];
    cls_Spawn *Spawn;
    int NumSpawns;
    cls_Teleport *Teleport;
    int NumTeleports;
    cls_Terminal *Terminal;
    int NumTerminals;
  }Object;
  cls_Map();
  int GetMapData(int x, int y);
  char *GetMapName(const char *Filename);
  int GetWidth();
  int GetHeight();
  int GetMapEnv();
  int LoadMap(const char *Filename);
  GLuint *GetGfx();
  GLuint *GetLM();
  unsigned char GetCol(unsigned int x, unsigned int y);
  char *GetGfxFile();
  char *GetColFile();
  char *GetLMFile();
  StructSurf GetRect();
  bool GetLoaded();
  void Unload();
  void DrawMapObjects(int pX, int pY);
  int GetSpawnX(int Num);
  int GetSpawnY(int Num);
  int GetNumSpawns();
  int GetNumTeleports();
  int GetTeleportX(int Num);
  int GetTeleportY(int Num);
  int GetTeleportToID(int Num);
  bool GetTeleportLeftsideSpawn(int Num);
  int GetNumElevators();
  int GetElevatorX(int Num);
  int GetElevatorY(int Num);
  void MoveElevator(int Num);
  void ResetElevator(int Num);
  int GetNumHbl();
  int GetHblX(int Num);
  int GetHblY(int Num);
  void CountHbl(int Num);
  bool HblSpawned(int Num);
  int GetNumDoors();
  int GetDoorX(int Num);
  int GetDoorY(int Num);
  void OpenDoor(int Num);
  int DoorKey(int Num);
  void CloseDoor(int Num);
  int DoorState(int Num);
  bool DoorOpened(int Num);
  int GetNumItems();
  int GetItemType(int Num);
  int GetItemX(int Num);
  int GetItemY(int Num);
  int PickupItem(int Num);
  int GetPickupItemValue(int Num);
  bool GetPickupItemSpawned(int Num);
  int GetNumEnemies(int Class);
  int GetEnemyX(int Class, int Num);
  int GetEnemyY(int Class, int Num);
  bool GetEnemySpawned(int Class, int Num);
  int GetSetEnemyHealth(int Class, int Num, int Change);
  void ResetMapObjects();
  void DrawMap(int x, int y);
  char TMPT[32];
};
int cls_Map::GetMapEnv(){
  return Env;
}
int cls_Map::GetWidth(){
  return Data.Width;
}
int cls_Map::GetHeight(){
  return Data.Height;
}
int cls_Map::GetMapData(int x, int y){
  return *(MAP+y*Data.Width+x);
}
unsigned char cls_Map::GetCol(unsigned int x, unsigned int y){
  int xi = (x/32);
  int yi = (y/32);
  
  int c = *(MAP+yi*Data.Width+xi);

  int xp = GetTileX(c)*32 + (x%32);
  int yp = GetTileY(c)*32 + (y%32);

  int bpp = Data.ColmapTmp.GetBPP()/8;
  //address = baseAddress + elementSize * (r*rowSize + c);
  return *((Data.Colmap + (bpp) * (xp + (255-yp)*256))+3);// * Data.Rect.Bottom) ;
  
  //return *((Data.Colmap + (bpp) * (x + (Data.Rect.Bottom-y)*Data.Rect.Right))+3);// * Data.Rect.Bottom) ;
}
cls_Map::cls_Map(){
  Loaded = 0;
  strcpy(Object.TexFile, "gfx/models/mapobjects.tga");
  strcpy(PickupObject.TexFile, "gfx/models/objects.tga");
  strcpy(Elevator.TexFile, "gfx/models/elevator.tga");
  strcpy(Door.TexFile, "gfx/models/door2.tga");
  strcpy(Hbl.TexFile, "gfx/models/hideblock.tga");
  strcpy(EnbarTexFile, "gfx/hud/enbar.tga");
}
int cls_Map::GetNumItems(){
  return PickupObject.NumItems;
}
int cls_Map::GetItemType(int Num){
  if( PickupObject.NumItems > 0 && Num < PickupObject.NumItems )
    return PickupObject.Item[Num].GetType();
  return 0;
}
int cls_Map::GetItemX(int Num){
  if( PickupObject.NumItems > 0 && Num < PickupObject.NumItems )
    return PickupObject.Item[Num].GetX();
  return 0;
}
int cls_Map::GetItemY(int Num){
  if( PickupObject.NumItems > 0 && Num < PickupObject.NumItems )
    return PickupObject.Item[Num].GetY();
  return 0;
}
int cls_Map::PickupItem(int Num){
  if( PickupObject.NumItems > 0 && Num < PickupObject.NumItems ){
    PickupObject.Item[Num].Pickup();
    return PickupObject.Item[Num].GetType();
  }
  return -1;
}
bool cls_Map::GetPickupItemSpawned(int Num){
    if( PickupObject.NumItems > 0 && Num < PickupObject.NumItems ){
        return PickupObject.Item[Num].IsSpawned();
    }
    return 0;
}
int cls_Map::GetPickupItemValue(int Num){
  if( PickupObject.NumItems > 0 && Num < PickupObject.NumItems ){
    return PickupObject.Item[Num].GetFlagInt();
  }
  return 0;
}

int cls_Map::GetNumHbl(){
  return Hbl.NumItems;
}
int cls_Map::GetHblX(int Num){
  if( Hbl.NumItems > 0 && Num < Hbl.NumItems )
    return Hbl.Item[Num].GetX();
  return 0;
}
int cls_Map::GetHblY(int Num){
  if( Hbl.NumItems > 0 && Num < Hbl.NumItems )
    return Hbl.Item[Num].GetY();  
  return 0;
}
void cls_Map::CountHbl(int Num){
  if( Hbl.NumItems > 0 && Num < Hbl.NumItems )
    Hbl.Item[Num].Animation(1);  
}
bool cls_Map::HblSpawned(int Num){
  if( Hbl.NumItems > 0 && Num < Hbl.NumItems )
    return Hbl.Item[Num].IsSpawned();  
  return 0;
}



int cls_Map::GetNumDoors(){
  return Door.NumItems;
}
int cls_Map::GetDoorX(int Num){
  if( Door.NumItems > 0 && Num < Door.NumItems )
    return Door.Item[Num].GetX();
  return 0;
}
int cls_Map::GetDoorY(int Num){
  if( Door.NumItems > 0 && Num < Door.NumItems )
    return Door.Item[Num].GetY();  
  return 0;
}

void cls_Map::OpenDoor(int Num){
  if( Door.NumItems > 0 && Num < Door.NumItems )
    Door.Item[Num].Open();
}
int cls_Map::DoorKey(int Num){
  if( Door.NumItems > 0 && Num < Door.NumItems )
    return Door.Item[Num].GetDoorKey();
  return 0;
}
void cls_Map::CloseDoor(int Num){
  if( Door.NumItems > 0 && Num < Door.NumItems )
    Door.Item[Num].Close();
}
int cls_Map::DoorState(int Num){
  if( Door.NumItems > 0 && Num < Door.NumItems )
    return Door.Item[Num].GetState();
  return 0;
}
bool cls_Map::DoorOpened(int Num){
  if( Door.NumItems > 0 && Num < Door.NumItems )
    switch( Door.Item[Num].GetState() ){
      case 1:
        if( Door.Item[Num].Animation(0) > 4 )
          return 1;
        break;
      case 2:
        return 1;
    }
  return 0;
}
int cls_Map::GetNumElevators(){
  return Elevator.NumItems;
}
int cls_Map::GetElevatorX(int Num){
  if( Elevator.NumItems > 0 && Num < Elevator.NumItems )
    return Elevator.Item[Num].GetX();
  return 0;
}
int cls_Map::GetElevatorY(int Num){
  if( Elevator.NumItems > 0 && Num < Elevator.NumItems )
    return Elevator.Item[Num].GetY();  
  return 0;
}
void cls_Map::MoveElevator(int Num){
  if( Elevator.NumItems > 0 && Num < Elevator.NumItems )
    Elevator.Item[Num].Move();
}
void cls_Map::ResetElevator(int Num){
  if( Elevator.NumItems > 0 && Num < Elevator.NumItems )
    Elevator.Item[Num].ResetMove();
}
int cls_Map::GetNumTeleports(){
  return Object.NumTeleports;
}
int cls_Map::GetTeleportX(int Num){
  if( Object.NumTeleports > 0 && Num < Object.NumTeleports )
    return Object.Teleport[Num].GetX();
  return 0;
}
int cls_Map::GetTeleportY(int Num){
  if( Object.NumTeleports > 0 && Num < Object.NumTeleports )
    return Object.Teleport[Num].GetY();
  return 0;
}
int cls_Map::GetTeleportToID(int Num){
  if( Object.NumTeleports > 0 && Num < Object.NumTeleports )
    return Object.Teleport[Num].GetToID();
  return 0;
}
bool cls_Map::GetTeleportLeftsideSpawn(int Num){
  if( Object.NumTeleports > 0 && Num < Object.NumTeleports )
    return Object.Teleport[Num].GetSpawnLeft();
  return 0;
}
int cls_Map::GetNumSpawns(){
  return Object.NumSpawns;
}
int cls_Map::GetSpawnX(int Num){
  if( Object.NumSpawns > 0 && Num < Object.NumSpawns )
    return Object.Spawn[Num].GetX();
  return 0;
}
int cls_Map::GetSpawnY(int Num){
  if( Object.NumSpawns > 0 && Num < Object.NumSpawns )
    return Object.Spawn[Num].GetY();
  return 0;
}
void cls_Map::Unload(){
  glDeleteTextures(1, GetGfx());
  glDeleteTextures(1, &Object.Tex);
  glDeleteTextures(1, &PickupObject.Tex);
  glDeleteTextures(1, &Elevator.Tex);
  glDeleteTextures(1, &Door.Tex);
  glDeleteTextures(1, &Hbl.Tex);
  glDeleteTextures(1, &EnbarTex);
  if( Object.NumSpawns > 0 )
    free(Object.Spawn);
  Object.Spawn = NULL;
  if( Object.NumTeleports > 0 )
    free(Object.Teleport);
  Object.Teleport = NULL;
  if( PickupObject.NumItems > 0 )
    free(PickupObject.Item);
  PickupObject.Item = NULL;
  if( Elevator.NumItems > 0 )
    free(Elevator.Item);
  Elevator.Item = NULL;
  if( Door.NumItems > 0 )
    free(Door.Item);
  Door.Item = NULL;
  if( Hbl.NumItems > 0 )
    free(Hbl.Item);
  Hbl.Item = NULL;
  if( NumExtraMapAnimations > 0 )
    free(ExtraMapAnimation);
  ExtraMapAnimation = NULL;
  Loaded = 0;
}
GLuint *cls_Map::GetGfx(){
  return &Data.Tex_Gfx;
}
GLuint *cls_Map::GetLM(){
  return &Data.Tex_LM;
}
char *cls_Map::GetGfxFile(){
  return Data.File_Tex_Gfx;
}
char *cls_Map::GetColFile(){
  return Data.File_Tex_Col;
}
char *cls_Map::GetLMFile(){
  return Data.File_Tex_LM;
}
StructSurf cls_Map::GetRect(){
  return Data.Rect;
}
bool cls_Map::GetLoaded(){
  return Loaded;
}
char *cls_Map::GetMapName(const char* Filename){
  FILE *fp;
  char dp[32];
  memset(Data.Name,'\0',64);
  if( (fp = fopen(Filename, "r")) == NULL ){
    strcpy(Data.Name,"'NO DATA'");
  } else {
    if( fgets(dp,32,fp) == NULL ){
      strcpy(Data.Name,"'NO DATA'");
    } else {
      strncpy(Data.Name,dp,strlen(dp)-1);
    }
  }
  fclose(fp);
  return Data.Name;
}
int cls_Map::LoadMap(const char *Filename){

  // Create the correct filename extensions
  //strcat(Data.File_Tex_Gfx,"gfx.tga");
  strcpy(Data.File_Tex_Col,"gfx/map/coltiles.tga");
  //strcat(Data.File_Tex_Col,"col.tga");

  // File pointer for reading the mapfile
  FILE *fp;

  // Open mapfile
  if( (fp = fopen(Filename, "r")) == NULL ){
    printf("File Not Found : %s\n",Filename);
    return 1;
  }

  // Temporary variables used for loading data
  char dp[32]; // For text strings
  char tt1[64], tt2[64];
  int x, y; // X and Y position of objects
  int flag1, flag2, flag3; // Object ID and Target ID used for Teleports, Spawns etc

  // Get name of the map
  if( fgets(dp,32,fp) == NULL ) return 1;
  memset(Data.Name,'\0',64);
  strncpy(Data.Name,dp,strlen(dp)-1);

  // Who created the map?
  if( fgets(dp,32,fp) == NULL ) return 1;
  memset(Data.Author,'\0',32);
  strncpy(Data.Author,dp,strlen(dp)-1);

  // Get map width and height
  if( fscanf(fp,"%i",&Data.Width) <= 0 ) return 1;
  if( fscanf(fp,"%i",&Data.Height) <= 0 ) return 1;

  // Set up the surface rectangle
  Data.Rect.Left = 0;
  Data.Rect.Right = Data.Width*32;
  Data.Rect.Top = 0;
  Data.Rect.Bottom = Data.Height*32;

  // Get musical score used for the map
  if( fscanf(fp,"%i",&Data.Music) <= 0 ) return 1;

  // Get map global environment (0 = space, 1 = earth)
  if( fscanf(fp,"%i",&Env) <= 0 ) return 1;
  printf("Environment: %i\n",Env);

  if( fscanf(fp,"%i",&flag1) <= 0 ) return 1;
  printf("Tileset: %i\n\n",flag1);

  sprintf(Data.File_Tex_Gfx,"gfx/map/tiles%i.tga",flag1);

  MAP = (int*) realloc(MAP, sizeof(int)*(Data.Width*Data.Height));
  if( MAP == NULL )
    return 1;
  
  for( y = 0; y < Data.Height; y++ ){
    for( x = 0; x < Data.Width; x++ ){
      if( fscanf(fp,"%2i",&flag1) <= 0 )
        return 1;
      *(MAP+y*Data.Width+x) = flag1;
    }
  }
  //if( fscanf(fp,"%s",dp) <= 0 ) return 1;
  //AC.SetNextMapFile(dp);
  //AC.UpdateMapFile();

  // Start music
  Sound.PlayTune(Data.Music);

  // Load map graphics
  GFX.LoadTexture(GetGfxFile(),GetGfx());
  usleep(10000);
  GFX.LoadTexture(Object.TexFile, &Object.Tex);
  usleep(10000);
  GFX.LoadTexture(PickupObject.TexFile, &PickupObject.Tex);
  usleep(10000);
  GFX.LoadTexture(Elevator.TexFile, &Elevator.Tex);
  usleep(10000);
  GFX.LoadTexture(Door.TexFile, &Door.Tex);
  usleep(10000);
  GFX.LoadTexture(Hbl.TexFile, &Hbl.Tex);
  usleep(10000);
  GFX.LoadTexture(EnbarTexFile, &EnbarTex);
  usleep(10000);

  // Load collision map to memory
  Data.ColmapTmp.Load(GetColFile());
  Data.Colmap = Data.ColmapTmp.GetImg();

  // Reset all objects
  Object.NumSpawns = 0;
  Object.Spawn = NULL;
  Object.NumTeleports = 0;
  Object.Teleport = NULL;
  PickupObject.NumItems = 0;
  PickupObject.Item = NULL;
  Elevator.NumItems = 0;
  Elevator.Item = NULL;
  Door.NumItems = 0;
  Door.Item = NULL;
  Hbl.NumItems = 0;
  Hbl.Item = NULL;
  
  NumExtraMapAnimations = 0;
  ExtraMapAnimation = NULL;
  
  

  // Print out some map information
  printf("%s\n",Data.Name);
  printf("%s\n",Data.Author);
  printf("Size %i x %i = %i x %i\n",Data.Rect.Right,Data.Rect.Bottom,Data.Width,Data.Height);

  int cx, cy;
  float tx, ty;
  char tmpstr[32] = {0};
  cx = Data.Rect.Right/32;
  cy = Data.Rect.Bottom/32;
  tx = 1.0/cx;
  ty = 1.0/cy;
  printf("cx: %i\ncy: %i\ntx: %f\nty: %f\n",cx,cy,tx,ty);

  // Start loading map objects
  printf("Loading Objects...\n");
  while( (fscanf(fp,"%s",dp)) > 0 ){
    if( strcmp(dp, "SPAWN") == 0 ){ // Found Spawn
      printf("Loading SPAWN Object ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("%i located at (%i, %i)\n",Object.NumSpawns,x,y);
      Object.Spawn = (cls_Spawn*) realloc(Object.Spawn, sizeof(cls_Spawn)*(Object.NumSpawns+1));
      if( Object.Spawn == NULL )
        return 1;
      Object.Spawn[Object.NumSpawns].SetSpawn(x,y,0,flag1,flag2);
      Object.NumSpawns++;
    } else if( strcmp(dp, "TELEPORT") == 0 ){ // Found Teleport
      printf("Loading TELEPORT Object ");
      if(fscanf(fp,"%i %i %i %i %i", &x, &y, &flag1, &flag2, &flag3) <= 0)
        return 1;
      printf("%i located at (%i, %i) goes to ID %i. Need key: %i\n",Object.NumTeleports,x,y,flag1,flag2);
      Object.Teleport = (cls_Teleport*) realloc(Object.Teleport, sizeof(cls_Teleport)*(Object.NumTeleports+1));
      if( Object.Teleport == NULL )
        return 1;
      Object.Teleport[Object.NumTeleports].SetTeleport(x,y,0,flag1,flag2,12,flag3); // 12 is the animation length
      Object.NumTeleports++;
    } else if( strcmp(dp, "DISC") == 0 ){ // Found Data Disc
      printf("Loading DISC Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      sprintf(tmpstr,"Disc %i",flag1+1);
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_DISC, tmpstr, flag1, 14, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "LAUNCHER") == 0 ){ // Found Blaster Weapon
      printf("Loading BLASTER Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_LAUNCHER, "Launcher Upgrade", flag1, 13, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "RAILGUN") == 0 ){ // Found Railgun Weapon
      printf("Loading RAILGUN Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_RAILGUN, "Railgun Upgrade", flag1, 9, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "TRAILGUN") == 0 ){ // Found Trailgun Weapon
      printf("Loading TRAILGUN Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_TRAILGUN, "Trailgun Upgrade", flag1, 10, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "CAP") == 0 ){ // Found Capacitor
      printf("Loading CAPACITOR Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_CAPACITOR, "Capacitor Upgrade", flag1, 11, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "SHIELD") == 0 ){ // Found Shield
      printf("Loading SHIELD Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_SHIELD, "Shield", flag1, 2, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "BATTERY") == 0 ){ // Found Battery
      printf("Loading BATTERY Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_BATTERY, "Railgun Battery Power", flag1, 5, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "SLUGS") == 0 ){ // Found Slugs
      printf("Loading SLUGS Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_SLUGS, "Trailgun Plasma Slugs", flag1, 4, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "ARMOR") == 0 ){ // Found Blaster Weapon
      printf("Loading ARMOR Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_ARMOR, "Armor Upgrade", flag1, 8, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "HEALTH") == 0 ){ // Found Blaster Weapon
      printf("Loading HEALTH Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_HEALTH, "Health", flag1, 16, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "GRENADES") == 0 ){ // Found Blaster Weapon
      printf("Loading GRENADES Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_GRENADES, "Launcher Shells", flag1, 6, flag2);
      PickupObject.NumItems++;
    } else if( strcmp(dp, "SENSOR") == 0 ){ // Found Blaster Weapon
      printf("Loading SENSOR Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      PickupObject.Item = (cls_PickupItem*) realloc(PickupObject.Item, sizeof(cls_PickupItem)*(PickupObject.NumItems+1));
      if( PickupObject.Item == NULL )
        return 1;
      PickupObject.Item[PickupObject.NumItems].SetItem(x, y, ITEM_SENSOR, "Heartbeat Sensor", flag1, 7, flag2);
      PickupObject.NumItems++;
      
    } else if( strcmp(dp, "ELEVATOR") == 0 ){ // Found Blaster Weapon
      printf("Loading ELEVATOR Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      Elevator.Item = (cls_Elevator*) realloc(Elevator.Item, sizeof(cls_Elevator)*(Elevator.NumItems+1));
      if( Elevator.Item == NULL )
        return 1;
      Elevator.Item[Elevator.NumItems].SetItem(x, y, flag1, flag2);
      Elevator.NumItems++;
      
    } else if( strcmp(dp, "DOOR") == 0 ){ // Found Blaster Weapon
      printf("Loading DOOR Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      Door.Item = (cls_Door*) realloc(Door.Item, sizeof(cls_Door)*(Door.NumItems+1));
      if( Door.Item == NULL )
        return 1;
      Door.Item[Door.NumItems].SetItem(x, y, flag1);
      Door.NumItems++;
      
    } else if( strcmp(dp, "HBL") == 0 ){ // Found Blaster Weapon
      printf("Loading HBL Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return 1;
      printf("(%i, %i)\n",x,y);
      Hbl.Item = (cls_Hbl*) realloc(Hbl.Item, sizeof(cls_Hbl)*(Hbl.NumItems+1));
      if( Hbl.Item == NULL )
        return 1;
      Hbl.Item[Hbl.NumItems].SetItem(x, y, flag1);
      Hbl.NumItems++;
      
    } else if( strcmp(dp, "EXTRA") == 0 ){ // Extra Animation
      printf("Loading EXTRA animation located at ");
      if(fscanf(fp,"%i %i %s %i %i %i",&x,&y,tt1,&flag1,&flag2,&flag3) <= 0)
        return 1;
      ExtraMapAnimation = (cls_MapExtra*) realloc(ExtraMapAnimation,sizeof(cls_MapExtra)*(NumExtraMapAnimations+1));
      if( ExtraMapAnimation == NULL )
        return 1;
      strcpy(tt2,Filename);
      strcat(tt2,"extgfx/");
      strcat(tt2,tt1);
      printf("(%i, %i), using file: \"%s\"\n",x,y,tt1);
      ExtraMapAnimation[NumExtraMapAnimations].SetMapExtra(x,y,tt2,flag1,flag2,flag3);
      NumExtraMapAnimations++;
    }
    usleep(10000);
  }

  fclose(fp);

  Loaded = 1;

  GUI.OSDMessage(Data.Name,4);
  
  return 0;
}
void cls_Map::ResetMapObjects(){
  int i;

  for( i = 0; i < PickupObject.NumItems; i++ ){
    PickupObject.Item[i].Spawn();
  }
  
  for( i = 0; i < Elevator.NumItems; i++ ){
    Elevator.Item[i].ResetAll();
  }
}
void cls_Map::DrawMapObjects(int pX, int pY){

  int i,x,y,w,h,s,t;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  for( i = 0; i < Object.NumTeleports; i++ ){
    x = Object.Teleport[i].GetX();
    y = Object.Teleport[i].GetY();
    s = Object.Teleport[i].Animation(1);
    
    glLoadIdentity();
    glTranslated(AC.GetHalfW()-pX-16+x,AC.GetHalfH()-pY-16+y,0);
    glBindTexture(GL_TEXTURE_2D,Object.Tex);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0625*s,        0.8125-0.0625); glVertex3f(  0, 32, 0);
      glTexCoord2f(0.0625*s+0.0625, 0.8125-0.0625); glVertex3f( 32, 32, 0);
      glTexCoord2f(0.0625*s+0.0625, 0.8750-0.0625); glVertex3f( 32,  0, 0);
      glTexCoord2f(0.0625*s,        0.8750-0.0625); glVertex3f(  0,  0, 0);
    glEnd();
    
  }

  for( i = 0; i < PickupObject.NumItems; i++ ){
    if( PickupObject.Item[i].IsSpawned() ){
      x = PickupObject.Item[i].GetX();
      y = PickupObject.Item[i].GetY();
      s = PickupObject.Item[i].Animation(1);
      t = 16-PickupObject.Item[i].GetAnimGfx();
      glLoadIdentity();
      glTranslated(AC.GetHalfW()-pX-16+x,AC.GetHalfH()-pY-16+y,0);
      glBindTexture(GL_TEXTURE_2D,PickupObject.Tex);
      glColor4f(1.0f,1.0f,1.0f,1.0f);
      glBegin(GL_QUADS);
        glTexCoord2f(0.125*s,       0.0625*t);        glVertex3f(  0, 32, 0);
        glTexCoord2f(0.125*s+0.125, 0.0625*t);        glVertex3f( 32, 32, 0);
        glTexCoord2f(0.125*s+0.125, 0.0625*t+0.0625); glVertex3f( 32,  0, 0);
        glTexCoord2f(0.125*s,       0.0625*t+0.0625); glVertex3f(  0,  0, 0);
      glEnd();
    } else {
      PickupObject.Item[i].CountSpawnTime();
    }
  }
  
  for( i = 0; i < Elevator.NumItems; i++ ){
    x = Elevator.Item[i].GetX();
    y = Elevator.Item[i].GetY();
    s = Elevator.Item[i].Animation(0);
    glLoadIdentity();
    glTranslated(AC.GetHalfW()-pX-16+x,AC.GetHalfH()-pY-16+y,0);
    glBindTexture(GL_TEXTURE_2D,Elevator.Tex);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(0.25*s,      0); glVertex3f(  0, 32, 0);
      glTexCoord2f(0.25*s+0.25, 0); glVertex3f( 32, 32, 0);
      glTexCoord2f(0.25*s+0.25, 1); glVertex3f( 32,  0, 0);
      glTexCoord2f(0.25*s,      1); glVertex3f(  0,  0, 0);
    glEnd();
  }
  
  for( i = 0; i < Door.NumItems; i++ ){
    x = Door.Item[i].GetX();
    y = Door.Item[i].GetY();
    s = Door.Item[i].Animation(1);
    t = 3-Door.Item[i].GetState();
    glLoadIdentity();
    glTranslated(AC.GetHalfW()-pX-16+x,AC.GetHalfH()-pY-16+y,0);
    glBindTexture(GL_TEXTURE_2D,Door.Tex);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(0.125*s,       0.25*t);      glVertex3f(  0, 32, 0);
      glTexCoord2f(0.125*s+0.125, 0.25*t);      glVertex3f( 32, 32, 0);
      glTexCoord2f(0.125*s+0.125, 0.25*t+0.25); glVertex3f( 32,  0, 0);
      glTexCoord2f(0.125*s,       0.25*t+0.25); glVertex3f(  0,  0, 0);
    glEnd();
  }
  
  for( i = 0; i < Hbl.NumItems; i++ ){
    if( Hbl.Item[i].IsSpawned() ){
      x = Hbl.Item[i].GetX();
      y = Hbl.Item[i].GetY();
      s = Hbl.Item[i].Animation(0);
      t = 1-Hbl.Item[i].GetState();
      glLoadIdentity();
      glTranslated(AC.GetHalfW()-pX-16+x,AC.GetHalfH()-pY-16+y,0);
      glBindTexture(GL_TEXTURE_2D,Hbl.Tex);
      glColor4f(1.0f,1.0f,1.0f,1.0f);
      glBegin(GL_QUADS);
        glTexCoord2f(0.125*s,       0.5*t);     glVertex3f(  0, 32, 0);
        glTexCoord2f(0.125*s+0.125, 0.5*t);     glVertex3f( 32, 32, 0);
        glTexCoord2f(0.125*s+0.125, 0.5*t+0.5); glVertex3f( 32,  0, 0);
        glTexCoord2f(0.125*s,       0.5*t+0.5); glVertex3f(  0,  0, 0);
      glEnd();
    } else {
      Hbl.Item[i].CountSpawnTime();
    }
  }

  for( i = 0; i < NumExtraMapAnimations; i++ ){
    
      x = ExtraMapAnimation[i].GetX();
      y = ExtraMapAnimation[i].GetY();
      
      w = ExtraMapAnimation[i].GetW();
      h = ExtraMapAnimation[i].GetH();

      t = ExtraMapAnimation[i].GetAlen();
      s = ExtraMapAnimation[i].Animation(1);

      float surfw = 1.0/t;
      
      glLoadIdentity();
      glTranslated(AC.GetHalfW()-pX-16+x,AC.GetHalfH()-pY-16+y,0);
      glBindTexture(GL_TEXTURE_2D,ExtraMapAnimation[i].GetTexture());
      glColor4f(1.0f,1.0f,1.0f,1.0f);
      glBegin(GL_QUADS);
        glTexCoord2f(s*surfw,       0.0); glVertex3f( 0, h, 0);
        glTexCoord2f(s*surfw+surfw, 0.0); glVertex3f( w, h, 0);
        glTexCoord2f(s*surfw+surfw, 1.0); glVertex3f( w, 0, 0);
        glTexCoord2f(s*surfw,       1.0); glVertex3f( 0, 0, 0);
      glEnd();

  }

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
 

}

void cls_Map::DrawMap(int x, int y){
  float tx, ty;
  int j,k,px,py,c;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, Data.Tex_Gfx);
  //glDisable(GL_TEXTURE_2D);
  //glDisable(GL_LIGHTING);

  // x = AC.GetHalfW()-px-16
  // px = AC.GHW - x - 16
  // y = AC.GetHalfH()-py-16

  for( j = 0; j < Data.Width; j++ ){
    for( k = 0; k < Data.Height; k++ ){
      px = j*32;
      py = k*32;
      if( px > AC.GetHalfW()-x-32-320 && px < AC.GetHalfW()-x+320 ){
        if( py > AC.GetHalfH()-y-32-200 && py < AC.GetHalfH()-y+200 ){
          c = *(MAP+k*Data.Width+j);
          tx = (float) GetTileX(c)*0.125;
          ty = (float) GetTileY(c)*0.125;
          if( c > 0 ){
            glLoadIdentity();
            glTranslated(320+px+x-AC.GetHalfW(),200+py+y-AC.GetHalfH(),0);
            glColor4f(1.0f,1.0f,1.0f,1.0f);
            glBegin(GL_QUADS);
            glTexCoord2f(tx,    (1-ty)-0.125); glVertex3f( 0,  32, 0);
            glTexCoord2f(tx+0.125, (1-ty)-0.125); glVertex3f( 32, 32, 0);
            glTexCoord2f(tx+0.125,  1-ty);     glVertex3f( 32, 0,    0);
            glTexCoord2f(tx,     1-ty);     glVertex3f( 0,  0,    0);
            glEnd();
          }
        }
      }
    }
  }
  //glEnable(GL_LIGHTING);
  //glEnable(GL_TEXTURE_2D);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

/*
void cls_Map::DrawMap(int x, int y){

  int cx, cy;
  float tx, ty;

  int res = 32;
  
  cx = Data.Rect.Right/res;
  cy = Data.Rect.Bottom/res;
  tx = 1.0/res;
  ty = 1.0/res;

  int j,k;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslated(x,y,0);
  glBindTexture(GL_TEXTURE_2D, Data.Tex_Gfx);
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  for( k = 0; k < cy; k++ ){
    for( j = 0; j < cx; j++ ){
      glBegin(GL_QUADS);
        glTexCoord2f(tx*j,    (1-ty)-k*ty); glVertex3f( cx*j,    cy*k+cy, 0);
        glTexCoord2f(tx*j+tx, (1-ty)-k*ty); glVertex3f( cx*j+cx, cy*k+cy, 0);
        glTexCoord2f(tx*j+tx,  1-ty*k);     glVertex3f( cx*j+cx, cy*k,    0);
        glTexCoord2f(tx*j,     1-ty*k);     glVertex3f( cx*j,    cy*k,    0);
      glEnd();
    }
  }
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

}
*/


cls_Map Map;


#endif

