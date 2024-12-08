#include "layout_handlers.h"
#include <ncurses.h>

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string) 
{
	int length, x, y;
	float temp;

	if(win == NULL)
	  win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
	  x = startx;
	if(starty != 0)
	  y = starty;
	if(width == 0)
	  width = 80;

	length = strlen(string);
	temp = ((float)width - (float)length)/ 2;
	x = startx + (int)temp;
	mvwprintw(win, y, x, "%s", string);
	refresh();
}

void use_all_width(char *str_to_write, int row) {
	int rows_n, cols_n;
	getmaxyx(stdscr, rows_n, cols_n);
	int strsize = strlen(str_to_write);
  int addition = cols_n - strsize - 6;
  for (int i = 0; i < addition; i++)
    strcat(str_to_write, " ");
	mvaddstr(row, 3, str_to_write);
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{ 
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0); 
	wrefresh(local_win);
	refresh();
	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}