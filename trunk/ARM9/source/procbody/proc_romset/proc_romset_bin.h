#ifndef proc_romset_bin_h
#define proc_romset_bin_h

typedef struct {  
  bool SoftReset;
  bool RealtimeSave;
  bool GameGuide;
  bool CheatState;
  bool DownloadPlayState;
  bool SpeciaMode;
  u8 Speed;
} TRomSetState;
extern  TRomSetState RomSetState;
extern  TRomSetState RomSetStateTmp;
typedef struct {  
  UnicodeChar FileName[256];
  char FullPathAlias[256];
} TRomSetInfo;
extern  TRomSetInfo RomSetInfo;

extern void SetFlag(void);
extern void ClearFlag(void);

extern void SetFlag2(void);
extern void ClearFlag2(void);
extern bool GetFlag2(void);

extern void OpenRomData(void);
extern void CloseRomData(void);
extern u32 dsi(void);

#endif
