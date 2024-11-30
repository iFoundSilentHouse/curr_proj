#include <curses.h>
#include <ncurses.h>
#include "colors.h"

int main(int argc,char *argv[]) {
    initscr();
    // global screen mods
    cbreak();
    noecho();
    curs_set(0);

    int rows_n, cols_n;
    getmaxyx(stdscr, rows_n, cols_n);
    
    bool colorful_term = has_colors();
    if(colorful_term == TRUE){
        start_color();
        use_default_colors();
        init_colors();
    }

    int8_t chosen_color = add_color_win();
    //getch(); // suspend waiting for keypress
    endwin();
    printf("%d\n", chosen_color);
    return 0;
}