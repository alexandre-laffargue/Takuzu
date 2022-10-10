CC=gcc
CFLAGS= -std=c99 -Wall
LDLIBS= -L. -lgame


all:game_text

game_text.o: game_text.c  game.h game_aux.h
	$(CC) $(CFLAGS) $< -c 


game_text: game_text.o libgame.a
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

.PHONY : clean
clean:
	-rm -f *.o game_text