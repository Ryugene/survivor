all: compile link

compile:
	g++ -c main.cpp -I"SFML-2.6.1/include" -DSFML_STATIC

link:
	g++ main.o -o game -Wall -Wextra -Wpedantic -Werror -std=c++17 -L"SFML-2.6.1/lib" -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

clean:
	rm main.o, game.exe