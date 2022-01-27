all: battleship

battleship: battleship.o networking.o SDL_setup.o setup.o game.o SDL_global_variables.o SDL_functions.o
	gcc -o battleship battleship.o networking.o SDL_functions.o SDL_global_variables.o SDL_setup.o setup.o game.o -lSDL2main -lSDL2 -lSDL2_ttf

battleship.o: battleship.c networking.h setup.h game.h SDL_global_variables.h
	gcc -c battleship.c

networking.o: networking.c networking.h
	gcc -c networking.c

setup.o: setup.c setup.h SDL_global_variables.h SDL_functions.h
	gcc -c setup.c

SDL_setup.o: SDL_setup.c SDL_setup.h SDL_global_variables.h SDL_functions.h
	gcc -c SDL_setup.c

game.o: game.c game.h
	gcc -c game.c

SDL_global_variables.o: SDL_global_variables.c SDL_global_variables.h
	gcc -c SDL_global_variables.c

SDL_functions.o: SDL_functions.c SDL_functions.h
	gcc -c SDL_functions.c

run:
	make && ./battleship

clean:
	rm *.o battleship
