NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
AR = ar rcs

SRC = \
	ft_printf \
	parse_options \
	print_argument \
	print_char \
	print_string \
	print_int \
	print_uint \
	print_hex \
	print_ptr \
	print_utils \
	num_utils
SRCS = $(addsuffix .c, $(SRC))

OBJ_DIR = ./obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

BONUS_SRC = $(SRC) parse_options_bonus
BONUS_SRCS = $(addsuffix .c, $(BONUS_SRC))
BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

LIB_DIR = ./libft
LIB = $(LIB_DIR)/libft.a

all: $(NAME)

bonus: fclean $(LIB) $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

$(NAME): $(LIB) $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIB_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
