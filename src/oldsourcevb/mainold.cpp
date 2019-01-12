/* 
 * File:   main.c
 * Author: nadlun-5
 *
 * Created on January 19, 2010, 7:28 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/global.h"

/*
 * 
 */
/* Predefine Functions */
int ActivatedCoreBasics(struct StructActivatedCore *AC);
int PrintCoreBasics(struct StructActivatedCore *AC);
int StartGame(void);
int Defaults(struct StructGameSettings *GameSettings);

/* ======================================================================== */
/*  FUNCTIONS                                                               */
/* ======================================================================== */
int main(){
  struct StructActivatedCore AC; /* Basic information about the program */
  ActivatedCoreBasics(&AC); /* Setup basic information compiler time */

  PrintCoreBasics(&AC);
  StartGame();

}

int ActivatedCoreBasics(struct StructActivatedCore *AC){
  /* This function setup the basic information about Activated Core. */
  strcpy(AC->Author,"Andre Lundkvist");
  strcpy(AC->Website,"http://www.jiisuki.net");
  strcpy(AC->Version,"Linux: Alpha 0.1");
  strcpy(AC->Description,"Activated Core, Game");
  AC->Initiated = 0;
  return 0;
}

int PrintCoreBasics(struct StructActivatedCore *AC){
  printf("======================================\n");
  printf("    Activated Core Information Box    \n");
  printf("======================================\n");
  printf(" Author:      %s\n",AC->Author);
  printf(" Website:     %s\n",AC->Website);
  printf(" Version:     %s\n",AC->Version);
  printf(" Description: %s\n",AC->Description);
  printf("======================================\n\n");
  
  return 0;
}


int StartGame(void){

    UI.ConsoleEnabled = 1;
    UI.OSDMessage("Initializing Game Engine...");

    struct StructSpawn Spawnpoint[32];      /* Spawnpoints */
    char Spawnpoint_Count; /* Number of Spawnpoints */

    struct StructMapExtraTexture ExtraMapAnimation[32]; /* Animated Map Areas */
    char ExtraMapAnimation_Count; /* Number of Animated Map Areas */

    struct StructGameSettings GameSettings;       /* G_Settings holds the above information */
    Defaults(&GameSettings);

    struct StructCharacter Character[(GameSettings.MaxClients)]; /* Allocate maximum number of chars */

    UI.OSDMessage("Initialization Completed. Starting up...");
    UI.ConsoleEnabled = 0;

    return 0;

}

int Defaults(struct StructGameSettings *GameSettings){
    GameSettings->DarknessEnabled = 0;
    GameSettings->EquilibriumEnabled = 0;
    GameSettings->FragLimit = 0;
    GameSettings->InstagibEnabled = 0;
    GameSettings->Map = 1;
    GameSettings->MaxClients = 8;
    GameSettings->Mode = G_MODE_DUEL;
    GameSettings->NextMap = 2;
    GameSettings->NumberOfBots = 0;
    GameSettings->PowerupsEnabled = 0;
    GameSettings->Started = 0;
    GameSettings->TimeLimit = 10;
    strcpy(GameSettings->MapName,"NULL");
    strcpy(GameSettings->NextMapName,"NULL");
    strcpy(GameSettings->MessageOfTheDay[0],"   Welcome to My Server");
    strcpy(GameSettings->MessageOfTheDay[1],"==========================");
    strcpy(GameSettings->MessageOfTheDay[2],"  Using Default Settings");
    strcpy(GameSettings->MessageOfTheDay[3]," www.jiisuki.net/eb3k.asp");
}

