NAME = libengine.a

CC = gcc
CFLAGS = -Wall -Werror -Wpedantic
LFLAGS = -lSDL2 -lGLEW -lGL -lcglm

SRC = $(wildcard ./**/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f $(NAME)

re: clean all

.PHONY: all clean re
