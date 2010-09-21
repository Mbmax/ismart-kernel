
#ifndef plug_ndsrom_h
#define plug_ndsrom_h

#define NDSROMTitle "NDSROM bootloader ver0.5"

__declspec(noreturn) extern void BootNDSROM(void);


extern "C"
{
    
    extern uint32 _End_function() ;
    extern uint16 _verify_str() ;
    extern void*  Search_DWORD(void* pstart, uint32 psize, uint32 data);
    
    extern void ITCM_DC_FlushAll();

    extern void hybrid_Read512(uint32 add,u8* buf); 
    extern void SendError(u32 k);  
}
#endif

