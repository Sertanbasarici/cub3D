NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iheaders/

SOURCE = new_main.c
OBJ = $(SOURCE:.c=.o)
LIBRARY = -Lminilibx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./minilibx
	@$(CC) $(CFLAGS) $(OBJ) $(LIBRARY) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C ./minilibx clean
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
