
CC = gcc 

CFLAGS = -Wall -Werror
CPPFLAGS = -Iinclude

BUILD_DIR = build
OBJECT_DIR = $(BUILD_DIR)/obj
EXE = $(BUILD_DIR)/seek

SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJECT_DIR)/%.o,$(SRCS))

$(EXE): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(EXE)

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJECT_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: run clean
