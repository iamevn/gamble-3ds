typedef int (*menuent_funcptr)(void);

int draw_menu(char **menu_entries, int total_menuentries, int x, int y);
int handle_menus(char **menu_entries, int menu_totalentries, menuent_funcptr *menu_entryhandlers);
