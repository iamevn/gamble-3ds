#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/* #include <3ds.h> */
#include </opt/devkitpro/libctru/include/3ds.h>

#include "archive.h"
#include "debugmenu.h"
#include "playcoin.h"
#include "menus.h"

int menu_blackjack();
int menu_debug();
int menu_exit();

int mainmenu_totalentries = 3;
char *mainmenu_entries[3] = {
"Blackjack",
"Debug",
"Exit"};
menuent_funcptr mainmenu_entryhandlers[5] = {menu_blackjack, menu_debug, menu_exit};

int menu_blackjack()
{
	printf("insert blackjack here");
	return 0;
}

int menu_debug()
{
	/* printf("insert debug here"); */
	runDebugMenu();
	return 0;
}

int menu_exit()
{
	printf("exiting...");
	return -2;
}

int main()
{
	Result ret = 0;

	// Initialize services
	gfxInitDefault();

	consoleInit(GFX_BOTTOM, NULL);

	printf("Play Coin Setter 3DSx\n");
	gfxFlushBuffers();
	gfxSwapBuffers();

	filebuffer = (u8*)malloc(0x400000);
	if(filebuffer==NULL)
	{
		printf("Failed to allocate memory.\n");
		gfxFlushBuffers();
		gfxSwapBuffers();
		ret = -1;
	}
	else
	{
		memset(filebuffer, 0, filebuffer_maxsize);
	}

	if(ret>=0)
	{
		printf("Opening extdata archives...\n");
		gfxFlushBuffers();
		gfxSwapBuffers();
		ret = open_extdata();
		if(ret==0)
		{
			printf("Finished opening extdata.\n");
			gfxFlushBuffers();
			gfxSwapBuffers();

			consoleClear();
			handle_menus(mainmenu_entries, mainmenu_totalentries, mainmenu_entryhandlers);
		}
	}

	if(ret<0)
	{
		printf("Press the START button to exit.\n");
		// Main loop
		while (aptMainLoop())
		{
			gspWaitForVBlank();
			hidScanInput();

			u32 kDown = hidKeysDown();
			if (kDown & KEY_START)
				break; // break in order to return to hbmenu

			// Flush and swap framebuffers
			gfxFlushBuffers();
			gfxSwapBuffers();
		}
	}

	free(filebuffer);
	close_extdata();

	// Exit services
	gfxExit();
	return 0;
}
