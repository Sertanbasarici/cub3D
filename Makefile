NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -lm

SOURCE = main.c
OBJ = $(SOURCE:.c=.o)
LIBRARY = -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./minilibx-linux
	@$(CC) $(CFLAGS) $(OBJ) $(LIBRARY) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C ./minilibx-linux clean
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
