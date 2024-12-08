CC=gcc
CFLAGS=-Wall -Wextra -pedantic -Wformat=2 -Wformat-truncation -pipe -lncurses -I../include

.PHONY: all

all: static_1menu

static_1menu: clean_static_1menu
	$(CC) $(CFLAGS) -o static_1menu $(filter-out ../src/main.c, $(wildcard ../src/*.c)) static_1menu.c
clean_static_1menu:
	rm -f static_1menu