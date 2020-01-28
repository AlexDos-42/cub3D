# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alesanto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 17:02:25 by alesanto          #+#    #+#              #
#    Updated: 2020/01/28 22:04:39 by alesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

SRC =		main.c \
		parsing.c \
		verifmap.c \
		ft_init.c \
		ft_rendu.c \
		ft_keys.c \
		ft_utiles.c \
		ft_texture.c \
		ft_sprites.c \
		ft_bonus.c \
		ft_hand.c \

PATHSRCS = srcs

HEADERS = ./include

FLAGS = -Wall -Wextra -Werror 

// -fsanitize=address -g  #DEBUG

SRCS = $(addprefix $(PATHSRCS)/,$(SRC))
LIBS = -lmlx -framework OpenGL -framework AppKit\
	   ./libft/libft.a

all: $(NAME)

$(NAME):
	@echo "Compilation..."
	@(make re -C libft/)
	@(gcc $(FLAGS) $(SRCS) $(LIBS) -o $(NAME))
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
