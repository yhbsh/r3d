SRC         = main.c
TARGET      = ../bin/main
ASSETS_DIR  = ../assets
INCLUDE_DIR = ../include
DATA_H      = $(ASSETS_DIR)/data.h

all: $(TARGET)

$(TARGET): $(SRC) $(DATA_H)
	clang -O3 $(SRC) -I$(INCLUDE_DIR) -I$(ASSETS_DIR) -o $@

clean:
	rm -f $(TARGET)
