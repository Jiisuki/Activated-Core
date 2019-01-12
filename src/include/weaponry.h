/* 
 * File:   weaponry.h
 * Author: nadlun-5
 *
 * Created on 12 June 2010, 19:13
 */

#define WEAPON_TYPE_BLASTER  0
#define WEAPON_TYPE_GRENADES 1
#define WEAPON_TYPE_TRAILGUN 2
#define WEAPON_TYPE_RAILGUN  3


class cls_Weapon{
private:
  int Ammo;
  int AmmoMax;
  int AmmoCost;
  int Power;
  char Name[32];
  char AmmoName[32];
  int Type;
  struct StructParticles{
    int x;
    int y;
    int xs;
    int ys;
    int t0;
    int t1;
    int life;
    int spread;
    int size;
  } Particles[128];
  float clr[3];
  int NumParticles;
public:
  cls_Weapon();
  void DefineWeapon(int dType, int dAmmo);
  int GetSetAmmo(bool ReduceByCost);
  void AddAmmo(int aAmmo);
  char *GetAmmoName();
  void Fire(int x, int y, float angle);
  void ParticlePhysics(int x, int y);
  float GetAmmoPercentage();
  void SetMaxAmmo(int dAmmo);
};
void cls_Weapon::SetMaxAmmo(int dAmmo){
  AmmoMax = dAmmo;
  if( Ammo > AmmoMax )
    Ammo = AmmoMax;
}
float cls_Weapon::GetAmmoPercentage(){
  float k;
  k = (float) Ammo/AmmoMax;
  return k;
}

cls_Weapon::cls_Weapon(){
  Ammo = 0;
  AmmoMax = 0;
  Power = 0;
  memset(Name,'\0',32);
  Type = WEAPON_TYPE_BLASTER;
}

void cls_Weapon::DefineWeapon(int dType, int dAmmo){
  Type = dType;
  Ammo = dAmmo;
  switch( Type ){
    case WEAPON_TYPE_BLASTER:
      AmmoMax = 1;
      AmmoCost = 0; // Unlimited Ammo
      Power = 1;
      strcpy(Name,"Blaster");
      strcpy(AmmoName,"Infinity");
      break;
    case WEAPON_TYPE_GRENADES:
      AmmoMax = 100;
      AmmoCost = 1;
      Power = 2;
      strcpy(Name,"Launcher");
      strcpy(AmmoName,"Shells");
      break;
    case WEAPON_TYPE_RAILGUN:
      AmmoMax = 100;
      AmmoCost = 10;
      Power = 10; // 48 particles
      strcpy(Name,"Railgun");
      strcpy(AmmoName,"Battery");
      break;
    case WEAPON_TYPE_TRAILGUN:
      AmmoMax = 100;
      AmmoCost = 5;
      Power = 4; // 64 particles
      strcpy(Name,"Trailgun");
      strcpy(AmmoName,"Plasma Slugs");
      break;
    default:
      AmmoMax = 1;
      AmmoCost = 0; // Unlimited Ammo
      Power = 1;
      strcpy(Name,"Blaster");
      strcpy(AmmoName,"Infinity");
      break;
  }
}

int cls_Weapon::GetSetAmmo(bool ReduceByCost){
  if( ReduceByCost ){
    Ammo -= AmmoCost;
    if( Ammo < 0 ){
      Ammo = 0;
    }
  }
  return Ammo;
}

void cls_Weapon::AddAmmo(int aAmmo){
  Ammo += aAmmo;
  if( Ammo > AmmoMax ){
    Ammo = AmmoMax;
  }
}

char *cls_Weapon::GetAmmoName(){
  return AmmoName;
}

void cls_Weapon::Fire(int x, int y, float angle){
  int spread, time, msp, size;
  switch( Type ){
  case WEAPON_TYPE_BLASTER:
      spread = 1;
      time = 15;
      msp = 24;
      size = 1;
      clr[0] = 1;
      clr[1] = 1;
      clr[2] = 0;
      NumParticles = 32;
      break;
    case WEAPON_TYPE_GRENADES:
      spread = 4;
      time = 15;
      msp = 16;
      size = 1;
      clr[0] = 0.85;
      clr[1] = 0.75;
      clr[2] = 0.65;
      NumParticles = 64;
      break;
    case WEAPON_TYPE_RAILGUN:
      spread = 1;
      time = 20;
      msp = 24;
      size = 2;
      clr[0] = 1;
      clr[1] = 0;
      clr[2] = 1;
      NumParticles = 128;
      break;
    case WEAPON_TYPE_TRAILGUN:
      spread = 2;
      time = 30;
      msp = 18;
      size = 2;
      clr[0] = 0;
      clr[1] = 1;
      clr[2] = 0;
      NumParticles = 96;
      break;
    default:
      spread = 1;
      time = 15;
      msp = 16;
      size = 1;
      clr[0] = 1;
      clr[1] = 1;
      clr[2] = 0;
      NumParticles = 32;
    break;
  }
  for( int k = 0; k < NumParticles; k++ ){
    Particles[k].x = x + 16;
    Particles[k].y = y + 16;
    Particles[k].t0 = 0;
    Particles[k].t1 = time;
    Particles[k].life = 1;
    Particles[k].spread = spread;
    Particles[k].size = size;
    float tmp = ((msp/2) + (rand()%msp));
    Particles[k].xs = (tmp)*cos(round(angle)*(2*pi)/16);
    Particles[k].ys = (-tmp)*sin(round(angle)*(2*pi)/16);
  }
}

void cls_Weapon::ParticlePhysics(int x, int y){
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslated(AC.GetHalfW()-16,AC.GetHalfH()-16,0);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  
  StructSurf MapRect = Map.GetRect();
    
  int k,tx,ty,i,s;
  float lf;
  for( k = 0; k < NumParticles; k++ ){
    if( Particles[k].life > 0 ){
      tx = Particles[k].x + Particles[k].xs;
      ty = Particles[k].y + Particles[k].ys;
      
      if( tx <= 16 || tx+32 >= (MapRect.Right-16) || ty <= 16 || ty+32 >= (MapRect.Bottom-16) ){
        tx = 0;
        ty = 0;
        Particles[k].life = 0;
      }
      
      //Particles[k].ys += (Particles[k].spread)*sin(rand());
      if( ++Particles[k].t0 > Particles[k].t1 )
        Particles[k].life = 0;
      if( Particles[k].life > 0 ){
        if( Map.GetCol(tx+1,ty+1) > 1 )
          Particles[k].life = 0;
      }
      
      for( i = 0; i < Map.GetNumDoors(); i++ ){
        if( tx > Map.GetDoorX(i) && tx < Map.GetDoorX(i)+32 && ty > Map.GetDoorY(i) && y < Map.GetDoorY(i)+32 ){
          if( !Map.DoorOpened(i) ){
            Particles[k].life = 0;
          }
        }
      }
      
      Particles[k].x = tx;
      Particles[k].y = ty;
      s = Particles[k].size;
      
      lf = 1 - (float) Particles[k].t0/Particles[k].t1;
      
      glBegin(GL_QUADS);
      glColor4f(clr[0],clr[1],clr[2],lf);
      glVertex3f(Particles[k].x-x,   Particles[k].y+s-y, 0);
      glVertex3f(Particles[k].x+s-x, Particles[k].y+s-y, 0);
      glVertex3f(Particles[k].x+s-x, Particles[k].y-y,   0);
      glVertex3f(Particles[k].x-x,   Particles[k].y-y,   0);
      glEnd();
    }
  }

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
    
}






