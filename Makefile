
NAME 		= 	21sh

SRC_DIR 	= 	src/
OBJ_DIR 	= 	obj/
LIBFT_DIR 	= 	libft/

FLAGS 		= 	-g
INC 		= 	-I ./inc/ -I $(LIBFT_DIR)/

LINE_DIR = line/
LINE_SRC = move.c \
setup.c
LINE_SRCS = $(addprefix $(LINE_DIR), $(SRC_NAME))

SRC_NAME 	= 	main.c \
				signals.c \
				line/line.c \
				line/move.c \
				line/setup.c \
				line/keyboard.c
				# setup.c \
				# prompt.c \
				# history.c \
				# edit.c \
				# cmd.c \
				# lexer.c
				# builtins/cd.c \
				# builtins/echo.c \
				# builtins/env_utils.c \
				# builtins/setenv.c \
				# builtins/unsetenv.c

SRCS 		= 	$(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_DIR) -lft -o $(NAME) -ltermcap

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@mkdir -p obj/line
	@gcc -c $(FLAGS) $(INC) $< -o $@

clean:
	@make -C $(LIBFT_DIR)/ clean
	rm -rf $(OBJ_DIR)

main:
	make
	./21sh

fclean: clean
	make -C $(LIBFT_DIR)/ fclean
	rm -rf $(NAME)

test:
	@make -C test/

re: fclean all

.PHONY: all, clean, fclean, re, test
