#ifndef PROC_GBA_H_
#define PROC_GBA_H_

typedef struct {  
  UnicodeChar FileName[256];
  char FullPathAlias[256];
} TGBAInfo;
extern  TGBAInfo GBAInfo;



extern void UpdataWindows(void);
extern uint32 gl_ShakeID;


#endif /*PROC_GBA_H_*/
