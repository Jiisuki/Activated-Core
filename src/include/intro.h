

#define INTROLINES 16

struct StructIntro{
  char Text[32];
  int LenText;
  int ScrambleData[32];
  int Decode;
} IntroL[INTROLINES];


int IntroCounter = 0;
int IntroWait = 0;

void InitIntro(){

  int i, k;

  for( i = 0; i < INTROLINES; i++ ){
    for( k = 0; k < 32; k++ ){
      IntroL[i].Text[k] = 0;
      IntroL[i].ScrambleData[k] = 0;
    }
    IntroL[i].Decode = 0;
  }

  i = 0;
  k = 30;

  IntroL[i].LenText = Font.ScrambleText(k,1,"Jiisuki Audio Lab",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Proudly Presents",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"An Atmospherical Trip",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"towards our Core",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Created by",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Jiisuki Audio Lab",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Lead Designer",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"A. Lundkvist",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Lead Programmer",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"A. Lundkvist",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Graphics",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"A. Lundkvist",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Music",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Various",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,"Game Website",&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;
  IntroL[i].LenText = Font.ScrambleText(k,1,AC.GetWebsite(),&IntroL[i].Text[0],&IntroL[i].ScrambleData[0]); i++;

  IntroCounter = 0;
  IntroWait = 0;

}
