#ifndef ards_h
#define ards_h

/*
'�ļ���1-12�ֽ��ǹ̶�����
'�ļ���13-15�ֽ�Ӧ���Ǹÿ�İ汾�ţ�1.0Ϊ��00 01 00 00
'���������ݿ������ַ���
'��Ϸ�б��100h��ʼ���ṹΪ��һ����Ϣ4��DWORLD���ֱ��ǣ�GameCode��GameCRC������ָ��ʼ��ַ������
'��Ϸ�б������־Ϊ������4���ֶζ�Ϊ0
'ÿ����Ϸ�Ľ���ָ���ݸ�ʽ��
'������һ���ַ���������С��40h����\0���뵽4��������������\0��������Ϸ˵��
'Ȼ����һ��DWORD���Ǹ���Ϸ��Ŀ�������壬ע������folder��������û�н���ָ��Ŀ������Ҳ����Ŀ������һ�������ֵҪ��FFFFFFFh
'Ȼ����8��DWORD�����庬��δ֪
'������Ǿ������Ŀ��ÿ��Ŀ�ĸ�ʽ��
'������һ��DWORD����ʾ����Ŀ���ͣ��������ֽڲ�Ϊ0��ʾΪfolder�������ʾcode��
'    ������Ϊfolderʱ��XYZZZZZZ��X��ʾfoler��Y��ʾ��one hot��ZZZZZZ�Ǳ�folder���������code����������XYһ����1��
'    ������Ϊcodeʱ��XY=0��Z�ĺ��岻��
'Ȼ����2���ַ������ֱ�������Ŀ��Name��Note����2���ַ�������Ҫ��\0���룬ʹ2���ַ������Ⱥ���4����������Ϊ���չ�32λϵͳ����
'�����folder�����Ŀ���˽����������code�����滹��ARDS��Σ���ʽΪ��ARDS���С+ARDS��
'   ARDS���С��1��DWORD��ʾ
'   ARDS����n��DWORD��ÿ2��DWORD����һ����䣬�����Ƹ�ʽ
*/
typedef struct _ARCHEAT{
	char	*pDescription;//����ָ����
	uint32  datasize;//����ָ��С
	uint32	*pData;//����ָ����
}ARCHEAT;

typedef struct _AR_DATA{
	char	*pFunction;//ע��1
	char	*pFunction2;//ע��2
	ARCHEAT ARCheat;
	bool	bFolder;//�Ƿ����ļ���
	bool	bUse;//��������ָ�Ƿ�ʹ��
	bool    bOneHot;
	bool 	bSub;
	bool	bExpd;//�ļ���չ����������
	uint32  SubCnt;//�ļ��������Ŀ��
	_AR_DATA *pARNextData;
	_AR_DATA *pARPreData;
}AR_DATA;

typedef struct _NDSCheatInfo{
  char		sign[5];
  uint32	dw_CRC; 
  uint32	dw_StartAddress;
} NDSCheatInfo;
//�������
typedef struct _IFFUN{
	uint32 index;
	vuint32 *pPos;
}IFFUN;

extern AR_DATA	*m_pARDataHead;
extern uint32	m_CheatItemCounter;
extern uint32	m_FirstLevelCIC;
uint32  crc32(uint32   crc,unsigned   char   *buf,   uint32   len) ;
NDSCheatInfo *FindNDSCheatInfo(char *sign,uint32 RomCRC);
bool GetCheatData(NDSCheatInfo *pInfo);
bool DeleteAR_DATA();
void PrintfARDSData();
//uint32 AnalyzeData(AR_DATA *pARData,uint32 off);
//void PrintfARDSData();
//uint32 FillARDSCheatData();
//void CleanbHotItem(AR_DATA *pARDataCurItem);



#endif










