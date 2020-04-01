SRC = $(wildcard src/*.c)
OBJ = $(addprefix obj/, $(notdir $(SRC:.c=.o)))

INCLUDE = -I ./include
CFLAGS = -g -Wall -pedantic
LFLAGS = -lSDL2 -lSDL2_image
BIN = ./bin/revel
RM_COMMAND = rm -f $(BIN) $(OBJ)

ifeq ($(OS),Windows_NT)
	INCLUDE := $(INCLUDE) -I c:/sdl/include
    WINOBJ := $(subst /,\\,$(OBJ))
    LFLAGS := -L c:/sdl/lib -lmingw32 -lSDL2main $(LFLAGS)
    BIN = bin/revel.exe
    WINBIN := $(subst /,\\,$(BIN))
    RM_COMMAND = del /s $(WINBIN) $(WINOBJ)
endif


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
	$(RM_COMMAND)
