#ifndef EnableCheatData_h
#define EnableCheatData_h


typedef struct _ARCHEATDATA{
	uint32  datasize;
	uint32	*pData;
}ARCHEATDATA;

extern ARCHEATDATA EnableCheatData[1024];
extern u32 EnableNum;
void EnableCheatDataPrintf(void);
void deleteEnableCheatData(void);

#endif

