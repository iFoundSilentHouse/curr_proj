#ifndef LAYOUT_HANDLERS_H
#define LAYOUT_HANDLERS_H
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "color_macros.h"

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
void use_all_width(char *str_to_write, int row);
WINDOW *create_newwin(int height, int width, int starty, int startx);
WINDOW *create_newwin_in_middle(int height, int width);
void destroy_win(WINDOW *local_win);
#endif