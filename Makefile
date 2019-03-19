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

FLAGSwww = -Wall -Wextra -Werror
FLAGS = -lmlx -framework OpenGL -framework Appkit
SRCS =	main.c fdf.c ft_count.c ft_paint.c create_and_free.c ft_rotate.c menu.c

INC = fdf.h

all: $(NAME)

OBJ = $(SRCS:.c=.o)

.PHONY : libft
libft:
	@make -C./libft

$(NAME): libft $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(FLAGS) ./libft/libft.a
	@echo "\033[34mFDF compilation DONE.\033[0m"

%.o: %.c $(INC)
	@gcc -o $@ -c $< $(FLAGSwww)

clean:
	@make clean -C ./libft
	@rm -f $(OBJ)
	@rm -f *.c~
	@rm -f *~

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re: fclean all
