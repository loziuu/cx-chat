.PHONY: all run test

name := cx_chat

#------------------------------------------------#
#   VARIABLES                                    #
#------------------------------------------------#
SRC_DIR := src
BUILD_DIR := .build

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CPPFLAGS := -I./src
CC          := clang
#CFLAGS      := -Wall -Wextra -Werror
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
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(name)

re:
	$(MAKE) fclean
	$(MAKE) all

# Add test target
test:
	gcc -g ./src/linked_list.c ./src/iterator.c ./src/websocket.c ./test/test_suite.c ./test/linked_list_test.c ./test/websocket_test.c  ./src/base64.c ./test/base64_test.c -o run-test
	./run-test

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#
.PHONY: clean flcean re
.SILENT: 
