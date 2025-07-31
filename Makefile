all: compile link

compile:
	g++ -c main.cpp -I"C:/Users/zitko/OneDrive/Plocha/game/SFML-2.6.1/include" -DSFML_STATIC

link:
	g++ main.o -o game -Wall -Wextra -Wpedantic -Werror -std=c++17 -L"C:/Users/zitko/OneDrive/Plocha/game/SFML-2.6.1/lib" -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg

clean:
	rm main.o, game.exe