NAME = fract-ol
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c # Add other .c files here
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

r: all
	./fract-ol

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
