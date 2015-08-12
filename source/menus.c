#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/* #include <3ds.h> */
#include </opt/devkitpro/libctru/include/3ds.h>

#include "menus.h"
int draw_menu(char **menu_entries, int total_menuentries, int x, int y)
{
	int i;
	int cursor = 0;
	int update_menu = 1;
	int entermenu = 0;

	while(aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysDown();

		if(kDown & KEY_A)
		{
			entermenu = 1;
			break;
		}
		if(kDown & KEY_B)return -1;

		if(kDown & KEY_UP)
		{
			update_menu = 1;
			cursor--;
			if(cursor<0)cursor = total_menuentries-1;
		}

		if(kDown & KEY_DOWN)
		{
			update_menu = 1;
			cursor++;
			if(cursor>=total_menuentries)cursor = 0;
		}

		if(update_menu)
		{
			for(i=0; i<total_menuentries; i++)
			{
				if(cursor!=i)printf("\x1b[%d;%dH   %s", y+i, x, menu_entries[i]);
				if(cursor==i)printf("\x1b[%d;%dH-> %s", y+i, x, menu_entries[i]);
			}

			gfxFlushBuffers();
			gfxSwapBuffers();
		}
	}

	if(!entermenu)return -2;
	return cursor;
}

int handle_menus(char **menu_entries, int menu_totalentries, menuent_funcptr *menu_entryhandlers)
{
	int ret;

	gfxFlushBuffers();
	gfxSwapBuffers();

	while(aptMainLoop())
	{
		consoleClear();

		ret = draw_menu(menu_entries, menu_totalentries, 0, 0);
		consoleClear();

		if(ret<0)return ret;

		ret = menu_entryhandlers[ret]();
		if(ret==-2)return ret;

		svcSleepThread(1000000000LL);
	}

	return -2;
}

