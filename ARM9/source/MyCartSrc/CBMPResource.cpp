#include "stdlib.h"
#include "string.h"
#include "CBMPResource.h"
#include "fat2.h"
#include "_console.h"
#include "shell.h"
#include "memtool.h"

extern void ShowLogHalt(void);

CBMPResource::CBMPResource(u8 *Buffer)
{
    m_p16data = NULL;
    m_pOrgdata = NULL;
    memset(&m_bmpHD,0,sizeof(TBMPHeader));
}

CBMPResource::CBMPResource(char *pathname)
{
    m_p16data = NULL;
    m_pOrgdata = NULL;
    FAT_FILE *pf = NULL;
    
    memset(&m_bmpHD,0,sizeof(TBMPHeader));
    const char *palias=ConvertFullPath_Ansi2Alias(pathname);
    if(palias!=NULL) pf=FAT2_fopen_AliasForRead(palias);
    if(pf==NULL)
    {
        _consolePrintf("not found '%s'. load default.\n",pathname);
        ShowLogHalt();
    }
    else
    {
        u32 filesize=FAT2_GetFileSize(pf);
        FAT2_fread(&m_bmpHD,1,sizeof(TBMPHeader),pf);
        if((m_bmpHD.biBitCount<16)||(m_bmpHD.biBitCount>32))
        {
            FAT2_fclose(pf);
            _consolePrintf("not supported BMP ,quit.\n");
            ShowLogHalt();
        }
        int size = m_bmpHD.biHeight*m_bmpHD.biWidth*(m_bmpHD.biBitCount>>3) ;
        if(m_bmpHD.biSizeImage>size)
        {
            m_pOrgdata = (u8*)safemalloc(m_bmpHD.biSizeImage);
        }
        else
            m_pOrgdata = (u8*)safemalloc(size);
        if(m_bmpHD.bfOffset!=sizeof(TBMPHeader))
        {
            FAT2_fseek(pf,m_bmpHD.bfOffset,SEEK_SET);
        }
        FAT2_fread(m_pOrgdata,1,m_bmpHD.biSizeImage,pf);
        FAT2_fclose(pf);
        _consolePrintf("readsize %x at %x\n",m_bmpHD.biSizeImage,m_pOrgdata);
    }
}

u32         CBMPResource::GetBMPWidth()
{
    return m_bmpHD.biWidth;
}

u32         CBMPResource::GetBMPHeight()
{
    return m_bmpHD.biHeight;
}

u32         CBMPResource::GetBitCount()
{
    return m_bmpHD.biBitCount;
}

u8*         CBMPResource::GetOriginalData()
{
    return m_pOrgdata ;
}

u16*        CBMPResource::Get16bitData()
{
    if(m_p16data == NULL)
    {
        int i ,j,k, wd , hd;
        int size = m_bmpHD.biWidth*m_bmpHD.biHeight*2;
        wd = m_bmpHD.biWidth ;
        hd = m_bmpHD.biHeight ;
        k = 0;
        switch(m_bmpHD.biBitCount)
        {
        case 16:
            m_p16data = (u16*)safemalloc(size);
             _consolePrintf("16bit mode\n");
            for(i=hd-1;i>=0;i--)
            {
                for(j=0;j<wd;j++)
                {
                    u8 b = ((u16*)m_pOrgdata)[k] & 0x1F;
                    u8 g = (((u16*)m_pOrgdata)[k]>>5)&0x1F;
                    u8 r = (((u16*)m_pOrgdata)[k]>>10)&0x1F;
                    k++;
                    m_p16data[i*wd+j] = RGB15(r,g,b)|0x8000;
                }

                   // m_p16data[i*wd+j] = ((u16*)m_pOrgdata)[k++]|0x8000;
            }
            break;
        case 24:
            m_p16data = (u16*)safemalloc(size);
            _consolePrintf("24bit mode\n");
            for(i=hd-1;i>=0;i--)
            {
                for(j=0;j<wd;j++)
                {
                    u8 b = m_pOrgdata[3*k+0]>>3;
                    u8 g = m_pOrgdata[3*k+1]>>3;
                    u8 r = m_pOrgdata[3*k+2]>>3;
                    k++;
                    m_p16data[i*wd+j] = RGB15(r,g,b)|0x8000;
                }
            }
            break;
        case 32:
            m_p16data = (u16*)safemalloc(size);
            _consolePrintf("32bit mode\n");
            for(i=hd-1;i>=0;i--)
            {
                for(j=0;j<wd;j++)
                {
                    u8 b = m_pOrgdata[4*i+0]>>3;
                    u8 g = m_pOrgdata[4*i+1]>>3;
                    u8 r = m_pOrgdata[4*i+2]>>3;
                    u16 a = m_pOrgdata[4*i+3]?0x8000:0;
                    m_p16data[i*wd+j] = RGB15(r,g,b)|a;
                }
            }
            break;
        }
        
        if(m_pOrgdata) safefree(m_pOrgdata);
        m_pOrgdata = NULL;
    }
    return m_p16data;
}


CBMPResource::~CBMPResource()
{
    if(m_pOrgdata) safefree(m_pOrgdata);
    m_pOrgdata = NULL;
    
    if(m_p16data) safefree(m_p16data);
    m_p16data = NULL;
}

