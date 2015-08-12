#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/* #include <3ds.h> */
#include </opt/devkitpro/libctru/include/3ds.h>

#include "archive.h"
#include "debugmenu.h"
#include "menus.h"
#include "playcoin.h"

int menu_setcoins();
int menu_gamecoindat2sd();
int menu_sd2gamecoindat();
int menu_back();

int debugmenu_totalentries = 4;
char *debugmenu_entries[4] = {
"Set Play Coins",
"Copy gamecoin.dat from extdata to sd",
"Copy gamecoin.dat from sd to extdata",
"Back"};
menuent_funcptr debugmenu_entryhandlers[5] = {menu_setcoins, menu_gamecoindat2sd, menu_sd2gamecoindat, menu_back};

int menu_setcoins()
{
	printf("Have %d coins\n", getCoins());
	return 0;
}

int menu_gamecoindat2sd()
{
	Result ret=0;
	char filepath[256];

	memset(filebuffer, 0, filebuffer_maxsize);

	memset(filepath, 0, 256);
	strncpy(filepath, "gamecoin.dat", 255);

	ret = archive_copyfile(GameCoin_Extdata, SDArchive, "/gamecoin.dat", filepath, filebuffer, 0x14, filebuffer_maxsize, "gamecoin.dat");

	if(ret==0)
	{
		printf("Successfully finished.\n");
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	return 0;
}

int menu_sd2gamecoindat()
{
	Result ret=0;
	char filepath[256];

	memset(filebuffer, 0, filebuffer_maxsize);

	memset(filepath, 0, 256);
	strncpy(filepath, "gamecoin.dat", 255);

	ret = archive_copyfile(SDArchive, GameCoin_Extdata, filepath, "/gamecoin.dat", filebuffer, 0x14, filebuffer_maxsize, "gamecoin.dat");

	if(ret==0)
	{
		printf("Successfully finished.\n");
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	return 0;
}

int menu_back()
{
	return -2;
}


int runDebugMenu()
{
	consoleClear();
	handle_menus(debugmenu_entries, debugmenu_totalentries, debugmenu_entryhandlers);
	return 0;
}
