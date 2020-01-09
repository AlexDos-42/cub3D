# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alesanto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 17:02:25 by alesanto          #+#    #+#              #
#    Updated: 2020/01/09 18:09:13 by alesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D.a

SRC =		main.c \
		parsing.c \
		verifmap.c \
		ft_init.c 

PATHSRCS = srcs

PATHTMP = tmp

HEADERS = ./include

// FLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix $(PATHSRCS)/,$(SRC))
OBJS = $(addprefix $(PATHTMP)/,$(SRC:.c=.o))
LIBS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compilation..."
	make -C libft/
	cp libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	@echo "Compilation terminée"

$(PATHTMP)/%.o: $(PATHSRCS)/%.c
	@(mkdir -p tmp)
	@(gcc $(FLAGS) -I $(HEADERS) -o $@ -c $< $(LIBS))

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
