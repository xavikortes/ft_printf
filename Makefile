NAME = _test.out

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
MEMCHECK = valgrind
MEMFLAGS = --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all

LIB_DIR = ./project
LIBS = \
	$(LIB_DIR)/libftprintf.a \
	$(LIB_DIR)/libft/libft.a

TEST = tests/test_suite.c

all: $(NAME)

$(NAME): $(LIBS)
	$(CC) $(CFLAGS) $(TEST) $(LIBS) -o $(NAME)
	./$(NAME)

$(LIBS):
	$(MAKE) bonus -C $(LIB_DIR)

memcheck: $(NAME)
	$(MEMCHECK) $(MEMFLAGS) ./$(NAME)

clean:
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all test memcheck clean fclean re
