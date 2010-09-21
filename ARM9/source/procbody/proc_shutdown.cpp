
#include <nds.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_console.h"
#include "_consolewritelog.h"
#include "maindef.h"
#include "memtool.h"
#include "_const.h"
#include "lang.h"
#include "BootROM.h"

#include "procstate.h"
#include "launchstate.h"
#include "datetime.h"

#include "glib/glib.h"

#include "fat2.h"
#include "shell.h"
#include "ErrorDialog.h"

#include "skin.h"
#include "component.h"
#include "sndeff.h"
#include "lang.h"
#include "mediatype.h"
#include "../../ipc6.h"


extern "C" {
void VRAMWriteCache_Enable(void);
void VRAMWriteCache_Disable(void);
}
//--------------------------
#define SYSColor1  ColorTable.ZV_SYSTEM.SYS_Color1
#define SYSColor2  ColorTable.ZV_SYSTEM.SYS_Color2

static bool isPressRect11=false;
static bool isPressRect12=false;

const TRect  menurect00={78,81,50,31};
const TRect  menurect01={78+60,81,50,31};

static void CB_CancelBtn_Click(void *pComponentButton)
{
  SetNextProc(ENP_FileList,EPFE_CrossFade);
}

// -----------------------------

static void CB_KeyPress(u32 VsyncCount,u32 Keys)
{
 
 if((Keys&KEY_A)!=0){
	 IPC6->LCDPowerControl=LCDPC_SOFT_POWEROFF;
  }
  
  if((Keys&KEY_B)!=0){

	CB_CancelBtn_Click(NULL);
  }
  if((Keys&(KEY_LEFT|KEY_RIGHT|KEY_UP|KEY_DOWN))!=0){}
}

static void CB_MouseDown(s32 x,s32 y)
{
	}

static void CB_MouseMove(s32 x,s32 y)
{
	
}

static void CB_MouseUp(s32 x,s32 y)
{
	if(isInsideRect(menurect00,x,y)==true)
	{
		 IPC6->LCDPowerControl=LCDPC_SOFT_POWEROFF;
	}
	if(isInsideRect(menurect01,x,y)==true)
	{
	 	CB_CancelBtn_Click(NULL);
	}	
}

static void gausscolor50bk(CglCanvas *pcan)
{
  CglCanvas *psrccan=new CglCanvas(NULL,ScreenWidth,ScreenHeight,pf15bit);
  pcan->BitBltFullBeta(psrccan);
  
  CglCanvas *pdstcan=new CglCanvas(NULL,ScreenWidth,ScreenHeight,pf15bit);
  pdstcan->FillFull(RGB15(0,0,0)|BIT15);
  
  for(u32 y=1;y<(ScreenHeight-1);y++){
    u16 *psrcbufm1=psrccan->GetScanLine(y-1);
    u16 *psrcbuf=psrccan->GetScanLine(y);
    u16 *psrcbufp1=psrccan->GetScanLine(y+1);
    u16 *ptagbuf=pdstcan->GetScanLine(y);
    for(u32 x=1;x<(ScreenWidth-1);x++){
      u32 c0=psrcbuf[x];
      u32 c1=psrcbufm1[x];
      u32 c2=psrcbuf[x-1];
      u32 c3=psrcbuf[x+1];
      u32 c4=psrcbufp1[x];
      u32 c5=psrcbufm1[x-1];
      u32 c6=psrcbufm1[x+1];
      u32 c7=psrcbufp1[x-1];
      u32 c8=psrcbufp1[x+1];
      u32 r0=(c0&(0x1f<<0))>>0;
      u32 r1=(c1&(0x1f<<0))>>0;
      u32 r2=(c2&(0x1f<<0))>>0;
      u32 r3=(c3&(0x1f<<0))>>0;
      u32 r4=(c4&(0x1f<<0))>>0;
      u32 r5=(c5&(0x1f<<0))>>0;
      u32 r6=(c6&(0x1f<<0))>>0;
      u32 r7=(c7&(0x1f<<0))>>0;
      u32 r8=(c8&(0x1f<<0))>>0;
      u32 g0=(c0&(0x1f<<5))>>5;
      u32 g1=(c1&(0x1f<<5))>>5;
      u32 g2=(c2&(0x1f<<5))>>5;
      u32 g3=(c3&(0x1f<<5))>>5;
      u32 g4=(c4&(0x1f<<5))>>5;
      u32 g5=(c5&(0x1f<<5))>>5;
      u32 g6=(c6&(0x1f<<5))>>5;
      u32 g7=(c7&(0x1f<<5))>>5;
      u32 g8=(c8&(0x1f<<5))>>5;
      u32 b0=(c0&(0x1f<<10))>>10;
      u32 b1=(c1&(0x1f<<10))>>10;
      u32 b2=(c2&(0x1f<<10))>>10;
      u32 b3=(c3&(0x1f<<10))>>10;
      u32 b4=(c4&(0x1f<<10))>>10;
      u32 b5=(c5&(0x1f<<10))>>10;
      u32 b6=(c6&(0x1f<<10))>>10;
      u32 b7=(c7&(0x1f<<10))>>10;
      u32 b8=(c8&(0x1f<<10))>>10;
      u32 r=((r0*4)+((r1+r2+r3+r4)*2)+((r5+r6+r7+r8)*1))/(4+8+4);
      u32 g=((g0*4)+((g1+g2+g3+g4)*2)+((g5+g6+g7+g8)*1))/(4+8+4);
      u32 b=((b0*4)+((b1+b2+b3+b4)*2)+((b5+b6+b7+b8)*1))/(4+8+4);
      r=r/2;
      g=g/2;
      b=b/2;
      ptagbuf[x]=RGB15(r,g,b)|BIT15;
    }
  }
  
  pdstcan->BitBltFullBeta(pcan);
  
  delete psrccan; psrccan=NULL;
  delete pdstcan; pdstcan=NULL;
}

static CglCanvas *pMasterBG;
#include "mycartsrc/CBMPResource.h"
static void DrawOnlineHelp(void)
{

	CglCanvas *pTmpBM=new CglCanvas(NULL,ScreenWidth,ScreenHeight,pf15bit);
	pScreenSub->pCanvas->BitBltFullBeta(pTmpBM);
	
//	gausscolor50bk(pTmpBM);
     
	VRAMWriteCache_Enable();
	pTmpBM->BitBltFullBeta(pScreenSub->pCanvas);
	VRAMWriteCache_Disable();
	if(pTmpBM!=NULL)
	{
	    delete pTmpBM; pTmpBM=NULL;
	}  
}

static void UpdataShutDown(void)
{
	CglCanvas *pTmpBM=new CglCanvas(NULL,ScreenWidth,ScreenHeight,pf15bit);
	pScreenSub->pCanvas->BitBltFullBeta(pTmpBM);
	
	CglTGF * pbm2= ShutDownAlpha_GetSkin(ESDSA_ShutDownBG);
	pbm2->BitBlt(pTmpBM,0,0);
	
	
	pTmpBM->SetCglFont(pCglFontDefault);
	pTmpBM->SetFontTextColor(SYSColor1);//设置字体颜色黑色  

     
	VRAMWriteCache_Enable();
	pTmpBM->BitBltFullBeta(pScreenSub->pCanvas);
	VRAMWriteCache_Disable();
	if(pTmpBM!=NULL)
	{
	    delete pTmpBM; pTmpBM=NULL;
	}   


}

static void CB_Start(void)
{
   lcdMainOnTop();
   DrawOnlineHelp(); 
}

static void CB_VsyncUpdate(u32 VsyncCount)
{

	UpdataShutDown();
}	

static void CB_End(void)
{
  
}

void ProcShutDown_SetCallBack(TCallBack *pCallBack)
{
  pCallBack->Start=CB_Start;
  pCallBack->VsyncUpdate=CB_VsyncUpdate;
  pCallBack->End=CB_End;
  pCallBack->KeyPress=CB_KeyPress;
  pCallBack->MouseDown=CB_MouseDown;
  pCallBack->MouseMove=CB_MouseMove;
  pCallBack->MouseUp=CB_MouseUp;
}

