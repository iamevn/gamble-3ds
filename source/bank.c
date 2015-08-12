#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/* #include <3ds.h> */
#include </opt/devkitpro/libctru/include/3ds.h>

#include "archive.h"
#include "playcoin.h"
#include "menus.h"
#include "bank.h"

int menu_buyCoins();
int menu_sellCoins();
int menu_bankback();

int bankmenu_totalentries = 3;
char *bankmenu_entries[3] = {
	"Buy Game Coins with Play Coins",
	"Sell Game Coins for Play Coins",
	"Back"};

menuent_funcptr bankmenu_entryhandlers[3] = {menu_buyCoins, menu_sellCoins, menu_bankback};

int menu_buyCoins()
{
	printf("Buy Coins menu");
	return 0;
}

int menu_sellCoins()
{
	printf("Sell Coins menu");
	return 0;
}

int menu_bankback()
{
	printf("Returning to Main Menu\nYou have %d Play Coins", getCoins());
	return -2;
}

int runBankMenu()
{
	consoleClear();
	handle_menus(bankmenu_entries, bankmenu_totalentries, bankmenu_entryhandlers);
	return 0;
}
