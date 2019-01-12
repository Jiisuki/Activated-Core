#define NumStars 256
#define NumStarLayers 8



class cls_Starfield{
private:
  bool StarfieldActive;
  struct StructStar{
    float X;
    float Y;
    float RelSpeed;
    float Color[3];
    float Star_Radius;
  } Star[NumStars];
  float StarfieldFacing;
  float StarfieldHeading;
  float StarfieldSpeed;
  float StarfieldAccel;
  float StarfieldMaxSpeed;
public:
  cls_Starfield();
  void StarPhysics();
  float GetX(int Num);
  float GetY(int Num);
  float *GetRgb(int Num);
  float GetRadius(int Num);
  void SetFacing(float NewFace);
};

cls_Starfield::cls_Starfield() {

  int w = 640;
  int h = 400;

  StarfieldActive = 1;
  StarfieldFacing = int(rand()%360);
  StarfieldHeading = int(rand()%360);
  StarfieldAccel = 0.04;
  StarfieldMaxSpeed = 2.8;
  StarfieldSpeed = 0;

  srand((unsigned int)time(0));
  int i;
  for( i = 0; i < NumStars; i++ ){
    Star[i].X = int(rand()%w);
    Star[i].Y = int(rand()%h);
    Star[i].RelSpeed = ((float(i) / (float(NumStars) / float(NumStarLayers))) + 1) / float(NumStarLayers);
    Star[i].Color[0] = 1;
    Star[i].Color[1] = 1;
    Star[i].Color[2] = 1;
    Star[i].Star_Radius = rand()%1+1;
  }
}

void cls_Starfield::StarPhysics(){

  float XC, YC;
  int i;

  XC = StarfieldSpeed * sin(StarfieldHeading) + StarfieldAccel * sin(StarfieldFacing);
  YC = StarfieldSpeed * cos(StarfieldHeading) + StarfieldAccel * cos(StarfieldFacing);

  StarfieldSpeed = sqrt(XC*XC + YC*YC);
  if( StarfieldSpeed > StarfieldMaxSpeed ){
    StarfieldSpeed = StarfieldMaxSpeed;
  }

  if( YC > 0 ){
    StarfieldHeading = atan(XC/YC);
  }
  if( YC < 0 ){
    StarfieldHeading = atan(XC/YC) + pi;
  }

  for( i = 0; i < NumStars; i++ ){
    Star[i].X = Star[i].X - (StarfieldSpeed * Star[i].RelSpeed * sin(StarfieldHeading));
    Star[i].Y = Star[i].Y + (StarfieldSpeed * Star[i].RelSpeed * cos(StarfieldHeading));
    if( Star[i].X > AC.GetScreenWidth() ) Star[i].X = 0;
    if( Star[i].X < 0 ) Star[i].X = AC.GetScreenWidth();
    if( Star[i].Y > AC.GetScreenHeight() ) Star[i].Y = 0;
    if( Star[i].Y < 0 ) Star[i].Y = AC.GetScreenHeight();
  }
}

float cls_Starfield::GetX(int Num){
  return Star[Num].X;
}
float cls_Starfield::GetY(int Num){
  return Star[Num].Y;
}
float *cls_Starfield::GetRgb(int Num){
  return &(Star[Num].Color[0]);
}
float cls_Starfield::GetRadius(int Num){
  return Star[Num].Star_Radius;
}
void cls_Starfield::SetFacing(float NewFace){
  StarfieldFacing = NewFace;
}




cls_Starfield Starfield;

void DrawStarfield(void){


glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glDisable(GL_TEXTURE_2D);
    
  int i;
  float x,y,r;
  float *rgb;
  for( i = 0; i < NumStars; i++ ){
    x = Starfield.GetX(i);        y = Starfield.GetY(i);
    r = Starfield.GetRadius(i); rgb = Starfield.GetRgb(i);
    
    glLoadIdentity();
    glTranslatef(x,y,0);
    //glDisable(GL_LIGHTING);
    glColor4f(rgb[0], rgb[1], rgb[2],0.5f);
    glBegin(GL_QUADS);
      glVertex3f(0,r,0);	// Bottom Left Of The Texture and Quad
      glVertex3f(r,r,0);	// Bottom Right Of The Texture and Quad
      glVertex3f(r,0,0);	// Top Right Of The Texture and Quad
      glVertex3f(0,0,0);	// Top Left Of The Texture and Quad
    glEnd();                                    // done with the polygon.
    
  }
glEnable(GL_TEXTURE_2D);
    //glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
