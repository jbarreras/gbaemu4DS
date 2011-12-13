#include <nds.h>
#include <stdio.h>

#include <filesystem.h>
#include "unzip.h"
#include "getopt.h"
#include "System.h"
#include <fat.h>
#include "ram.h"
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <nds/memory.h>//#include <memory.h> ichfly
#include <nds/ndstypes.h>
#include <nds/memory.h>
#include <nds/bios.h>
#include <nds/system.h>
#include <nds/arm9/math.h>
#include <nds/arm9/video.h>
#include <nds/arm9/videoGL.h>
#include <nds/arm9/trig_lut.h>
#include <nds/arm9/sassert.h>
#include <stdarg.h>

void VblankHandler();

void BIOScall(int op,  s32 *R);

extern "C" void cpu_SetCP15Cnt(u32 v);
extern "C" u32 cpu_GetCP15Cnt();


#include <filesystem.h>
#include "GBA.h"
#include "Sound.h"
#include "unzip.h"
#include "Util.h"
#include "getopt.h"
#include "System.h"
#include <fat.h>
#include "ram.h"
#include <dirent.h>

#include "cpumg.h"
#include "GBAinline.h"


#include "main.h"

#include "armdis.h"


	FILE * pFile;


#include "main.h"


extern "C" void swiHalt(void);

#include <stdio.h>
#include <stdlib.h>
#include <nds/memory.h>//#include <memory.h> ichfly
#include <nds/ndstypes.h>
#include <nds/memory.h>
#include <nds/bios.h>
#include <nds/system.h>
#include <nds/arm9/math.h>
#include <nds/arm9/video.h>
#include <nds/arm9/videoGL.h>
#include <nds/arm9/trig_lut.h>
#include <nds/arm9/sassert.h>
#include <stdarg.h>
#include <string.h>

#include "GBA.h"
#include "GBAinline.h"
#include "Globals.h"
#include "Gfx.h"
#include "EEprom.h"
#include "Flash.h"
#include "Sound.h"
#include "Sram.h"
#include "bios.h"
#include "unzip.h"
#include "Cheats.h"
#include "NLS.h"
#include "elf.h"
#include "Util.h"
#include "Port.h"
#include "agbprint.h"


void CPUWriteMemory(u32 addr, u32 value);
void CPUWriteHalfWord(u32 addr, u16 value);
void CPUWriteByte (u32 addr, u8  value);

u32 CPUReadMemory(u32 addr);
u16 CPUReadHalfWordSigned(u32 addr);
u8  CPUReadByte (u32 addr);


extern "C" void swiIntrWaitc();

//#define DEV_VERSION


extern bool disableMessage;



void gbaExceptionHdl();















#include "main.h"
#include "cpumg.h"

#define PU_PAGE_4K		(0x0B << 1)
#define PU_PAGE_8K		(0x0C << 1)
#define PU_PAGE_16K		(0x0D << 1)
#define PU_PAGE_32K		(0x0E << 1)
#define PU_PAGE_64K		(0x0F << 1)
#define PU_PAGE_128K		(0x10 << 1)
#define PU_PAGE_256K		(0x11 << 1)
#define PU_PAGE_512K		(0x12 << 1)
#define PU_PAGE_1M		(0x13 << 1)
#define PU_PAGE_2M		(0x14 << 1)
#define PU_PAGE_4M		(0x15 << 1)
#define PU_PAGE_8M		(0x16 << 1)
#define PU_PAGE_16M		(0x17 << 1)
#define PU_PAGE_32M		(0x18 << 1)
#define PU_PAGE_64M		(0x19 << 1)
#define PU_PAGE_128M		(0x1A << 1)
#define PU_PAGE_256M		(0x1B << 1)
#define PU_PAGE_512M		(0x1C << 1)
#define PU_PAGE_1G		(0x1D << 1)
#define PU_PAGE_2G		(0x1E << 1)
#define PU_PAGE_4G		(0x1F << 1)

// extern void puSetMemPerm(u32 perm);
extern "C" void pu_Enable();
// extern void puSetGbaIWRAM();
extern "C" void pu_SetRegion(u32 region, u32 value);

extern "C" void pu_SetDataPermissions(u32 v);
extern "C" void pu_SetCodePermissions(u32 v);
extern "C" void  pu_SetDataCachability(u32 v);
extern "C" void  pu_SetCodeCachability(u32 v);
extern "C" void pu_GetWriteBufferability(u32 v);

u16 gbaIME = 0;
u16 gbaDISPCNT = 0;
u16 gbaBGxCNT[4] = {0, 0, 0, 0};


char disbuffer[0x2000];

//extern "C" void exMain(); 

extern void __attribute__((section(".dtcm"))) (*exHandler)();
extern void __attribute__((section(".dtcm"))) (*exHandlerswi)();
extern s32  __attribute__((section(".dtcm"))) exRegs[];
extern s32  __attribute__((section(".dtcm"))) BIOSDBG_SPSR;

//#define BIOSDBG_CP15 *((volatile u32*)0x027FFD8C)
//#define BIOSDBG_SPSR *((volatile u32*)0x027FFD90)
//#define BIOSDBG_R12  *((volatile u32*)0x027FFD94)
//#define BIOSDBG_PC   *((volatile u32*)0x027FFD98)



int durchlauf = 0;


void exInitswisystem(void (*customswiHdl)())
{
	exHandlerswi = customswiHdl;
}

void exInit(void (*customHdl)())
{
	//EXCEPTION_VECTOR = exMain; //no more needed
	exHandler = customHdl;
}


/*
void Write32(u32 address, u32 value)
{
	Log("Write32: *%08X = %08X\n", address, value);
	if((address & 0x0F000000) == 0x04000000)	/* IO *//*
	{
		switch(address & 0xFFF)
		{
			case 0x208:	/* REG_IME *//*
				gbaIME = value & 0x1; 
				break;
			default:
				Log("Unh. IO Write32 at %08X\n", address);
				break;
		}
	}			
}

#define					BG0_CR		(*(vu16*)0x4000008)
#define DISPLAY_CR (*(vu32*)0x04000000)

void Write16(u32 address, u16 value)
{
	Log("Write16: *%08X = %04X\n", address, value);
	if((address & 0x0F000000) == 0x04000000)	/* IO *//*
	{
		switch(address & 0xFFF)
		{
			case 0x000: {	/* REG_DISPCNT *//*
				u32 dsValue;
				gbaDISPCNT = value;
				dsValue  = value & 0xFF87;
				dsValue |= (value & (1 << 5)) ? (1 << 23) : 0;	/* oam hblank access *//*
				dsValue |= (value & (1 << 6)) ? (1 << 4) : 0;	/* obj mapping 1d/2d *//*
				dsValue |= (value & (1 << 7)) ? 0 : (1 << 16);	/* forced blank => no display mode *//*
				/* TODO: gérer mode 4 *//*
				REG_DISPCNT = dsValue;
			} break;
			case 0x004: /* REG_DISPSTAT *//*
				/* TODO *//*
				break;
			case 0x008: /* REG_BG0CNT *//*
			case 0x00A: /* REG_BG1CNT *//*
			case 0x00C: /* REG_BG2CNT *//*
			case 0x00E: { /* REG_BG3CNT *//*
				u16 dsValue;
				int bg = (address - 0x4000008) >> 1;
				gbaBGxCNT[bg] = value;
				dsValue = value;
				*(&REG_BG0CNT + bg) = dsValue;
			} break;
			case 0x208: /* REG_IME *//*
				gbaIME = value & 0x1; 
				break;
			default:
				Log("Unh. IO Write16 at %08X\n", address);
				break;
		}
	}
}
void Write8 (u32 address, u8  value)
{
	Log("Write8 : *%08X = %02X\n", address, value);
	if((address & 0x0F000000) == 0x04000000)	/* IO *//*
	{
		switch(address & 0xFFF)
		{
			default:
				Log("Unh. IO Write8 at %08X\n", address);
				break;
		}
	}
}

u32 Read32(u32 address)
{
	u32 value = 0;
	Log("Read32: *%08X\n", address);
	if((address & 0x0F000000) == 0x04000000)	/* IO *//*
	{
		switch(address & 0xFFF)
		{
			case 0x208:
				value = gbaIME; 
				break;
			default:
				Log("Unh. IO Read32 at %08X\n", address);
				break;
		}
	}
	return value;
}

u16 Read16(u32 address)
{
	u16 value = 0;
	Log("Read16: *%08X\n", address);
	if((address & 0x0F000000) == 0x04000000)	/* IO *//*
	{
		switch(address & 0xFFF)
		{
			case 0x000: /* REG_DISPCNT *//*
				value = gbaDISPCNT; break;
			case 0x004: /* REG_DISPSTAT *//*
				/* TODO *//*
				break;
			case 0x006: /* REG_VCOUNT *//*
				value = REG_VCOUNT;
				if(value > 227) value = 227;	/* limite à la taille de la gba *//*
				break;
			case 0x008: /* REG_BG0CNT *//*
			case 0x00A: /* REG_BG1CNT *//*
			case 0x00C: /* REG_BG2CNT *//*
			case 0x00E: { /* REG_BG3CNT *//*
				int bg = (address - 0x4000008) >> 1;
				value = gbaBGxCNT[bg];
			} break;
			case 0x208: /* REG_IME *//*
				value = gbaIME;  break;
			default:
				Log("Unh. IO Read16 at %08X\n", address);
				break;
		}
	}
	return value;
}
u8  Read8 (u32 address)
{
	u8 value = 0;
	Log("Read8 : *%08X\n", address);
	if((address & 0x0F000000) == 0x04000000)	/* IO *//*
	{
		switch(address & 0xFFF)
		{
			default:
				Log("Unh. IO Read8 at %08X\n", address);
				break;
		}
	}
	return value;
}
*/
void emuInstrARM(u32 instr, s32 *regs);
void emuInstrTHUMB(u16 instr, s32 *regs);

#define B8(h,g,f,e,d,c,b,a) ((a)|((b)<<1)|((c)<<2)|((d)<<3)|((e)<<4)|((f)<<5)|((g)<<6)|((h)<<7))

void debugDump()
{
// 	Log("dbgDump\n");
// 	return;
	

	int i;
	for(i = 0; i <= 15; i++) {
		Log("R%d=%X ", i, exRegs[i]);
	} 
	Log("\n");
	for(i = 0; i < 4; i++) {
		Log("+%02X: %08X %08X %08X\n", i*3*4, ((u32*)exRegs[13])[i*3], ((u32*)exRegs[13])[i*3+1], ((u32*)exRegs[13])[i*3+2]);
	}
	Log("SPSR %08x CPSR %08x\n",BIOSDBG_SPSR,cpuGetCPSR());
}

int durchgang = 0;

void gbaInit()
{

	/*
	Region 0 - IO registers	0x04000000 PAGE_64M
	Region 1 - System ROM 0xFFFF0000 PAGE_32K   
	--> Standard Palettes 0x05000000  (2KByte DS) (1KByte gba)  PAGE_16M
	Region 2 - alternate vector base 0x00000000 PAGE_4K
	Region 3 - DS Accessory (GBA Cart) / DSi switchable iwram 0x08000000 PAGE_16M (0x03000000 PAGE_8M DSi) 
	--> Shared WRAM (32KByte) 0x03000000 PU_PAGE_16M
	Region 4 - ITCM 0x01000000 PAGE_32K
	Region 5 - DTCM 0x0b000000 PAGE_16K
	Region 6 - non cacheable main ram 0x02000000 PAGE_16M
	--> same to secure that everything works
	Region 7 - cacheable main ram 0x02000000 PAGE_4M
	--> VRAM/OAM 0x06000000 PU_PAGE_32M


	

	*/


	//pFile = fopen("fat:/gbaemulog.log","w");
	pu_SetDataCachability(   0b00000010); //ichfly todo slowdown !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pu_SetCodeCachability(   0b00000010);
	pu_GetWriteBufferability(0b00000000);
	
	DC_FlushAll(); //try it
	
	
	IC_InvalidateAll();
	
	//Logsd ("test %x\r\n",pFile);
	
	//fputs ("fopen example\r\n",pFile);
	
	// 	puSetGbaIWRAM();

	pu_SetRegion(3, 0x03000000 | PU_PAGE_16M | 1);	/* gba iwram */ //it is the GBA Cart in the original //ichfly for log jumps it is 2 as bit as it should
	pu_SetRegion(6, 0x02000000 | PU_PAGE_16M | 1);    //ram
	//pu_SetRegion(7, 0x07000000 | PU_PAGE_16M | 1);
	pu_SetRegion(1, 0x05000000 | PU_PAGE_16M | 1);
	pu_SetRegion(7, 0x06000000 | PU_PAGE_32M | 1);	//todo swap
	//pu_SetRegion(2, 0x05000000 | PU_PAGE_64M | 1);
	//pu_SetRegion(3, 0x00000000 | PU_PAGE_32M | 1);
	//pu_SetRegion(4, 0x02040000 | PU_PAGE_8M | 1);
	WRAM_CR = 0;
#ifdef releas
	exInit(gbaExceptionHdl);
#endif

	exInitswisystem(gbaswieulatedbios);

	iprintf("gbainit done\n\r");
	
}

void gbaswieulatedbios()
{
	//Log("\n\rswi\n\r");
	//debugDump();

//while(1);

	//Log("%08X S\n", exRegs[15]);

	u16 tempforwtf = *(u16*)(exRegs[15] - 2);
	BIOScall(tempforwtf,  exRegs);

		gbaMode();
	//while(1);
}


void BIOScall(int op,  s32 *R)
{
	int comment = op & 0x003F;
	
	switch(comment) {
	  case 0x00:
		BIOS_SoftReset();
		break;
	  case 0x01:
		BIOS_RegisterRamReset();
		break;
	  case 0x02:
		  Log("Halt: IE %x\n",IE);        
		//holdState = true;
		//holdType = -1;
		//cpuNextEvent = cpuTotalTicks;
		
		
		//durchlauf = 1;
		
		//debugDump();
		
		//VblankHandler();
		
		//swiIntrWaitc();
		
		break;
	  case 0x03:
		  Log("Stop(not yet)\n");         
		//holdState = true;
		//holdType = -1;
		//stopState = true;
		//cpuNextEvent = cpuTotalTicks; 
		break;
	  case 0x04:
		  Log("IntrWait: 0x%08x,0x%08x\n",
			  R[0],
			  R[1]);      
	
		swiIntrWait(R[0],R[1]);
		//CPUSoftwareInterrupt();
		break;    
	  case 0x05:
	#ifdef DEV_VERSION
		  Log("VBlankIntrWait:\n");
		  //VblankHandler(); //todo
	#endif
		if((REG_DISPSTAT & DISP_IN_VBLANK)) while((REG_DISPSTAT & DISP_IN_VBLANK)); //workaround
		while(!(REG_DISPSTAT & DISP_IN_VBLANK));
		
		break;
	  case 0x06:
		BIOS_Div();
		break;
	  case 0x07:
		BIOS_DivARM();
		break;
	  case 0x08:
		BIOS_Sqrt();
		break;
	  case 0x09:
		BIOS_ArcTan();
		break;
	  case 0x0A:
		BIOS_ArcTan2();
		break;
	  case 0x0B:
		BIOS_CpuSet();
		break;
	  case 0x0C:
		BIOS_CpuFastSet();
		break;
	  case 0x0D:
		BIOS_GetBiosChecksum();
		break;
	  case 0x0E:
		BIOS_BgAffineSet();
		break;
	  case 0x0F:
		BIOS_ObjAffineSet();
		break;
	  case 0x10:
		BIOS_BitUnPack();
		break;
	  case 0x11:
		BIOS_LZ77UnCompWram();
		break;
	  case 0x12:
		BIOS_LZ77UnCompVram();
		break;
	  case 0x13:
		BIOS_HuffUnComp();
		break;
	  case 0x14:
		BIOS_RLUnCompWram();
		break;
	  case 0x15:
		BIOS_RLUnCompVram();
		break;
	  case 0x16:
		BIOS_Diff8bitUnFilterWram();
		break;
	  case 0x17:
		BIOS_Diff8bitUnFilterVram();
		break;
	  case 0x18:

		BIOS_Diff16bitUnFilter();
		break;
	  case 0x19:
	#ifdef DEV_VERSION
		  Log("SoundBiasSet: 0x%08x \n",
			  R[0]);      
	#endif    
		//if(reg[0].I) //ichfly sound todo
		  //systemSoundPause(); //ichfly sound todo
		//else //ichfly sound todo
		  //systemSoundResume(); //ichfly sound todo
		break;
	  case 0x1F:
		BIOS_MidiKey2Freq();
		break;
	  case 0x2A:
		BIOS_SndDriverJmpTableCopy();
		break;
		// let it go, because we don't really emulate this function
	  case 0x2D: //silent debug call
		break;
	  case 0x2F: //debug call all
		debugDump();
		break;
	  default:
		if((comment & 0x30) == 0x30)
		{
			iprintf("r%x %08x",(comment & 0xF),R[(comment & 0x30)]);
		}
		else
		{
			if(!disableMessage) {
			  systemMessage(MSG_UNSUPPORTED_BIOS_FUNCTION,
							N_("Unsupported BIOS function %02x. A BIOS file is needed in order to get correct behaviour."),
							comment);
			  disableMessage = true;
			}
		}
		break;
	  }
}
void switch_to_unprivileged_mode()
{
	u32 temp = cpuGetCPSR();
	temp = temp & ~0x1F;
	temp = temp |= 0x10;
	cpuSetCPSR(temp);
}

void emulateedbiosstart()
{
	cpu_SetCP15Cnt(cpu_GetCP15Cnt() &~BIT(13));
}

void downgreadcpu()
{
	cpu_SetCP15Cnt(cpu_GetCP15Cnt() | BIT(15));
}


 __attribute__((section(".itcm"))) inline void puGba()
{
	/* NDS PU REGIONS: 
	0: io + vram
	1: bios
	2: alternate vector base
	3: DTCM
	4: ITCM
	5: new 0x300000 (old gba slot)
	6: non cacheable main ram
	7: cacheable main ram
	*/
	
	
	//REG_IME = IME_DISABLE;
	
	//DC_FlushRange((void*)0x02000000, 4 * 1024 * 1024); //slowdown and is not realy needed
	//pu_SetDataCachability(   B8(0,0,0,0,0,0,1,0)); //ichfly todo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//pu_SetCodeCachability(   B8(0,0,0,0,0,0,1,0));
	//pu_GetWriteBufferability(B8(0,0,0,0,0,0,0,0));
	
	//pu_SetRegion(0, 0x00000000 | PU_PAGE_4G | 1);	/* fond */ //ichfly wtf
	//pu_SetRegion(1, 0x04000000 | PU_PAGE_16M | 1);	/* io */
	//pu_SetDataPermissions(0x36333303);
	//pu_SetCodePermissions(0x36636303);
	
	pu_SetCodePermissions(0x33333330);
	
	pu_SetDataPermissions(0x33333330);

	//REG_IME = IME_ENABLE;	//lol don't enable this
	
	
}
 __attribute__((section(".itcm"))) inline void puNds()
{
	/* NDS PU REGIONS: 
	0: io + vram
	1: bios
	2: alternate vector base
	3: DTCM
	4: ITCM
	5: new 0x300000 (old gba slot)
	6: non cacheable main ram
	7: cacheable main ram
	*/
	
	
	pu_SetDataPermissions(0x33333333);
	pu_SetCodePermissions(0x33333333);
	

	
	//pu_SetRegion(6, 0x02000000 | PU_PAGE_16M  | 1);	/* main ram */ //why
	//pu_SetRegion(7, 0x02000000 | PU_PAGE_4M  | 1);	/* main rams */
	//pu_SetRegion(0, 0x04000000 | PU_PAGE_64M | 1);	/* io + vram */
	
	/*pu_SetDataCachability(   B8(1,0,0,0,0,0,1,0)); //ichfly todo
	pu_SetCodeCachability(   B8(1,0,0,0,0,0,1,0));
	pu_GetWriteBufferability(B8(1,0,0,0,0,0,0,0));*/
	
	//REG_IME = IME_ENABLE;	//ichfy for test
}





void ndsExceptionHdl()
{
	u32 mode = cpuGetCPSR() & 0x1F;
	u32 instrset = BIOSDBG_SPSR & 0x20;
	if(mode == 0x17)
	{
		u32 codeAddress = exRegs[15] - 8;
		if (	(codeAddress > 0x02000000 && codeAddress < 0x02400000) ||
		(codeAddress > (u32)0x01000000 && codeAddress < (u32)(0x01000000 + 32768)) )
		{
			Log("NDS DATA ABORT AT %08X\n",getExceptionAddress( codeAddress, instrset));
		}
		else
		{
			Log("NDS DATA ABORT\n");
		}
	}
	else if(mode == 0x1B) Log("NDS UNDEFINED INSTRUCTION\n");
	else Log("NDS STRANGE EXCEPTION !\n");
	Log("SAVED PC = %08X (%s)\n", exRegs[15], instrset ? "THUMB" : "ARM");
	debugDump();
	/*if(instrset) Log("FAILED INSTR = %04X\n", *(u16*)(exRegs[15] - (mode == 0x17 ? 4 : 2)));
	else Log("FAILED INSTR = %08X\n", *(u32*)(exRegs[15] - (mode == 0x17 ? 8 : 4)));*/ //ichfly don't like that
	while(1) { ; }
}


 __attribute__((section(".itcm")))inline void ndsModeinline()
{
	puNds();
#ifndef releas
	exInit(ndsExceptionHdl);
#endif
}

void ndsMode()
{
	puNds();
#ifndef releas
	exInit(ndsExceptionHdl);
#endif
}


 __attribute__((section(".itcm"))) void gbaExceptionHdl()
{

	//debugDump();

//Log("test\r\n");

	int i;
	u32 instr;
	u32 sysMode;
	u32 cpuMode;
	
	ndsModeinline();
	//sysMode = cpuGetCPSR() & 0x1F; //ichfly don't need that
	cpuMode = BIOSDBG_SPSR & 0x20;
	
	BIOSDBG_SPSR = BIOSDBG_SPSR & ~0x80;
	
	/*u32 opSize;
	if(cpuMode) opSize = 2;
	else opSize = 4;*/
	
	 /*if(cpuMode)Log("%08X %08X\n", exRegs[15],BIOSDBG_SPSR);
	 else
	 {
		Log("%08X %08X\n", exRegs[15],BIOSDBG_SPSR);
	 }*/
	
	//exRegs[15] -= 4; //ichfly patch not working on emulators
	

	//exRegs[15] += 4;
		
	
	//while(1);
	

	
	//Log("%08X %08X\n", exRegs[15] , BIOSDBG_SPSR);
	
	//debugDump();

	
#ifndef unsave
	if(exRegs[15] < 0x02000000 || exRegs[15] > 0x04000000 && !(exRegs[15] & 0x08000000))
	{
		Log("gba jumped to an unknown region\n");
		debugDump();
		while(1);
	}
#endif
	
	/*if(exRegs[15] > (u32)(rom + 0x200))
	{
		//debugDump();
		Log("%08X\n", exRegs[15]);
		durchlauf++;
		if((s32)workaroundread32((u32*)&rom) + 0x458 < exRegs[15] && (s32)workaroundread32((u32*)&rom) + 0x5a4 > exRegs[15])while(1);
		//debugDump();
	}*/
	
	if(exRegs[15] & 0x08000000)
	{
		//if(exRegs[15] == 0x08000290)while(1);
		//Logsd("%08X\n", exRegs[15]);
		//debugDump();
		
		//debugDump();
		
		//iprintf("\n\r%08X",BIOSDBG_SPSR);
		

		
		//suche quelle
		/*for(i = 0; i <= 14; i++) {
			if((exRegs[i] & ~0x1) == (exRegs[15] - 4))
			{
				if(exRegs[i] &0x1) BIOSDBG_SPSR |= 0x20;
				else  BIOSDBG_SPSR &= ~0x20;
				break;
			}
		}*/ //ichfly check if needed
		
		
		//exRegs[15] -= 8; //for my emu
		//exRegs[15] -= 4; //for nothing
		
		//volatile static u32 temp;
		
		//temp = exRegs[15];
		exRegs[15] = (exRegs[15] & 0x07FFFFFF) + (s32)rom;
		
		//temp = exRegs[15];
		//sehen[1] = (u32)rom;
		//Log("ende %08X %08X %08X \n", sehen[0], sehen[1], sehen[2]);
		
	
	}
	else
	{
	 //		Logsd("-------- DA :\n");

			
			//exRegs[15] += 4; //for emu
			
			//debugDump();
			
			//durchgang++;
			
			//iprintf("%08X %X (%08X)\n", exRegs[15],cpuMode,*(u32*)(exRegs[15] - 8));
			
			
				//debugDump();
			
			/*if(cpuMode) instr = (u32)*(u16*)(exRegs[15] - 4);
			else instr = *(u32*)(exRegs[15] - 4);*/
			
			if(cpuMode)
			{
				instr = *(u16*)(exRegs[15] - 8);
				exRegs[15] -= 2;
#ifdef BREAKswisupport
				u16 tempforwtf = *(u16*)(exRegs[15] - 2);

				//Logsd("%08X\n", instr);
				if(tempforwtf > 0xBE00 && tempforwtf < 0xBE2B)
				{
				
					
					exRegs[15] += 4;
					//debugDump();
					BIOScall(tempforwtf,  exRegs);
					
					
					
					//while(1);
					//debugDump();
				}
				else
#endif
				{
					emuInstrTHUMB(instr, exRegs);
				}
				//exRegs[15] -= 2;
				
			}
			else
			{
				instr = *(u32*)(exRegs[15] - 8);
				u32 tempforwtf = *(u32*)(exRegs[15] - 4);
#ifdef BREAKswisupport
				if((tempforwtf &0xFFF000F0) == 0xE1200070) //wtf ²àà 0xB2 10 E0 E0
				{
					exRegs[15] += 4;
					BIOScall((tempforwtf & 0xFFF00)>>0x8, exRegs);
				}
				else
#endif
				if((tempforwtf &0x0F200090) == 0x00200090) //wtf why dos this tigger an exeption it is strh r1,[r0]+2! ²àà 0xB2 10 E0 E0 on gba 0xE0E010B2 so think all strh rx,[ry]+z! do that it is an comand interpreter error 
				{
					*(u32*)(exRegs[15] - 4) = tempforwtf & ~0x200000;//ther is just a wrong bit so don't worry patch it to strh r1,[r0]+2
				}
				else
				{
				/*u32 offset = exRegs[15] - 8;
				if(offset > 0x02040000) offset = exRegs[15] - 8 - (s32)workaroundread32((u32*)&rom) + 0x08000000;
				if(offset == 0x0800311C || offset == 0x08003120)
				{
					disArm(offset - 4,disbuffer,DIS_VIEW_ADDRESS);
					Log(disbuffer);
					Log("\r\n");
										disArm(offset,disbuffer,DIS_VIEW_ADDRESS);
					Log(disbuffer);
					Log("\r\n");
										disArm(offset + 4,disbuffer,DIS_VIEW_ADDRESS);
					Log(disbuffer);
					Log("\r\n");
										disArm(offset + 8,disbuffer,DIS_VIEW_ADDRESS);
					Log(disbuffer);
					Log("\r\n");
					
					debugDump();
					while(1);
				}*/
	 			//Log("ARM: %08X\n", instr);
				emuInstrARM(instr, exRegs);
				}
	// 			Logsd("NDS TRACE\n")
				//exRegs[15] -= 4;
			}
			
	// 		exRegs[15] += opSize;
	// 		while(1) { }
		/*else if(sysMode == 0x1B)
		{
			if(cpuMode) instr = (u32)*(u16*)(exRegs[15] - 2);
			else instr = *(u32*)(exRegs[15] - 4);
			
			// Undefined instruction (debug...) 
			if((!cpuMode && instr == 0xE7F000F0) || (cpuMode && instr == 0xDE00))
			{
				Log("Trace... [%s]\n", cpuMode ? "THUMB" : "ARM");
			}
			else if((!cpuMode && instr == 0xE7F000F1) || (cpuMode && instr == 0xDE01))
			{
				debugDump();
			}
			else
			{
				Log("Unhandled und. except. (%08X)\n", instr);
				//while(1)swiWaitForVBlank();
			}
			
			exRegs[15] += 4;
		}*/ //ichfly not reachable
	}

		//while(1);
	
	//Log("%08X\n", exRegs[1]);
	//Log("%08X\n", exRegs[0]);
	//while(1);
	//debugDump();
	
	//test mode
	
	
	/*iprintf("test\r\n%x\r\n%x\r\n%x\r\n%x\r\n",BIOSDBG_CP15, BIOSDBG_SPSR, BIOSDBG_R12, BIOSDBG_PC);
	
	BIOSDBG_PC = 0;
	
	iprintf("%x", BIOSDBG_PC);
	while(1);*/
	//test mode end
	
	//Log("%08X\n", exRegs[15]);
	
	//debugDump();
	
//Log("exit");



	 /*if(cpuMode)Log("%08X %08X\n", exRegs[15],BIOSDBG_SPSR);
	 else
	 {
		Log("%08X %08X\n", exRegs[15],BIOSDBG_SPSR);
	 }*/

	gbaMode();
	
	//if(*(u16*)(exRegs[15] - 2) == 0xBE05) while(1);
			//swiDelay(0x2000000); --
	//swiDelay(0x20000);
	
	//if(exRegs[15] < 0x02000000)while(1) { ; } //i was funny hahahahaha

}





#ifndef releas
 __attribute__((section(".itcm"))) void gbaMode()
{

	exInit(gbaExceptionHdl);
	puGba();
	
}
 void gbaMode2()
{
	exInit(gbaExceptionHdl);
	puGba();	
}
#endif

 #ifdef releas

void gbaMode2()
{
	puGba();	
}
  __attribute__((section(".itcm"))) inline void gbaMode()
{
	puGba();	
}
#endif


//extern things

//---------------------------------------------------------------------------------
u32 getExceptionAddress( u32 opcodeAddress, u32 thumbState) {
//---------------------------------------------------------------------------------

	int Rf, Rb, Rd, Rn, Rm;

	if (thumbState) {
		// Thumb

		unsigned short opcode = *(unsigned short *)opcodeAddress ;
		// ldr r,[pc,###]			01001ddd ffffffff
		// ldr r,[r,r]				0101xx0f ffbbbddd
		// ldrsh					0101xx1f ffbbbddd
		// ldr r,[r,imm]			011xxfff ffbbbddd
		// ldrh						1000xfff ffbbbddd
		// ldr r,[sp,###]			1001xddd ffffffff
		// push						1011x10l llllllll
		// ldm						1100xbbb llllllll


		if ((opcode & 0xF800) == 0x4800) {
			// ldr r,[pc,###]
			s8 offset = opcode & 0xff;
			return exRegs[15] + offset;
		} else if ((opcode & 0xF200) == 0x5000) {
			// ldr r,[r,r]
			Rb = (opcode >> 3) & 0x07 ;
			Rf = (opcode >> 6) & 0x07 ;
			return exRegs[Rb] + exRegs[Rf];

		} else if ((opcode & 0xF200) == 0x5200) {
			// ldrsh
			Rb = (opcode >> 3) & 0x07;
			Rf = (opcode >> 6) & 0x03;
			return exRegs[Rb] + exRegs[Rf];

		} else if ((opcode & 0xE000) == 0x6000) {
			// ldr r,[r,imm]
			Rb = (opcode >> 3) & 0x07;
			Rf = (opcode >> 6) & 0x1F ;
			return exRegs[Rb] + (Rf << 2);
		} else if ((opcode & 0xF000) == 0x8000) {
			// ldrh
			Rb = (opcode >> 3) & 0x07 ;
			Rf = (opcode >> 6) & 0x1F ;
			return exRegs[Rb] + (Rf << 2);
		} else if ((opcode & 0xF000) == 0x9000) {
			// ldr r,[sp,#imm]
			s8 offset = opcode & 0xff;
			return exRegs[13] + offset;
		} else if ((opcode & 0xF700) == 0xB500) {
			// push/pop
			return exRegs[13];
		} else if ((opcode & 0xF000) == 0xC000) {
			// ldm/stm
			Rd = (opcode >> 8) & 0x07;
			return exRegs[Rd];
		}
	} else {
		// arm32
		unsigned long opcode = *(unsigned long *)opcodeAddress ;

		// SWP			xxxx0001 0x00nnnn dddd0000 1001mmmm
		// STR/LDR		xxxx01xx xxxxnnnn ddddffff ffffffff
		// STRH/LDRH	xxxx000x x0xxnnnn dddd0000 1xx1mmmm
		// STRH/LDRH	xxxx000x x1xxnnnn ddddffff 1xx1ffff
		// STM/LDM		xxxx100x xxxxnnnn llllllll llllllll

		if ((opcode & 0x0FB00FF0) == 0x01000090) {
			// SWP
			Rn = (opcode >> 16) & 0x0F;
			return exRegs[Rn];
		} else if ((opcode & 0x0C000000) == 0x04000000) {
			// STR/LDR
			Rn = (opcode >> 16) & 0x0F;
			if (opcode & 0x02000000) {
				// Register offset
				Rm = opcode & 0x0F;
				if (opcode & 0x01000000) {
					unsigned short shift = (unsigned short)((opcode >> 4) & 0xFF) ;
					// pre indexing
					long Offset = ARMShift(exRegs[Rm],shift);
					// add or sub the offset depending on the U-Bit
					return exRegs[Rn] + ((opcode & 0x00800000)?Offset:-Offset);
				} else {
					// post indexing
					return exRegs[Rn];
				}
			} else {
				// Immediate offset
				unsigned long Offset = (opcode & 0xFFF) ;
				if (opcode & 0x01000000) {
					// pre indexing
					// add or sub the offset depending on the U-Bit
					return exRegs[Rn] + ((opcode & 0x00800000)?Offset:-Offset);
				} else {
					// post indexing
					return exRegs[Rn];
				}
			}
		} else if ((opcode & 0x0E400F90) == 0x00000090) {
			// LDRH/STRH with register Rm
			Rn = (opcode >> 16) & 0x0F;
			Rd = (opcode >> 12) & 0x0F;
			Rm = opcode & 0x0F;
			unsigned short shift = (unsigned short)((opcode >> 4) & 0xFF);
			long Offset = ARMShift(exRegs[Rm],shift);
			// add or sub the offset depending on the U-Bit
			return exRegs[Rn] + ((opcode & 0x00800000)?Offset:-Offset);
		} else if ((opcode & 0x0E400F90) == 0x00400090) {
			// LDRH/STRH with immediate offset
			Rn = (opcode >> 16) & 0x0F;
			Rd = (opcode >> 12) & 0x0F;
			unsigned long Offset = (opcode & 0xF) | ((opcode & 0xF00)>>8) ;
			// add or sub the offset depending on the U-Bit
			return exRegs[Rn] + ((opcode & 0x00800000)?Offset:-Offset) ;
		} else if ((opcode & 0x0E000000) == 0x08000000) {
			// LDM/STM
			Rn = (opcode >> 16) & 0x0F;
			return exRegs[Rn];
		}
	}
	return 0;
}


//---------------------------------------------------------------------------------
unsigned long ARMShift(unsigned long value,unsigned char shift) {
//---------------------------------------------------------------------------------
	// no shift at all
	if (shift == 0x0B) return value ;
	int index ;
	if (shift & 0x01) {
		// shift index is a register
		index = exRegs[(shift >> 4) & 0x0F];
	} else {
		// constant shift index
		index = ((shift >> 3) & 0x1F) ;
	} ;
	int i ;
	bool isN ;
	switch (shift & 0x06) {
		case 0x00:
			// logical left
			return (value << index) ;
		case 0x02:
			// logical right
			return (value >> index) ;
		case 0x04:
			// arithmetical right
			isN = (value & 0x80000000) ;
			value = value >> index ;
			if (isN) {
				for (i=31;i>31-index;i--) {
					value = value | (1 << i) ;
				} ;
			} ;
			return value ;
		case 0x06:
			// rotate right
			index = index & 0x1F;
			value = (value >> index) | (value << (32-index));
			return value;
	};
	return value;
}


//b