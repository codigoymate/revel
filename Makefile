SRC = $(wildcard src/*.c)
OBJ = $(addprefix obj/, $(notdir $(SRC:.c=.o)))

INCLUDE = -I ./include
CFLAGS = -g -Wall -pedantic
LFLAGS = -lSDL2

BIN = ./bin/revel

all: $(BIN)
	@$(BIN)

$(BIN): $(OBJ) | bin
	gcc $(CFLAGS) $(INCLUDE) $(OBJ) -o $(BIN) $(LFLAGS)

obj/%.o: src/%.c | obj
	gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

bin:
	@mkdir -p ./bin

obj:
	@mkdir -p ./obj


.PHONY=clean
clean:
	rm -f $(BIN) $(OBJ)
