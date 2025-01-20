CC=gcc
DEV_FLAGS=-Wall -Wextra -pedantic -Wformat=2 -Wformat-truncation -pipe 
PROD_FLAGS=-Wall -pipe -O2 -flto

TARGET=curr_proj

SOURCES=src/*.c

PATH_TO_INSTALL=/usr/local/bin/

.PHONY: dev

NO_FLAGS= $(CC) -o $(TARGET) $(SOURCES) -lform -lncurses -Iinclude 

dev: clean
	$(NO_FLAGS) $(DEV_FLAGS)
release: clean
	$(NO_FLAGS) $(PROD_FLAGS)
debug: clean
	$(NO_FLAGS) $(DEV_FLAGS) -g
debug_natively: clean debug
	xterm -fa fixed -fs 16 -e /bin/sh -c "gdbserver localhost:1234 $(TARGET)" &
	gdb $(TARGET) -ex "target remote localhost:1234"

clean: 
	rm -f $(TARGET)

install: release
	cp -f $(TARGET) $(PATH_TO_INSTALL)
uninstall:
	rm -f $(PATH_TO_INSTALL)$(TARGET)
