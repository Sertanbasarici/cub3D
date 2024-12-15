NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -lm

SOURCE = new_main.c
OBJ = $(SOURCE:.c=.o)
LIBRARY = -Lminilibx-linux -lmlx -lXext -lX11 -lm

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./minilibx-linux
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIBRARY) $(LIBFT) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./minilibx-linux clean
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY:
	all clean fclean re
