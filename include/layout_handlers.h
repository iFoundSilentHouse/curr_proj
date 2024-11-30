#ifndef LAYOUT_HANDLERS_H
#define LAYOUT_HANDLERS_H
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
#endif