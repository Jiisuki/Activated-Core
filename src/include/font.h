
#define NumFonts 3

class cls_Font{
private:
  struct StructFont{
    GLuint Tex_Font;
    GLuint Tex_Font_Base;
    char Filename[64];
  } FontDef[NumFonts];
public:
  cls_Font();
  GLuint *GetTex(int FontNo);
  GLuint *GetTexBase(int FontNo);
  char *GetFilename(int FontNo);
  void BuildFont(int FontNo);
  void KillFont();
  void glPrint(GLint X, GLint Y, const char *String, int FontNo);
  int ScrambleText(int TimesMax, int Step, const char *Input, char *Coded, int *Coding);
};

cls_Font::cls_Font(){
  strcpy(FontDef[0].Filename, "gfx/charmap/font1.tga");
  strcpy(FontDef[1].Filename, "gfx/charmap/font2.tga");
  strcpy(FontDef[2].Filename, "gfx/charmap/font3.tga");
}
GLuint *cls_Font::GetTex(int FontNo){
  return &FontDef[FontNo].Tex_Font;
}
GLuint *cls_Font::GetTexBase(int FontNo){
  return &FontDef[FontNo].Tex_Font_Base;
}
char *cls_Font::GetFilename(int FontNo){
  return FontDef[FontNo].Filename;
}
void cls_Font::BuildFont(int FontNo){
  float cx, cy;

  GFX.LoadTexture(GetFilename(FontNo),GetTex(FontNo));

  FontDef[FontNo].Tex_Font_Base = glGenLists(256);
  glBindTexture(GL_TEXTURE_2D, FontDef[FontNo].Tex_Font);

  float LS = 16;
  int Step = 12;

  int loop;
  for( loop=0; loop<256; loop++){
    cx = float(loop%16)/16.0f;
    cy = float(loop/16)/16.0f;
    glNewList(FontDef[FontNo].Tex_Font_Base+loop,GL_COMPILE);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(cx,1-cy-0.0625f);
      glVertex2i(0,LS);
      glTexCoord2f(cx+0.0625f,1-cy-0.0625f);
      glVertex2i(LS,LS);
      glTexCoord2f(cx+0.0625f,1-cy);
      glVertex2i(LS,0);
      glTexCoord2f(cx,1-cy);
      glVertex2i(0,0);
    glEnd();
    glTranslated(Step,0,0);
    glEndList();
  }
}
void cls_Font::KillFont(){
  int i;
  for( i = 0; i < NumFonts; i++ ){
    glDeleteLists(FontDef[i].Tex_Font_Base,256);
  }
}
void cls_Font::glPrint(GLint X, GLint Y, const char *String, int FontNo){

  if( FontNo > NumFonts ){
    FontNo = NumFonts;
  }
  glBindTexture(GL_TEXTURE_2D,FontDef[FontNo].Tex_Font);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslated(X,Y,0);
  glListBase(FontDef[FontNo].Tex_Font_Base);
  glCallLists(strlen(String),GL_UNSIGNED_BYTE,String);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

}
int cls_Font::ScrambleText(int TimesMax, int Step, const char *Input, char *Coded, int *Coding){
  int l,t,Times,Acc,LenCode;

  LenCode = strlen(Input);
  if( LenCode == 0 ){
    return -1;
  }

  strncpy(Coded,Input,LenCode);

  for( l = 0; l < LenCode; l+=Step ){
    Times = int(rand()%TimesMax)+1;
    for( t = 0; t < Times; t++ ){
      Coded[l]++;
      Coding[l]++;
      Acc++;
    }
  }
  return LenCode;
}

cls_Font Font;
