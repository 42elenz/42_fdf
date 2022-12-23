NAME = fdf
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIBS = -lmlx -lm -lft -L$(LIBFT_DIR) -L$(MLX_DIR) -framework OpenGL -framework AppKit
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEADERS) -I$(MLX_HEADERS)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_HEADERS = $(LIBFT_DIR)

MLX = $(MLX_DIR)libmlx.a
MLX_DIR = ./mlx/
MLX_HEADERS = $(MLX_DIR)

HEADERS_LIST =	fdf.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_DIR = ./src/
SRC_LIST =	main.c \
			init_frame.c \
			free_functions.c \
			estab_matrix.c \
			draw_mash.c \
			besigheim.c \
			pixel_to_iso.c \
			error.c


SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY : all bonus clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIR)

$(MLX):
	$(MAKE) -sC $(MLX_DIR)

clean :
	$(MAKE) -sC $(LIBFT_DIR) clean
	$(MAKE) -sC $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(MLX)
	rm -f $(LIBFT)
	rm -f $(NAME)

re : fclean all
