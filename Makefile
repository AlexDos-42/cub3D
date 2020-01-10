# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alesanto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 17:02:25 by alesanto          #+#    #+#              #
#    Updated: 2020/01/10 14:47:44 by alesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC =		main.c \
		parsing.c \
		verifmap.c \
		ft_init.c 

PATHSRCS = srcs

HEADERS = ./include

FLAGS = -Wall -Wextra -Werror

SRCS = $(addprefix $(PATHSRCS)/,$(SRC))
LIBS = -lmlx -framework OpenGL -framework AppKit\
	   ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compilation..."
	@(make -C libft/)
	@(gcc $(FLAGS) $(SRCS) $(LIBS))
	@(echo "Compilation terminée")

clean:
	@echo "Clean"
	@(make clean -C ./libft/)

fclean:	clean
	@echo "Fclean"
	@(make fclean -C ./libft/)
	@(rm -rf $(NAME))

re:	fclean all

.PHONY:	all clean fclean re
