# Meta Symbols
BIN := bin
CC := gcc
LINKER := $(CC)
TARGET := app.x
EXAMPLE ?= boids

# Path Symbols
EXAMPLES_DIR := examples
SRC_DIR := src
UTIL_DIR := util
LIB_DIR := lib
RAYLIB_SRC := raylib/src

# Compiler Flags
LFLAGS := -L./$(LIB_DIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
IFLAGS := -I./include
OPT := -O1
CFLAGS := $(OPT) -Wall -std=c99 -Wno-missing-braces

# Source Symbols
UTIL_SRC := $(wildcard $(UTIL_DIR)/*.c)
SRC_SRC := $(wildcard $(SRC_DIR)/*.c)
EXAMPLE_SRC := $(EXAMPLES_DIR)/$(EXAMPLE).c

# Object Symbols
UTIL_OBJS := $(UTIL_SRC:$(UTIL_DIR)/%.c=$(BIN)/%.o)
SRC_OBJS := $(SRC_SRC:$(SRC_DIR)/%.c=$(BIN)/%.o)
EXAMPLE_OBJS = $(BIN)/$(EXAMPLE).o

.PHONY: all build build_lib run build run

build:
	@$(MAKE) create build_lib $(EXAMPLE_OBJS) 
	$(LINKER) $(UTIL_OBJS) $(SRC_OBJS) $(EXAMPLE_OBJS) $(LFLAGS) -o $(BIN)/$(TARGET)
	@echo "Linking complete!"

run: build
	@echo "Running Now"
	$(BIN)/$(TARGET)

build_lib: $(UTIL_OBJS) $(SRC_OBJS)
	@echo "Compiled Library Successfully!"

create:
	@mkdir -p $(BIN)

$(UTIL_OBJS): $(BIN)/%.o : $(UTIL_DIR)/%.c
	@$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(SRC_OBJS): $(BIN)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(EXAMPLE_OBJS): $(BIN)/%.o : $(EXAMPLES_DIR)/%.c
	@$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< successfully!"

build_raylib:
	@make -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP
	@cp $(RAYLIB_SRC)/libraylib.a $(LIB_DIR)


clean_raylib:
	make -C $(RAYLIB_SRC) clean
	$(RM) $(LIB)/libraylib.a

clean:
	$(RM) -rf $(BIN) $(OBJS)