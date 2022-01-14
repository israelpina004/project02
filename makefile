all: battleship

battleship: battleship.o networking.o
	gcc -o battleship battleship.o networking.o

battleship.o: battleship.c networking.h
	gcc -c battleship.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
