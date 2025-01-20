#include "layout_handlers.h"

WINDOW *create_newwin_in_middle(int height, int width) {
	int starty, startx;
	int maxy, maxx;
	getmaxyx(stdscr, maxy, maxx);
	starty = maxy/2-height/2;
	startx = maxx/2-width/2;
	return create_newwin(height, width, starty, startx);
}

void use_all_width(char *str_to_write, int row) {
	int max_w = getmaxx(stdscr);
	int strsize = strlen(str_to_write);
  	int addition = max_w - strsize - 6;
  	for (int i = 0; i < addition; i++)
    strcat(str_to_write, " ");
	mvaddstr(row, 3, str_to_write);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{ 
	int max_h, max_w;
	getmaxyx(stdscr, max_h, max_w);
	if ((height+starty > max_h) || (width+startx > max_w)) {
        endwin();
        fprintf(stderr, "%s%s",
		"Not enough space to open handler window\n",
		"If your terminal supports it, zoom in and re-run the app\n");
		exit(1);
	}

	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
    wbkgd(local_win, COLOR_PAIR(BASE_COLOR));
	box(local_win, 0 , 0); 
	wrefresh(local_win);
	refresh();
	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	delwin(local_win);
	refresh();
	clear();
}