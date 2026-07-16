all: compile link clean

compile:
	g++ -c main.cpp menu.cpp Monsters.cpp resource.cpp Player.cpp Weapons.cpp DataStructures.cpp -I"SFML-2.6.1/include" -DSFML_STATIC

link:
	g++ main.o menu.o Monsters.o resource.o Player.o Weapons.o DataStructures.o -o game -Wall -Wextra -Wpedantic -Werror -std=c++17 \
	-L"SFML-2.6.1/lib" -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg \
	-static -static-libgcc -static-libstdc++

clean:
	del main.o menu.o Monsters.o resource.o Player.o Weapons.o