SRC = ./src/main.cpp \
./src/func.cpp
OBJ = $(SRC:.c=.o)
NAME = 302separation
CC = g++
CFLAGS  = -Wall -Isrc/ -Wextra -Werror

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re