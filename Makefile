TOOLS_DIR   = tools
SRC_DIR     = src
ASSETS_DIR  = assets
BIN_DIR     = bin
TOOLS_BIN   = $(TOOLS_DIR)/obj2c
TARGET      = $(BIN_DIR)/main
DATA_H      = $(ASSETS_DIR)/data.h
OBJ_FILE    = $(ASSETS_DIR)/penger.obj

all: $(DATA_H) $(TARGET)

$(TOOLS_BIN):
	make -C $(TOOLS_DIR)

$(DATA_H): $(TOOLS_BIN) $(OBJ_FILE)
	$(TOOLS_BIN) $(OBJ_FILE) > $(DATA_H)

$(TARGET): $(SRC_DIR)/main.c $(DATA_H)
	@mkdir -p $(BIN_DIR)
	make -C $(SRC_DIR)

clean:
	make -C $(TOOLS_DIR) clean
	make -C $(SRC_DIR) clean
	rm -f $(TARGET) $(DATA_H)
