#include "output.h"
#include "colors.h"
#include "layout_handlers.h"
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// attempting to not load projects in memory but access them with fread every representation/change

uint8_t get_proj_n (FILE *savfile) {
    uint8_t i = 0;
    project prj;
    while (fread(&prj, sizeof(project), 1, savfile)) {
        i++;
    }
    rewind(savfile);
    return i;
}

void redraw_projs(FILE *savfile, uint8_t chosen) {
    project prj;
    uint8_t proj_iter = 0;
    // exception handling - if data is corrupted or savefile is empty. If everything is fine just go on
    while (fread(&prj, sizeof(project), 1, savfile)) {
        //
        if (!prj.color)
            attron(COLOR_PAIR(BASE_COLOR));
        else
            attron(COLOR_PAIR(prj.color));
        if (chosen == proj_iter)
            attron(A_BOLD);
        //
        use_all_width(prj.name, 3+2*proj_iter);
        //
        if (!prj.color)
            attroff(COLOR_PAIR(BASE_COLOR));
        else
            attroff(COLOR_PAIR(prj.color));
        if (chosen == proj_iter)
            attroff(A_BOLD);
        //
        proj_iter++;
    }
    mvaddstr(1, 2, "Add new project: a; See description: d; See tech: t; Launch chosen: l; Change color: c");
    rewind(savfile);
}

// for default screen (stdscr)
void show_projs(char *savfile_path) {
    FILE *savfile;
    // if file doesn't exist, create it and then open with rb+
    if (!(savfile = fopen(savfile_path, "rb+"))) {
        savfile = fopen(savfile_path, "w");
        savfile = fopen(savfile_path, "rb+");
    }
    uint8_t proj_n = get_proj_n(savfile);
    if (savfile == NULL) {
        endwin();
        printf("Error opening file %s\n", savfile_path);
        exit(1);
    }
    
    keypad(stdscr, TRUE);
    int chosen = 0;
    redraw_projs(savfile, chosen);
    int key = 0;
    while(key != 10 && key != 'q') { // 10 is ENTER key; 113 is 'q'
        key = getch();
        switch(key) {
            case KEY_DOWN:
            case 'j': // vim binding
                chosen++;
                if(chosen > proj_n-1)
                    chosen = 0;
                break;
            case KEY_UP:
            case 'k': // vim binding
                chosen--;
                if(chosen < 0)
                    chosen = proj_n-1;
                break;
            case 'A':
            case 'a':
            
                break;
            case 'D':
            case 'd':
            
                break;
            case 'T':
            case 't':
            
                break;
            case 'C':
            case 'c':
            
                break;
            default:
                break;
        }
        redraw_projs(savfile, chosen);
    }
    attroff(COLORS);
}