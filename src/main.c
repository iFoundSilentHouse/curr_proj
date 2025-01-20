#include "colors.h"
#include "io.h"
#include "output.h"

int main(int argc,char *argv[]) {
    initscr();
    // global screen mods
    cbreak();
    noecho();
    curs_set(0);

    bool colorful_term = has_colors();
    if(colorful_term == TRUE){
        start_color();
        use_default_colors();
        init_colors();
    }

    char *savefile_path;
    savefile_path = get_savfile_path(argc, argv);
    
    show_projs(savefile_path);

    endwin();
    return 0;
}