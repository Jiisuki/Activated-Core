
#include "fmod/fmod.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"

#define MUSIC_TUNE_INTRO     0
#define MUSIC_TUNE_TITLE     1
#define MUSIC_TUNE_CUTSCENE  2
#define MUSIC_TUNE_LOOP1     3
#define MUSIC_TUNE_LOOP2     4
#define MUSIC_TUNE_LOOP3     5
#define MUSIC_TUNE_LOOP4     6
#define MUSIC_TUNE_LOOP5     7
#define MUSIC_TUNE_LOOP6     8
#define MUSIC_TUNE_LOOP7     9
#define MUSIC_TUNE_LOOP8    10
#define MUSIC_TUNE_LOOP9    11
#define MUSIC_TUNE_LOOP10   12
#define MUSIC_TUNE_BOSS1    13
#define MUSIC_TUNE_BOSS2    14
#define MUSIC_GAME_OVER     15
#define MUSIC_CREDITS       16

#define MUSIC_NUMBER_OF_TUNES 17

#define SFX_HIT    0
#define SFX_FIRE   1
#define SFX_PICKUP 2
#define SFX_SPAWN  3

#define NUMBER_OF_SFX 4

void ERRCHECK(FMOD_RESULT result)
{
  if( result != FMOD_OK )
  {
    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
  }
}


class cls_SoundEngine{
private:
  FMOD::Sound *mod;
  FMOD::Channel *channel;
  FMOD::System *system;
  FMOD_RESULT result;
  int  SelectedTune;
  bool Playing;
  struct StructTune{
    bool Playable;
    char Filename[32];
    char Name[32];
  } Tune[MUSIC_NUMBER_OF_TUNES];
  struct StructSFX{
    bool Playable;
    char Filename[32];
  } SFX[NUMBER_OF_SFX];
  void LoadTune(int TuneSelect);
  void LoadSFX(int SfxSelect);
  void Init();
public:
  cls_SoundEngine();
  void Close();
  void PlayTune(int TuneSelect);
  void PlaySfx(int SfxSelect);
  const char *GetTuneName();
  void PlayPrev();
  void PlayNext();
  int GetTune();
};



cls_SoundEngine::cls_SoundEngine(){
  
  SelectedTune = MUSIC_TUNE_TITLE;
  Playing = 0;

  strcpy(Tune[MUSIC_TUNE_INTRO].Filename,    "music/intro.xm");
  strcpy(Tune[MUSIC_TUNE_INTRO].Name,        "Atmospheric Introduction");
  strcpy(Tune[MUSIC_TUNE_TITLE].Filename,    "music/title.xm");
  strcpy(Tune[MUSIC_TUNE_TITLE].Name,        "Title Music");
  strcpy(Tune[MUSIC_TUNE_CUTSCENE].Filename, "music/cutscene.xm");
  strcpy(Tune[MUSIC_TUNE_CUTSCENE].Name,     "What happens next?");
  strcpy(Tune[MUSIC_TUNE_LOOP1].Filename,    "music/loop1.xm");
  strcpy(Tune[MUSIC_TUNE_LOOP1].Name,        "Mission Begins");
  strcpy(Tune[MUSIC_TUNE_LOOP2].Filename,    "music/loop2.xm");
  strcpy(Tune[MUSIC_TUNE_LOOP2].Name,        "Headquarters");
  strcpy(Tune[MUSIC_TUNE_LOOP3].Filename,    "music/loop3.s3m");
  strcpy(Tune[MUSIC_TUNE_LOOP3].Name,        "Laboratory");
  strcpy(Tune[MUSIC_TUNE_LOOP4].Filename,    "music/loop4.s3m");
  strcpy(Tune[MUSIC_TUNE_LOOP4].Name,        "Weapon Factory");
  strcpy(Tune[MUSIC_TUNE_LOOP5].Filename,    "music/loop5.it");
  strcpy(Tune[MUSIC_TUNE_LOOP5].Name,        "Entrance Gate");
  strcpy(Tune[MUSIC_TUNE_LOOP6].Filename,    "music/loop6.xm");
  strcpy(Tune[MUSIC_TUNE_LOOP6].Name,        "The Monster");
  strcpy(Tune[MUSIC_TUNE_LOOP7].Filename,    "music/loop7.xm");
  strcpy(Tune[MUSIC_TUNE_LOOP7].Name,        "Tight Spaces");
  strcpy(Tune[MUSIC_TUNE_LOOP8].Filename,    "music/loop8.it");
  strcpy(Tune[MUSIC_TUNE_LOOP8].Name,        "The Empty Hive");
  strcpy(Tune[MUSIC_TUNE_LOOP9].Filename,    "music/loop9.s3m");
  strcpy(Tune[MUSIC_TUNE_LOOP9].Name,        "Closure");
  strcpy(Tune[MUSIC_TUNE_LOOP10].Filename,   "music/loop10.s3m");
  strcpy(Tune[MUSIC_TUNE_LOOP10].Name,       "Escape Elevator");
  strcpy(Tune[MUSIC_TUNE_BOSS1].Filename,    "music/boss1.xm");
  strcpy(Tune[MUSIC_TUNE_BOSS1].Name,        "Time to FIGHT!");
  strcpy(Tune[MUSIC_TUNE_BOSS2].Filename,    "music/boss2.xm");
  strcpy(Tune[MUSIC_TUNE_BOSS2].Name,        "Time to FIGHT! (Again)");
  strcpy(Tune[MUSIC_GAME_OVER].Filename,     "music/gameover.xm");
  strcpy(Tune[MUSIC_GAME_OVER].Name,         "Game Over!");
  strcpy(Tune[MUSIC_CREDITS].Filename,       "music/credits.xm");
  strcpy(Tune[MUSIC_CREDITS].Name,           "Credits");

  strcpy(SFX[SFX_HIT].Filename,   "sfx/hit.wav");
  strcpy(SFX[SFX_FIRE].Filename,  "sfx/weap1.wav");
  strcpy(SFX[SFX_PICKUP].Filename,"sfx/pickup.wav");
  strcpy(SFX[SFX_SPAWN].Filename, "sfx/spawn.wav");

  Init();

}

void cls_SoundEngine::Init(){
  
  channel = 0;
  unsigned int version;

  result = FMOD::System_Create(&system);
  ERRCHECK(result);

  result = system->getVersion(&version);
  ERRCHECK(result);

  if (version < FMOD_VERSION)
  {
    printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
    return;
  }

  result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
  ERRCHECK(result);

  result = system->init(32, FMOD_INIT_NORMAL, 0);
  ERRCHECK(result);
}

void cls_SoundEngine::LoadTune(int TuneSelect){

  result = system->createSound(Tune[TuneSelect].Filename, FMOD_SOFTWARE, 0, &mod);

  if (!mod){
    printf("Error loading song '%s'\n",Tune[TuneSelect].Filename);
    Tune[TuneSelect].Playable = 0;

  } else {
    printf("Loaded song '%s'\n",Tune[TuneSelect].Filename);
    Tune[TuneSelect].Playable = 1;
  }
}

void cls_SoundEngine::Close(){
  result = mod->release();
  ERRCHECK(result);
  result = system->close();
  ERRCHECK(result);
  result = system->release();
  ERRCHECK(result);
}

void cls_SoundEngine::PlayTune(int TuneSelect){

  if( Playing ){
    result = mod->release();
    Playing = 0;
    ERRCHECK(result);
  }

//  return;
  
  SelectedTune = TuneSelect;
  if( SelectedTune < 0 ) SelectedTune = MUSIC_NUMBER_OF_TUNES-1;
  if( SelectedTune >= MUSIC_NUMBER_OF_TUNES ) SelectedTune = 0;
  LoadTune(SelectedTune);

  if( Tune[SelectedTune].Playable ){
    result = system->playSound(FMOD_CHANNEL_FREE, mod, 0, &channel);
    printf("Playing song %s.\n",GetTuneName());
    Playing = 1;
  } else {
    printf("Not Playing!");
    Playing = 0;
  }
}

const char *cls_SoundEngine::GetTuneName(){
  return Tune[SelectedTune].Name;
}

void cls_SoundEngine::PlayNext(){
  int tmp = SelectedTune;
  PlayTune(++tmp);
}

void cls_SoundEngine::PlayPrev(){
  int tmp = SelectedTune;
  PlayTune(--tmp);
}

int cls_SoundEngine::GetTune(){
  if( !Playing )
    return -1;
  return SelectedTune;
}

void cls_SoundEngine::LoadSFX(int SfxSelect){
 result = system->createSound(SFX[SfxSelect].Filename, FMOD_SOFTWARE, 0, &mod);

  if (!mod){
    printf("Error loading song '%s'\n",SFX[SfxSelect].Filename);
    SFX[SfxSelect].Playable = 0;

  } else {
    SFX[SfxSelect].Playable = 1;
  }
}

void cls_SoundEngine::PlaySfx(int SfxSelect){
  /*if( Playing ){
    result = mod->release();
    Playing = 0;
    ERRCHECK(result);
  }*/

  return;
  LoadSFX(SfxSelect);

  if( SFX[SfxSelect].Playable ){
    result = system->playSound(FMOD_CHANNEL_FREE, mod, 0, &channel);
  }
}

cls_SoundEngine Sound;
