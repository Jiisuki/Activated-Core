

#ifndef _PLAYER_H
#define _PLAYER_H

#include "global.h"

#define Max 4
#define HMax 1.5

#define HITDMG 30

typedef enum
{
    Player_Team_Red,
    Player_Team_Blue,
    Player_Team_Yellow,
    Player_Team_Green,
} Player_Team_t;

typedef enum
{
    Player_JumpStrength_Environment0 = -9,
    Player_JumpStrength_Environment1 = -8,
    Player_JumpStrength_Environment2 = -7,
} Player_JumpStrength_t;

typedef enum
{
    Player_Animation_Standing,              /* Standing, first row in animation board */
    Player_Animation_Running,               /* Running, second row in animation board */
    Player_Animation_Firing,                /* Standing still and firing */
    Player_Animation_FiringRunning,         /* Running and firing */
    Player_Animation_FiringRunningBack,     /* Running backwards and firing (not used for the moment) */
    Player_Animation_JumpAssist,            /* Using jump assist */
    Player_Animation_InTheAir,              /* Flying in the air (or falling) */
    Player_Animation_FiringInTheAir,        /* Firing in the air (or falling + firing) */
    Player_Animation_AirShaft,              /* Using the airshaft (flaps) */
    Player_Animation_Jumping,               /* Jumping */
    Player_Animation_JumpingAndRunning,     /* Jumping when running */
    Player_Animation_JumpingAndRunningBack, /* Jumping when running backwards (not used) */
    Player_Animation_Crouching,             /* Crouching */
    Player_Animation_Crawling,              /* Crawling */
} Player_Animation_t;

typedef enum
{
    Player_State_OnTheGround,
    Player_State_InTheAir,
    Player_State_Crouching,
    Player_State_Freeze,
    Player_State_Jetpack,
    Player_State_Firing,
    Player_State_Dead,
} Player_State_t;

typedef enum
{
    Player_Move_Stop,
    Player_Move_Left,
    Player_Move_Right,
    Player_Move_Up,
    Player_Move_Down,
} Player_Move_t;


#define WALL_GRAV_DEC 64
#define SPEED_CHANGE_COEFF 32



#define CHAR_ITEM_NUMBER_OF_DISCS 4


class cls_Character
{
private:
    GLuint Tex;
    char Filename[64];
    bool TextureLoaded;
    struct StructAnimation
    {
        int  AnimationState;
        float PosInc;
        int  Position;
        int  Length;
        bool ReverseFlag;
        int  Model;
        int  Menu;  /* Only for selecting character in menues */
    } animation; /* Animation info */
  struct StructPhysics{
    struct StructPosition{
      float X;
      float Y;
    }Position;
    struct StructSpeed{
      float XSpeed;
      float YSpeed;
      float XMax;
      float XSpeedTarget;
      float YSpeedTarget;
      float SpeedJet;
      float ASpeed;
      float YMax;
      float YMaxDmg;
      float YMin;
      float Angle;
      float AngleChange;
    }Speed;
    int State;
    bool Jet;
  }Physics;   /* Position, speed, etc */
  struct StructAboutPlayer{
    char Name[32];
    char TeamName[32];
    int  Team;
  }About;     /* Name, Teamname, etc */
  struct StructPlayerSettings{
    int Crosshair;
    int CrosshairAnimation;
  }Settings;  /* Player Custom settings */
  struct StructPlayerStatus{
    int Health;
    int HealthMax;
    int Armor;
    int ArmorMax;
    int Frags;
    int Deaths;
    int SpawnTime;
  }Status;    /* Health, frags, etc */
  struct StructPlayerItems{
    bool HeartSensor;
    bool Capacitor;
    bool GotSuit;
    bool Shield;
    bool GotDisk[CHAR_ITEM_NUMBER_OF_DISCS];
  }Items;
  cls_Weapon Weapon[4];
  int SelectedWeapon;
  //char AmmoName[32];
  bool GotWeapon[4];
  bool CanEnterTerminal;
  int ActiveTerminalID;
  int TerminalID;
  int TerminalScreen;
  int OperateElevator;
public:
  cls_Character();
  void SetName(const char *Name);
  const char *GetName();
  void SetTeam(int TeamNo, const char *TeamName);
  const char *GetTeamName();
  int GetTeamNo();
  void SetAnimation(int NewState, int Length, int Menu, int Model, int Position, bool ReverseFlag);
  void StepAnimationFrame(bool Backward);
  void SetStatus(int Health, int HealthMax, int Armor, int ArmorMax, int Frags, int Deaths, int SpawnTime);
  void ChangeHealth(int Change);
  void SetCrosshair(int Crosshair);
  void SpawnPlayer(bool KeepPowerups);
  void PrintDebugInfo();
  int GetPosX();
  void SetSpeedX(int RelIncX);
  int GetPosY();
  void SetSpeedY(int RelIncY);
  void PerformPhysics();
  void SetItem(int Item, int Index, bool Val);
  GLuint *GetTex();
  char *GetFilename();
  void BuildAnimations();
  void KillTexture();
  void DrawPlayer();
  void Jump(int MF);
  void Move(int MF);
  void Crouch(bool On);
  void Fire();
  void SwitchWeapon(bool Prev);
  float GetHealth();
  float GetArmor();
  float GetAmmo();//char *AmmoName);
  void SetCharEnv(int Env);
  bool GotWeaponInv(int N);
  int GetWeaponSel();
  bool GotItemInv(int N);
  bool GotDiscInv(int N);
  void ControlElevator(int Operate);
  void Jet(bool Enable);
};
#endif
