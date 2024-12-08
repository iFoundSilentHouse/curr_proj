#ifndef COLORS_H
#define COLORS_H
#include <stdint.h>
#include <ncurses.h>

#define COLORS 8
#define BASE_COLOR COLORS+1
void init_colors();
int8_t add_color_win();

#endif