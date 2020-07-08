NAME 		= 	21sh

SRC_DIR 	= 	src/
OBJ_DIR 	= 	obj/
LIBFT_DIR 	= 	libft/

FLAGS 		=
INC 		= 	-I ./inc/ -I $(LIBFT_DIR)/

SRC_NAME 	= 	main.c \
				debug.c \
				signals.c \
				utils.c \
				builtins/cd.c \
				builtins/echo.c \
				builtins/index.c \
				builtins/setenv.c \
				builtins/unsetenv.c \
				builtins/utils.c \
				exec/exec.c \
				exec/index.c \
				exec/open.c \
				exec/pipe.c \
				exec/redir.c \
				exec/utils.c \
				lexer/index.c \
				lexer/token_control.c \
				lexer/token_new.c \
				lexer/token_string.c \
				lexer/utils.c \
				linedit/setup.c \
				linedit/linedit.c \
				linedit/read_more.c \
				linedit/redraw.c \
				linedit/check_keys.c \
				linedit/movement_line.c \
				linedit/movement_row.c \
				linedit/movement_cursor.c \
				linedit/utils.c \
				linedit/history.c \
				linedit/history_actions.c \
				linedit/clipboard.c \
				linedit/autocomplete/autocomplete.c \
				linedit/autocomplete/envs.c \
				linedit/autocomplete/execs.c \
				linedit/autocomplete/paths.c \
				linedit/autocomplete/buffer.c \
				linedit/autocomplete/filter.c \
				linedit/autocomplete/clean.c \
				parser/ast.c \
				parser/astutil.c \
				parser/expand.c \
				parser/heredoc.c \
				parser/index.c \
				parser/quotes.c \
				parser/syntax.c \
				parser/utils.c

SRCS 		= 	$(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_DIR) -lft -o $(NAME) -ltermcap

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj/builtins
	@mkdir -p obj/exec
	@mkdir -p obj/lexer
	@mkdir -p obj/linedit/autocomplete
	@mkdir -p obj/parser
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
