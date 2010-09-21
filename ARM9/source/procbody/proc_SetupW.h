#ifndef PROC_SETUPW_H_
#define PROC_SETUPW_H_




typedef struct {  
  UnicodeChar FileName[256];
  char FullPathAlias[256];
} TSetupRom;
extern  TSetupRom SetupRom;

extern void SetFlag3(void);
extern void ClearFlag3(void);
extern bool GetFlag3(void);

extern void SetKoreanFlg();
extern void ClearKoreanFlg();
extern bool GetKoreanFlg();

extern void SetFrenchFlg();
extern void ClearFrenchFlg();
extern bool GetFrenchFlg();




#endif /*PROC_SETUPW_H_*/
