
NAME = 21shell

SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft/

FLAGS = -Wall -Wextra -Werror -g
INC = -I ./inc/ -I $(LIBFT_DIR)/inc/

SRC_NAME = main.c \
setup.c \
signals.c \
keyboard.c \
utils.c \
editor.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_DIR) -lft -o $(NAME) -ltermcap

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@

clean:
	@make -C $(LIBFT_DIR)/ clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR)/ fclean
	rm -rf $(NAME)

test:
	@make -C test/

re: fclean all

.PHONY: all, clean, fclean, re, test
