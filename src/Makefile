ASSETS_DIR    = ../assets
INCLUDE_DIR   = ../deps/include
LIB_DIR       = ../deps/lib
DATA_H        = $(ASSETS_DIR)/data.h
SOURCES       = main.c render.c
LIBS          = -L$(LIB_DIR) -lraylib -framework Cocoa -framework IOKit
BIN_DIR       = ../bin
EXECUTABLES   = $(SOURCES:%.c=$(BIN_DIR)/%)

all: $(EXECUTABLES)

$(BIN_DIR)/%: %.c $(DATA_H)
	@mkdir -p $(BIN_DIR)
	clang -O3 $< -I$(INCLUDE_DIR) -I$(ASSETS_DIR) $(LIBS) -o $@

clean:
	rm -f $(EXECUTABLES)
