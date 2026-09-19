CC = gcc

CFLAGS = -Wall -Werror
CPPFLAGS = -Iinclude -Iexternal/unity/src

BUILD_DIR = build
OBJECT_DIR = $(BUILD_DIR)/obj
TEST_BUILD_DIR = $(BUILD_DIR)/tests

SRC_DIR = src
TEST_DIR = tests
UNITY_DIR = external/unity/src

EXE = $(BUILD_DIR)/seek

# Project source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJECT_DIR)/%.o,$(SRCS))

# Source files that can be linked into tests.
# main.c is excluded because each test file has its own main().
LIB_SRCS = $(filter-out $(SRC_DIR)/main.c,$(SRCS))

# Unity
UNITY_SRC = $(UNITY_DIR)/unity.c

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(TEST_BUILD_DIR)/%,$(TEST_SRCS))


# ---------------------------------------------------------
# Main executable
# ---------------------------------------------------------

$(EXE): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(EXE)


# ---------------------------------------------------------
# Project object files
# ---------------------------------------------------------

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJECT_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------

$(TEST_BUILD_DIR)/%: $(TEST_DIR)/%.c $(UNITY_SRC) $(LIB_SRCS)
	mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@


test: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test"; \
		$$test || exit 1; \
	done


# ---------------------------------------------------------
# Run
# ---------------------------------------------------------

run: $(EXE)
	./$(EXE)


# ---------------------------------------------------------
# Clean
# ---------------------------------------------------------

clean:
	rm -rf $(BUILD_DIR)


.PHONY: run test clean
