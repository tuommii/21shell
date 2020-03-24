NAME 		= 	21sh

SRC_DIR 	= 	src/
OBJ_DIR 	= 	obj/
LIBFT_DIR 	= 	libft/

FLAGS 		= 	-g -Wall -Wextra -Werror
INC 		= 	-I ./inc/ -I $(LIBFT_DIR)/

SRC_NAME 	= 	main.c \
				linedit/setup.c \
				linedit/linedit.c \
				linedit/signals.c \
				linedit/keyboard.c \
				linedit/redraw.c \
				linedit/cut_copy_paste.c \
				linedit/check_keys.c \
				linedit/line_movement.c \
				linedit/row_movement.c \
				linedit/utils.c \
				linedit/autocomplete.c \
				linedit/history.c

SRCS 		= 	$(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_DIR) -lft -o $(NAME) -ltermcap

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@mkdir -p obj/linedit
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
