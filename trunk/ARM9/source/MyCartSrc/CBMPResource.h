#ifndef CBMPRESOURCE_H_
#define CBMPRESOURCE_H_
#include "nds.h"


#ifdef __GNUC__
 #define __PACKED __attribute__ ((__packed__))
#else
 #define __PACKED 
 #pragma pack(1)
#endif


typedef struct
{
    __PACKED    u8 bfType[2];
    __PACKED    u32 bfSize;
    __PACKED    u16 bfReserved1;
    __PACKED    u16 bfReserved2;
    __PACKED    u32 bfOffset;
    __PACKED    u32 biSize;
    __PACKED    u32 biWidth;
    __PACKED    u32 biHeight;
    __PACKED    u16 biPlanes;
    __PACKED    u16 biBitCount;
    __PACKED    u32 biCopmression;
    __PACKED    u32 biSizeImage;
    __PACKED    u32 biXPixPerMeter;
    __PACKED    u32 biYPixPerMeter;
    __PACKED    u32 biClrUsed;
    __PACKED    u32 biCirImportant;
} TBMPHeader; 

typedef struct
{

    __PACKED    u32 Palette[256];
    __PACKED    u32 DataWidth;

} TBMPHeader2; 


class CBMPResource
{
public:
	CBMPResource(u8 *Buffer);
    CBMPResource(char *pathname);
	virtual ~CBMPResource();
	
	TBMPHeader  m_bmpHD ;
	u16*        m_p16data ;
	u8*        m_pOrgdata ;
	
	u32         GetBMPWidth();
    u32         GetBMPHeight();
    u32         GetBitCount();
    u8*         GetOriginalData();
    u16*        Get16bitData();
};

#endif /*CBMPRESOURCE_H_*/
