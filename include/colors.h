#ifndef COLORS_H
#define COLORS_H
#include <stdint.h>
#include <ncurses.h>
#include "layout_handlers.h"
#include "color_macros.h"

void init_colors();
int8_t choose_color_win();

#endif