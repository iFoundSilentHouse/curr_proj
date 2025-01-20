curr_proj - organize your programming projects in TUI (WIP).
curr_proj is TUI ncurses script that represents all user defined projects and shell scripts to open them with Enter key. It was created to intuitively recover work on old projects after a long break.
It's useful when you want to start at blank TUI and open X/Wayland (or your DE) with your project tools and chosen configuration.
Working functions: 
- adding projects in ~/.curr_proj file with: project name, description, used tech, command to launch, presenting color options.
- launching project by executing command passed to "command to launch field". (system(`command`))
- deleting last project

See TODO for functionality plan
Test in Docker: 
```
docker build -t curr_proj .
docker run -it curr_pro
```
in project folder

Developing
If anyone is interested to help, i added vscode debugging tasks. Everything else is done with Makefiles now. You can use `make` to build a dev executable with all warnings; `make release` to make light executable; `make debug` to make executable with debug info for debugging yourself; `make debug-natively` to build and start gdb with graphical debugging mode
Dependencies to build yourself: gcc, ncurses.
