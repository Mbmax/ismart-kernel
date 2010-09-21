
#include <nds.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_console.h"
#include "_consolewritelog.h"
#include "maindef.h"
#include "memtool.h"
#include "_const.h"
#include "../../ipc6.h"
#include "datetime.h"
#include "arm9tcm.h"
#include "strpcm.h"
#include "lang.h"

#include "glib/glib.h"

#include "fat2.h"
#include "shell.h"
#include "sndeff.h"
#include "splash.h"
#include "resume.h"
#include "procstate.h"
#include "launchstate.h"
#include "strtool.h"
#include "unicode.h"
#include "rect.h"
#include "skin.h"
#include "cfont.h"
#include "BootROM.h"
#include "ErrorDialog.h"
#include "extlink.h"
#include "dll.h"
#include "dllsound.h"
#include "NDSROMIcon.h"
#include "cipk_simple.h"

#include "EnableCheatData.h"

ARCHEATDATA EnableCheatData[1024];
u32 EnableNum=0;
void EnableCheatDataPrintf()
{
	u32 idx=0;
	_consolePrintf("\n Num=%x",EnableNum);
	while(idx<EnableNum)
	{
		_consolePrintf("\n size=%x,pData=%x%x",EnableCheatData[idx].datasize,EnableCheatData[idx].pData[0],EnableCheatData[idx].pData[1]);	
		idx++;
	}	
}
void deleteEnableCheatData()
{
	u32 idx=0;
	_consolePrintf("\n Num=%x",EnableNum);
	while(idx<EnableNum)
	{
		if(EnableCheatData[idx].pData)
			safefree(EnableCheatData[idx].pData);
		idx++;
	}	
}