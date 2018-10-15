CC=gcc
CFLAGS=-g -std=c99 -Wall #-Werror

all: mp8 mp8_gold test

mp8: main.o game.o getch_fun.o
	$(CC) $(CFLAGS) main.o game.o getch_fun.o -o mp8

mp8_gold: main.o getch_fun.o
	$(CC) $(CFLAGS) main.o test_src/game_gold.o getch_fun.o -o mp8_gold

test: test_src/test.o test_src/game_test.o game.o getch_fun.o
	$(CC) $(CFLAGS) test_src/test.o test_src/game_test.o game.o getch_fun.o -o mp8_test

grade_mp8: grade_mp8.o game.o getch_fun.o test_src/game_test.o
	$(CC) $(CFLAGS) grade_mp8.o game.o getch_fun.o test_src/game_test.o -o grade_mp8

grade_mp8.o: grade_mp8.c
	$(CC) $(CFLAGS) -c grade_mp8.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

getch_fun.o: getch_fun.c
	$(CC) $(CFLAGS) -c getch_fun.c



clean:
	rm -f getch_fun.o test_src/game_test.o test_src/test.o game.o main.o mp8 mp8_gold
