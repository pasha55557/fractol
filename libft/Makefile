# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsticks <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 16:35:53 by rsticks           #+#    #+#              #
#    Updated: 2019/04/06 19:53:28 by rsticks          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = *.c 

HEAD = libft.h

O = *.o

all: $(NAME)
$(NAME):
	gcc -Wall -Werror -Wextra -c $(SRC) -I $(HEAD)
	ar rc $(NAME) $(O)
	ranlib $(NAME)
clean:
		rm -f $(O)
fclean: clean
		rm -f $(NAME)

re: fclean all
