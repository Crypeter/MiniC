NOW_DIR = $(shell pwd)
CC = gcc
CFLAGS = -Wall -g -fPIC
BUILD_DIR = build
INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = test
RESULT = .result
mainargs = test1
$(shell > $(RESULT))

all:run

color:$(SRC_DIR)/color.c
	$(CC) $(CFLAGS) -shared $(SRC_DIR)/color.c -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$@
lexer:$(SRC_DIR)/lexer.c
	$(CC) $(CFLAGS) -shared $(SRC_DIR)/lexer.c -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$@ 	
parse:$(SRC_DIR)/parse.c
	$(CC) $(CFLAGS) -shared $(SRC_DIR)/parse.c -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$@ 

build:color lexer parse
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(NOW_DIR)/$(BUILD_DIR)/parse $(NOW_DIR)/$(BUILD_DIR)/lexer $(NOW_DIR)/$(BUILD_DIR)/color -I$(INCLUDE_DIR) -o $(BUILD_DIR)/MiniC

run:build
	$(BUILD_DIR)/MiniC $(NOW_DIR)/$(TEST_DIR)/$(mainargs).c   
