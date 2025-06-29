NAME = ProjetX

CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -Iengine
LFLAGS = -Lengine -lengine -lSDL2 -lGLEW -lGL -lcglm

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

all: bin $(NAME)

bin:
	mkdir -p $(BIN)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o ./$(BIN)/$(NAME) $(LFLAGS)

clean:
	rm -rf $(BIN)
	rm -f $(OBJ)

re: clean all

run: all
	./$(BIN)/$(NAME)

ren: clean run

.PHONY: all clean re run ren
