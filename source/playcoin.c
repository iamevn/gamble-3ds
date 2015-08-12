/* #include <3ds.h> */
#include </opt/devkitpro/libctru/include/3ds.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "archive.h"
#include "playcoin.h"

u32 filebuffer_maxsize = 0x400000;

/* from https://github.com/MrCheeze/playcoin, */
int setcoins(u8 highByte, u8 lowByte)
{	
	Result ret=0;

	printf("Reading gamecoin.dat...\n");
	gfxFlushBuffers();
	gfxSwapBuffers();

	ret = archive_readfile(GameCoin_Extdata, "/gamecoin.dat", filebuffer, 0x14);
	if(ret!=0)
	{
		printf("Failed to read file: 0x%08x\n", (unsigned int)ret);
		gfxFlushBuffers();
		gfxSwapBuffers();
		return 0;
	}

	filebuffer[0x4]=lowByte;
	filebuffer[0x5]=highByte;

	printf("Writing updated gamecoin.dat...\n");
	gfxFlushBuffers();
	gfxSwapBuffers();

	ret = archive_writefile(GameCoin_Extdata, "/gamecoin.dat", filebuffer, 0x14);
	if(ret!=0)
	{
		printf("Failed to write file: 0x%08x\n", (unsigned int)ret);
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	return 0;
}

int setCoins(u16 value)
{
	if (value > 300) {
		printf("can't set coins to %d\n", (unsigned int)value);
		gfxFlushBuffers();
		gfxSwapBuffers();
		return -1;
	}
	u8 highbyte, lowbyte;
	highbyte = value >> 8 & 0xFF;
	lowbyte = value & 0xFF;
	return setcoins(highbyte, lowbyte);
}

u16 getCoins()
{
	Result ret=0;

	ret = archive_readfile(GameCoin_Extdata, "/gamecoin.dat", filebuffer, 0x14);
	if(ret!=0) {
		printf("failed to read file: 0x%08x\n", (unsigned int)ret);
		gfxFlushBuffers();
		gfxSwapBuffers();
		return 0;
	}

	u8 lowbyte = filebuffer[0x4];
	u8 highbyte = filebuffer[0x5];

	u16 combined = highbyte;
	combined <<= 8;
	combined = combined | lowbyte;
	return combined;
}

int changeCoins(s16 amt)
{
	s16 cnt = getCoins();
	s16 final = cnt + amt;

	if (final < 0 || final > 300) {
		if (amt > 0) {
			final = 300;
		}
		else {
			final = 0;
		}
	}
	return setCoins(final);
}
