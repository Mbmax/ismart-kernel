1. Resources on the card:
	1)EEPROM, size 0x200000Byte, refer to SPI graphic for details
	2)SPAM, size0x800Byte, detail as below:
	//****************************************************
		0x0-0x600 reserved
		0x600 - cluster for RTS.bin  RTG fat table begins at 0x1000
		0x700 - 0x58050 - replace 0x5c000 - 4000000  registers backup //=0x4000240

		0x79C - for RTS, SDK_STATIC_BSS_START-0x2000; starting backup address 2000000
		0x7A8 - arm7 waiting code jump to reset address
		0x7AC - arm7 waiting code starting address
		
		0x7B0 - Special game sign position, enabled sign 0xF5A05259, General game without the sign
		0x7B4 - Special game setup position, saved position
		0x7B8 - reserved
		0x7BC - reserved
		
		0x7C0 - Soft Reset (Y/N)?
		0x7C4 - Cheat finger?
		0x7C8 - RTS (Y/N)?
		0x7CC - ARM7 Patched Code location 0x230000C - 0x2300600 ��This data is reserved for soft reset median
		
		0x7D0 - Start up Code of the 2nd process existence (Y/N)?
		0x7D4 - Saved code Asynchronous (Y/N)?  1 means synchronous��modification needed�� �� 0 means Asynchronous
		0x7D8 - Execute ReadRom synchronous (Y/N)?   1 means synchronous��modification needed�� �� 0 means Asynchronous
		0x7DC - Address for the current patched information, no need to look for game to patch on next startup. It can execute directly. This data is for ARM9 patch
		0x7E0 - SDHC sign
		0x7E4 - how many sectors per cluster
		0x7E8 - cluster 1 for debug.bin 
		0x7EC - cluster 2 for debug.bin
		0x7F0 - Special game
		0x7F4 - 1st cluster of the game
		0x7FC - address for debug information
	//***************************************************
2.Methods for visiting information
	1)EEPROM reads 0x4 Bytes:uint32 Mart_ReadFlashCommand(uint32 address)
	2)EEPROM reads 0x200 bytes:uint32  Mart_ReadFlash(uint32 address, uint8* pbuf)
	3)EEPROM erase 0x1000 bytes:void cardEepromBlockErase(uint32 address)
	4)EEPROM erase 0x10000 bytes:void cardEepromSectorErase(uint32 address)
	5)EEPROM writes :void cardWriteEeprom(uint32 address, uint8 *data, uint32 length, uint32 addrtype)
	6)SRAM reads 0x4 bytes:uint32  Mart_ReadSram4byte(uint32 address)
	7)SRAM writes0x4 bytes:uint32 dsCardi_WriteSram(uint32 address,uint16 data)
		for example:
		{    
		    temp = 0x12345678 ;
		    dsCardi_WriteSram(0x7dfdc , temp&0xFFFF);  
		    dsCardi_WriteSram(0x7dfde , (temp>>16)&0xFFFF); 
	    }
3.Special Notes
	1)ismart premium uses 0x1C0000-0x1E0000, total of 0x20000 Bytes for mapping of game FAT table
	//***************************************************
	ROM size	Byte/cluster  EEPROM 	
    512MBYTE  	- 4K   	-- use 0x80000 (cant use) 
              	- 8K   	-- use 0x40000 (cant use)
              	- 16K  	-- use 0x20000
              	- 32K  	-- use 0x10000
              
    256MBYTE  	- 4K   	-- use 0x40000 (cant use) 
              	- 8K   	-- use 0x20000
              	- 16K  	-- use 0x10000
              	- 32K  	-- use 0x8000
              
    128MBYTE  	- 4K   	-- use 0x20000 
              	- 8K   	-- use 0x10000
              	- 16K  	-- use 0x8000
              	- 32K  	-- use 0x4000
              
    64MBYTE   	- 4K   	-- use 0x10000 
              	- 8K   	-- use 0x8000
              	- 16K  	-- use 0x4000
              	- 32K  	-- use 0x2000
              
    32MBYTE   	- 4K   	-- use 0x8000 
              	- 8K   	-- use 0x4000
              	- 16K  	-- use 0x2000
              	- 32K  	-- use 0x1000 
              
    16MBYTE   	- 4K   	-- use 0x4000 
              	- 8K   	-- use 0x2000
              	- 16K  	-- use 0x1000
              	- 32K  	-- use 0x800
              
    8MBYTE    	- 4K   	-- use 0x2000 
              	- 8K   	-- use 0x1000
              	- 16K  	-- use 0x800
              	- 32K  	-- use 0x400  
	//***************************************************
	Therefore, you can not format your TF as 4K/cluster,, it has to more 8K/cluster or larger

	2)The red portion of the SPI graphics resource allocation can not be modified. Otherwise, iSmart Premium will not work.




#############################################################
1.���ϵ���Դ
	1)EEPROM,��С0x200000Byte,������俴SPIͼƬ
	2)SRAM,��С0x800Byte,�����������:
	//***************************************************
		0x0-0x600 ����
		0x600 - RTS.bin�ļ��Ĵ� 0x1000��ʼ�Ǽ�ʱ���Ե�fat��
		0x700 - 0x58050 - ���� 0x5c000 - 4000000 �Ĵ������� /=0x4000240
		
		0x79C - ��ʱ�浵����,SDK_STATIC_BSS_START-0x2000;��ʼ����2000000�ĵ�ַ
		0x7A8 - arm7�ȴ�����������reset�ĵ�ַ
		0x7AC - arm7�ȴ����뿪ʼ��ַ
		
		0x7B0 - ����������Ϸ���ñ�־λ�����ñ�־ 0xF5A05259 ���Ǵ˱�־��ʾͨ��
		0x7B4 - ����ĵ�ַ���ã������λ��
		0x7B8 - ����
		0x7BC - ����
		
		0x7C0 - �Ƿ���λ
		0x7C4 - �Ƿ����ָ
		0x7C8 - �Ƿ�ʱ�浵
		0x7CC - ARM7���벹�����������λ�� 0x230000C - 0x2300600 �������ݱ���Ϊ��λʱʹ�����м�ֵ
		
		0x7D0 - �ڶ����̵����������Ƿ����
		0x7D4 - �浵�����ͬ����� 1 ��ʾʹ��ͬ������Ҫ�޸ģ� �� 0 ��ʾ�첽
		0x7D8 - �Ƿ�ִ��ReadRom��ͬ����� 1.��ʾʹ��ͬ������Ҫ�޸ģ� �� 0 ��ʾ�첽
		0x7DC - ��ǰ�Ĵ򲹶���Ϣ�ĵ�ַ,���´��������Բ���Ѱ����Ϸ���в���������ֱ��ִ�� , ��������ARM9����
		0x7E0 - SDHC ��־
		0x7E4 - ÿ�ض��ٸ�sector
		0x7E8 - debug.bin�ļ��Ĵ�1
		0x7EC - debug.bin�ļ��Ĵ�2
		0x7F0 - ������Ϸ
		0x7F4 - ��Ϸ�ĵ�һ����
		0x7FC - debug��Ϣ��ַ
	//***************************************************
2.��Դ���ʷ���
	1)EEPROM��0x4�ֽ�:uint32 Mart_ReadFlashCommand(uint32 address)
	2)EEPROM��0x200�ֽ�:uint32  Mart_ReadFlash(uint32 address, uint8* pbuf)
	3)EEPROM����0x1000�ֽ�:void cardEepromBlockErase(uint32 address)
	4)EEPROM����0x10000�ֽ�:void cardEepromSectorErase(uint32 address)
	5)EEPROMд:void cardWriteEeprom(uint32 address, uint8 *data, uint32 length, uint32 addrtype)
	6)SRAM��0x4�ֽ�:uint32  Mart_ReadSram4byte(uint32 address)
	7)SRAMд0x4�ֽ�:uint32 dsCardi_WriteSram(uint32 address,uint16 data)
		for example:
		{    
		    temp = 0x12345678 ;
		    dsCardi_WriteSram(0x7dfdc , temp&0xFFFF);  
		    dsCardi_WriteSram(0x7dfde , (temp>>16)&0xFFFF); 
	    }
3.ע������
	1)�������ʹ��0x1C0000-0x1E0000,��0x20000Byte��С��Ϊ��ϷFAT���ӳ��.
	//***************************************************
	ROM size	Byte/cluster  EEPROM 	
    512MBYTE  	- 4K   	-- use 0x80000 (cant use) 
              	- 8K   	-- use 0x40000 (cant use)
              	- 16K  	-- use 0x20000
              	- 32K  	-- use 0x10000
              
    256MBYTE  	- 4K   	-- use 0x40000 (cant use) 
              	- 8K   	-- use 0x20000
              	- 16K  	-- use 0x10000
              	- 32K  	-- use 0x8000
              
    128MBYTE  	- 4K   	-- use 0x20000 
              	- 8K   	-- use 0x10000
              	- 16K  	-- use 0x8000
              	- 32K  	-- use 0x4000
              
    64MBYTE   	- 4K   	-- use 0x10000 
              	- 8K   	-- use 0x8000
              	- 16K  	-- use 0x4000
              	- 32K  	-- use 0x2000
              
    32MBYTE   	- 4K   	-- use 0x8000 
              	- 8K   	-- use 0x4000
              	- 16K  	-- use 0x2000
              	- 32K  	-- use 0x1000 
              
    16MBYTE   	- 4K   	-- use 0x4000 
              	- 8K   	-- use 0x2000
              	- 16K  	-- use 0x1000
              	- 32K  	-- use 0x800
              
    8MBYTE    	- 4K   	-- use 0x2000 
              	- 8K   	-- use 0x1000
              	- 16K  	-- use 0x800
              	- 32K  	-- use 0x400  
	//***************************************************
	���,���TF�����ܸ�ʽ��Ϊ4k�ֽ�ÿ��.������ڵ���8k�ֽ�ÿ��.
	
	2)SPIͼƬ�ϵ���Դ����,��ɫ���ֲ����޸�,����޸�,��Ŀ������ܹ���.

#############################################################

	
