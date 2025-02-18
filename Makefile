CFLAGS = -O3 -Wno-deprecated-declarations -DGL_SILENCE_DEPRECATION $(shell pkg-config --cflags --libs glfw3 raylib) -framework OpenGL

all: gl png raylib

gl: gl.cpp
	clang++ -std=c++17 $(CFLAGS) gl.cpp -o gl

png: png.c
	clang $(CFLAGS) png.c -o png

raylib: raylib.c
	clang $(CFLAGS) raylib.c -o raylib

obj2c: obj2c.c
	clang obj2c.c -o obj2c

clean:
	rm -f gl png raylib obj2c
