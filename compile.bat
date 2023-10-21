@echo off
g++ -c *.cpp -I include -DSFML_STATIC
g++ *.o -o game -L lib -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-network-s -lsfml-system-s -lws2_32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main