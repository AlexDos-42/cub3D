NAME = cub3D.a

SRC =		main.c \ 
			parsing.c \

PATHSRCS = srcs

PATHTMP = tmp

HEADERS	= ./include

FLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix $(PATHSRCS)/,$(SRC))
OBJS = $(addprefix $(PATHTMP)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compilation de ft_printf..."
	@(make -C libft/)
	@(cp libft/libft.a ./$(NAME))
	@(ar rc $(NAME) $(OBJS))
	@(ranlib $(NAME))
	@echo "Compilation terminée"

$(PATHTMP)/%.o: $(PATHSRCS)/%.c
	@(mkdir -p tmp)
	@(gcc $(FLAGS) -I $(HEADERS) -o $@ -c $<)

clean:
	@echo "Clean"
	@(make clean -C ./libft/)
	@(rm -rf $(PATHTMP))
	@(rm -rf $(SRCS:.c=.o))

fclean:	clean
	@echo "Fclean"
	@(make fclean -C ./libft/)
	@(rm -rf $(NAME))

re:	fclean all

.PHONY:	all clean fclean re
