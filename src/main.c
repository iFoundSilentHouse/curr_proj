#include <curses.h>
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define HAS_COLORS

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

#define MENUSIZE 3 
void redraw_menu(int8_t chosen_option) {
    clear();
    uint8_t c;
    for(c=0; c < MENUSIZE; c++) {
        attron(COLOR_PAIR(c+1));
        if(c != chosen_option)    
            mvaddstr(3, 15+(5*c), "< >");
        else
            mvaddstr(3, 15+(5*c), "<*>");
    }
}

int main(int argc,char *argv[]) {
    initscr();
    // global screen mods
    cbreak();
    noecho();

    int rows_n, cols_n;
    getmaxyx(stdscr, rows_n, cols_n);
    
    bool colorful_term = has_colors();
    if(colorful_term == TRUE){
        start_color();
        use_default_colors();
    }

    // color menu module
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    int8_t chosen = 0;

    //redraw_menu(chosen);
    int key = 0;
    keypad(stdscr, TRUE); // menu input mode
    curs_set(0);
    while(key != 10) { // 10 is ENTER key
        key = getch();
        switch(key) {
            case KEY_RIGHT:
                chosen++;
                if(chosen > MENUSIZE-1)
                    chosen = 0;
                break;
            case KEY_LEFT:
                chosen--;
                if(chosen < 0)
                    chosen = MENUSIZE-1;
                break;
            default:
                break;
        }
        //redraw_menu(chosen);
    }
    //getch(); // suspend waiting for keypress
    endwin();
    return 0;
}