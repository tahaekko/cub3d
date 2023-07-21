# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taha <taha@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 17:25:24 by msamhaou          #+#    #+#              #
#    Updated: 2023/07/21 12:39:07 by taha             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
CC = cc
CFLAGS = -o3
HEADER = cub3d.h

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -lmlx -lm -lbsd -lX11 -lXext
	MLX_DIR = minilibx-linux/
	MLX_LINK = -L/usr/lib/
	MLX_INC = -I/usr/include
else
	MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
	MLX_DIR =
	MLX_LINK =
	MLX_INC = -I /usr/local/include
endif


OBJ_DIR = obj/

#*****************GNL*****************

GNL_SRC = get_next_line.c		get_next_line_utils.c
GNL_DIR = GNL/
GNL_OBJ_FILE = $(GNL_SRC:.c=.o)
GNL_OBJ = $(addprefix $(OBJ_DIR), $(GNL_OBJ_FILE))
#****************LIBFT****************
LIBFT_SRC =	ft_strlen.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strjoin.c ft_strdup.c ft_memcpy.c ft_strlcpy.c\
			ft_itoa.c ft_strncmp.c ft_substr.c ft_atoi.c ft_split.c
LIBFT_DIR =	libft/
LIBFT_OBJ_FILE = $(LIBFT_SRC:.c=.o)
LIBFT_OBJ = $(addprefix $(OBJ_DIR), $(LIBFT_OBJ_FILE))


#*****************SRC*****************
SRC_DIR = src/
SRC = ft_debug_tools.c ft_init.c  main.c libx_tools.c ft_grid.c ft_parse.c ft_vector_draw.c
FSRC = $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(SRC:.c=.o)
FOBJ = $(addprefix $(OBJ_DIR), $(OBJ))

all : $(NAME)

$(NAME): $(OBJ_DIR) $(FOBJ) $(LIBFT_OBJ) $(GNL_OBJ)
	${CC} $(CFLAGS) -o $(NAME) $(FOBJ) $(LIBFT_OBJ) $(GNL_OBJ) $(MLX_LINK) $(MLX_FLAGS)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(LIBFT_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(MLX_INC) -Iinclude/

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(MLX_INC) -Iinclude/

$(OBJ_DIR)%.o : $(GNL_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(MLX_INC) -Iinclude/

prog : all
	./$(NAME)
clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : fclean all
