CC=g++-4.9
SRC_DIR=src
CFLAGS=-Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -std=c++11 -pedantic -Werror -g -c -I$(SRC_DIR)
LFLAGS=-lSDL2 -lSDL2_image `sdl-config --libs` -lSDL2_ttf

all: orbitgame

orbitgame: structure misc spikes
	$(CC) *.o -o orbitgame $(LFLAGS)

structure: main.o game.o map.o text.o stopwatch.o highscore.o
misc: hitbox.o sprite.o orbital.o bubble.o goal.o victory.o
spikes: spike.o cluster.o launcher.o projectile.o

main.o: $(SRC_DIR)/main.cc
	$(CC) $(CFLAGS) $(SRC_DIR)/main.cc

game.o: $(SRC_DIR)/game.cc
	$(CC) $(CFLAGS) $(SRC_DIR)/game.cc

hitbox.o: $(SRC_DIR)/hitbox.cc $(SRC_DIR)/hitbox.h
	$(CC) $(CFLAGS) $(SRC_DIR)/hitbox.cc

sprite.o: $(SRC_DIR)/sprite.cc $(SRC_DIR)/sprite.h
	$(CC) $(CFLAGS) $(SRC_DIR)/sprite.cc

orbital.o: $(SRC_DIR)/orbital.cc $(SRC_DIR)/orbital.h
	$(CC) $(CFLAGS) $(SRC_DIR)/orbital.cc

bubble.o: $(SRC_DIR)/bubble.cc $(SRC_DIR)/bubble.h
	$(CC) $(CFLAGS) $(SRC_DIR)/bubble.cc

spike.o: $(SRC_DIR)/spike.cc $(SRC_DIR)/spike.h
	$(CC) $(CFLAGS) $(SRC_DIR)/spike.cc

cluster.o: $(SRC_DIR)/cluster.cc $(SRC_DIR)/cluster.h
	$(CC) $(CFLAGS) $(SRC_DIR)/cluster.cc

launcher.o: $(SRC_DIR)/launcher.cc $(SRC_DIR)/launcher.h
	$(CC) $(CFLAGS) $(SRC_DIR)/launcher.cc

projectile.o: $(SRC_DIR)/projectile.cc $(SRC_DIR)/projectile.h
	$(CC) $(CFLAGS) $(SRC_DIR)/projectile.cc

map.o: $(SRC_DIR)/map.cc $(SRC_DIR)/map.h
	$(CC) $(CFLAGS) $(SRC_DIR)/map.cc

goal.o: $(SRC_DIR)/goal.cc $(SRC_DIR)/goal.h
	$(CC) $(CFLAGS) $(SRC_DIR)/goal.cc

text.o: $(SRC_DIR)/text.cc $(SRC_DIR)/text.h
	$(CC) $(CFLAGS) $(SRC_DIR)/text.cc

stopwatch.o: $(SRC_DIR)/stopwatch.cc $(SRC_DIR)/stopwatch.h
	$(CC) $(CFLAGS) $(SRC_DIR)/stopwatch.cc

victory.o: $(SRC_DIR)/victory.cc $(SRC_DIR)/victory.h
	$(CC) $(CFLAGS) $(SRC_DIR)/victory.cc

highscore.o: $(SRC_DIR)/highscore.cc $(SRC_DIR)/highscore.h
	$(CC) $(CFLAGS) $(SRC_DIR)/highscore.cc

clean:
	rm -rf *.o orbitgame

run: orbitgame
	./orbitgame
