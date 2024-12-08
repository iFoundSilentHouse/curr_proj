// color menu module
#include "colors.h"
#include "layout_handlers.h"
WINDOW *colwin;

void init_colors()
{
    // color menu module
    for (int i = 1; i < COLORS+1; i++) {
        init_pair(i, COLOR_BLACK, i);
    }
    init_pair(BASE_COLOR, COLOR_WHITE, COLOR_BLACK);
}

void redraw_color_menu(int8_t chosen_option) 
{
    //wclear(colwin);
    uint8_t c;
    for(c=0; c < COLORS; c++) {
        wattron(colwin, COLOR_PAIR(c+1));
        if(c != chosen_option)    
            mvwaddstr(colwin, 1, 3+(5*c), "< >");
        else
            mvwaddstr(colwin, 1, 3+(5*c), "<*>");
    }
    wrefresh(colwin);
}

int8_t add_color_win() {
    colwin = create_newwin(3, COLORS*5+4, 3, 5);
    wbkgd(colwin, COLOR_PAIR(BASE_COLOR));
    int chosen = 0;
    keypad(stdscr, TRUE); // menu input mode
    int key = 0;
    redraw_color_menu(chosen);
    while(key != 10 && key != 113) { // 10 is ENTER key; 113 is 'q'
        key = getch();
        switch(key) {
            case KEY_RIGHT:
                chosen++;
                if(chosen > COLORS-1)
                    chosen = 0;
                break;
            case KEY_LEFT:
                chosen--;
                if(chosen < 0)
                    chosen = COLORS-1;
                break;
            default:
                break;
        }
        redraw_color_menu(chosen);
    }
    destroy_win(colwin);
    if (key == 10)
        return chosen;
    else
        return -1;
}
