TOOLS_SRC = obj2c.c
TOOLS_BIN = obj2c

all: $(TOOLS_BIN)

$(TOOLS_BIN): $(TOOLS_SRC)
	clang -O3 $< -o $@

clean:
	rm -f $(TOOLS_BIN)
