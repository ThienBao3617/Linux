CUR_DIR := .
SRC_DIR := $(CUR_DIR)/Src
INC_DIR := $(CUR_DIR)/Inc
BIN_SHARED_DIR := $(CUR_DIR)/bin/shared
BIN_STATIC_DIR := $(CUR_DIR)/bin/static
OBJ_DIR := $(CUR_DIR)/obj
OBJ_SHARED_DIR := $(OBJ_DIR)/shared
OBJ_STATIC_DIR := $(OBJ_DIR)/static
LIB_DIR := $(CUR_DIR)/lib
LIB_SHARED_DIR := $(LIB_DIR)/shared
LIB_STATIC_DIR := $(LIB_DIR)/static

C_FLAGS := -I$(INC_DIR)

.PHONY: all clean create_dirs

all: create_dirs create_objs create_shared_lib create_static_lib
	# link shared lib
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -lAddAnswerShared -o $(BIN_SHARED_DIR)/use-shared-library
	# link static lib
	gcc $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -lAddAnswerStatic -o $(BIN_STATIC_DIR)/statically-linked

create_dirs:
	@echo "Creating folder structure..."
	@mkdir -p $(BIN_SHARED_DIR) $(BIN_STATIC_DIR)
	@mkdir -p $(OBJ_SHARED_DIR) $(OBJ_STATIC_DIR)
	@mkdir -p $(LIB_SHARED_DIR) $(LIB_STATIC_DIR)

create_objs: create_dirs
	# create object files for shared lib
	gcc -c -fPIC $(SRC_DIR)/add.c -o $(OBJ_SHARED_DIR)/add.o $(C_FLAGS)
	gcc -c -fPIC $(SRC_DIR)/ans.c -o $(OBJ_SHARED_DIR)/ans.o $(C_FLAGS)
	# create object files for static lib
	gcc -c $(SRC_DIR)/add.c -o $(OBJ_STATIC_DIR)/add.o $(C_FLAGS)
	gcc -c $(SRC_DIR)/ans.c -o $(OBJ_STATIC_DIR)/ans.o $(C_FLAGS)
	# create object file for main
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(C_FLAGS)

create_shared_lib: create_dirs
	# create shared lib
	gcc -shared $(OBJ_SHARED_DIR)/add.o $(OBJ_SHARED_DIR)/ans.o -o $(LIB_SHARED_DIR)/libAddAnswerShared.so

create_static_lib: create_dirs
	# create static lib
	ar rcs $(LIB_STATIC_DIR)/libAddAnswerStatic.a $(OBJ_STATIC_DIR)/add.o $(OBJ_STATIC_DIR)/ans.o

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(BIN_SHARED_DIR) $(BIN_STATIC_DIR)
