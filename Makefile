#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiven <dpiven@student.unit.ua>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/27 15:15:05 by dpiven            #+#    #+#              #
#    Updated: 2019/02/27 15:15:08 by dpiven           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fdf

SRC = main.c fdf.c ft_count.c ft_paint.c

LIB = @make -C libft/

all: $(NAME)

$(NAME):
	$(LIB)
#	@gcc -Wall -Wextra -Werror -o $(NAME) $(SRC) ./libft/libft.a -I./ -I./libft/ -lmlx -framework OpenGL -framework AppKit
	@gcc -Wall  -o $(NAME) $(SRC) ./libft/libft.a -I./ -I./libft/ -lmlx -framework OpenGL -framework AppKit
clean:
	@$(LIB) clean

fclean: clean
	@$(LIB) fclean
	@rm -f $(NAME)
	@rm -f *.c~
	@rm -f *~

re: fclean all