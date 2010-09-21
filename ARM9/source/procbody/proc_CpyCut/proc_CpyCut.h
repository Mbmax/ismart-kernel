#ifndef proc_CpyCut_h
#define proc_CpyCut_h


typedef struct {  
  UnicodeChar FileName[256];  
  UnicodeChar SrcPath[256];
  UnicodeChar DesPath[256];  
  char SrcFullPathAlias[256];  
  char DesFullPathAlias[256];
} TCpyCutFileInfo;
extern  TCpyCutFileInfo CpyCutFileInfo;



extern void SetX1Flag(void);
extern void ClearX1Flag(void);
extern bool GetX1Flag(void);

extern void SetX2Flag(void);
extern void ClearX2Flag(void);
extern bool GetX2Flag(void);

extern void SetY1Flag(void);
extern void ClearY1Flag(void);
extern bool GetY1Flag(void);

extern void SetY2Flag(void);
extern void ClearY2Flag(void);
extern bool GetY2Flag(void);

extern void SetClearAllFlgTrans(void);
extern void ClearClearAllFlgTrans(void);
extern bool GetClearAllFlgTrans(void);

extern u32 SetProgressVal(u32 Val);
extern void UpdataProgress(void);

extern u32 ProgressVal;
#endif