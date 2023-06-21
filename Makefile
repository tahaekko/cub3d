# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 17:25:24 by msamhaou          #+#    #+#              #
#    Updated: 2023/06/21 17:34:10 by msamhaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
CC = cc
HEADER = cub3d.h

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -lmlx -lm -lbsd -lX11 -lXext
	MLX_DIR = minilibx-linux
	MLX_LINK = -L$(MLX_DIR)
	MLX_INC = -I$(MLX_DIR)
else
	MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
	MLX_DIR =
	MLX_LINK =
	MLX_INC = -I /usr/local/include
endif


OBJ_DIR = obj/

#*****************GNL*****************

GNL_SRC = get_next_line.c             get_next_line_bonus.c      get_next_line_utils.c       get_next_line_utils_bonus.c
GNL_DIR = gnl/
GNL_OBJ_FILE = $(GNL_SRC:.c=.o)
GNL_OBJ = $(addprefix $(OBJ_DIR), $(GNL_OBJ_FILE))
#****************LIBFT****************
LIBFT_SRC =	ft_atoi.c         ft_islpha.c       ft_lstdelone.c    ft_memcmp.c       ft_putnbr_fd.c    ft_strjoin.c      ft_strnstr.c\
			ft_bzero.c        ft_isprint.c      ft_lstiter.c      ft_memcpy.c       ft_putstr_fd.c    ft_strlcat.c      ft_strrchr.c\
			ft_calloc.c       ft_itoa.c         ft_lstlast.c      ft_memmove.c      ft_split.c        ft_strlcpy.c      ft_strtrim.c\
			ft_isalnum.c      ft_lstadd_back.c  ft_lstnew.c       ft_memset.c       ft_strchr.c       ft_strlen.c       ft_substr.c\
			ft_isascii.c      ft_lstadd_front.c ft_lstsize.c      ft_putchar_fd.c   ft_strdup.c       ft_strmapi.c      ft_tolower.c\
			ft_isdigit.c      ft_lstclear.c     ft_memchr.c       ft_putendl_fd.c   ft_striteri.c     ft_strncmp.c      ft_toupper.c
LIBFT_DIR =	libft/
LIBFT_OBJ_FILE = $(LIBFT_SRC:.c=.o)
LIBFT_OBJ = $(addprefix $(OBJ_DIR), $(LIBFT_OBJ_FILE))


#*****************SRC*****************
SRC_DIR = src/
SRC = ft_character.c  ft_init.c  libx_tools.c  main.c	ft_grid.c	ft_vector_draw.c
FSRC = $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(SRC:.c=.o)
FOBJ = $(addprefix $(OBJ_DIR), $(OBJ))

all : $(NAME)

$(NAME): $(OBJ_DIR) $(FOBJ) $(GNL_OBJ)
	${CC} -o $(NAME) $(FOBJ) $(MLX_FLAGS) $(MLX_LINK)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(LIBFT_DIR)%.c
	$(CC) -c $< -o $@ $(MLX_INC) -Iinclude/

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) -c $< -o $@ $(MLX_INC) -Iinclude/

$(OBJ_DIR)%.o : $(GNL_DIR)%.c
	$(CC) -c $< -o $@ $(MLX_INC) -Iinclude/

clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : fclean all
