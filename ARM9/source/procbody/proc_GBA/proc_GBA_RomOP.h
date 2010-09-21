#ifndef PROC_GBA_ROMOP_H_
#define PROC_GBA_ROMOP_H_


typedef struct {  
  UnicodeChar FileName[256];
  char FullPathAlias[256];
} TGBAOPInfo;
extern  TGBAOPInfo GBAOPInfo;

typedef struct 
{  
  char Sign[3];
  char SAlis[13];
  UnicodeChar WName[256]; 
}GbaTmp;
extern  GbaTmp GbaTmpInfo;

extern bool WriteGbaRomToNorFlash();
extern bool WriteGbaRomToPsRam();


extern void SetbEraseFlag(void);
extern void ClearbEraseFlag(void);
extern bool GetbEraseFlag(void);
extern void SetbWriteFlag(void);
extern void ClearbWriteFlag(void);
extern bool GetbWriteFlag(void);
extern void SetbSaveFlag(void);
extern void ClearbSaveFlag(void);
extern bool GetbSaveFlag(void);
extern void SetbSaveMagFlag(void);
extern void ClearbSaveMagFlag(void);
extern bool GetbSaveMagFlag(void);

extern u32 SetEraseProgressVal(u32 Val);
extern u32 GetEraseProgressVal();
#endif /*PROC_GBA_ROMOP_H_*/
