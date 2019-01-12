/* 
 * File:   main.c
 * Author: nadlun-5
 *
 * Created on January 19, 2010, 7:28 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header File For sleeping.

// Constants
#define SCRW 80
#define SCRH 60
#define PW 8

// Public graphics stuff.
Display *dis;
Window win;
XEvent report;

char ARENA1[32][32]    = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                          1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

char Character[8][8]   = {0,0,0,1,1,0,0,0,
                          0,0,0,1,1,0,0,0,
                          0,0,1,1,1,1,0,0,
                          0,1,0,1,1,0,1,0,
                          0,1,0,1,1,0,1,0,
                          0,0,0,1,1,0,0,0,
                          0,0,1,0,0,1,0,0,
                          0,1,1,0,0,1,1,0};

int PutPixel(int X, int Y, int W, GC gc);
int BlitMap(char *, int X, int Y, int W, int H, GC gc);
int RunGame(void);

int main(void){

  // Initialize Main Window
  dis = XOpenDisplay(NULL);
  if( dis != 0 ){
    win = XCreateSimpleWindow(dis, RootWindow(dis,0),1,1,SCRW*PW,SCRH*PW,0,BlackPixel(dis,0),BlackPixel(dis,0));
    XMapWindow(dis,win);
    XFlush(dis);
  }else{
    return -1;
  }

  // Setup Input
  XSelectInput(dis,win,ExposureMask | KeyPressMask);

  int RF = 0;
  while( RF == 0 ){
    RF = RunGame();
    printf("RF = %i\n",RF);
  }

  XCloseDisplay(dis);

  printf("\n             Thank you for playing!\n\n");
  printf("       If you got the game from a friend,\n");
  printf("      make sure you check out the webside!\n");
  printf(" =============================================\n");
  printf("            http://www.jiisuki.net\n");
  printf(" =============================================\n\n");
  printf("     Created by: Jiisuki (Andre Lundkvist)\n\n");


  return 0;

}

int RunGame(void){
 
  char RunFlag = 1;
  
  // Prepare Colors
  Colormap colmap = DefaultColormap(dis,0);
  XColor dummy, black, fcol;
  char fclr[] = "#0FFF10";
  XAllocNamedColor(dis, colmap, "black", &black, &dummy);
  XParseColor(dis, colmap, fclr, &fcol);
  XAllocColor(dis, colmap, &fcol);

  // Load Font
  XFontStruct *font = XLoadQueryFont( dis, "fixed" );
  if( !font ){
    return -1;
  }

  // Setup more stuff
  XGCValues gv;
  gv.function = GXcopy;
  gv.line_width = 1;
  gv.foreground = fcol.pixel;
  gv.background = fcol.pixel;
  gv.font = font->fid;

  GC gc = XCreateGC(dis, RootWindow(dis,0), GCFunction | GCLineWidth | GCForeground | GCBackground | GCFont, &gv);

  // Setup more stuff
  XGCValues gv0;
  gv0.function = GXcopy;
  gv0.line_width = 1;
  gv0.foreground = black.pixel;
  gv0.background = black.pixel;
  gv0.font = font->fid;

  GC gc0 = XCreateGC(dis, RootWindow(dis,0), GCFunction | GCLineWidth | GCForeground | GCBackground | GCFont, &gv0);

  const char *loadtext1 = "+----------------+";
  const char *loadtext2 = "| ACTIVATED CORE |";
  const char *loadtext3 = "|    REWARPED    |";
  const char *loadtext4 = "+----------------+";
  const char *loadbrac = "[                ]";
  const char *loaddots = " **************** ";

  int fontHeight = font->ascent + font->descent;
  int loadtextWidth1 = XTextWidth(font,loadtext1,strlen(loadtext1));
  int loadtextWidth2 = XTextWidth(font,loadtext2,strlen(loadtext2));
  int loadtextWidth3 = XTextWidth(font,loadtext3,strlen(loadtext3));
  int loadtextWidth4 = XTextWidth(font,loadtext4,strlen(loadtext4));
  int loadbracWidth = XTextWidth(font,loadbrac,strlen(loadbrac));
  int loaddotsWidth = XTextWidth(font,loaddots,strlen(loaddots));

  XWindowAttributes attr;
  XGetWindowAttributes(dis,win,&attr);
  int w = attr.width, h = attr.height;

  // Run_Loop
  int i = (w-8*PW)/2;
  int j = (h+32*PW)/2-9*PW;
  int LIFE = strlen(loaddots)-1;
  while(RunFlag == 1){
    XFillRectangle(dis,win,gc0,0,0,w,h);
    BlitMap(*ARENA1, (w-32*PW)/2, (h-32*PW)/2, 32, 32, gc);
    BlitMap(*Character, i, j, 8, 8, gc);
    XDrawString(dis,win,gc,(w - loadtextWidth1)/2, fontHeight*2, loadtext1, strlen(loadtext1));
    XDrawString(dis,win,gc,(w - loadtextWidth2)/2, fontHeight*3, loadtext2, strlen(loadtext2));
    XDrawString(dis,win,gc,(w - loadtextWidth3)/2, fontHeight*4, loadtext3, strlen(loadtext3));
    XDrawString(dis,win,gc,(w - loadtextWidth4)/2, fontHeight*5, loadtext4, strlen(loadtext4));
    XDrawString(dis,win,gc,(w - loadbracWidth)/2, fontHeight*7, loadbrac, strlen(loadbrac));
    XDrawString(dis,win,gc,(w - loaddotsWidth)/2, fontHeight*7, loaddots, LIFE);
    XFlush(dis);

    XNextEvent(dis, &report);
    switch( report.type ){
      case KeyPress:
        if( XLookupKeysym(&report.xkey,0) == XK_Escape) {
          RunFlag = 0;
        }
        if( XLookupKeysym(&report.xkey,0) == XK_j){ i = i - PW; }else
        if( XLookupKeysym(&report.xkey,0) == XK_l){ i = i + PW; }else
        if( XLookupKeysym(&report.xkey,0) == XK_k){ j = j + PW; }else
        if( XLookupKeysym(&report.xkey,0) == XK_i){ j = j - PW; }else{
          j = j + PW;
          if( j > h-(8*PW) ){
            RunFlag = 0;
          }
        }
        break;
      default:
        break;
    }
    //Check Borders:
    if( i < (w-32*PW)/2 ){
      i = (w-32*PW)/2;
    }else if( i+8*PW > (w+32*PW)/2 ){
      i = (w+32*PW)/2-8*PW;
    }else if( j-PW < (h-32*PW)/2 ){
      j = (h-32*PW)/2+PW;
    }else if( j+9*PW > (h+32*PW)/2 ){
      j = (h+32*PW)/2-9*PW;
    }

    //LIFE++;
    //if( LIFE > strlen(loaddots)-1 ){
    //  RunFlag = 0;
    //}
  }

  const char *endtext1 = "This is the END";
  const char *endtext2 = "Jennifer RULEZ!";
  const char *endtext3 = "Press ESC to Quit, R to Restart";

  int endtextWidth1 = XTextWidth(font,endtext1,strlen(endtext1));
  int endtextWidth2 = XTextWidth(font,endtext2,strlen(endtext2));
  int endtextWidth3 = XTextWidth(font,endtext3,strlen(endtext3));

  RunFlag = 1;
  while(RunFlag == 1){
    XFillRectangle(dis,win,gc0,0,0,w,h);
    XDrawString(dis,win,gc,(w - endtextWidth1)/2, (h-fontHeight*4)/2, endtext1, strlen(endtext1));
    XDrawString(dis,win,gc,(w - endtextWidth2)/2, (h-fontHeight*2)/2, endtext2, strlen(endtext2));
    XDrawString(dis,win,gc,(w - endtextWidth3)/2, (h+fontHeight*2)/2, endtext3, strlen(endtext3));
    XFlush(dis);
    XNextEvent(dis, &report);
    switch( report.type ){
      case KeyPress:
        if( XLookupKeysym(&report.xkey,0) == XK_Escape) {
          RunFlag = -1;
        }
        if( XLookupKeysym(&report.xkey,0) == XK_r) {
          RunFlag = 0;
        }
        break;
      default:
        break;
    }
  }

  XFreeFont(dis,font);
  XFreeGC(dis,gc);
  return RunFlag;

}

int PutPixel(int X, int Y, int W, GC gc){
  XFillRectangle(dis,win,gc,X,Y,W,W);
  //XDrawLine(dis,win,gc,X,Y,X+W,Y+W);
}

int BlitMap(char *Image, int X, int Y, int W, int H, GC gc){
  int m = 0, n = 0;
  for( m = 0; m < H; m++ ){
    for( n = 0; n < W; n++ ){
      if( *(Image+(m*H)+n) != 0 ){
        PutPixel(X+(n*PW), Y+(m*PW), PW, gc);
      }
    }
  }
}


