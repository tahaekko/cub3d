
NAME = Cub3D
CC = cc

MLX_DIR = minilibx-linux

SRC_DIR = src/
SRC = ft_character.c  ft_init.c  libx_tools.c  main.c	ft_grid.c
FSRC = $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR = obj/
OBJ = $(SRC:.c=.o)
FOBJ = $(addprefix $(OBJ_DIR), $(OBJ))

all : $(NAME)

$(NAME): $(FOBJ)
	${CC} -o $(NAME) $(FOBJ) -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ -I $(MLX_DIR) -I .

clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : fclean all
