.PHONY: all clean

all: tools src

tools:
	@make -C tools
	@./tools/obj2c assets/penger.obj > deps/include/penger.h

src: tools
	@make -C src

clean:
	@make -C tools clean
	@make -C src clean
	@rm -f include/data.h
