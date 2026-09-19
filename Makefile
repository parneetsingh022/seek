CC = gcc

CFLAGS = -Wall -Werror
CPPFLAGS = -Iinclude

BUILD_DIR = build
OBJECT_DIR = $(BUILD_DIR)/obj
TEST_BUILD_DIR = $(BUILD_DIR)/tests

EXE = $(BUILD_DIR)/seek

SRC_DIR = src
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJECT_DIR)/%.o,$(SRCS))

# All source files except main.c, because tests have their own main()
LIB_SRCS = $(filter-out $(SRC_DIR)/main.c,$(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c,$(TEST_BUILD_DIR)/%,$(TEST_SRCS))


$(EXE): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(EXE)


$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJECT_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


$(TEST_BUILD_DIR)/%: $(TEST_DIR)/%.c $(LIB_SRCS)
	mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LIB_SRCS) -o $@


test: $(TEST_BINS)
	@for test in $(TEST_BINS); do \
		echo "Running $$test"; \
		$$test || exit 1; \
	done


run: $(EXE)
	./$(EXE)


clean:
	rm -rf $(BUILD_DIR)


.PHONY: run test clean
