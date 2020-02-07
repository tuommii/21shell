
NAME 		= 	21sh
SRC_DIR 	= 	src/
OBJ_DIR 	= 	obj/
LIBFT_DIR 	= 	libft/
FLAGS 		= 	-g
INC 		= 	-I ./inc/ -I $(LIBFT_DIR)/includes

SRC_NAME 	= 	main.c \
				setup.c \
				signals.c \
				prompt.c \
				debug/debug.c \
				input/move.c \
				input/history.c \
				input/edit.c \
				input/keyboard.c \
				lexer/lexer.c \
				lexer/token.c \
				lexer/utils.c \
				parser/parser.c \
				parser/syntax.c \
				parser/utils.c
				# builtins/cd.c \
				# builtins/echo.c \
				# builtins/env_utils.c \
				# builtins/setenv.c \
				# builtins/unsetenv.c

SRCS 		= 	$(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(SRCS) $(INC) -L $(LIBFT_DIR) -lft -o $(NAME) -ltermcap

clean:
	@make -C $(LIBFT_DIR)/ clean

fclean: clean
	@make -C $(LIBFT_DIR)/ fclean
	@rm -rf $(NAME)

re: fclean all

norm:
	norminette src/*.c
	norminette inc/*.h
	make norm -C libft

push:
	git push origin srouhe

pull:
	git pull origin srouhe

.PHONY: all, clean, fclean, re, norm, push, pull
