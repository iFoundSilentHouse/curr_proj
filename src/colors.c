// color menu module
#include "colors.h"
static WINDOW *colwin;

void init_colors()
{
    // color menu module
    for (int i = 1; i <= COLORS; i++) {
        init_pair(i, COLOR_BLACK, i);
    }
    init_pair(BASE_COLOR, COLOR_WHITE, COLOR_BLACK);
}

void redraw_color_menu(int8_t chosen_option) 
{
    uint8_t c;
    for(c=1; c <= COLORS; c++) {
        wattron(colwin, COLOR_PAIR(c));
        if(c != chosen_option)
            mvwaddstr(colwin, 1, 5*c-2, "< >");
        else
            mvwaddstr(colwin, 1, 5*c-2, "<*>");
    }
    wrefresh(colwin);
}

int8_t choose_color_win() {
    colwin = create_newwin(3, COLORS*5+4, 3, 5);
    curs_set(0);
    int chosen = 1;
    keypad(stdscr, true);
    int key = 0;
    redraw_color_menu(chosen);
    while(key != '\n' && key != 'q') {
        key = getch();
        switch(key) {
            case KEY_RIGHT:
                chosen++;
                if(chosen > COLORS)
                    chosen = 1;
                break;
            case KEY_LEFT:
                chosen--;
                if(chosen < 1)
                    chosen = COLORS;
                break;
            default:
                break;
        }
        redraw_color_menu(chosen);
    }
    destroy_win(colwin);
    curs_set(1);
    if (key == '\n')
        return chosen;
    else
        return BASE_COLOR;
}
