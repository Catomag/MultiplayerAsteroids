SOURCES = $(wildcard ./src/*.c)
SRC = $(addprefix src/, $(SOURCES))
OBJ = $(addsuffix .o, $(addprefix bin/, $(basename $(notdir $(SRC)))));
INCLUDE = -I include
CFLAGS = -W -mrecip -ffast-math -O2# -D_DEBUG_

all: asteroids

again: clean asteroids

server1: $(OBJ)
	echo $(SOURCES)
	gcc -W server1.o -lm -lraylib -o $@

server2: $(OBJ)
	echo $(SOURCES)
	gcc -W server2.o -lm -lraylib -o $@

client: $(OBJ)
	echo $(SOURCES)
	gcc -W client.o -lm -lraylib -o $@

bin/%.o : src/%.c
	gcc $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/*
	rm asteroids

install:
	echo "Can't install surry"

try: asteroids
	./asteroids

run:
	./asteroids
