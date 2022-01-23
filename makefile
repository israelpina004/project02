all: battleship

battleship: battleship.o networking.o setup.o game.o
	gcc -o battleship battleship.o networking.o setup.o game.o

battleship.o: battleship.c networking.h setup.h game.h
	gcc -c battleship.c

networking.o: networking.c networking.h
	gcc -c networking.c

setup.o: setup.c setup.h
	gcc -c setup.c

game.o: game.c game.h
	gcc -c game.c

clean:
	rm *.o battleship
