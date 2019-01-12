
#include "global.h"
#include "player.h"

#define Max 4
#define HMax 1.5

#define HITDMG 30


typedef enum
{
    Player_Team_Red,
    Player_Team_Blue,
    Player_Team_Yellow,
    Player_Team_Green,
} Player_Team_t;

typedef enum
{
    Player_JumpStrength_Environment0 = -9,
    Player_JumpStrength_Environment1 = -8,
    Player_JumpStrength_Environment2 = -7,
} Player_JumpStrength_t;

typedef enum
{
    Player_Animation_Standing,              /* Standing, first row in animation board */
    Player_Animation_Running,               /* Running, second row in animation board */
    Player_Animation_Firing,                /* Standing still and firing */
    Player_Animation_FiringRunning,         /* Running and firing */
    Player_Animation_FiringRunningBack,     /* Running backwards and firing (not used for the moment) */
    Player_Animation_JumpAssist,            /* Using jump assist */
    Player_Animation_InTheAir,              /* Flying in the air (or falling) */
    Player_Animation_FiringInTheAir,        /* Firing in the air (or falling + firing) */
    Player_Animation_AirShaft,              /* Using the airshaft (flaps) */
    Player_Animation_Jumping,               /* Jumping */
    Player_Animation_JumpingAndRunning,     /* Jumping when running */
    Player_Animation_JumpingAndRunningBack, /* Jumping when running backwards (not used) */
    Player_Animation_Crouching,             /* Crouching */
    Player_Animation_Crawling,              /* Crawling */
} Player_Animation_t;

typedef enum
{
    Player_State_OnTheGround,
    Player_State_InTheAir,
    Player_State_Crouching,
    Player_State_Freeze,
    Player_State_Jetpack,
    Player_State_Firing,
    Player_State_Dead,
} Player_State_t;

typedef enum
{
    Player_Move_Stop,
    Player_Move_Left,
    Player_Move_Right,
    Player_Move_Up,
    Player_Move_Down,
} Player_Move_t;

#define WALL_GRAV_DEC 64
#define SPEED_CHANGE_COEFF 32

#define CHAR_ITEM_NUMBER_OF_DISCS 4

void cls_Character::Jet(bool enable)
{
    if (enable)
    {
        Physics.Jet = 1;
    }
    else
    {
        Physics.Jet = 0;
        Physics.Speed.SpeedJet = 0;
    }
}

void cls_Character::ControlElevator(int Operate)
{
    OperateElevator = Operate;
}

bool cls_Character::GotDiscInv(int N)
{
    if (N < 0)
    {
        return (0);
    }
    else if (N >= 4)
    {
        return (0);
    }

    return Items.GotDisk[N];
}

bool cls_Character::GotItemInv(int N)
{
    switch (N)
    {
        case ITEM_SENSOR:
            return Items.HeartSensor;
    }
    return (0);
}

int cls_Character::GetWeaponSel()
{
    return SelectedWeapon;
}

bool cls_Character::GotWeaponInv(int N)
{
    return GotWeapon[N];
}

GLuint* cls_Character::GetTex()
{
    return &Tex;
}

void cls_Character::SetCharEnv(int Env)
{
    if (0 == Env)
    {
        Physics.Speed.YMin = Player_JumpStrength_Environment0;
    }
    else if (1 == Env)
    {
        Physics.Speed.YMin = Player_JumpStrength_Environment1;
    }
    else if (2 == Env)
    {
        Physics.Speed.YMin = Player_JumpStrength_Environment2;
    }
}

void cls_Character::Crouch(bool On)
{
    if (On)
    {
        Physics.State = CHAR_CROUCHING;
        SetAnimation(CHAR_ANIMATION_CROUCHING,1,0,0,0,Animation.ReverseFlag);
    }
    else
    {
        Physics.State = CHAR_IN_THE_AIR; // To prevent crouch->jump abuse.
        SetAnimation(CHAR_ANIMATION_IN_THE_AIR,1,0,0,0,Animation.ReverseFlag);
    }
}

float cls_Character::GetHealth()
{
    const float k = (float) Status.Health/Status.HealthMax;
    return (k);
}

float cls_Character::GetArmor()
{
    const float k = (float) Status.Armor/Status.ArmorMax;
    return (k);
}

float cls_Character::GetAmmo(){//char *AmmoName){
  //strcpy(AmmoName,Weapon[SelectedWeapon].GetAmmoName());
  return Weapon[SelectedWeapon].GetAmmoPercentage();//SetAmmo(0);
}

char *cls_Character::GetFilename(){
  return Filename;
}
void cls_Character::BuildAnimations(){
  if( !TextureLoaded )
    GFX.LoadTexture(GetFilename(),GetTex());
}
void cls_Character::KillTexture(){
  if( TextureLoaded )
    glDeleteTextures(1,&Tex);
}
void cls_Character::DrawPlayer(){

  Weapon[SelectedWeapon].ParticlePhysics(Physics.Position.X,Physics.Position.Y);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslated(AC.GetHalfW()-16,AC.GetHalfH()-16,0);
  glBindTexture(GL_TEXTURE_2D,Tex);
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  if( Animation.ReverseFlag ){
    glTexCoord2f(Animation.Position*0.0625+0.0625, 1-0.0625-Animation.AnimationState*0.0625); glVertex3f(  0, 32, 0);
    glTexCoord2f(Animation.Position*0.0625,     1-0.0625-Animation.AnimationState*0.0625); glVertex3f( 32, 32, 0);
    glTexCoord2f(Animation.Position*0.0625,     1.0-Animation.AnimationState*0.0625); glVertex3f( 32,  0, 0);
    glTexCoord2f(Animation.Position*0.0625+0.0625, 1.0-Animation.AnimationState*0.0625); glVertex3f(  0,  0, 0);
  } else {
    glTexCoord2f(Animation.Position*0.0625,     1-0.0625-Animation.AnimationState*0.0625); glVertex3f(  0, 32, 0);
    glTexCoord2f(Animation.Position*0.0625+0.0625, 1-0.0625-Animation.AnimationState*0.0625); glVertex3f( 32, 32, 0);
    glTexCoord2f(Animation.Position*0.0625+0.0625, 1.0-Animation.AnimationState*0.0625); glVertex3f( 32,  0, 0);
    glTexCoord2f(Animation.Position*0.0625,     1.0-Animation.AnimationState*0.0625); glVertex3f(  0,  0, 0);
  }
  glEnd();

//  char tmp[64];
//  sprintf(tmp,"A:%3.2f, X:%3.2f, Y:%3.2f",Physics.Speed.Angle,Physics.Speed.XSpeed,Physics.Speed.YSpeed);
//  GUI.OSDMessage(tmp,1);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();



}


cls_Character::cls_Character(){
  // About
  SetName("Player 1");
  SetTeam(1,"Human");
  SetAnimation(CHAR_ANIMATION_STANDING,6,0,0,0,0);
  SetCrosshair(0);
  Physics.Position.X = 0;
  Physics.Position.Y = 0;
  Physics.Speed.XMax = 5;
  Physics.Speed.XSpeedTarget = 0;
  Physics.Speed.YSpeedTarget = 0;
  Physics.Speed.YMax = 5;
  Physics.Speed.YMaxDmg = 10;
  Physics.Speed.YMin = -8; // Jumping Strength
  SelectedWeapon = 0;
  Weapon[WEAPON_TYPE_BLASTER].DefineWeapon(WEAPON_TYPE_BLASTER,1);
  Weapon[WEAPON_TYPE_GRENADES].DefineWeapon(WEAPON_TYPE_GRENADES,0);
  Weapon[WEAPON_TYPE_RAILGUN].DefineWeapon(WEAPON_TYPE_RAILGUN,0);
  Weapon[WEAPON_TYPE_TRAILGUN].DefineWeapon(WEAPON_TYPE_TRAILGUN,0);
  GotWeapon[WEAPON_TYPE_BLASTER] = 1;
  GotWeapon[WEAPON_TYPE_GRENADES] = 0;
  GotWeapon[WEAPON_TYPE_RAILGUN] = 0;
  GotWeapon[WEAPON_TYPE_TRAILGUN] = 0;
  SetItem(0,0,0);
  SetItem(1,0,0);
  SetItem(2,0,1);
  SetItem(4,0,0); // SHIELD
  TextureLoaded = 0;
  strcpy(Filename,"gfx/models/character0.tga");
  CanEnterTerminal = 0;
  ActiveTerminalID = 0;
  int i;
  for( i = 0; i < CHAR_ITEM_NUMBER_OF_DISCS; i++ ){
    SetItem(3,i,0);
  }

}
void cls_Character::SetItem(int Item, int Index, bool Val){
  switch( Item ){
    case 0: // HS
      Items.HeartSensor = Val;
      break;
    case 1: // CAP
      Items.Capacitor = Val;
      break;
    case 2: // SUIT
      Items.GotSuit = Val;
      break;
    case 3:
      if( Index >= 0 && Index < CHAR_ITEM_NUMBER_OF_DISCS)
        Items.GotDisk[Index] = Val;
      break;
    case 4:
      Items.Shield = Val;
      break;
  }
}
void cls_Character::SetName(const char *Name)
{
  strcpy(About.Name,Name);
}
const char *cls_Character::GetName(){
  return About.Name;
}
void cls_Character::SetTeam(int TeamNo, const char *TeamName){
  strcpy(About.TeamName,TeamName);
  About.Team = TeamNo;
}
const char *cls_Character::GetTeamName(){
  return About.TeamName;
}
int cls_Character::GetTeamNo(){
  return About.Team;
}
void cls_Character::SetAnimation(int NewState, int Length, int Menu, int Model, int Position, bool ReverseFlag){

  Animation.AnimationState = NewState;
  Animation.Length = Length;
  Animation.Menu = Menu;
  Animation.Model = Model;
  Animation.Position = Position;
  Animation.ReverseFlag = ReverseFlag;
  Animation.PosInc = 0;
}
void cls_Character::StepAnimationFrame(bool Backward){
  return;
  Animation.PosInc+=0.3;

  if( Animation.PosInc > 1 ){
    if( Backward ){
      Animation.Position--;
      if( Animation.Position < 0 )
        Animation.Position = Animation.Length-1;
    } else {
      if( Animation.AnimationState == CHAR_ANIMATION_FIRING && Physics.Speed.XSpeed != 0 ){
        Animation.AnimationState = CHAR_ANIMATION_FIRING_RUNNING;
      }
      if( Animation.AnimationState == CHAR_ANIMATION_FIRING_RUNNING && Physics.Speed.XSpeed == 0 ){
        Animation.AnimationState = CHAR_ANIMATION_FIRING;
      }
      Animation.Position++;
      if( Animation.Position > Animation.Length-1 ){
        Animation.Position = 0;
        if( Animation.AnimationState == CHAR_ANIMATION_FIRING ){
          if( Physics.Speed.XSpeed != 0 ){
            SetAnimation(CHAR_ANIMATION_RUNNING,8,0,0,0,Animation.ReverseFlag);
          } else {
            SetAnimation(CHAR_ANIMATION_STANDING,6,0,0,0,Animation.ReverseFlag);
          }
        }
        if( Animation.AnimationState == CHAR_ANIMATION_FIRING_RUNNING ){
          if( Physics.Speed.XSpeed != 0 ){
            SetAnimation(CHAR_ANIMATION_RUNNING,8,0,0,0,Animation.ReverseFlag);
          } else {
            SetAnimation(CHAR_ANIMATION_STANDING,6,0,0,0,Animation.ReverseFlag);
          }
        }
      }
    }
    Animation.PosInc = 0;
  }

}
void cls_Character::SetStatus(int Health, int HealthMax, int Armor, int ArmorMax, int Frags, int Deaths, int SpawnTime){
  Status.Armor = Armor;
  Status.ArmorMax = ArmorMax;
  Status.Frags = Frags;
  Status.Deaths = Deaths;
  Status.Health = Health;
  Status.HealthMax = HealthMax;
  Status.SpawnTime = SpawnTime;
}
void cls_Character::ChangeHealth(int Change){
  if( Change < 0 ){
    Sound.PlaySfx(SFX_HIT);
    if( Status.Armor > 0 ){
      Status.Armor += (Change/2);
      if( Status.Armor < 0 ){
        Status.Health += (Change/4);
        Status.Armor = 0;
      } else {
        Status.Health += (Change/8);
      }
    } else {
      Status.Health += Change;
    }
  } else {
    Status.Health += Change;
  }
  if( Status.Health > Status.HealthMax )
    Status.Health = Status.HealthMax;
  if( Status.Health < 0 )
    Status.Health = 0;
}
void cls_Character::SetCrosshair(int Crosshair){
  Settings.Crosshair = Crosshair;
  Settings.CrosshairAnimation = 0;
}
void cls_Character::SpawnPlayer(bool KeepPowerups){

  int X, Y, id;

  if( Map.GetNumSpawns() < 1 ){
    X = 0;
    Y = 0;
  } else {
    id = rand()%(Map.GetNumSpawns());
    X = Map.GetSpawnX(id);
    Y = Map.GetSpawnY(id);
  }

  SetCharEnv(Map.GetMapEnv());
  Physics.Position.X = X;
  Physics.Position.Y = Y;
  Physics.Speed.XSpeed = 0;
  Physics.Speed.YSpeed = -3;
  Physics.Speed.Angle = 4;
  Items.Shield = 0;
  Items.GotSuit = 0;
  Items.GotDisk[0] = 0;
  Items.GotDisk[1] = 0;
  Items.GotDisk[2] = 0;
  Items.GotDisk[3] = 0;

  Physics.Speed.SpeedJet = 0;
  Physics.Jet = 0;

  Animation.AnimationState = 0;

  OperateElevator = 0;

  if( !KeepPowerups ){
    Map.ResetMapObjects();
    GotWeapon[WEAPON_TYPE_BLASTER] =  1;
    GotWeapon[WEAPON_TYPE_GRENADES] = 0;
    GotWeapon[WEAPON_TYPE_RAILGUN] =  0;
    GotWeapon[WEAPON_TYPE_TRAILGUN] = 0;
    SelectedWeapon = 0;
    Items.HeartSensor = 0;
    Weapon[WEAPON_TYPE_RAILGUN].SetMaxAmmo(100);
    Items.Capacitor = 0;
  }

  if( Status.Health <= 0 )
    SetStatus(50,100,0,100,0,0,3);
  Physics.State = CHAR_ON_THE_GROUND;


    Sound.PlaySfx(SFX_SPAWN);

}
void cls_Character::PrintDebugInfo(){
  printf("Character Information:\n");
  printf("Name: %s\n",GetName());
  printf("Team %i: %s\n",GetTeamNo(),GetTeamName());
  printf("Animation: %i\n",Animation.AnimationState);
}
int cls_Character::GetPosX(){
  return Physics.Position.X;
}
void cls_Character::SetSpeedX(int RelIncX){
  Physics.Speed.XSpeed = RelIncX;
}
int cls_Character::GetPosY(){
  return Physics.Position.Y;
}
void cls_Character::SetSpeedY(int RelIncY){
  Physics.Speed.YSpeed = RelIncY;
}
void cls_Character::Jump(int MF){
  switch( MF ){
    case CHAR_MOVE_STOP:
      Physics.Speed.SpeedJet = -0.5;
      break;
    case CHAR_MOVE_UP:
      Physics.Speed.SpeedJet = 3;
      break;
    default:
      Physics.Speed.SpeedJet = -0.5;
      break;
  }
}
void cls_Character::Move(int MF){
  switch( MF ){
    case CHAR_MOVE_STOP:
      Physics.Speed.AngleChange = 0;
      break;
    case CHAR_MOVE_LEFT:
      Physics.Speed.AngleChange = 0.25;

      //Animation.ReverseFlag = 1;
      break;
    case CHAR_MOVE_RIGHT:
      Physics.Speed.AngleChange = -0.25;
      //Animation.ReverseFlag = 0;
      break;
    default:
      Physics.Speed.AngleChange = 0;
      break;
  }
}
void cls_Character::Fire(){
  if( GotWeapon[SelectedWeapon] == 0 )
    return;
  if( (Weapon[SelectedWeapon].GetSetAmmo(0) > 0) || (SelectedWeapon == 0) ){
    Weapon[SelectedWeapon].Fire(Physics.Position.X,Physics.Position.Y,Physics.Speed.Angle);
    Weapon[SelectedWeapon].GetSetAmmo(1);
    Sound.PlaySfx(SFX_FIRE);
  } else {
    SwitchWeapon(1);
  }
}
void cls_Character::SwitchWeapon(bool Prev){
  if( Prev ){
    SelectedWeapon--;
    if( SelectedWeapon < 0 )
      SelectedWeapon = 4;
    while(GotWeapon[SelectedWeapon] <= 0 ){
      SelectedWeapon--;
      if( SelectedWeapon <= 0 ){
        SelectedWeapon = 0;
        break;
      }
    }
  } else {
    SelectedWeapon++;
    if( SelectedWeapon >= 4 )
      SelectedWeapon = 0;
    while(GotWeapon[SelectedWeapon] <= 0 ){
      SelectedWeapon++;
      if( SelectedWeapon >= 4 ){
        SelectedWeapon = 0;
        break;
      }
    }
  }
}
void cls_Character::PerformPhysics(){

  Physics.Speed.Angle += Physics.Speed.AngleChange;
  if( Physics.Speed.Angle > 15 )
    Physics.Speed.Angle = 0;
  if( Physics.Speed.Angle < 0 )
    Physics.Speed.Angle = 15;

  Animation.Position = round(Physics.Speed.Angle);

  Physics.Speed.ASpeed += Physics.Speed.SpeedJet;
  if( Physics.Speed.ASpeed > 3 ){
    Physics.Speed.ASpeed = 3;
    Physics.Speed.SpeedJet = 0;
  }
  if( Physics.Speed.ASpeed < 0 ){
    Physics.Speed.ASpeed = 0;
    Physics.Speed.SpeedJet = 0;
  }

  Animation.AnimationState = round(Physics.Speed.ASpeed);

//  float gx = 0;
//  float gy = 0;
//  for( int x = Physics.Position.X+16; x < Physics.Position.X+48; x++ ){
//    if( Map.GetCol(x,Physics.Position.Y+16) > 1 ){
//      gx += (x-Physics.Position.X+16)/WALL_GRAV_DEC;
//      break;
//    }
//  }
//  for( int x = Physics.Position.X-16; x < Physics.Position.X+16; x++ ){
//    if( Map.GetCol(x,Physics.Position.Y+16) > 1 ){
//      gx += (x-Physics.Position.X+16)/WALL_GRAV_DEC;
//      break;
//    }
//  }
//  for( int y = Physics.Position.Y+16; y < Physics.Position.Y+48; y++ ){
//    if( Map.GetCol(Physics.Position.X+16,y) > 1 ){
//      gy += (y-Physics.Position.Y+16)/WALL_GRAV_DEC;
//      break;
//    }
//  }
//  for( int y = Physics.Position.Y-16; y < Physics.Position.Y+16; y++ ){
//    if( Map.GetCol(Physics.Position.X+16,y) > 1 ){
//      gy += (y-Physics.Position.Y+16)/WALL_GRAV_DEC;
//      break;
//    }
//  }


  Physics.Speed.XSpeedTarget = cos(round(Physics.Speed.Angle)*(2*pi)/16)*Physics.Speed.ASpeed;
  Physics.Speed.XSpeed += Physics.Speed.XSpeedTarget/SPEED_CHANGE_COEFF;
//  Physics.Speed.XSpeed += gx;
  Physics.Speed.YSpeedTarget = sin(round(Physics.Speed.Angle)*(2*pi)/16)*Physics.Speed.ASpeed;
  Physics.Speed.YSpeed -= Physics.Speed.YSpeedTarget/SPEED_CHANGE_COEFF;

  Physics.Speed.YSpeed += 0.025;

//  Physics.Speed.YSpeed += gy;

  //Physics.Speed.XSpeed = Physics.Speed.XSpeed + ((Physics.Speed.XSpeedTarget));//-Physics.Speed.XSpeed)/4);
  //Physics.Speed.YSpeed = Physics.Speed.YSpeed + ((Physics.Speed.YSpeedTarget));//-Physics.Speed.YSpeed));

  if( Physics.Speed.XSpeed < -Max )
    Physics.Speed.XSpeed = -Max;
  if( Physics.Speed.YSpeed < -Max )
    Physics.Speed.YSpeed = -Max;
  if( Physics.Speed.XSpeed > Max )
    Physics.Speed.XSpeed = Max;
  if( Physics.Speed.YSpeed > Max )
    Physics.Speed.YSpeed = Max;

  int cw,ch,cw8,i,tmp;
  cw = 32;
  ch = 32;
  cw8 = cw/8;



  float x, y;
  x = Physics.Position.X + Physics.Speed.XSpeed;
  y = Physics.Position.Y + Physics.Speed.YSpeed;

  StructSurf MapRect = Map.GetRect();

  // Check if character is outside map, than respawn!
  if( x <= 16 || x+cw >= (MapRect.Right-16) || y <= 16 || y+ch >= (MapRect.Bottom-16) ){
    ChangeHealth(-666);
    SpawnPlayer(0);
    return;
  }




  // ===================================================================
  // Check for left right side collision with walls
  // ===================================================================
  if( Physics.Speed.XSpeed < 0 ){
    while( Map.GetCol(x+cw8,y+ch/2) > 1 ){
      if( abs(Physics.Speed.XSpeed) > HMax )
        ChangeHealth(-(HITDMG*(abs(Physics.Speed.XSpeed)-HMax)));
      x++;
      Physics.Speed.XSpeed = -Physics.Speed.XSpeed/4;
    }
  } else if( Physics.Speed.XSpeed > 0 ) {
    while( Map.GetCol(x+cw-cw8,y+ch/2) > 1 ){
      if( abs(Physics.Speed.XSpeed) > HMax )
        ChangeHealth(-(HITDMG*(abs(Physics.Speed.XSpeed)-HMax)));
      x--;
      Physics.Speed.XSpeed = -Physics.Speed.XSpeed/4;
    }
  }



  // ===================================================================
  // Check for feet collision with walls
  // ===================================================================
  while( Map.GetCol(x+cw8,y+ch-cw8) > 1 || Map.GetCol(x+cw-cw8,y+ch-cw8) > 1 || Map.GetCol(x+cw/2,y+ch-cw8) > 1 ){
    y--;
    if( abs(Physics.Speed.YSpeed) > HMax )
        ChangeHealth(-(HITDMG*(abs(Physics.Speed.YSpeed)-HMax)));
    Physics.State = CHAR_ON_THE_GROUND;
    /*if( Physics.Speed.YSpeed > Physics.Speed.YMaxDmg ){
      ChangeHealth(-(5*(Physics.Speed.YSpeed - Physics.Speed.YMaxDmg)));
    }*/
    Physics.Speed.YSpeed = -(Physics.Speed.YSpeed/4);
  }
  // ===================================================================
  // Check for head left collision with walls
  // ===================================================================
  while( Map.GetCol(x+cw8,y+cw8) > 1 || Map.GetCol(x+cw-cw8,y+cw8) > 1 || Map.GetCol(x+cw/2,y+cw8) > 1 ){
    y++;
    if( abs(Physics.Speed.YSpeed) > HMax )
        ChangeHealth(-(HITDMG*(abs(Physics.Speed.YSpeed)-HMax)));
    Physics.State = CHAR_ON_THE_GROUND;
    Physics.Speed.YSpeed = -(Physics.Speed.YSpeed/4);
  }
  // ===================================================================
  // DONE WITH WALL CHECKS
  // ===================================================================




  // Update character position!
  Physics.Position.X = x;
  Physics.Position.Y = y;

  // ===================================================================
  // Check for collision with pickup objects
  // ===================================================================
  for( i = 0; i < Map.GetNumItems(); i++ ){
    if( x+cw/2 > Map.GetItemX(i) && x+cw/2 < Map.GetItemX(i)+cw && y+ch/2 > Map.GetItemY(i) && y+ch/2 < Map.GetItemY(i)+ch ){
      // On item location!
        if( Map.GetPickupItemSpawned(i) ){
          switch( Map.PickupItem(i) ){
            case ITEM_DISC:
              tmp = Map.GetPickupItemValue(i);
              if( tmp >= 0 && tmp < 4 ){
                Items.GotDisk[tmp] = 1;
              }
              break;
            case ITEM_CAPACITOR:
              Items.Capacitor = 1;
              Weapon[WEAPON_TYPE_RAILGUN].SetMaxAmmo(200);
              break;
            case ITEM_SHIELD:
              Items.Shield = 1;
              break;
            case ITEM_SENSOR:
              Items.HeartSensor = 1;
              break;
            case ITEM_LAUNCHER:
              Weapon[WEAPON_TYPE_GRENADES].AddAmmo(Map.GetPickupItemValue(i)); // Add some ammo.
              GotWeapon[WEAPON_TYPE_GRENADES] = 1; // Yes, the weapon is in inventory now.
              SelectedWeapon = WEAPON_TYPE_GRENADES;
              break;
            case ITEM_RAILGUN:
              Weapon[WEAPON_TYPE_RAILGUN].AddAmmo(Map.GetPickupItemValue(i)); // Add some ammo.
              GotWeapon[WEAPON_TYPE_RAILGUN] = 1; // Yes, the weapon is in inventory now.
              SelectedWeapon = WEAPON_TYPE_RAILGUN;
              break;
            case ITEM_TRAILGUN:
              Weapon[WEAPON_TYPE_TRAILGUN].AddAmmo(Map.GetPickupItemValue(i)); // Add some ammo.
              GotWeapon[WEAPON_TYPE_TRAILGUN] = 1; // Yes, the weapon is in inventory now.
              SelectedWeapon = WEAPON_TYPE_TRAILGUN;
              break;
            case ITEM_ARMOR:
              Status.Armor += Map.GetPickupItemValue(i);
              if( Status.Armor > Status.ArmorMax )
                Status.Armor = Status.ArmorMax;
              break;
            case ITEM_BATTERY:
              Weapon[WEAPON_TYPE_RAILGUN].AddAmmo(Map.GetPickupItemValue(i));
              break;
            case ITEM_SLUGS:
              Weapon[WEAPON_TYPE_TRAILGUN].AddAmmo(Map.GetPickupItemValue(i));
              break;
            case ITEM_GRENADES:
              Weapon[WEAPON_TYPE_GRENADES].AddAmmo(Map.GetPickupItemValue(i));
              break;
            case ITEM_HEALTH:
              ChangeHealth(Map.GetPickupItemValue(i));
              break;
            default:
              break;
          }
      }
    }
  }

  if( Status.Health <= 0 )
    SpawnPlayer(0);



}

cls_Character Player;

#endif
