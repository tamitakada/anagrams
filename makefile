all: player server


player: player.o networking.o word_handling.o
	gcc -o player player.o networking.o word_handling.o -lm

server: server.o networking.o word_handling.o
	gcc -o server server.o networking.o word_handling.o -lm

player.o: player.c networking.h word_handling.h
	gcc -c player.c

server.o: server.c networking.h word_handling.h
	gcc -c server.c

networking.o: networking.c networking.h word_handling.h
	gcc -c networking.c
	
word_handling.o: word_handling.c networking.h
	gcc -c word_handling.c

clean:
	rm *.o
	rm server
	rm player
	rm player_0.txt
	rm player_1.txt
	rm score_0.data
	rm score_1.data
	rm *~
