TARGET = bin/stardoo
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*

$(TARGET): $(OBJ)
	gcc -o $@ $? `sdl2-config --cflags --libs`

obj/%.o : src/%.c
	gcc -c $< -o $@ -Iinclude
