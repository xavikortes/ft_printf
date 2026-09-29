NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
AR = ar rcs

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

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
SRC_ = $(addsuffix .c, $(SRC))
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_))
OBJS = $(SRC_:%.c=$(OBJ_DIR)/%.o)

BONUS_SRC = $(SRC) parse_options_bonus
BONUS_SRC_ = $(addsuffix .c, $(BONUS_SRC))
BONUS_SRCS = $(addprefix $(SRC_DIR)/, $(BONUS_SRC_))
BONUS_OBJS = $(BONUS_SRC_:%.c=$(OBJ_DIR)/%.o)

LIB_DIR = ./libft
LIB = $(LIB_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: fclean $(LIB) $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

$(LIB):
	$(MAKE) -C $(LIB_DIR)
	cp $(LIB) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIB_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
