

#include "loadtga.h"

/* The number of our GLUT window */
int Glut_Window;

typedef struct StructSurf{
  int Left;
  int Right;
  int Top;
  int Bottom;
} StructSurf;

class cls_GfxFcns{
public:
  bool LoadTexture(char *TexName, GLuint *TexHandle);
  void DrawSurf(float X, float Y, StructSurf Surf, GLuint Texture);
  void ResetLights();
  void InitGL(int Width, int Height);
  void SetLightning(bool On);
};



// Load a TGA texture
bool cls_GfxFcns::LoadTexture(char *TexName, GLuint *TexHandle){
  TGAImg Img;        // Image loader

  // Load our Texture
  int errn = Img.Load(TexName);
  if(errn!=IMG_OK){
    printf("Error loading %s\nError is: %i, %s\n",TexName,errn,GetTGAError(errn));
    return false;
  }

  glGenTextures(1, TexHandle);
  glBindTexture(GL_TEXTURE_2D,*TexHandle); // Set our Tex handle as current

  // Create the texture
  if(Img.GetBPP()==24)
    glTexImage2D(GL_TEXTURE_2D,0,3,Img.GetWidth(),Img.GetHeight(),0,
                 GL_RGB,GL_UNSIGNED_BYTE,Img.GetImg());
  else if(Img.GetBPP()==32)
    glTexImage2D(GL_TEXTURE_2D,0,4,Img.GetWidth(),Img.GetHeight(),0,
                 GL_RGBA,GL_UNSIGNED_BYTE,Img.GetImg());
  else
    return false;

   // Specify filtering and edge actions GL_NEAREST GL_LINEAR
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); // IMPORTANT (?)
   if( AC.GetLinScale() ){
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   } else {
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   }

   return true;
}

void cls_GfxFcns::DrawSurf(float X, float Y, StructSurf Surf, GLuint Texture){
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslated(X,Y,0);
  glBindTexture(GL_TEXTURE_2D, Texture);
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( Surf.Left,  Surf.Bottom, 0);
    glTexCoord2f(1, 0); glVertex3f( Surf.Right, Surf.Bottom, 0);
    glTexCoord2f(1, 1); glVertex3f( Surf.Right, Surf.Top,    0);
    glTexCoord2f(0, 1); glVertex3f( Surf.Left,  Surf.Top,    0);
  glEnd();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void cls_GfxFcns::InitGL(int Width, int Height){

  glEnable(GL_TEXTURE_2D); // Enable Texture Mapping

  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glAlphaFunc(GL_GREATER,0.1f);
  glEnable(GL_ALPHA_TEST);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// Clear background color.

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); // Reset projection matrix.

  // Game is in 2D
  glOrtho(0, Width, Height, 0, -1, 1);

  // Set up model view matrix.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  ResetLights();

  glDisable(GL_DEPTH_TEST);

}

void cls_GfxFcns::ResetLights(){
  glEnable(GL_LIGHT0);
  GLfloat LightPos0[4]={AC.GetHalfW(),AC.GetHalfH(),AC.GetEquilibriumStrength(),1.0f};
  GLfloat whiteSpecularLight0[] = {1.0, 1.0, 1.0};
  GLfloat matShininess[] = {100.0};
  GLfloat blackAmbientLight0[] = {0.0, 0.0, 0.0};
  glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0/(1000*AC.GetEquilibriumStrength()));
  glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight0);
  glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);
}

void cls_GfxFcns::SetLightning(bool On){
  if( On ){
    glEnable(GL_LIGHTING);
  } else {
    glDisable(GL_LIGHTING);
  }
  
}

cls_GfxFcns GFX;

