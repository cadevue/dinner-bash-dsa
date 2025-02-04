# Variables
EXE_NAME    = my_program
OUT_DIR     = build
SRC_DIR     = src
OBJ_DIR     = $(OUT_DIR)/intermediate
BIN_DIR     = $(OUT_DIR)/bin

# Compiler and flags
CC          = gcc
CFLAGS      = -Wall -Wextra -O2
LDFLAGS     =

# Source and object files
SRCS        = $(shell find $(SRC_DIR) -name '*.c')
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Targets
.PHONY: all build clean run

all: build run

build: $(BIN_DIR)/$(EXE_NAME)

$(BIN_DIR)/$(EXE_NAME): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Create the directory for the object file
	$(CC) $(CFLAGS) -c $< -o $@

run:
	@$(BIN_DIR)/$(EXE_NAME)

clean:
	rm -rf $(OUT_DIR)