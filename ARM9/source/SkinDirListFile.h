#ifndef SKINDIRLISTFILE_H_
#define SKINDIRLISTFILE_H_


typedef struct _SkinListFile
{
	char Filename[256];
	char DispName[256];
}SkinListFile;

extern SkinListFile  ListFile[128];
extern int ListFileNum;

extern SkinListFile  MulLangListFile[128];
extern int MulLangListFileNum;

extern void ListSkinDirFile(void);
extern void printSkinFileList(void);
extern void ListMulLangFile(void);
extern void printMulLangFileList(void);

#endif /*SKINDIRLISTFILE_H_*/
