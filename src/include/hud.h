

#ifndef _HUD_H
#define _HUD_H

#include "player.h"




#define HUD_TRANS 0.5
#define HUD_UPDATE_SPEED 10

class cls_Hud{
private:
  GLuint Tex;
  GLuint TexLower;
  char Filename[64];
  char FilenameLower[64];
  bool TextureLoaded;
  struct StructStatus{
    float Health;
    float HealthTarg;
    float Armor;
    float ArmorTarg;
    float Ammo;
    float AmmoTarg;
  }Status;
public:
  cls_Hud();
  GLuint *GetTex();
  char *GetFilename();
  GLuint *GetTexLower();
  char *GetFilenameLower();
  void BuildHud();
  void KillTexture();
  void Update();
};
GLuint *cls_Hud::GetTex(){
  return &Tex;
}
GLuint *cls_Hud::GetTexLower(){
  return &TexLower;
}
char *cls_Hud::GetFilename(){
  return Filename;
}
char *cls_Hud::GetFilenameLower(){
  return FilenameLower;
}
void cls_Hud::BuildHud(){
  if( !TextureLoaded ){
    GFX.LoadTexture(GetFilename(),GetTex());
    usleep(1000);
    GFX.LoadTexture(GetFilenameLower(),GetTexLower());
  }
  Status.Health = 0;
  Status.Armor = 0;
  Status.Ammo = 0;
}
void cls_Hud::KillTexture(){
  if( TextureLoaded ){
    glDeleteTextures(1,&Tex);
    glDeleteTextures(1,&TexLower);
  }
}
void cls_Hud::Update(){

  Status.HealthTarg = Player.GetHealth();
  Status.ArmorTarg = Player.GetArmor();
  Status.AmmoTarg = Player.GetAmmo();
  
  if( Status.Health < Status.HealthTarg ){
    Status.Health += (Status.HealthTarg-Status.Health)/HUD_UPDATE_SPEED;
  } else if( Status.Health > Status.HealthTarg ){
    Status.Health -= (Status.Health-Status.HealthTarg)/HUD_UPDATE_SPEED;
  }
  
  if( Status.Armor < Status.ArmorTarg ){
    Status.Armor += (Status.ArmorTarg-Status.Armor)/HUD_UPDATE_SPEED;
  } else if( Status.Armor > Status.ArmorTarg ){
    Status.Armor -= (Status.Armor-Status.ArmorTarg)/HUD_UPDATE_SPEED;
  }
  
  if( Status.Ammo < Status.AmmoTarg ){
    Status.Ammo += (Status.AmmoTarg-Status.Ammo)/HUD_UPDATE_SPEED;
  } else if( Status.Ammo > Status.AmmoTarg ){
    Status.Ammo -= (Status.Ammo-Status.AmmoTarg)/HUD_UPDATE_SPEED;
  }

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
 
  
  glLoadIdentity();
  glTranslated(0,0,0);
  glBindTexture(GL_TEXTURE_2D,Tex);
  glDisable(GL_LIGHTING);
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(  0, 32, 0);
    glTexCoord2f(1, 0); glVertex3f(320, 32, 0);
    glTexCoord2f(1, 1); glVertex3f(320,  0, 0);
    glTexCoord2f(0, 1); glVertex3f(  0,  0, 0);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);
  
  
  //Health
  glColor4f(1-Status.Health,Status.Health,0,1);
  glTranslated(6,12,0);
  glBegin(GL_QUADS);
    glVertex3f(  0, 8, 0);
    glVertex3f(84*Status.Health, 8, 0);
    glVertex3f(84*Status.Health,  0, 0);
    glVertex3f(  0,  0, 0);
  glEnd();
  
  //Armor
  glColor4f(1-Status.Armor,Status.Armor,0,1);
  glTranslated(96,0,0);
  glBegin(GL_QUADS);
    glVertex3f(  0, 8, 0);
    glVertex3f(84*Status.Armor, 8, 0);
    glVertex3f(84*Status.Armor,  0, 0);
    glVertex3f(  0,  0, 0);
  glEnd();
  
  //Ammo
  glColor4f(1-Status.Ammo,0,Status.Ammo,1);
  glTranslated(96,0,0);
  glBegin(GL_QUADS);
    glVertex3f(  0, 8, 0);
    glVertex3f(116*Status.Ammo, 8, 0);
    glVertex3f(116*Status.Ammo,  0, 0);
    glVertex3f(  0,  0, 0);
  glEnd();
    
  glLoadIdentity();
  glTranslated(206,22,0);
  for( int k = 0; k < 4; k++ ){
    
    if( Player.GotWeaponInv(k) ){
      if( Player.GetWeaponSel() == k ){
        glColor4f(0,1,0,1);
      } else {
        glColor4f(.5,0.5,.5,1);
      }
      glBegin(GL_QUADS);
        glVertex3f(0,4,0);
        glVertex3f(4,4,0);
        glVertex3f(4,0,0);
        glVertex3f(0,0,0);
      glEnd();
    }
    glTranslated(6,0,0);
  }
  
  glLoadIdentity();
  glTranslated(284,22,0);
  glColor4f(1,0,1,1);
  for( int k = 0; k < 4; k++ ){
    if( Player.GotDiscInv(k) ){        
      glBegin(GL_QUADS);
        glVertex3f(0,4,0);
        glVertex3f(4,4,0);
        glVertex3f(4,0,0);
        glVertex3f(0,0,0);
      glEnd();
    }
    glTranslated(6,0,0);
  }
  

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  
  if( Player.GotItemInv(ITEM_SENSOR) ){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslated(0,AC.GetScreenHeight()-64,0);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f( 0,  64, 0);
    glVertex3f( 64, 64, 0);
    glVertex3f( 64, 0,    0);
    glVertex3f( 0,  0,    0);
    glEnd();
    int tmpx1 = Player.GetPosX()/32-16;
    if( tmpx1 < 0 )
      tmpx1 = 0;
    int tmpx2 = tmpx1 + 31;
    if( tmpx2 > Map.GetWidth() )
      tmpx2 = Map.GetWidth();
    int tmpy1 = Player.GetPosY()/32-16;
    if( tmpy1 < 0 )
      tmpy1 = 0;
    int tmpy2 = tmpy1 + 31;
    if( tmpy2 > Map.GetHeight() )
      tmpy2 = Map.GetHeight();

    glTranslated(1,1,0);

    for( int y = tmpy1; y < tmpy2; y++ ){
      for( int x = tmpx1; x < tmpx2; x++ ){
        if( x == round(Player.GetPosX()/32) && y == round(Player.GetPosY()/32) ){
          glColor4f(0.0f,1.0f,0.0f,1.0f);
          glBegin(GL_QUADS);
            glVertex3f(0, 2, 0);
            glVertex3f(2, 2, 0);
            glVertex3f(2, 0, 0);
            glVertex3f(0, 0, 0);
          glEnd();
        } else if( x == round(Enemy.GetPosX()/32) && y == round(Enemy.GetPosY()/32) ){
          glColor4f(1.0f,0.0f,0.0f,1.0f);
          glBegin(GL_QUADS);
            glVertex3f(0, 2, 0);
            glVertex3f(2, 2, 0);
            glVertex3f(2, 0, 0);
            glVertex3f(0, 0, 0);
          glEnd();
        } else {
          glColor4f(1.0f,1.0f,1.0f,1.0f);
          if( Map.GetCol(x*32,y*32) > 1 ){
            glBegin(GL_QUADS);
              glVertex3f(0, 2, 0);
              glVertex3f(2, 2, 0);
              glVertex3f(2, 0, 0);
              glVertex3f(0, 0, 0);
            glEnd();
          }
        }
        glTranslated(2,0,0);
      }
      glTranslated(-(tmpx2-tmpx1)*2,2,0);
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
  }
}


cls_Hud::cls_Hud(){

  TextureLoaded = 0;
  strcpy(Filename,"gfx/hud/main.tga");
  strcpy(FilenameLower,"gfx/hud/lower.tga");

}

cls_Hud HUD;



#endif
