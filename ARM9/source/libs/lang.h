
#ifndef lang_h
#define lang_h

typedef struct {
  char *pItem;
  u32 ItemHash;
  char *pValue;
} TLangData;

#define MulLangDataMaxCount (256)
extern u32 MulLangDataCount;
extern TLangData MulLangData[MulLangDataMaxCount];

#define SkinMaxCount (256)
extern u32 SkinDataCount;
extern TLangData SkinData[SkinMaxCount];


extern void Lang_Load(void);
extern void Lang_Free(void);

extern void MulLang_Load(void);

extern void SkinData_Load(void);

extern const char* Lang_GetUTF8_internal(const char *pItemName,const char *pErrorMsg);

extern const char* Mul_Lang_GetUTF8_internal(const char *pItemName,const char *pErrorMsg);

extern const char* SkinData_GetUTF8_internal(const char *pItemName,const char *pErrorMsg);



#define Lang_GetUTF8(name) Lang_GetUTF8_internal(name,"LangErr:" name)
#define Mul_Lang_GetUTF8(name) Mul_Lang_GetUTF8_internal(name,"LangErr:" name)
#define SkinData_GetUTF8(name) SkinData_GetUTF8_internal(name,"LangErr:" name)




#endif
