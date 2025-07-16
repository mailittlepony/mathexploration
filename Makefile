######################################################################
# @author      : mailitg (mailitg@$HOSTNAME)
# @file        : Makefile
# @created     : Thursday Dec 26, 2024 19:44:39 CET
######################################################################

APP_NAME=math_exploration

BUILD_DIR=build
OBJ_DIR:=$(BUILD_DIR)/obj
BIN_DIR:=$(BUILD_DIR)/bin

SRC_DIR=src
SRCS:=$(shell find $(SRC_DIR) -name '*.cpp')

OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

LIBS_DIR=libs
INCLUDE_DIR=include \
			$(LIBS_DIR)/glfw/include \
			$(LIBS_DIR)/glew/include \
			$(LIBS_DIR)/simpleECS/include \
			$(LIBS_DIR)/glm \
			$(LIBS_DIR)/stb \
			$(SRC_DIR)  
INCLUDES:=$(addprefix -I, $(INCLUDE_DIR))

CPPFLAGS:= $(INCLUDES)

CC=g++
CFLAGS=-g -Wall -std=c++17

# Linker flags
LDFLAGS= 
LDLIBS= -framework OpenGL -framework Cocoa -framework IOKit \
			  $(LIBS_DIR)/glew/lib/libGLEW.a \
			  $(LIBS_DIR)/simpleECS/build/lib/libECSCPP.a \
			  $(LIBS_DIR)/glfw/lib-universal/libglfw3.a


.PHONY: build
build: $(BIN_DIR)/$(APP_NAME)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(APP_NAME): $(OBJS) | $(BIN_DIR)
	@mkdir -p $(BIN_DIR)  
	$(CC) $(OBJS) $(LDLIBS) -o $(BIN_DIR)/$(APP_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: run
run: $(BIN_DIR)/$(APP_NAME)
	$(BIN_DIR)/$(APP_NAME)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

