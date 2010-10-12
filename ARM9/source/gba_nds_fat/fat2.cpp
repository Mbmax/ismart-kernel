
#include <stdio.h>
#include <stdlib.h>
#include <nds.h>
#include "string.h"
#include "../_console.h"
#include "../_consoleWriteLog.h"
#include "../libs/memtool.h"

#include "fat2.h"
#include "gba_nds_fat.h"
#include "disc_io.h"
#include "shell.h"

extern __declspec(noreturn) void ShowLogHalt(void);

// Link from gba_nds_fat.

extern int filesysRootDir;
extern int filesysRootDirClus;
extern int filesysFAT;
extern int filesysSecPerFAT;
extern int filesysNumSec;
extern int filesysData;
extern int filesysBytePerSec;
extern int filesysSecPerClus;
extern int filesysBytePerClus;

extern FS_TYPE filesysType;

#define FAT_ClustToSect(m) (((m-2) * filesysSecPerClus) + filesysData)

extern u8 globalBuffer[BYTE_PER_READ];

extern FAT_FILE openFiles[MAX_FILES_OPEN];

extern u32 wrkDirCluster;
extern int wrkDirSector;
extern int wrkDirOffset;

extern u32 curWorkDirCluster;

extern UnicodeChar lfnNameUnicode[MAX_FILENAME_LENGTH];

extern u32 FAT_LinkFreeCluster(u32 cluster);
extern u32 FAT_NextCluster(u32 cluster);
extern DIR_ENT FAT_DirEntFromPath (const char* path);

// -----------------------

bool FAT2_InitFiles(void)
{
  extern bool FAT_InitFiles(void);
  if(FAT_InitFiles()==false) return(false);
  
  return(true);
}

void FAT2_Disabled64kClusterMode(void)
{
  if((32*1024/512)<filesysSecPerClus){
    _consolePrintf("\nFatal error: The cluster size that exceeds 32kbyte is not supported.\n");
    ShowLogHalt();
  }
  
  extern void FAT_Disabled64kClusterMode(void);
  FAT_Disabled64kClusterMode();
}

bool FAT2_FreeFiles(void)
{
  extern bool FAT_FreeFiles(void);
  return(FAT_FreeFiles());
}

static u16 SystemDateTime_Date=0,SystemDateTime_Time=0;

void FAT2_SetSystemDateTime(TFAT2_TIME time)
{
  u16 Date=0,Time=0;
  
  Date|=(time.Year-1980)<<9;
  Date|=time.Month<<5;
  Date|=time.Day;
  
  Time|=time.Hour<<11;
  Time|=time.Minuts<<5;
  Time|=time.Second/2;
  
  SystemDateTime_Date=Date;
  SystemDateTime_Time=Time;
  
  FAT_SetSystemDateTime(Date,Time);
}

// -----------------------

u32 FAT2_GetFATType(void)
{
  switch (filesysType) 
  {
    case FS_UNKNOWN: return 0;
    case FS_FAT12: return 12;
    case FS_FAT16: return 16;
    case FS_FAT32: return 32;
    default: return 0;
  }
  
 return 0;
}

u32 FAT2_ClustToSect(u32 cluster)
{
  return(FAT_ClustToSect(cluster));
}

u32 FAT2_NextCluster(u32 cluster)
{
  return(FAT_NextCluster(cluster));
}

u32 FAT2_GetSecPerClus(void)
{
  return(filesysSecPerClus);
}

// -----------------------

FILE_TYPE FAT2_FindFirstFile (const char **pFilenameAlias)
{
  return(FAT_FindFirstFile(pFilenameAlias));
}

FILE_TYPE FAT2_FindNextFile (const char **pFilenameAlias)
{
  return(FAT_FindNextFile(pFilenameAlias));
}

// -----------------------

static TFAT2_TIME FAT2_FileTimeToTime (u16 fileTime, u16 fileDate)
{
  TFAT2_TIME ft;
  
  ft.Year = (fileDate >> 9) + 1980;    // years since midnight January 1970
  ft.Month = ((fileDate >> 5) & 0xf);  // Months since january
  ft.Day = fileDate & 0x1f;        // Day of the month

  ft.Hour = fileTime >> 11;        // hours past midnight
  ft.Minuts = (fileTime >> 5) & 0x3f;    // minutes past the hour
  ft.Second = (fileTime & 0x1f) * 2;    // seconds past the minute

  return(ft);
}

TFAT2_TIME FAT2_GetFileCreationTime(void)
{
  DIR_ENT *pDirEntry = &((DIR_ENT*) globalBuffer)[wrkDirOffset];
  
  TFAT2_TIME ft=FAT2_FileTimeToTime(pDirEntry->cTime,pDirEntry->cDate);
  
  return(ft);
}

TFAT2_TIME FAT2_GetFileLastWriteTime(void)
{
  DIR_ENT *pDirEntry = &((DIR_ENT*) globalBuffer)[wrkDirOffset];
  
  TFAT2_TIME ft=FAT2_FileTimeToTime(pDirEntry->mTime,pDirEntry->mDate);
  
  return(ft);
}

u32 FAT2_CurEntry_GetFileSize(void)
{
  DIR_ENT *pDirEntry = &((DIR_ENT*) globalBuffer)[wrkDirOffset];
  return(pDirEntry->fileSize);
}

u32 FAT2_GetFirstCluster(void)
{
  DIR_ENT *pDirEntry = &((DIR_ENT*) globalBuffer)[wrkDirOffset];
  u32 firstCluster = pDirEntry->startCluster | (pDirEntry->startClusterHigh << 16);
  return(firstCluster);
}

u8 FAT2_GetAttrib (void)
{
  DIR_ENT *pDirEntry = &((DIR_ENT*) globalBuffer)[wrkDirOffset];
  return(pDirEntry->attrib);
}

const UnicodeChar* FAT2_GetLongFilenameUnicode(void)
{
  if(lfnNameUnicode[0]==0) return(NULL);
  return(lfnNameUnicode);
}

// -----------------------

bool FAT2_chdir_Alias(const char *pPathAlias)
{
  return(FAT_chdir(pPathAlias));
}

bool FAT2_remove(const char *pFilenameAlias)
{
  return(FAT_remove(pFilenameAlias));
}

// -----------------------

FAT_FILE* FAT2_fopen_AliasForRead(const char *pFilenameAlias)
{
  FAT_FILE *pf=FAT_fopen(pFilenameAlias,"r");
  return(pf);
}

FAT_FILE* FAT2_fopen_AliasForWrite(const char *pFilenameAlias)
{
  FAT_FILE *pf=FAT_fopen(pFilenameAlias,"w");
  return(pf);
}

FAT_FILE* FAT2_fopen_AliasForModify(const char *pFilenameAlias)
{
  FAT_FILE *pf=FAT_fopen(pFilenameAlias,"a");
  return(pf);
}

#include "FAT2_fopen_CreateForWrite_on_CurrentFolder.h"
#include "FAT2_fopen_CurrentForRead.h"

bool FAT2_fclose (FAT_FILE* file)
{
  return(FAT_fclose(file));
}

// -----------------------

u32 FAT2_ftell (FAT_FILE* file)
{
  return(FAT_ftell(file));
}

int FAT2_fseek(FAT_FILE* file, s32 offset, int origin)
{
  return(FAT_fseek(file,offset,origin));
}

// -----------------------

u32 FAT2_fread (void *pBuf, u32 size, u32 count, FAT_FILE* file)
{
  return(FAT_fread(pBuf,size,count,file));
}

u32 FAT2_fread_fast (void *pBuf, u32 size, u32 count, FAT_FILE* file)
{
  return(FAT_fread_fast(pBuf,size,count,file));
}

u32 FAT2_fwrite (const void *pBuf, u32 size, u32 count, FAT_FILE* file)
{
  return(FAT_fwrite(pBuf,size,count,file));
}

// -----------------------

u32 FAT2_GetFileSize(FAT_FILE *file)
{
  return(file->length);
}

// -----------------------

void FAT2_SetSize(FAT_FILE *file, const u32 size, const u8 FillChar)
{
  extern void FAT2_SetSize_CallBack_ProgressStart(void);
  extern void FAT2_SetSize_CallBack_ProgressDraw(u32 pos,u32 max);
  extern void FAT2_SetSize_CallBack_ProgressEnd(void);
  
  if(file->length!=0){
    _consolePrintf("Fatal error: FAT2_SetSize already file size is not zero.\n");
    ShowLogHalt();
  }
  
  if(file->write==false){
    _consolePrintf("Fatal error: FAT2_SetSize file handle is not write mode.\n");
    ShowLogHalt();
  }
  
  FAT2_SetSize_CallBack_ProgressStart();
  
  u32 SecPerClus=FAT2_GetSecPerClus();
  u32 blocksize=SecPerClus*512;
  u8 *pblockbuf=(u8*)safemalloc(blocksize);
  if(pblockbuf==NULL){
    _consolePrintf("Fatal error: FAT2_SetSize block memory overflow.\n");
    ShowLogHalt();
  }
  
  MemSet32CPU((FillChar<<0)|(FillChar<<8)|(FillChar<<16)|(FillChar<<24),pblockbuf,blocksize);
  
  u32 ClusListMax=(size+blocksize-1)/blocksize;
  u32 *pClusList=(u32*)safemalloc(ClusListMax*4);
  if(pClusList==NULL){
    _consolePrintf("Fatal error: FAT2_SetSize Cluster list memory overflow.\n");
    ShowLogHalt();
  }
  
  MemSet32CPU(0,pClusList,ClusListMax*4);
  
  u32 ClusListCount=0;
  
  {
    _consolePrint("FAT2_SetSize: Reserve cluster.\n");
    
    u32 curClus=file->curClus;
    u32 reqsize=size;
    
    if(reqsize!=0){
      pClusList[ClusListCount++]=curClus;
      FAT2_SetSize_CallBack_ProgressDraw(ClusListCount,ClusListMax*2);
      if(blocksize<=reqsize){
        reqsize-=blocksize;
        }else{
        reqsize=0;
      }
    }
    
    while(reqsize!=0){
      curClus=FAT_LinkFreeCluster(curClus);
      if((curClus==0)||(curClus==CLUSTER_FREE)){
        FAT_fclose(file);
        _consolePrintf("Fatal error: FAT2_SetSize disk full.\n");
        ShowLogHalt();
      }
      pClusList[ClusListCount++]=curClus;
      FAT2_SetSize_CallBack_ProgressDraw(ClusListCount,ClusListMax*2);
      if(blocksize<=reqsize){
        reqsize-=blocksize;
        }else{
        reqsize=0;
      }
    }
  }
  
  file->length=size;
  FAT_freopen(file);
  
  if(FillChar != 0xAB){
    _consolePrint("FAT2_SetSize: Initial data area.\n");
    
    extern LPIO_INTERFACE active_interface;
    
    for(u32 idx=0;idx<ClusListCount;idx++){
      u32 curClus=pClusList[idx];
      if((curClus==0)||(curClus==CLUSTER_FREE)){
        FAT_fclose(file);
        _consolePrintf("Fatal error: FAT2_SetSize Initial error.\n");
        ShowLogHalt();
      }
      u32 curSec=FAT_ClustToSect(curClus);
      if(curSec==0){
        FAT_fclose(file);
        _consolePrintf("Fatal error: FAT2_SetSize Initial error.\n");
        ShowLogHalt();
      }
      active_interface->fn_WriteSectors(curSec,blocksize/512,pblockbuf);
      FAT2_SetSize_CallBack_ProgressDraw(ClusListMax+idx,ClusListMax*2);
    }
  }
  
  safefree(pblockbuf); pblockbuf=NULL;
  
  safefree(pClusList); pClusList=NULL;
  
  FAT2_SetSize_CallBack_ProgressEnd();
  
  _consolePrint("FAT2_SetSize: Proceeded.\n");
}

// -----------------------
bool FAT2_move(const char *pFullPathAliasFrom,const char *pPathAliasTo,UnicodeChar *DesPath,UnicodeChar *FileName)
{
	FAT_movefile(pFullPathAliasFrom,pPathAliasTo,DesPath,FileName);
	
}
extern 	void videoSub_SetShowLog(bool);
static FAT_FILE *CreatFile( char *pFullPathAliasFrom,const char *pPathAliasTo,/*const char *pFilenameAlias,*/u32 DesSize)
{
	FAT_FILE *FileHandle=FAT2_fopen_AliasForRead(pFullPathAliasFrom);
    UnicodeChar* pUcode = (UnicodeChar* )FAT2_GetLongFilenameUnicode();
    FAT2_fclose(FileHandle);
    int j =0;
    do
    {
        _consolePrintf("%04x ",pUcode[j]);
        j++ ;
    }
    while(pUcode[j]);
        _consolePrintf("\n");
    _consolePrintf("***************\n");
    
    char a_saver[13];
    char *ap = strrchr(pFullPathAliasFrom,'/');
    _consolePrintf("\n a_saver2=%s ",ap);
    if(ap)
        ap++;    
    UnicodeChar w_saver[256];
    memcpy(a_saver,ap,13);
    _consolePrintf("\n a_saver1=%s ",a_saver);
    char* s = strchr(a_saver,'.');
   *(s+4)=0;
   
   
   _consolePrintf("\n a_saver=%s ",a_saver);
   
    memcpy(w_saver,pUcode,j*2);
    w_saver[j]=0;
    FAT_FILE *filePK ;
	const char *pafn; 
	UnicodeChar *pufn;
    FILE_TYPE fstype2 = FT_NONE;
    {   
    	FAT2_chdir_Alias(pPathAliasTo);
    	u32 FAT_FileType=FAT2_FindFirstFile(&pafn);
   
    	while(FAT_FileType!=FT_NONE)       	
    	{
	        pufn=(UnicodeChar* )FAT2_GetLongFilenameUnicode();
	        if(pufn==NULL)
	        {
	          _consolePrintf("FatalError: Can not read unicode filename.\n");
	          ShowLogHalt();
	          return;
	        }
	        if(FAT_FileType == FT_FILE)
	        {
	        	fstype2 =FT_FILE;   
	        	for (int namePos = 0; (namePos < MAX_FILENAME_LENGTH) && (pufn[namePos] != '\0') && (w_saver[namePos] != '\0'); namePos++)
	        	{
	        	 // if (( pufn[namePos] > 0x60) && ( pufn[namePos] < 0x7B))
	        	//	  pufn[namePos] -= 0x20;
	        	 // if (( w_saver[namePos] > 0x60) && ( w_saver[namePos] < 0x7B))
	        	//	  w_saver[namePos] -= 0x20;  
	        	 /// 
	        	  if (w_saver[namePos] != pufn[namePos])
	        	  {
	        		  fstype2 =FT_NONE;
	        		  break;
	        	  }	        	  
	        	}
	        }
	      if(fstype2 == FT_FILE) break;
	      FAT_FileType=FAT2_FindNextFile(&pafn);     
    	}//end while
    	
    	//FILE_TYPE fstype = FAT_FileExists(a_saver);
        if(fstype2 == FT_NONE)
        {

            //创建存档文件
            //MessageDialog_Draw(pScreenMainOverlay->pCanvas,(UnicodeChar *)L"Create SAVER");
            filePK = FAT2_fopen_CreateForWrite_on_CurrentFolder(a_saver,w_saver);
           	FAT2_SetSize(filePK,DesSize,0xAB); 
           	FAT2_fclose(filePK);
            //ClearMessageBox(pScreenMainOverlay->pCanvas);
        }
        else
        {
        	memcpy(a_saver,pafn,13);//用这个别名打开已有存档
        }
        FAT_FILE *pf=FAT2_fopen_AliasForWrite(a_saver);
        return pf;
    }

}
#include "../procbody/proc_CpyCut/proc_CpyCut.h"
bool FAT2_Copy(char *pFullPathAliasFrom,char *pFullPathAliasTo,const char *pPathAliasTo)//,const char *pFilenameAlias)
{	
	//videoSub_SetShowLog(true);
	FAT_FILE *FileSrc=FAT2_fopen_AliasForRead(pFullPathAliasFrom);
	u32 SrcSize=FAT2_GetFileSize(FileSrc);
	//创建Des文件
	FAT_FILE *FileDes=CreatFile(pFullPathAliasFrom,pPathAliasTo,/*pFilenameAlias,*/SrcSize);
	//拷贝文件
	{
		char puf[512];
		FAT2_fseek(FileSrc,0,SEEK_SET);
	//	u32 lenNum=SrcSize/512;
	//u32 StepNum=lenNum/175;
	//	u32 ProgressCnt=0;
		//TestPauseKey();
		for(u32 ii=0;ii<SrcSize;ii+=512)
		{
		
			SetProgressVal((ProgressVal*((ii+512)/512)/(SrcSize/512)));
			UpdataProgress();
			memset(puf,0,512);
			FAT2_fread(puf,512,1,FileSrc);
			FAT2_fwrite(puf,512,1,FileDes);		
		}
	}
	FAT2_fclose(FileSrc);
	FAT2_fclose(FileDes);	
}
//-----------------------------------------------------------
extern "C" uint32  A9_ReadSram(uint32 psramAdd);
extern void BootRomProgress(int iCnt,int flg);
FAT_FILE *CheckFile_in_Folder(char *CheckName,char*extname,char*Folder,uint32 createSize)
{
    FILE_TYPE fstype = FAT_FileExists(Folder); //大小写无关
    if(fstype == FT_DIR)
       _consolePrintf("Folder exist \n");
    else
    {
        _consolePrintf("Folder NOT exist \n");
        if(FAT_mkdir(Folder)==0)
        {
        	_consolePrintf("Folder Create success\n");
        }
        else
            _consolePrintf("Folder Create failed\n");
    }
    //检测文件是否存在
    FAT_FILE *FileHandle=FAT2_fopen_AliasForRead(CheckName);
    UnicodeChar* pUcode = (UnicodeChar* )FAT2_GetLongFilenameUnicode();
    FAT2_fclose(FileHandle);
    _consolePrintf(CheckName);_consolePrintf("\n"); 
    int j =0;
    do
    {
        _consolePrintf("%04x ",pUcode[j]);
        j++ ;
    }
    while(pUcode[j]);
        _consolePrintf("\n");
	_consolePrintf("*****[%s]*****\n",extname);
    char a_saver[13];
    char *ap = strrchr(CheckName,'/');
    if(ap)
        ap++;
    
    UnicodeChar w_saver[256];
    memcpy(a_saver,ap,13);
    char* s = strchr(a_saver,'.');
    *(s+1) = extname[0];
    *(s+2) = extname[1];
    *(s+3) = extname[2];
    *(s+4) = 0 ;
    memcpy(w_saver,pUcode,j*2);
    w_saver[j-3]=(UnicodeChar)extname[0];
    w_saver[j-2]=(UnicodeChar)extname[1];
    w_saver[j-1]=(UnicodeChar)extname[2];
    w_saver[j]=0;
    {//攻略2
    	if(createSize == 0x22)
    	{
    	    w_saver[j-4]=L'_';
    	    w_saver[j-3]=L'2';
    	    w_saver[j-2]=L'.';
    	    w_saver[j-1]=L'W';
    	    w_saver[j]=L'L';
    	    w_saver[j+1]=L'K';
    	    w_saver[j+2]=0;
    	}
    }
    FAT_FILE *filePK ;
	const char *pafn; 
	UnicodeChar *pufn;
	char pafn_temp[13];
	char count=0;
	memcpy(pafn_temp,a_saver,13);
    FILE_TYPE fstype2 = FT_NONE;

    //先检查文件是否存在
    FAT_chdir(Folder);
    u32 FAT_FileType=FAT2_FindFirstFile(&pafn);
   
    while(FAT_FileType!=FT_NONE)       	
    {
        if(!memcmp(a_saver,pafn,7))
        {
            memcpy(pafn_temp,pafn,13);
        	if(pafn[7] > count)
        	{
        		count = pafn[7];       				
        	}  
            pafn_temp[7] = count+1;
        }
        pufn=(UnicodeChar* )FAT2_GetLongFilenameUnicode();
	    if(pufn==NULL)
	    {
	    	_consolePrintf("FatalError: Can not read unicode filename.\n");
	    	ShowLogHalt();
	     	return ;
	    }
	    if(FAT_FileType == FT_FILE)
	    {
	    	fstype2 =FT_FILE;   
	    	for (int namePos = 0; (namePos < MAX_FILENAME_LENGTH) && (pufn[namePos] != '\0') && (w_saver[namePos] != '\0'); namePos++)
	        {
	    		if (( pufn[namePos] > 0x60) && ( pufn[namePos] < 0x7B))
	    			pufn[namePos] -= 0x20;
	    		if (( w_saver[namePos] > 0x60) && ( w_saver[namePos] < 0x7B))
	    			w_saver[namePos] -= 0x20;  
	        	  
	    		if (w_saver[namePos] != pufn[namePos])
	    		{
	    			fstype2 =FT_NONE;
	    			break;
	    		}	        	  
	        }
	    }
	    if(fstype2 == FT_FILE) break;
	    FAT_FileType=FAT2_FindNextFile(&pafn);     
    }//end while

    if(fstype2 == FT_NONE)
    { 	
    	if(!memcmp(extname,"sav",3)) BootRomProgress(150,2);//存档的进度
    	else if(!memcmp(extname,"SST",3))
    	{
        	//使用默认的
    		const char* pfullalias=ConvertFullPath_Ansi2Alias(DefaultDataPath"/message.SST");    
        	filePK = FAT2_fopen_AliasForRead(pfullalias);
    		if(filePK==NULL)
    		{
    			_consolePrint("Can not open message.SST file.\n");
    			//ShowLogHalt(); 
    			//return ;
    		}
        	_consolePrintf("not game.SST, use message.SST \n");
            return filePK;	
    	}
        filePK = FAT2_fopen_CreateForWrite_on_CurrentFolder(pafn_temp,w_saver);
        if(!memcmp(extname,"sav",3))
        {
        	if(A9_ReadSram(0x7DF80)==0xB01)//2436 必须初始化为0才正常 
        		FAT2_SetSize(filePK,createSize,0x00);
        	else
        		FAT2_SetSize(filePK,createSize,0xAB);
        }        
        else
        {
        	FAT2_SetSize(filePK,createSize,0xAB);
        }
        FAT2_fclose(filePK);
        memcpy(a_saver,pafn_temp,13);//用这个新别名打开新建文件
    }
    else
    {
    	memcpy(a_saver,pafn,13);//用这个别名打开已有文件
    	if(!memcmp(extname,"sav",3)) BootRomProgress(120,3);//存档的进度
    }
	_consolePrintf("Write file %s.\n",a_saver);
	//之前的代码已经解决了文件创建的问题
	if(!memcmp(extname,"DAT",3))
	{
		filePK=FAT2_fopen_AliasForModify(a_saver);
		if(filePK == NULL)
		{
			_consolePrintf("Fatal error: can't open DAT file.\n");
			ShowLogHalt();            
		}
	}
	else
	{
		filePK=FAT2_fopen_AliasForRead(a_saver);
	    if(filePK == NULL)
	    {
	    	_consolePrintf("Fatal error: can't open SAV file.\n");
	    	ShowLogHalt();            
	    }	
	}	
    return filePK;
}
