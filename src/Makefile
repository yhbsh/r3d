CFLAGS = -O3 -std=c++17 -Wno-deprecated-declarations -DGL_SILENCE_DEPRECATION -I../deps/include

all: ../bin/gl ../bin/png ../bin/raylib

../bin/gl: gl.cpp | ../bin
	clang++ $(CFLAGS) gl.cpp -o ../bin/gl -L../deps/lib -lglfw -framework Cocoa -framework IOKit -framework OpenGL

../bin/png: png.cpp | ../bin
	clang++ $(CFLAGS) png.cpp -o ../bin/png

../bin/raylib: raylib.cpp | ../bin
	clang++ $(CFLAGS) raylib.cpp -o ../bin/raylib -L../deps/lib -lraylib -framework Cocoa -framework IOKit

clean:
	rm -f ../bin/gl ../bin/png ../bin/raylib

../bin:
	mkdir -p ../bin
