/* Test output.c function only */
#include <ncurses.h>
#include <string.h>
#include "colors.h"
#include "io.h"
#include "output.h"

int main() {
    // setup ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    bool colorful_term = has_colors();
    if(colorful_term == TRUE){
        start_color();
        use_default_colors();
        init_colors();
    }
    // set 3 projects
    project first, second, third;
    strcpy(first.name, "first");
    strcpy(first.tech, "vscode-oss");
    strcpy(first.desc, "My first project in vscode");
    strcpy(first.open, "code-oss");
    first.color = 1;
    
    strcpy(second.name, "second");
    strcpy(second.tech, "neovim");
    strcpy(second.desc, "My first project in neovim");
    strcpy(second.open, "nvim");
    second.color = 2;

    strcpy(third.name, "third");
    strcpy(third.tech, "eclipse");
    strcpy(third.desc, "My first project in eclipse");
    strcpy(third.open, "eclipse");
    third.color = 3;

    // write :
    char *savfile_path = "/tmp/static_1menu.bin"; // linux-only
    FILE *savfile = fopen(savfile_path, "wb");
    fwrite(&first, sizeof(project), 1, savfile);
    fwrite(&second, sizeof(project), 1, savfile);
    fwrite(&third, sizeof(project), 1, savfile);
    fclose(savfile);

    // read :
    show_projs(savfile_path);

    // clean
    endwin();
    remove(savfile_path);
    return 0;
}