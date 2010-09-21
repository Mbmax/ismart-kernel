#ifndef SDSAVELIB_H_
#define SDSAVELIB_H_



extern uint32 *pSave2_23XX;
extern uint32 addsize;
/*extern "C"
{
    
    extern uint32 _End_function() ;
    extern uint16 _verify_str() ;
    extern void*  Search_DWORD(void* pstart, uint32 psize, uint32 data);
    extern uint32 patch_Saver_dirctSD();
    extern uint32 patch_Saver_dirctSD_thumb();
    extern uint32 VerifySaver_thumb();
    extern uint32 Mapping_SDRealAddress();
    
    extern uint32 special_for0991();
    
    extern void arm7Reset();
    extern void arm7Reset_wait();
    extern void RTS_arm9sendcommreset();
    extern void ITCM_DC_FlushAll();
    extern void PatchNDSGameITCM(uint32 game);
    extern void hybrid_Read512(uint32 add,u8* buf);
    extern void SendError(u32 k);    
}
extern void _consolePrintf(const char* format, ...);
extern uint32  dsCardi_WriteSram(uint32 address,uint16 data);*/
extern bool FindAndPatch_DirectSave(void* pBuffer,uint32 bfsize ,uint32* &packStart , uint32* &packEnd);

#endif /*SDSAVELIB_H_*/
