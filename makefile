exe:	main.cpp
	g++ main.cpp src/*.cpp src/*.c classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses -o Galaxia

asan:	main.cpp
	g++ -g -fsanitize=address main.cpp src/*.cpp src/*.c classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses -o Galaxia

leak:	main.cpp
	g++ -g -fsanitize=leak main.cpp src/*.cpp src/*.c classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses -o Galaxia

run:
	./Galaxia

r:
	ASAN_OPTIONS=detect_leaks=1 ./Galaxia

clean:
	rm Galaxia

c:
	rm Galaxia
