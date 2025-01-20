#include "output.h"
#include "color_macros.h" // for BASE_COLOR macro
#include "colors.h"
#include "delete.h"
#include "launch.h"

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
    clear();
    refresh();
    project prj;
    uint8_t proj_iter = 0;
    // TODO: exception handling - if data is corrupted or savefile is empty. If everything is fine just go on
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
    mvaddstr(1, 2, "Add: a; Launch: Enter; Edit chosen: e; Delete: r; See description and tech: d; Quit: q");
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
        fprintf(stderr, "Error opening file %s\n", savfile_path);
        exit(1);
    }
    
    keypad(stdscr, true);
    int chosen = 0;
    redraw_projs(savfile, chosen);
    int key = 0;
    while(key != '\n' && key != 'q') { // 10 is ENTER key; 113 is 'q'
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
                addproj(savfile_path);
                proj_n++;
                break;
            case 'E':
            case 'e':

                break;
            case 'D':
            case 'd':
            
                break;
            case 'R':
            case 'r':
                if(del(chosen, savfile_path)) {
                    proj_n--;
                    chosen = 0;
                }
                break;
            default:
                break;
        }
        redraw_projs(savfile, chosen);
    }
    attroff(COLORS);
    fclose(savfile);
    if (key == 10) { // launch
        // pass if chosen_project.launch is empty
        launch(chosen, savfile_path);
    }
}