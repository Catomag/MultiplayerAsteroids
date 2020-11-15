SOURCES = $(wildcard ./src/*.c)
SRC = $(addprefix src/, $(SOURCES))
OBJ = $(addsuffix .o, $(addprefix bin/, $(basename $(notdir $(SRC)))));
INCLUDE = -I include
CFLAGS = -W -mrecip -ffast-math -O2# -D_DEBUG_

all: server1 server2 client

server1: $(OBJ)
	echo $(SOURCES)
	gcc -W bin/server1.o -lm -lraylib -o $@

server2: $(OBJ)
	echo $(SOURCES)
	gcc -W bin/server2.o -lm -lraylib -o $@

client: $(OBJ)
	echo $(SOURCES)
	gcc -W bin/client.o -lm -lraylib -o $@

bin/%.o : src/%.c
	gcc $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/*
	rm client server1 server2

install:
	echo "Can't install surry"

try: asteroids
	./asteroids

run:
	./asteroids
