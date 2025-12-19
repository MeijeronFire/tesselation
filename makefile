# mogrify -format png *.ppm

CC      = gcc

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

CFLAGS  = -Ofast -Wall -Wextra -Wpedantic -I$(INC_DIR)

LDLIBS  = -lpthread -pthread -lm

OBJS = \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/fast_tesselation.o \
	$(OBJ_DIR)/tpool.o \
	$(OBJ_DIR)/defs.o \

all: tes

tes: $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

# Ensure build directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# C sources --> build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf out/*.ppm out/*.png
