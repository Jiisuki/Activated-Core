/* 
 * File:   editor.h
 * Author: nadlun-5
 *
 * Created on 18 May 2011, 17:08
 */

#ifndef EDITOR_H
#define	EDITOR_H




#define NUMEDOBJ 128
#define EDNUMTILESETS 2



#define ED_STEP 1
struct StrEditor{
  char MapFile[128];
  int Ex;
  int Ey;
  int SetTile;
  GLuint EdTex[2];
  char EdTexFile[64];
  char EdTexColFile[64];
  GLuint EdTopTex;
  char EdTopTexFile[64];
  GLuint EdItemsTex;
  char EdItemsTexFile[64];
  int Width;
  int Height;
  int Song;
  int Env;
  int Tileset;
  char Name[64];
  struct strobj{
    int x;
    int y;
    int type;
    int flag1;
    int flag2;
    bool used;
    float gfx;
  } Object[NUMEDOBJ];
  int NumObjects;
  int Zoom;
} Editor;

void DumpMap(){
  FILE *fp;

  // Open mapfile
  if( (fp = fopen(Editor.MapFile, "w")) == NULL ){
    printf("Could not create file : %s\n",Editor.MapFile);
    return;
  }

  fprintf(fp,"%s \n",Editor.Name);
  fprintf(fp,"Jiisuki\n");
  fprintf(fp,"%i\n",Editor.Width);
  fprintf(fp,"%i\n",Editor.Height);
  fprintf(fp,"%i\n",Editor.Song);
  fprintf(fp,"%i\n",Editor.Env);
  fprintf(fp,"%i\n",Editor.Tileset);

  int row = 0;
  for( int i = 0; i < Editor.Height; i++ ){
    for( int j = 0; j < Editor.Width; j++ ){
      if( i*j == Editor.Width*Editor.Height){
        fprintf(fp,"%2i",*(MAP+i*Editor.Width+j));
      } else {
        fprintf(fp,"%2i ",*(MAP+i*Editor.Width+j));
      }
      row++;
      if( row >= 32 ){
        fprintf(fp,"\n");
        row = 0;
      }
    }
  }

  
 

  for( int i = 0; i < NUMEDOBJ; i++ ){
    if( Editor.Object[i].used ){
      fprintf(fp,"%s\n",GetItemName(Editor.Object[i].type));
      fprintf(fp,"%i %i %i %i\n",Editor.Object[i].x,Editor.Object[i].y,Editor.Object[i].flag1,1);
    }
  }

  fclose(fp);

  GUI.OSDMessage("Map Saved!",1);

}

void EditorControl(unsigned char key){
  if( key == Control.GetBoundKey(CTRL_KEY_ESCAPE) ){
    
    AC.SpecifyLoop(LOOP_MAIN_MENU);
    Sound.PlayTune(MUSIC_TUNE_INTRO);
    Menu.SetMenuSelection(MENU_MAIN);
  }
  if( key == 104 ){ // h
    Map.LoadMap(Editor.MapFile); // Load map file.
    Player.SpawnPlayer(0); // Set player starting positions.
    AC.SpecifyLoop(LOOP_GAME); // Graphics Loop.
  }
  if( key == Control.GetBoundKey(CTRL_KEY_UP) ){
    Editor.Ey-=ED_STEP;
    if( Editor.Ey < 0 )
      Editor.Ey = 0;
  }
  if( key == Control.GetBoundKey(CTRL_KEY_DOWN) ){
    Editor.Ey+=ED_STEP;
    if( Editor.Ey >= Editor.Height )
      Editor.Ey = Editor.Height-1;
  }
  if( key == Control.GetBoundKey(CTRL_KEY_LEFT) ){
    Editor.Ex-=ED_STEP;
    if( Editor.Ex < 0 )
      Editor.Ex = 0;
  }
  if( key == Control.GetBoundKey(CTRL_KEY_RIGHT) ){
    Editor.Ex+=ED_STEP;
    if( Editor.Ex >= Editor.Width )
      Editor.Ex = Editor.Width-1;
  }
  if( key == Control.GetBoundKey(CTRL_KEY_CONFIRM_OPTION) ){
    *(MAP+Editor.Ey*Editor.Width+Editor.Ex) = Editor.SetTile;
    if( *(MAP+Editor.Ey*Editor.Width+Editor.Ex) >= (TILES_RES*TILES_RES) )
      *(MAP+Editor.Ey*Editor.Width+Editor.Ex) = 0;
  }
  if( key == 112 ){
    Editor.SetTile = *(MAP+Editor.Ey*Editor.Width+Editor.Ex);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_ACTION_1) ){
    Editor.SetTile--;
    if( Editor.SetTile < 0 )
      Editor.SetTile = (TILES_RES*TILES_RES);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_ACTION_2) ){
    Editor.SetTile++;
    if( Editor.SetTile >= (TILES_RES*TILES_RES) )
      Editor.SetTile = 0;
  }
  if( key == 49 ){
    Editor.Song++;
    if( Editor.Song > MUSIC_CREDITS )
      Editor.Song = 0;
    Sound.PlayTune(Editor.Song);
  }
  if( key == 51 ){
    Editor.Tileset++;
    if( Editor.Tileset >= EDNUMTILESETS )
      Editor.Tileset = 0;
  }
  if( key == 52 ){
    for( int k = 0; k < NUMEDOBJ; k++ ){
      if( !Editor.Object[k].used ){
        Editor.Object[k].x = Editor.Ex*32;
        Editor.Object[k].y = Editor.Ey*32;
        Editor.Object[k].type = ITEM_HEALTH;
        Editor.Object[k].flag1 = 25;
        Editor.Object[k].flag2 = 0;
        Editor.Object[k].used = 1;
        break;
      }
    }
  }

  if( key == 43 ){ //+
    for( int k = 0; k < NUMEDOBJ; k++ ){
      if( Editor.Object[k].x == Editor.Ex*32 && Editor.Object[k].y == Editor.Ey*32 ){
        Editor.Object[k].flag1++;
      }
    }
  }
  if( key == 45 ){ //-
    for( int k = 0; k < NUMEDOBJ; k++ ){
      if( Editor.Object[k].x == Editor.Ex*32 && Editor.Object[k].y == Editor.Ey*32 ){
        Editor.Object[k].flag1--;
        if( Editor.Object[k].flag1 < 0 )
          Editor.Object[k].flag1 = 50;
      }
    }
  }
  if( key == 122 ){ // z
    for( int k = 0; k < NUMEDOBJ; k++ ){
      if( Editor.Object[k].x == Editor.Ex*32 && Editor.Object[k].y == Editor.Ey*32 ){
        Editor.Object[k].type--;
        if( Editor.Object[k].type < 1 )
          Editor.Object[k].flag2 = HIGH_ITEM;
      }
    }
  }
  if( key == 120 ){ // x
    for( int k = 0; k < NUMEDOBJ; k++ ){
      if( Editor.Object[k].x == Editor.Ex*32 && Editor.Object[k].y == Editor.Ey*32 ){
        Editor.Object[k].type++;
        if( Editor.Object[k].type > HIGH_ITEM )
          Editor.Object[k].type = ITEM_SPAWN;
      }
    }
  }
  if( key == 56 ){
    for( int k = 0; k < NUMEDOBJ; k++ ){
      if( Editor.Object[k].x == Editor.Ex*32 && Editor.Object[k].y == Editor.Ey*32 ){
        Editor.Object[k].used = 0;
      }
    }
  }
  if( key == 57 ){
    Editor.Zoom++;
    if( Editor.Zoom > 2 )
      Editor.Zoom = 1;
  }
  if( key == 48 ){
    DumpMap();
  }
}


void DrawEditorMap(int x, int y){
  float tx, ty;
  int j,k,px,py,c;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth()*Editor.Zoom,AC.GetScreenHeight()*Editor.Zoom,0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, Editor.EdTex[Editor.Tileset]);
  for( j = 0; j < Editor.Width; j++ ){
    for( k = 0; k < Editor.Height; k++ ){
      px = j*32;
      py = k*32;
      c = *(MAP+k*Editor.Width+j);
      tx = (float) GetTileX(c)*0.125;
      ty = (float) GetTileY(c)*0.125;

      if( px > AC.GetHalfW()-x-32-(320*Editor.Zoom) && px < AC.GetHalfW()-x+(320*Editor.Zoom) ){
        if( py > AC.GetHalfH()-y-32-(200*Editor.Zoom) && py < AC.GetHalfH()-y+(200*Editor.Zoom) ){
          if( c > 0 ){
            glLoadIdentity();
            glTranslated(320*Editor.Zoom+px+x-AC.GetHalfW(),200*Editor.Zoom+py+y-AC.GetHalfH(),0);
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
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void DrawEditorItems(int x, int y){
  int px,py,s,t;
  char f[32];
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth()*Editor.Zoom,AC.GetScreenHeight()*Editor.Zoom,0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  for( int u = 0; u < NUMEDOBJ; u++ ){
    if( Editor.Object[u].used ){
      glBindTexture(GL_TEXTURE_2D, Editor.EdItemsTex);
      px = Editor.Object[u].x;
      py = Editor.Object[u].y;
      glLoadIdentity();
      glTranslated(320*Editor.Zoom+px+x-AC.GetHalfW(),200*Editor.Zoom+py+y-AC.GetHalfH(),0);
      t = 16-Editor.Object[u].type;
      Editor.Object[u].gfx += 0.3;
      if( Editor.Object[u].gfx > 8 )
        Editor.Object[u].gfx = 0;
      s = (int) Editor.Object[u].gfx;
      glColor4f(1.0f,1.0f,1.0f,1.0f);
      glBegin(GL_QUADS);
        glTexCoord2f(0.125*s,       0.0625*t);        glVertex3f(  0, 32, 0);
        glTexCoord2f(0.125*s+0.125, 0.0625*t);        glVertex3f( 32, 32, 0);
        glTexCoord2f(0.125*s+0.125, 0.0625*t+0.0625); glVertex3f( 32,  0, 0);
        glTexCoord2f(0.125*s,       0.0625*t+0.0625); glVertex3f(  0,  0, 0);
      glEnd();
      if( Editor.Zoom == 1 ){
        sprintf(f,"[%i]",Editor.Object[u].flag1);
        Font.glPrint(320+px+x-AC.GetHalfW()-(strlen(f)*6)+16,200+py+32+y-AC.GetHalfH(),f,1);
      }
    }
  }
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}


void DrawSetTile(){
  float tx, ty;
  int c;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth()*2,AC.GetScreenHeight()*2,0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glDisable(GL_TEXTURE_2D);
  glLoadIdentity();
  glTranslated(0,AC.GetScreenHeight()*2-32,0);
  glColor4f(0.05f,0.0f,0.0f,1.0f);
  glBegin(GL_QUADS);
  glVertex3f( 0,  32, 0);
  glVertex3f(320*4, 32, 0);
  glVertex3f(320*4, 0,    0);
  glVertex3f( 0,  0,    0);
  glEnd();
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, Editor.EdTex[0]);
  for( int x = 0; x < 44; x++ ){
    c = Editor.SetTile - 20 + x;
    if( c >= 0 && c < TILES_RES*TILES_RES ){
      tx = (float) GetTileX(c)*0.125;
      ty = (float) GetTileY(c)*0.125;
      glLoadIdentity();
      glTranslated(32*x-16,AC.GetScreenHeight()*2-32,0);
      glColor4f(1.0f,1.0f,1.0f,1.0f);
      glBegin(GL_QUADS);
      glTexCoord2f(tx,    (1-ty)-0.125); glVertex3f( 0,  32, 0);
      glTexCoord2f(tx+0.125, (1-ty)-0.125); glVertex3f( 32, 32, 0);
      glTexCoord2f(tx+0.125,  1-ty);     glVertex3f( 32, 0,    0);
      glTexCoord2f(tx,     1-ty);     glVertex3f( 0,  0,    0);
      glEnd();
    }
  }
  glDisable(GL_TEXTURE_2D);
  glLoadIdentity();
  glTranslated(320*2-16,AC.GetScreenHeight()*2-32,0);
  glColor4f(0.0f,1.0f,0.0f,0.5f);
  glBegin(GL_LINE_LOOP);
  glVertex3f( 0,  32, 0);
  glVertex3f( 32, 32, 0);
  glVertex3f( 32, 0,    0);
  glVertex3f( 0,  0,    0);
  glEnd();
  
  glEnable(GL_TEXTURE_2D);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void DrawEditorTopMenu(){

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslated(0,0,0);
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBindTexture(GL_TEXTURE_2D, Editor.EdTopTex);

      glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex3f( 0,   32, 0);
      glTexCoord2f(1, 0); glVertex3f( 320, 32, 0);
      glTexCoord2f(1, 1); glVertex3f( 320,  0, 0);
      glTexCoord2f(0, 1); glVertex3f( 0,    0, 0);
      glEnd();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void DrawEditorBox(){
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth()*Editor.Zoom,AC.GetScreenHeight()*Editor.Zoom,0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glDisable(GL_TEXTURE_2D);
  glLoadIdentity();
  glTranslated(AC.GetHalfW()*Editor.Zoom-16,AC.GetHalfH()*Editor.Zoom-16,0);
  glColor4f(1.0f,0.0f,0.0f,0.5f);
  glBegin(GL_LINE_LOOP);
  glVertex3f( 0,  32, 0);
  glVertex3f( 32, 32, 0);
  glVertex3f( 32, 0,    0);
  glVertex3f( 0,  0,    0);
  glEnd();
  glEnable(GL_TEXTURE_2D);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

}

void DrawEditor(){
  time_t start,end;
  time(&start);

//  Map.SetLightSources(1);
  GFX.SetLightning(0);
  DrawEditorMap(AC.GetHalfW()-(Editor.Ex*32)-16,AC.GetHalfH()-(Editor.Ey*32)-16);
  DrawEditorItems(AC.GetHalfW()-(Editor.Ex*32)-16,AC.GetHalfH()-(Editor.Ey*32)-16);
  DrawEditorBox();
  DrawSetTile();
  DrawEditorTopMenu();
  //Map.DrawMapObjects(Player.GetPosX(),Player.GetPosY());

  // Print On Screen Message
  Font.glPrint(AC.GetHalfW()-strlen(GUI.ReadOSDMessage())*12/2,AC.GetHalfH()+24,GUI.ReadOSDMessage(),1);

  char tmp[32];
  sprintf(tmp,"%02i x %02i",Editor.Ex,Editor.Ey);
  Font.glPrint(4,20,tmp,0);
  //sprintf(tmp,"Tune: %i",Editor.Song);
  //Font.glPrint(4,20,tmp,2);


  usleep(AC.GetProgramHoldTime());

  time(&end);
  AC.dif = AC.dif + difftime (end,start);
  if( AC.dif >= 1 ){
    sprintf(AC.FPS,"%i FPS",AC.FPSc);
    AC.FPSc = 0;
    AC.dif = 0;
    Menu.ShowInfo = !Menu.ShowInfo;
    Menu.InfoDelay++;
    if( Menu.InfoDelay > Menu.InfoDelayStop ){
      Menu.InfoDelay = 0;
      Starfield.SetFacing(int(rand()%360));
    }
  }
}

void SetEditorObject(int i, int x, int y, int type, int f1, int f2, int f3){//, int gfx){
  Editor.Object[i].type = type;
  Editor.Object[i].x = x;
  Editor.Object[i].y = y;
  Editor.Object[i].flag1 = f1;
  Editor.Object[i].flag2 = f2;
  Editor.Object[i].used = 1;
}

void EditorLoadMap(const char *Filename){

  // File pointer for reading the mapfile
  FILE *fp;

  Editor.NumObjects = 0;

  for( int k = 0; k < NUMEDOBJ; k++ ){
    Editor.Object[k].used = 0;
  }

  strcpy(Editor.MapFile,Filename);

  // Open mapfile
  if( (fp = fopen(Filename, "r")) == NULL ){
    printf("File Not Found : %s\n",Filename);
    Editor.Width = 32;
    Editor.Height = 32;
    MAP = (int*) realloc(MAP, sizeof(int)*(Editor.Width*Editor.Height));
    for( int y = 0; y < Editor.Height; y++ ){
      for( int x = 0; x < Editor.Width; x++ ){
        *(MAP+y*Editor.Width+x) = 0;
      }
    }
    return;
  }


  
  
  // Temporary variables used for loading data
  char dp[32]; // For text strings
  int x, y; // X and Y position of objects
  int flag1, flag2; // Object ID and Target ID used for Teleports, Spawns etc

  // Get name of the map
  if( fgets(dp,32,fp) == NULL ) return;
  memset(Editor.Name,'\0',64);
  strncpy(Editor.Name,dp,strlen(dp)-1);

  // Who created the map?
  if( fgets(dp,32,fp) == NULL ) return;
  
  // Get map width and height
  if( fscanf(fp,"%i",&Editor.Width) <= 0 ) return;
  if( fscanf(fp,"%i",&Editor.Height) <= 0 ) return;

  // Get musical score used for the map
  if( fscanf(fp,"%i",&Editor.Song) <= 0 ) return;

  // Get map global environment (0 = space, 1 = earth)
  if( fscanf(fp,"%i",&Editor.Env) <= 0 ) return;

  // Get graphics sheet
  if( fscanf(fp,"%i",&Editor.Tileset) <= 0 ) return;

  MAP = (int*) realloc(MAP, sizeof(int)*(Editor.Width*Editor.Height));
  if( MAP == NULL )
    return;

  for( y = 0; y < Editor.Height; y++ ){
    for( x = 0; x < Editor.Width; x++ ){
      if( fscanf(fp,"%2i",&flag1) <= 0 )
        return;
      *(MAP+y*Editor.Width+x) = flag1;
    }
  }

  // Start loading map objects
  printf("Loading Objects...\n");
  while( (fscanf(fp,"%s",dp)) > 0 ){
    if( strcmp(dp, "SPAWN") == 0 ){ // Found Spawn
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("SPAWN --> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_SPAWN,flag1,flag2,0);
      Editor.Ex = x/32;
      Editor.Ey = y/32;
    } else if( strcmp(dp, "DISC") == 0){
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_DISC,flag1,flag2,0);
    } else if( strcmp(dp, "CAP") == 0){
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_CAPACITOR,flag1,flag2,0);
    } else if( strcmp(dp, "LAUNCHER") == 0 ){ // Found Blaster Weapon
      printf("Loading BLASTER Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_LAUNCHER,flag1,flag2,0);
    } else if( strcmp(dp, "RAILGUN") == 0 ){ // Found Railgun Weapon
      printf("Loading RAILGUN Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_RAILGUN,flag1,flag2,0);
    } else if( strcmp(dp, "TRAILGUN") == 0 ){ // Found Trailgun Weapon
      printf("Loading TRAILGUN Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_TRAILGUN,flag1,flag2,0);
    } else if( strcmp(dp, "SHIELD") == 0 ){ // Found Shield
      printf("Loading SHIELD Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_SHIELD,flag1,flag2,0);
    } else if( strcmp(dp, "BATTERY") == 0 ){ // Found Battery
      printf("Loading BATTERY Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_BATTERY,flag1,flag2,0);
    } else if( strcmp(dp, "SLUGS") == 0 ){ // Found Slugs
      printf("Loading SLUGS Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_SLUGS,flag1,flag2,0);
    } else if( strcmp(dp, "ARMOR") == 0 ){ // Found Blaster Weapon
      printf("Loading ARMOR Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_ARMOR,flag1,flag2,0);
    } else if( strcmp(dp, "HEALTH") == 0 ){ // Found Blaster Weapon
      printf("Loading HEALTH Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_HEALTH,flag1,flag2,0);
    } else if( strcmp(dp, "GRENADES") == 0 ){ // Found Blaster Weapon
      printf("Loading GRENADES Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_GRENADES,flag1,flag2,0);
    } else if( strcmp(dp, "SENSOR") == 0 ){ // Found Blaster Weapon
      printf("Loading SENSOR Object, located at ");
      if(fscanf(fp,"%i %i %i %i", &x, &y, &flag1, &flag2) <= 0)
        return;
      printf("--> %i, %i\n",x,y);
      Editor.NumObjects++;
      SetEditorObject(Editor.NumObjects,x,y,ITEM_SENSOR,flag1,flag2,0);
    }
  }

  fclose(fp);
}


void InitEditor(void){
  strcpy(Editor.EdTexFile,"gfx/map/tiles0.tga");
  GFX.LoadTexture(Editor.EdTexFile,&Editor.EdTex[0]);
  usleep(10000);

  strcpy(Editor.EdTexFile,"gfx/map/tiles1.tga");
  GFX.LoadTexture(Editor.EdTexFile,&Editor.EdTex[1]);
  usleep(10000);

  strcpy(Editor.EdTopTexFile,"gfx/menu/editor.tga");
  GFX.LoadTexture(Editor.EdTopTexFile,&Editor.EdTopTex);
  usleep(10000);

  strcpy(Editor.EdItemsTexFile,"gfx/models/objects.tga");
  GFX.LoadTexture(Editor.EdItemsTexFile,&Editor.EdItemsTex);
  usleep(10000);

  Editor.Ex = 0;
  Editor.Ey = 0;
  Editor.SetTile = 0;
  Editor.Width = 32;
  Editor.Height = 32;
  Editor.Song = 3;
  Editor.Env = 2;
  Editor.Tileset = 0;
  Editor.Zoom = 1;
  strcpy(Editor.Name,"Mission Begins");

  Editor.NumObjects = 0;

  for( int k = 0; k < NUMEDOBJ; k++ ){
    Editor.Object[k].used = 0;
  }

  MAP = (int*) realloc(MAP, sizeof(int)*(Editor.Width*Editor.Height));
  memset(MAP,0,sizeof(int)*Editor.Width*Editor.Height);
}

#endif	/* EDITOR_H */

