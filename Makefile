# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/21 17:06:57 by rsticks           #+#    #+#              #
#    Updated: 2019/09/25 15:00:21 by rsticks          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol
FLAGS := -Wall -Werror -Wextra
MLX := -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit -framework OpenCL
SRCS := srcs/main.c srcs/add.c
LIB := -L./libft -lft -lm
INCL := -I include/ -I libft/
CC := gcc
OBJ := $(SRCS:.c=.o)

all: lib $(OBJ) $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@ $(INCL)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(LIB) $(OBJ) $(MLX)

lib:
	@make -C libft/

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@make -C libft/ clean
	@make -C libft/ fclean

re: fclean all
