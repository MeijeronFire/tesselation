CC      = gcc
NVCC    = nvcc

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build

CFLAGS  = -O3 -Wall -Wextra -I$(INC_DIR)
NVFLAGS = -O3 -I$(INC_DIR)

LDLIBS  = -Wpedantic -lpthread -pthread -lm

OBJS = \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/fast_tesselation.o \
	$(OBJ_DIR)/tpool.o \
	$(OBJ_DIR)/defs.o \
	$(OBJ_DIR)/gpu_kernels.o

all: tes

tes: $(OBJ_DIR) $(OBJS)
	$(NVCC) $(OBJS) -o $@ $(LDLIBS)

# Ensure build directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# C sources → build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# CUDA sources → build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cu | $(OBJ_DIR)
	$(NVCC) $(NVFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*
