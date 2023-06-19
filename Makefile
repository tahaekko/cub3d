
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


SRC_DIR = src/
SRC = ft_character.c  ft_init.c  libx_tools.c  main.c	ft_grid.c
FSRC = $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR = obj/
OBJ = $(SRC:.c=.o)
FOBJ = $(addprefix $(OBJ_DIR), $(OBJ))

all : $(NAME)

$(NAME): $(FOBJ)
	${CC} -o $(NAME) $(FOBJ) $(MLX_FLAGS) $(MLX_LINK)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(MLX_INC) -I.

clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : fclean all
