.PHONY: all run test

name := cx_chat

#------------------------------------------------#
#   VARIABLES                                    #
#------------------------------------------------#
SRC_DIR := src
BUILD_DIR := .build
TEST_DIR := test

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS = $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

CPPFLAGS := -I./src
CC          := clang
CFLAGS      := -Wunsused-command-line-argument -lssl -lcrypto 
CPPFLAGS    := -MMD -MP -I include
AR          := ar
ARFLAGS     := -r -c -s

#------------------------------------------------#
#   UTILS                                        #
#------------------------------------------------#
RM := rm -rf
MAKEFLAGS := --no-print-directory
DIR_DUP = mkdir -p $(@D)

#------------------------------------------------#
#   TARGETS                                      #
#------------------------------------------------#
all: $(name)

$(name): $(OBJS)
	$(AR) $(ARFLAGS) $(name) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(name)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(info CREATED: $@)

-include $(DEPS)

run: all
	./$(name)

clean:
	$(RM) $(OBJS) $(DEPS) $(TEST_OBJS)

fclean: clean
	$(RM) $(name)

re:
	$(MAKE) fclean
	$(MAKE) all

# Add test target
test: fclean $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(filter-out .build/runner.o, $(OBJS)) $(TEST_OBJS) -o run_test
	./run_test

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(info CREATED: $@)

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#
.PHONY: clean flcean re
.SILENT: 
