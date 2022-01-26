all: player server


player: player.o networking.o word_handling.o game.o
	gcc -o player player.o networking.o word_handling.o game.o -lm

server: server.o networking.o word_handling.o game.o
	gcc -o server server.o networking.o word_handling.o game.o -lm

player.o: player.c networking.h word_handling.h game.h
	gcc -c player.c

server.o: server.c networking.h word_handling.h
	gcc -c server.c

networking.o: networking.c networking.h word_handling.h game.h
	gcc -c networking.c
	
word_handling.o: word_handling.c networking.h
	gcc -c word_handling.c

game.o: game.c game.h networking.h word_handling.h
	gcc -c game.c

clean:
	rm *.o
	rm server
	rm player
	rm player_0.txt
	rm player_1.txt
	rm score_0.data
	rm score_1.data
	rm *~