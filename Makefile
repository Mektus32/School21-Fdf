# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojessi <ojessi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/07 11:10:50 by ojessi            #+#    #+#              #
#    Updated: 2019/06/07 18:19:58 by ojessi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, obj, clean, fclean, re

NAME = fdf

#src / obj files
SRC =	main.c \
		key_hook.c \
		print_line.c \
		parse_points.c
		

OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

# compiler
CC = gcc
CFLAGS = -Wextra -Wall -Werror -g

# mlx library
MLX = ./minilibx/
MLX_LIB = $(addprefix $(MLX), mlx.a)
MLX_INC = -I ./minilibx
MLX_LNK = -L ./minilibx -l mlx -framework OpenGL -framework AppKit

# ft library
FT = ./libft
FT_LIB	= $(addprefix $(FT), libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

# directorues
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(MLX_LIB):
	make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all