
/*========================================================================================================================*/
/*                                                                                                                        */
/*                                              A C T I V A T E D   C O R E                                               */
/*                                                                                                                        */
/*   Activated Core is a game which intends to mix several game genres, including platforming, action, puzzle and more.   */
/*   The first version was a tile based platformer only, which then expanded beyond the tiles with large bitmapped maps.  */
/*     This allowed for fast rendering which was needed back then. The game was originally programmed in Visual Basic,    */
/*   using the extraordinary powers of DirectDraw 4 in the DirectX library (chuckles). This was year 2004. By the means   */
/*   of switching permanently to Linux, the development of this version stopped, until May 20:th 2010. The game is now    */
/*                              beging completely rewritten in C++ using OpenGL  and GLUT.                                */
/*                                                                                                                        */
/*                                                                                                                        */
/*                                                                                                                        */
/*                                                B A S I C   S T O R Y                                                   */
/*                                                                                                                        */
/*   Our character (nameless at the moment) was given a mission to explore a distant planet. On her way back to earth,    */
/*   she discovered at a distance that the earch atmosphere now have a purple hue. As she is getting closer and closer    */
/*   she picks up a transmission from the headquarters. The distress call mentioning something about foreign lifeforms    */
/*    converting earth into a machine, before it vanishes. When entering through the atmosphere, the ship breaks down     */
/*    and crashes. Altough she survives, she is weak and most of the equipment was destroyed in the crash. What is she    */
/*                                          going to do, to save mankind?                                                 */
/*                                                                                                                        */
/*========================================================================================================================*/

/*========================================================================================================================*/
/*                                                                                                                        */
/*   This game (including all game content, excluding FMOD [fmod.org] and TGALoader.h) was created by André Lundkvist     */
/*                                             during the years 2004-2011.                                                */
/*                                                                                                                        */
/*    Considering the effort, if you feel that the code has been useful for any of your projects, or if you just want     */
/*    to say hello or give feedback, don't hesitate to contact Jiisuki Audio Lab at ( contact@jiisuki.net ), or visit     */
/*    Please visit WWW.JIISUKI.NET for more information about the company and the products available, for free or for     */
/*   purchase. The company main focus in modular audio equipment for musical creation, but also has some freeware signal  */
/*                                        processing software, games, and more.                                           */
/*                                                                                                                        */
/*========================================================================================================================*/

/*========================================================================================================================*/
/*                                                                                                                        */
/*                                                  D I S C L A M E R                                                     */
/*                                                                                                                        */
/*    This game and code is provided as is, the creator holds no responsibility for any crashes or destruction of data    */
/*                                  that occurs, because this should never happen anyway :P                               */
/*                                                                                                                        */
/*                         J U S T   G O   A N D   P L A Y   T H E   G A M E   A L R E A D Y !                            */
/*                                                                                                                        */
/*========================================================================================================================*/



/* main.cpp
 *
 * This file contains all needed class headers, main function and a few more.
 * The game is built on c++ classes, which depends on each other in a nasty way ;)
 * The dependencies are such that the include order in this file need to be the way
 * they are at the moment. I will consider changing the structure later on
 *
 */

/* Header files */
#include <GL/glut.h>             // GLUT library
#include <GL/gl.h>               // OpenGL32 library
#include <GL/glu.h>              // GLu32 library
#include <stdio.h>               // Standard file i/o
#include <stdlib.h>              // For malloc/free
#include <string.h>              // For string operations
#include <math.h>                // For math operations
#include <unistd.h>              // For sleep operations (get control of that fps)
#include <time.h>                // For time

#define pi 3.141592653589793

#include "include/global.h"      // For global settings of the game. cls_AC
#include "include/graphics.h"    // The cls_GfxFcns class (graphics functions, draw surface etc). Also holds variable for GLUT window
#include "include/gui.h"         // The cls_GUI class (Graphical User Interface), including console system
#include "include/sfx.h"         // The cls_SoundEngine class. Uses FMOD to play Sound and sound effects
#include "include/controls.h"    // The cls_Control class. Holds settings for the controls
#include "include/menu.h"        // The cls_Menu class. Holds the structure of all menus
#include "include/map.h"         // The cls_Map class. Loads and stores map information and data (textures, items etc)
#include "include/weaponry.h"
#include "include/player.h"      // The cls_Character class. This contains functions for the player (fire, jump, animation, etc)
#include "include/ai.h"
#include "include/starfield.h"   // The cls_Starfield class. As the name suggests, class for the background starfield
#include "include/font.h"        // The cls_Font class. All functions needed for writing text on the screen with this game
#include "include/configfiles.h" // The cls_ConfigurationFile class. Has functions to save and load profile settings
#include "include/intro.h"       // Header file for the intro sequence
#include "include/hud.h"         // Functions for drawing the Heads Up Display
#include "include/editor.h"


int InstructionScreen = 0;
#define NUM_INSTR_SCR 12

struct StrInstr{
  GLuint Tex;
  char TexFile[128];
  float Count;
  int Num;
} InstrObj;

/* LoadGLTextures()
 * Function to load all textures needed at the beginning of the game. */
void LoadGLTextures(){

  // Load fonts used by GUI and Menus.
  SYSTEM.SysMessage("Building Font 1");
  Font.BuildFont(0);
  SYSTEM.SysMessage("Building Font 2");
  Font.BuildFont(1);
  SYSTEM.SysMessage("Building Font 3");
  Font.BuildFont(2);
  SYSTEM.SysMessage("Loading HUD");
  HUD.BuildHud();
  
  strcpy(InstrObj.TexFile,"gfx/models/objects.tga");
  GFX.LoadTexture(InstrObj.TexFile, &InstrObj.Tex);
  usleep(10000);

  InitEditor();
  
};


/* SetupDefaultGUI()
 * Function to set up all GUI rectangles, colors etc. */
void SetupDefaultGUI(){
  SYSTEM.SysMessage("Console");
  GUI.ClearConsole();
}

/* SetupGameSettings()
 * This function prints some information and sets up some non-profile specific settings of the game */
void SetupGameSettings(){
  // Inform that the game is starting and print out when the game was compiled.
  SYSTEM.NewSection("Starting Activated Core");
  printf("File was %s\n",AC.GetCompiled());

  // Display loaded control bindings.
  SYSTEM.NewSection("Loading Control Scheme");
  Control.CheckBinds();

  // Setup default menu selection = Introduction
  SYSTEM.NewSection("Selecting Menu");
  Menu.SetMenuSelection(MENU_INTRO);
  Menu.SetItemSelection(0);

  // Load default GUI setup.
  SYSTEM.NewSection("Loading GUI Scheme");
  SetupDefaultGUI();

  // Load textures (build fonts etc)
  SYSTEM.NewSection("Loading Graphics");
  LoadGLTextures();

  // Code the introduction screen welcome text.
  SYSTEM.NewSection("Coding Text Segments");
  SYSTEM.SysMessage("Main Menu");
  Menu.lenwelc = Font.ScrambleText(40,1,"ACTIVATED CORE",&Menu.welc[0],&Menu.scrm[0]);
  // Code all introduction credits.
  SYSTEM.SysMessage("Introduction");
  InitIntro();

  // Start the sound system.
  SYSTEM.NewSection("Initializing Sound");
  Sound.PlayTune(MUSIC_TUNE_INTRO);
  printf("Playing.\n");

  // Game should now start...
  SYSTEM.NewSection("Activated Core Running");
  
}




/* QuitAC()
 * Function to handle the shutdown, freeing of memory resources, deleting textures etc. */
void QuitAC(){

  // Indicate new section and save profile settings.
  SYSTEM.NewSection("Powering Down Activated Core");
  SYSTEM.SysMessage("Saving Profile Settings");
  Profile.SaveProfileSettings();

  // Set no key repeat ignore. (default)
  SYSTEM.SysMessage("Restoring Keyboard");
  glutIgnoreKeyRepeat(0);

  // Kill window.
  SYSTEM.SysMessage("Destroying Window");
  glutDestroyWindow(Glut_Window);

  // Close FSound.
  SYSTEM.SysMessage("Stopping Sound");
  Sound.Close();

  // Unload any loaded map.
  SYSTEM.SysMessage("Destroying Textures");
  if( Map.GetLoaded() )
    Map.Unload();
  HUD.KillTexture();

  // Destroy font textures.
  SYSTEM.SysMessage("Destroying Fonts");
  int i;
  for( i = 0; i < NumFonts; i++ ){
    glDeleteTextures(1, Font.GetTex(i));
  }
    
  glDeleteTextures(1, &InstrObj.Tex);

  // Destroy player textures.
  Player.KillTexture();
  Enemy.KillTexture();

  free(MAP);

  glDeleteTextures(1, &Editor.EdItemsTex);
  glDeleteTextures(1, &Editor.EdTex[0]);
  glDeleteTextures(1, &Editor.EdTex[1]);
  glDeleteTextures(1, &Editor.EdTopTex);

  // Shutdown pretty much completed.
  SYSTEM.NewSection("Power Down Completed!");
  SYSTEM.SysMessage("Thank you for playing!");
  SYSTEM.SysMessage("");
  SYSTEM.SysMessage("Make sure to check out the website:");
  SYSTEM.SysMessage(AC.GetWebsite());


  // Exit the program. Normal termination.
  exit(0);
}

/* GameControl(unsigned char key)
 * Handles the key bindings when in the actual platforming gameplay. */
void GameControl(unsigned char key){
  if( key == Control.GetBoundKey(CTRL_KEY_ESCAPE) ){
    AC.SpecifyLoop(LOOP_MAIN_MENU);
    Sound.PlayTune(MUSIC_TUNE_INTRO);
    Map.Unload();
    Menu.SetMenuSelection(MENU_MAIN);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_UP) ){
    Player.ControlElevator(1);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_DOWN) ){
    Player.ControlElevator(-1);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_LEFT) ){
    Player.Move(CHAR_MOVE_LEFT);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_RIGHT) ){
    Player.Move(CHAR_MOVE_RIGHT);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_JETPAK) ){
    //Player.Jet(1);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_SWITCH_WEAPON) ){
    Player.SwitchWeapon(0);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_ACTION_1) ){
    Player.Fire();
  }
  if( key == Control.GetBoundKey(CTRL_KEY_ACTION_2) ){
    Player.Jump(CHAR_MOVE_UP);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_TEMPORARY_DEBUG_USAGE) ){
    Player.SpawnPlayer(0);
  }
  if( key == Control.GetBoundKey(CTRL_KEY_INC_EQ) ){
    AC.SetEquilibriumStrength(AC.GetEquilibriumStrength()+5);
    GFX.ResetLights();
  }
  if( key == Control.GetBoundKey(CTRL_KEY_DEC_EQ) ){
    AC.SetEquilibriumStrength(AC.GetEquilibriumStrength()-5);
    GFX.ResetLights();
  }
}

/* MenuInGameControl(unsigned char key)
 * Function to handle all in game menu control. Basically the same as the main menu,
 * but with fewer options and some things to handle resuming etc. */
void MenuInGameControl(unsigned char key){
if( key == Control.GetBoundKey(CTRL_KEY_ESCAPE) )
  AC.Quit();
}



/* MenuControl(unsigned char key)
 * Function to handle control of the main menu. */
void MenuControl(unsigned char key){
    char tmp[64] = {0};
    char tmpmap[32];

  /* If escape is pressed, kill everything. */
  if( key == Control.GetBoundKey(CTRL_KEY_ESCAPE) ){
    switch( Menu.GetMenu() ){
      case MENU_MAIN:
        AC.Quit();
        break;
      case MENU_SELECT_LEVEL:
        Menu.SetMenuSelection(MENU_MAIN);
        break;
      case MENU_SETUP_GAME:
        Menu.SetMenuSelection(MENU_MAIN);
        break;
      case MENU_START_LEVEL:
        Menu.SetMenuSelection(MENU_SETUP_GAME);
        break;
      case MENU_SETTINGS_MAIN:
        Menu.SetMenuSelection(MENU_MAIN);
        break;
      case MENU_INSTRUCTIONS:
        Menu.SetMenuSelection(MENU_MAIN);
        break;
      case MENU_SETTINGS_CONTROLS:
        Menu.SetMenuSelection(MENU_SETTINGS_MAIN);
        break;
      case MENU_SETTINGS_CHECK_BINDS:
        Menu.SetMenuSelection(MENU_SETTINGS_CONTROLS);
        break;
      case MENU_SETTINGS_SET_BINDS:
        Menu.SetMenuSelection(MENU_SETTINGS_CONTROLS);
        break;
      case MENU_SETTINGS_SFX:
        if( Sound.GetTune() != MUSIC_TUNE_INTRO )
          Sound.PlayTune(MUSIC_TUNE_INTRO);
        Menu.SetMenuSelection(MENU_SETTINGS_MAIN);
        break;
      case MENU_SETTINGS_GFX:
        Menu.SetMenuSelection(MENU_SETTINGS_MAIN);
        break;
      default:
        Menu.SetMenuSelection(MENU_MAIN);
        break;
    }
  }

  if( key == Control.GetBoundKey(CTRL_KEY_UP) ){
    if( Menu.GetMenu() != MENU_LOADING_MAP ) {
      Menu.MenuUp();
    }
  }
  if( key == Control.GetBoundKey(CTRL_KEY_DOWN) ){
    if( Menu.GetMenu() != MENU_LOADING_MAP ) {
      Menu.MenuDown();
    }
  }
  if( key == Control.GetBoundKey(CTRL_KEY_LEFT) ){
    switch( Menu.GetMenu() ){
      case MENU_SETTINGS_SFX:
        Sound.PlayPrev();
        sprintf(tmp,"%s",Sound.GetTuneName());
        Menu.SetOptionalText(tmp);
        break;
      case MENU_INSTRUCTIONS:
        if( --InstructionScreen < 0 )
          InstructionScreen = NUM_INSTR_SCR-1;
        break;
      default:
        break;
    }
  }
  if( key == Control.GetBoundKey(CTRL_KEY_RIGHT) ){
    switch( Menu.GetMenu() ){
      case MENU_SETTINGS_SFX:
        Sound.PlayNext();
        sprintf(tmp,"%s",Sound.GetTuneName());
        Menu.SetOptionalText(tmp);
        break;
      case MENU_INSTRUCTIONS:
        if( ++InstructionScreen >= NUM_INSTR_SCR )
          InstructionScreen = 0;
        break;
      default:
        break;
    }
  }
  if( key == Control.GetBoundKey(CTRL_KEY_ACTION_1) ){
    if( Menu.GetMenu() == MENU_INSTRUCTIONS ){}
      //Player.Fire();
  }
  if( key == Control.GetBoundKey(CTRL_KEY_ACTION_2) ){
    if( strcmp(Menu.GetItemName(0),"Quit") == 0 ){
      AC.Quit();
    }
  }
  if( key == Control.GetBoundKey(CTRL_KEY_CONFIRM_OPTION) ){
    switch( Menu.GetMenu() ){
      case MENU_INTRO:
        Menu.SetMenuSelection(MENU_MAIN);
        break;

      case MENU_LOADING_MAP:
        break;
        
      case MENU_SELECT_LEVEL:
        switch( Menu.GetItem() ){
          
          case 0:
            strcpy(tmpmap,"maps/map01");
            break;
          
          case 1:
            strcpy(tmpmap,"maps/map02");
            break;
            
          case 2:
            strcpy(tmpmap,"maps/map03");
            break;
            
          case 3:
            strcpy(tmpmap,"maps/map04");
            break;
            
          case 4:
            strcpy(tmpmap,"maps/map05");
            break;

          case 5:
            strcpy(tmpmap,"maps/custom01");
            break;

          case 6:
            strcpy(tmpmap,"maps/custom02");
            break;

          case 7:
            strcpy(tmpmap,"maps/custom03");
            break;

          default:
            strcpy(tmpmap,"maps/noname");
            break;
        }
        EditorLoadMap(tmpmap);
        AC.SpecifyLoop(LOOP_EDITOR);
        Sound.PlayTune(Editor.Song);
        break;

        case MENU_START_LEVEL:
        switch( Menu.GetItem() ){

          case 0:
            strcpy(tmpmap,"maps/map01");
            break;

          case 1:
            strcpy(tmpmap,"maps/map02");
            break;

          case 2:
            strcpy(tmpmap,"maps/map03");
            break;

          case 3:
            strcpy(tmpmap,"maps/map04");
            break;

          case 4:
            strcpy(tmpmap,"maps/map05");
            break;

          case 5:
            strcpy(tmpmap,"maps/custom01");
            break;

          case 6:
            strcpy(tmpmap,"maps/custom02");
            break;

          case 7:
            strcpy(tmpmap,"maps/custom03");
            break;

          default:
            strcpy(tmpmap,"maps/noname");
            break;
        }

        SYSTEM.NewSection("Loading Map"); // Create new logging section.
        Map.LoadMap(tmpmap); // Load map file.
        Player.SpawnPlayer(0); // Set player starting positions.
        Enemy.SpawnPlayer(0);
        AC.SpecifyLoop(LOOP_GAME); // Graphics Loop.
        break;

      case MENU_SETUP_GAME:
        switch( Menu.GetItem() ){
          case 0:
            AC.NumberOfPlayers(1);
            break;

          case 1:
            AC.SetGameMode(1);
            break;

          case 2:
            AC.GetSetLimits(LIM_F,1);
            if( AC.GetSetLimits(LIM_F,0) > 25 )
              AC.GetSetLimits(LIM_F,-26);
            break;

          case 3:
            AC.GetSetLimits(LIM_T,1);
            if( AC.GetSetLimits(LIM_T,0) > 25 )
              AC.GetSetLimits(LIM_T,-26);
            break;
            
          case 4:
            Menu.SetMenuSelection(MENU_START_LEVEL);
            Menu.SetItemString(5,Map.GetMapName("maps/custom01"));
            Menu.SetItemString(6,Map.GetMapName("maps/custom02"));
            Menu.SetItemString(7,Map.GetMapName("maps/custom03"));
            break;
        }
        break;

      case MENU_MAIN:
        switch( Menu.GetItem() ){
          case 0:
            Menu.SetMenuSelection(MENU_SETUP_GAME);
            break;
          case 1:
            Menu.SetMenuSelection(MENU_SELECT_LEVEL);
            Menu.SetItemString(5,Map.GetMapName("maps/custom01"));
            Menu.SetItemString(6,Map.GetMapName("maps/custom02"));
            Menu.SetItemString(7,Map.GetMapName("maps/custom03"));
            break;
          case 2:
            Menu.SetMenuSelection(MENU_SETTINGS_MAIN);
            break;
          case 3:
            Menu.SetMenuSelection(MENU_INSTRUCTIONS);
            break;
          case 4:
            AC.Quit();
            break;
          default:
            break;
        }
        break;

      case MENU_SETTINGS_MAIN:
        switch( Menu.GetItem() ){
          case 0:
            Menu.SetMenuSelection(MENU_SETTINGS_CONTROLS);
            break;
          case 1:
            Menu.SetMenuSelection(MENU_SETTINGS_SFX);
            break;
          case 2:
            Menu.SetMenuSelection(MENU_SETTINGS_GFX);
            break;
          default:
            break;
        }
        break;

      case MENU_INSTRUCTIONS:
//        switch( Menu.GetItem() ){
//          case 0:
//            Menu.SetMenuSelection(MENU_INSTRUCTIONS);
//            break;
//          case 1:
//            Menu.SetMenuSelection(MENU_SETTINGS_CONTROLS);
//            break;
//          case 2:
//            Menu.SetMenuSelection(MENU_SETTINGS_SFX);
//            break;
//          case 3:
//            Menu.SetMenuSelection(MENU_SETTINGS_GFX);
//            break;
//          default:
//            break;
//        }
        break;

        case MENU_SETTINGS_CONTROLS:
        switch( Menu.GetItem() ){
          case 0:
            Menu.SetMenuSelection(MENU_SETTINGS_CHECK_BINDS);
            break;
          case 1:
            Menu.SetMenuSelection(MENU_SETTINGS_SET_BINDS);
            break;
          default:
            break;
        }
        break;

        case MENU_SETTINGS_SFX:
        switch( Menu.GetItem() ){
          case 0:
            Menu.SetMenuSelection(MENU_SETTINGS_MAIN);
            break;
          default:
            break;
        }
        break;

        case MENU_SETTINGS_GFX:
        switch( Menu.GetItem() ){
          case 0:
            if( AC.GetFullscreen() ){
              AC.SetWindowed();
              Menu.SetOptionalText("Fullscreen Disabled");
            } else {
              AC.SetFullscreen();
              Menu.SetOptionalText("Fullscreen Enabled");
            }
            break;
          case 1:
            if( AC.GetResolution(0) >= AC.GetResolution(1) ){
              AC.SetResolution(0, AC.GetAspectRatio(0) );
            } else {
              AC.SetResolution(AC.GetResolution(0)+1,AC.GetAspectRatio(0));
            }
            Menu.SetOptionalText(AC.GetResolutionDesc());
            break;
          case 2:
            if( AC.GetAspectRatio(0) >= AC.GetAspectRatio(1) ){
              AC.SetResolution(AC.GetResolution(0), 0 );
            } else {
              AC.SetResolution(AC.GetResolution(0),AC.GetAspectRatio(0)+1);
            }
            Menu.SetOptionalText(AC.GetResolutionDesc());
            break;
          default:
            break;
        }
        break;

      default:
        break;
    }

  }
  
}








/* The function called whenever a key is released. */
void keyReleased(unsigned char key, int x, int y){
  if( AC.GetSpecifiedLoop() == LOOP_GAME ){
    if( key == Control.GetBoundKey(CTRL_KEY_LEFT) ){
      Player.Move(CHAR_MOVE_STOP);
    }
    if( key == Control.GetBoundKey(CTRL_KEY_RIGHT) ){
      Player.Move(CHAR_MOVE_STOP);
    }
    if( key == Control.GetBoundKey(CTRL_KEY_UP) ){
      Player.ControlElevator(0);
    }
    if( key == Control.GetBoundKey(CTRL_KEY_DOWN) ){
      Player.ControlElevator(0);
    }
    if( key == Control.GetBoundKey(CTRL_KEY_ACTION_2) ){
      Player.Jump(CHAR_MOVE_STOP);
    }
  }
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
  /* avoid thrashing this procedure */
  usleep(100);

  switch( AC.GetSpecifiedLoop() ){
    case LOOP_MAIN_MENU:
      MenuControl(key);
      break;
    case LOOP_GAME:
      GameControl(key);
      break;
    case LOOP_IN_GAME_MENU:
      MenuInGameControl(key);
      break;
    case LOOP_EDITOR:
      EditorControl(key);
      break;
    default:
      MenuControl(key);
      break;
  }

}

/* DrawMainGame()
 * This function draws the frames of the main platforming gameplay.
 * Including drawing of map, player, interface etc. */
void DrawMainGame(){
  time_t start,end;
  time(&start);

//  Map.SetLightSources(1);
  GFX.SetLightning(1);
    Map.DrawMap(AC.GetHalfW()-Player.GetPosX()-16,AC.GetHalfH()-Player.GetPosY()-16);
    Map.DrawMapObjects(Player.GetPosX(),Player.GetPosY());
    Enemy.DrawPlayer(Player.GetPosX(),Player.GetPosY());
    Player.DrawPlayer();
  GFX.SetLightning(0);

  // Print On Screen Message
  Font.glPrint(AC.GetHalfW()-strlen(GUI.ReadOSDMessage())*12/2,AC.GetHalfH()+24,GUI.ReadOSDMessage(),1);


  HUD.Update();

  // Update some Physics
  Player.PerformPhysics();
  Enemy.PerformPhysics();
  Player.StepAnimationFrame(0);
  Enemy.StepAnimationFrame(0);
  
  EnemyAI();

  //Font.glPrint(16,AC.GetScreenHeight()-48,Map.TMPT,0);

  //usleep(AC.GetProgramHoldTime());



  // Get FPS
  while(++AC.FPSc < 60){
    time(&end);
  }
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


void DrawInstructions(int Scr){
  glDisable(GL_LIGHTING);
  char tmp[32];
  int t,k;
  
  k = 32;
  t = Scr;
  
  sprintf(tmp,"Page %i",Scr+1);
  Font.glPrint(8,8,tmp,2);
  switch( Scr ){
    case 0:
      
      Font.glPrint(8,k,"HEALTH",1); k+=32;
      Font.glPrint(8,k,"The health object",0); k+=16;
      Font.glPrint(8,k,"will replenish some",0); k+=16;
      Font.glPrint(8,k,"health upon pickup",0); k+=32;
      Font.glPrint(8,k,"The amount of health",0); k+=16;
      Font.glPrint(8,k,"can vary from 0 to 100",0);
      t = 0;
      break;
      
    case 1:
      
      Font.glPrint(8,k,"ARMOR",1); k+=32;
      Font.glPrint(8,k,"The armor object",0); k+=16;
      Font.glPrint(8,k,"will replenish some",0); k+=16;
      Font.glPrint(8,k,"armor upon pickup",0); k+=32;
      Font.glPrint(8,k,"The amount of armor",0); k+=16;
      Font.glPrint(8,k,"can vary from 0 to 100",0);
      t = 8;
      break;
      
    case 2:
      
      Font.glPrint(8,k,"MEGAHEALTH",1); k+=32;
      Font.glPrint(8,k,"The megahealth object",0); k+=16;
      Font.glPrint(8,k,"will replenish all",0); k+=16;
      Font.glPrint(8,k,"health upon pickup.",0);
      t = 9;
      break;
      
    case 3:
      
      Font.glPrint(8,k,"SHIELD",1); k+=32;
      Font.glPrint(8,k,"The shield protects",0); k+=16;
      Font.glPrint(8,k,"against projectiles",0); k+=32;
      Font.glPrint(8,k,"The shield lasts for",0); k+=16;
      Font.glPrint(8,k,"an infinite time or",0); k+=16;
      Font.glPrint(8,k,"until it is dead",0);
      t = 14;
      break;
      
    case 4:
      
      Font.glPrint(8,k,"LAUNCHER",1); k+=32;
      Font.glPrint(8,k,"The launcher works",0); k+=16;
      Font.glPrint(8,k,"like a shotgun",0); k+=32;
      Font.glPrint(8,k,"Power:       2",0); k+=16;
      Font.glPrint(8,k,"Fragments:  64",0); k+=16;
      Font.glPrint(8,k,"Ammo Drain:  1",0);
      t = 3;
      break;
      
    case 5:
      
      Font.glPrint(8,k,"SHELLS",1); k+=32;
      Font.glPrint(8,k,"The launcher ammo",0);
      t = 10;
      break;
      
    case 6:
      
      Font.glPrint(8,k,"TRAILGUN",1); k+=32;
      Font.glPrint(8,k,"An enchanced",0); k+=16;
      Font.glPrint(8,k,"launcher",0); k+=32;
      Font.glPrint(8,k,"Power:       4",0); k+=16;
      Font.glPrint(8,k,"Fragments:  64",0); k+=16;
      Font.glPrint(8,k,"Ammo Drain:  5",0);
      t = 6;
      break;
      
    case 7:
      
      Font.glPrint(8,k,"SLUGS",1); k+=32;
      Font.glPrint(8,k,"The trailgun ammo",0);
      t = 12;
      break;
      
    case 8:
      
      Font.glPrint(8,k,"RAILGUN",1); k+=32;
      Font.glPrint(8,k,"Fire a beam of",0); k+=16;
      Font.glPrint(8,k,"destruction",0); k+=32;
      Font.glPrint(8,k,"Power:      10",0); k+=16;
      Font.glPrint(8,k,"Fragments:  96",0); k+=16;
      Font.glPrint(8,k,"Ammo Drain: 10",0);
      t = 7;
      break;
      
    case 9:
      
      Font.glPrint(8,k,"BATTERY",1); k+=32;
      Font.glPrint(8,k,"The powerful railgun",0); k+=16;
      Font.glPrint(8,k,"ammo. Get capacitor",0); k+=16;
      Font.glPrint(8,k,"to store more power",0);
      t = 11;
      break;
      
    case 10:
      
      Font.glPrint(8,k,"CAPACITOR",1); k+=32;
      Font.glPrint(8,k,"Allows more railgun",0); k+=16;
      Font.glPrint(8,k,"ammo to be stored",0);
      t = 5;
      break;
      
    case 11:
      
      Font.glPrint(8,k,"DATA DISC",1); k+=32;
      Font.glPrint(8,k,"Allows opening locked",0); k+=16;
      Font.glPrint(8,k,"doors and elevators",0);
      t = 2;
      break;
  }
  
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0,AC.GetScreenWidth(),AC.GetScreenHeight(),0,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslated(AC.GetScreenWidth()-64,16,0);
  glBindTexture(GL_TEXTURE_2D,InstrObj.Tex);
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
    glTexCoord2f(0.125*InstrObj.Num,       0.0625*t);        glVertex3f(  0, 32, 0);
    glTexCoord2f(0.125*InstrObj.Num+0.125, 0.0625*t);        glVertex3f( 32, 32, 0);
    glTexCoord2f(0.125*InstrObj.Num+0.125, 0.0625*t+0.0625); glVertex3f( 32,  0, 0);
    glTexCoord2f(0.125*InstrObj.Num,       0.0625*t+0.0625); glVertex3f(  0,  0, 0);
  glEnd();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  
  InstrObj.Count+=0.3;
  if( InstrObj.Count > 1 ){
    InstrObj.Num++;
    if( InstrObj.Num >= 8 )
      InstrObj.Num = 0;
    InstrObj.Count = 0;
  }
  
  glEnable(GL_LIGHTING);
}

void DrawMenu(){

  time_t start,end;
  time(&start);

  bool HoldASec[2] = {0};
  int i;

  switch( Menu.GetMenu() ){
    case MENU_INTRO:

      GFX.SetLightning(1);
      for( i = 0; i < 2; i++ ){
        if( IntroL[IntroCounter+i].Decode < IntroL[IntroCounter+i].LenText ){
          if( IntroL[IntroCounter+i].ScrambleData[IntroL[IntroCounter+i].Decode] > 0 ){
            IntroL[IntroCounter+i].Text[IntroL[IntroCounter+i].Decode]--;
            IntroL[IntroCounter+i].ScrambleData[IntroL[IntroCounter+i].Decode]--;
          } else {
            IntroL[IntroCounter+i].Decode++;
          }
          HoldASec[i] = 0;
        } else {
          HoldASec[i] = 1;
        }
        Font.glPrint(AC.GetHalfW()-strlen(IntroL[IntroCounter+i].Text)*12/2,AC.GetHalfH()-24+i*24,IntroL[IntroCounter+i].Text,i);

      }
      GFX.SetLightning(0);
      break;

    case MENU_MAIN:

      GFX.SetLightning(1);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(1))*12/2),AC.GetHalfH()-16,Menu.GetItemName(1),2);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(0))*12/2),AC.GetHalfH(),Menu.GetItemName(0),1); // Sel
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(2))*12/2),AC.GetHalfH()+16,Menu.GetItemName(2),2);
      GFX.SetLightning(0);

      if( Menu.decode < Menu.lenwelc ){
        if( Menu.scrm[Menu.decode] > 0 ){
          Menu.welc[Menu.decode]--;
          Menu.scrm[Menu.decode]--;
        } else {
          Menu.decode++;
        }
        const char *decm = "Decoding Message";
        if( Menu.ShowInfo ) Font.glPrint((AC.GetHalfW())-(strlen(decm)*12/2),AC.GetHalfH()/2-32,decm,0);
      }
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.welc)*12/2),AC.GetHalfH()/2,Menu.welc,1);

      
      break;
    case MENU_LOADING_MAP:

      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),0);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetOptinalInfo())*12/2),AC.GetHalfH()-8,Menu.GetOptinalInfo(),1);

      break;
      
    case MENU_SELECT_LEVEL:
    
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(1);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(1))*12/2),AC.GetHalfH()-16,Menu.GetItemName(1),2);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(0))*12/2),AC.GetHalfH(),Menu.GetItemName(0),1); // Sel
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(2))*12/2),AC.GetHalfH()+16,Menu.GetItemName(2),2);
      GFX.SetLightning(0);    
      //for( i = 0; i < Menu.GetNumItems(); i++ ){
      //  Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetFreeItemName(i))*12/2),AC.GetHalfH()-(16*Menu.GetItem())+16*i,Menu.GetFreeItemName(i),!Menu.IsSelected(i)+1);
      //}
      //GFX.SetLightning(0);
      break;

    case MENU_START_LEVEL:

      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(1);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(1))*12/2),AC.GetHalfH()-16,Menu.GetItemName(1),2);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(0))*12/2),AC.GetHalfH(),Menu.GetItemName(0),1); // Sel
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetItemName(2))*12/2),AC.GetHalfH()+16,Menu.GetItemName(2),2);
      GFX.SetLightning(0);
      break;

    case MENU_SETUP_GAME:

      char tmp[32];
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(0);

      Font.glPrint(96,AC.GetHalfH()-16,Menu.GetFreeItemName(0),!Menu.IsSelected(0)+1);
      sprintf(tmp,"%i",AC.NumberOfPlayers(0));
      Font.glPrint(320,AC.GetHalfH()-16,tmp,!Menu.IsSelected(0)+1);

      Font.glPrint(96,AC.GetHalfH(),Menu.GetFreeItemName(1),!Menu.IsSelected(1)+1); // Sel
      Font.glPrint(320,AC.GetHalfH(),AC.GetGameMode(),!Menu.IsSelected(1)+1);

      Font.glPrint(96,AC.GetHalfH()+16,Menu.GetFreeItemName(2),!Menu.IsSelected(2)+1);
      sprintf(tmp,"%i",AC.GetSetLimits(LIM_F,0));
      Font.glPrint(320,AC.GetHalfH()+16,tmp,!Menu.IsSelected(2)+1);

      Font.glPrint(96,AC.GetHalfH()+32,Menu.GetFreeItemName(3),!Menu.IsSelected(3)+1);
      sprintf(tmp,"%i",AC.GetSetLimits(LIM_T,0));
      Font.glPrint(320,AC.GetHalfH()+32,tmp,!Menu.IsSelected(3)+1);
      
      Font.glPrint(96,AC.GetHalfH()+64,Menu.GetFreeItemName(4),!Menu.IsSelected(4)+1);


      break;
      
    case MENU_SETTINGS_MAIN:

      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(1);
      for( i = 0; i < Menu.GetNumItems(); i++ ){
        Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetFreeItemName(i))*12/2),AC.GetHalfH()-(16*Menu.GetItem())+16*i,Menu.GetFreeItemName(i),!Menu.IsSelected(i)+1);
      }
      GFX.SetLightning(0);

      break;
    case MENU_INSTRUCTIONS:
      DrawInstructions(InstructionScreen);
      
      

      break;
    case MENU_SETTINGS_CONTROLS:

      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(1);
      for( i = 0; i < Menu.GetNumItems(); i++ ){
        Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetFreeItemName(i))*12/2),AC.GetHalfH()-(16*Menu.GetItem())+16*i,Menu.GetFreeItemName(i),!Menu.IsSelected(i)+1);
      }
      GFX.SetLightning(0);

      break;
    case MENU_SETTINGS_CHECK_BINDS:

      //Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(1);
      for( i = 0; i < CTRL_NUM_OF_CONTROL_KEYS-2; i++ ){
        Font.glPrint((AC.GetHalfW())-(strlen(Control.GetBoundString(i))*12/2),AC.GetHalfH()-(14*CTRL_NUM_OF_CONTROL_KEYS/2)+16*i,Control.GetBoundString(i),0);
      }
      GFX.SetLightning(0);

      break;
    case MENU_SETTINGS_SET_BINDS:

      //Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(1);
      for( i = 0; i < Menu.GetNumItems()-1; i++ ){
        Font.glPrint((AC.GetHalfW())-(strlen(Control.GetBoundString(i))*12/2),AC.GetHalfH()-(14*CTRL_NUM_OF_CONTROL_KEYS/2)+16*i,Control.GetBoundString(i),!Menu.IsSelected(i)+1);
      }
      GFX.SetLightning(0);

      break;
    case MENU_SETTINGS_SFX:

      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(1);
      for( i = 0; i < Menu.GetNumItems(); i++ ){
        Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetFreeItemName(i))*12/2),AC.GetHalfH()-(16*Menu.GetItem())+16*i,Menu.GetFreeItemName(i),!Menu.IsSelected(i)+1);
      }
      GFX.SetLightning(0);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetOptinalInfo())*12/2),AC.GetScreenHeight()-64,Menu.GetOptinalInfo(),0);

      break;
    case MENU_SETTINGS_GFX:

      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetMenuName())*12/2),AC.GetHalfH()/4,Menu.GetMenuName(),1);
      GFX.SetLightning(1);
      for( i = 0; i < Menu.GetNumItems(); i++ ){
        Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetFreeItemName(i))*12/2),AC.GetHalfH()-(16*Menu.GetItem())+16*i,Menu.GetFreeItemName(i),!Menu.IsSelected(i)+1);
      }
      GFX.SetLightning(0);
      Font.glPrint((AC.GetHalfW())-(strlen(Menu.GetOptinalInfo())*12/2),AC.GetScreenHeight()-24,Menu.GetOptinalInfo(),0);

      break;
    default:
      break;
  }

  // Slow stuff down a tad.
  while(++AC.FPSc < 60){
    time(&end);
  }
  
  AC.dif = AC.dif + difftime (end,start);
  if( AC.dif >= 1 ){
    sprintf(AC.FPS,"Running this screen at %i FPS",AC.FPSc);
    AC.FPSc = 0;
    AC.dif = 0;

    Menu.ShowInfo = !Menu.ShowInfo;
    Menu.InfoDelay++;
    if( Menu.InfoDelay > Menu.InfoDelayStop ){
      Menu.InfoDelay = 0;
      Starfield.SetFacing(int(rand()%360));
    }

    if( HoldASec[0] == HoldASec[1] && HoldASec[0] == 1 ){
      IntroWait++;
      if( IntroWait > 1 ){
        HoldASec[0] = 0;
        HoldASec[1] = 0;
        IntroCounter+=2;
        IntroWait = 0;
        if( IntroCounter > (INTROLINES - 2) ){
          IntroCounter = 0;
          Menu.SetMenuSelection(MENU_MAIN);
        }
      }
    }
  }
}





/* The main drawing function. */
void DrawGLScene()
{

  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity(); // Reset The View

  // Enable lighting for the stars
  GFX.SetLightning(1);
    DrawStarfield();
    Starfield.StarPhysics();
  GFX.SetLightning(0);
  
  switch( AC.GetSpecifiedLoop() ){
    case LOOP_MAIN_MENU:
      DrawMenu();
      break;
    case LOOP_GAME:
      DrawMainGame();
      break;
    case LOOP_IN_GAME_MENU:
      break;
    case LOOP_EDITOR:
      DrawEditor();
      break;
    default:
      DrawMenu();
      break;
  }
  if( AC.QuitConfirmed() )
    QuitAC();

  // since this is double buffered, swap the buffers to display what just got drawn.
  glutSwapBuffers();

  

}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
	  Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

//  glMatrixMode(GL_MODELVIEW);
}




































































int main(int argc, char **argv) 
{

  SYSTEM.NewSection("Writing Game Core Information");

  
  Profile.LoadProfileSettings();

  AC.SetLinScale(0);
  
  AC.PrintInformation();

  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(&argc, argv);  

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);

  glutInitWindowSize(AC.GetGameWidth(), AC.GetGameHeight());

  if( AC.GetFullscreen() ){
    glutInitWindowPosition(0, 0);
  } else {
    glutInitWindowPosition(200, 100);
  }

  Glut_Window = glutCreateWindow(AC.GetWindowTitle());

  glutDisplayFunc(&DrawGLScene);  

//  glutGameModeString("1280x960:32");
//  glutEnterGameMode();

  if( AC.GetFullscreen() == 1 ){
    glutFullScreen();
  }

  // Even if there are no events, redraw our gl scene.
  glutIdleFunc(&DrawGLScene);

  // Register the function called when our window is resized.
  glutReshapeFunc(&ReSizeGLScene);

  // Register the function called when the keyboard is pressed.
  glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(&keyPressed);
	glutKeyboardUpFunc(&keyReleased);
  
//  glutKeyboardFunc(&keyPressed);




  SetupGameSettings();

  /* Initialize our window. */
  GFX.InitGL(AC.GetScreenWidth(), AC.GetScreenHeight());

  Player.BuildAnimations(); // Load player textures (should only be done for the first mapload at the session)
  Enemy.BuildAnimations();


  AC.ConfirmInitiated();
  
  /* Start Event Processing Engine */  
  glutMainLoop();  

  return 1;
}

