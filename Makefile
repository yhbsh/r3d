CFLAGS = -O3 -std=c++17 -Wno-deprecated-declarations -DGL_SILENCE_DEPRECATION $(shell pkg-config --cflags --libs glfw3 raylib) -framework OpenGL

all: bin/gl bin/png bin/raylib

bin/gl: gl.cpp
	clang++ $(CFLAGS) gl.cpp -o bin/gl

bin/png: png.cpp
	clang++ $(CFLAGS) png.cpp -o bin/png

bin/raylib: raylib.cpp | bin
	clang++ $(CFLAGS) raylib.cpp -o bin/raylib

clean:
	rm -rf bin
