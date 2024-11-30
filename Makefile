CC=gcc
DEV_FLAGS=-Wall -Wextra -pedantic -Wformat=2 -Wformat-truncation -pipe 
PROD_FLAGS=-Wall -pipe -O2 -flto

TARGET=curr_proj

SOURCES=src/*.c

.PHONY: clean dev

NO_FLAGS= $(CC) -lncurses -o $(TARGET) $(SOURCES)

dev:
	$(NO_FLAGS) $(DEV_FLAGS)
prod:
	$(NO_FLAGS) $(PROD_FLAGS)

clean: 
	rm $(TARGET)
