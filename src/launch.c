#include "launch.h"
#include "io.h"

void launch(int pr_num, char *path_tosave) {
    FILE *savfile;
    project pr_tolaunch;
    savfile = fopen(path_tosave, "r");
    fseek(savfile, pr_num*sizeof(project), SEEK_SET);
    fread(&pr_tolaunch, sizeof(project), 1, savfile);
    fclose(savfile);

    const char *cmd = pr_tolaunch.open;
    endwin();
    system(cmd);
    exit(0);
}