#ifndef inifile_h
#define inifile_h


typedef struct {
  s32 x,y,width,height;
  u16 color;
  char png1[128],png2[128];
} TiniSkinUserBody;

typedef struct {
  TiniSkinUserBody LightControl,ToggleControl,HelpControl,SystemControl,ShutDownContol,ScrollUP,ScrollDOWN,Launch,Gameicon,Gamename,/*Companyname*/Time/*Rumble*/;
}TiniSkinUser;

extern TiniSkinUser GlobalUserINI;

extern void InitINI_SkinUser(bool e);
extern void LoadINI_SkinUser(void);

#endif 
