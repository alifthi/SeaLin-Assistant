PROJECT_NAME = SeaLin-Assistant
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
LDFLAGS = -Wl,-rpath,./vendor/llama.cpp/build/bin

SRC_DIR = src
INCLUDE_DIR = include
VENDOR_INCLUDE_DIR = vendor/llama.cpp
VENDOR_LIB_DIR = vendor/llama.cpp/build/bin
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

INCLUDES = -I$(INCLUDE_DIR) -I$(VENDOR_INCLUDE_DIR) -I$(VENDOR_INCLUDE_DIR)/include -I$(VENDOR_INCLUDE_DIR)/ggml/include

LIBS = -L$(VENDOR_LIB_DIR) -lllama -lggml -lm -lpthread

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = $(BUILD_DIR)/$(PROJECT_NAME)

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): vendor/llama.cpp/build/bin/libllama.so $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) $(LIBS)
	@echo "Build complete: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
vendor/llama.cpp/build/bin/libllama.so:
	cd vendor/llama.cpp && mkdir -p build && cd build && cmake -DGGML_CUDA=ON .. && make -j4

clean:
	rm -rf $(BUILD_DIR)
	@echo "Clean complete"

install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/$(PROJECT_NAME)
	@echo "Installed to /usr/local/bin/$(PROJECT_NAME)"

uninstall:
	sudo rm -f /usr/local/bin/$(PROJECT_NAME)
	@echo "Uninstalled $(PROJECT_NAME)"

run: $(TARGET)
	cd $(BUILD_DIR) && ./$(PROJECT_NAME)

debug: CFLAGS += -DDEBUG -g3 -O0
debug: $(TARGET)

release: CFLAGS += -DNDEBUG -O3
release: clean $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(TARGET)

print-%:
	@echo $* = $($*)

help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  debug    - Build with debug flags"
	@echo "  release  - Build optimized release version"
	@echo "  run      - Build and run the program"
	@echo "  install  - Install to /usr/local/bin"
	@echo "  uninstall- Remove from /usr/local/bin"
	@echo "  valgrind - Run with valgrind memory checker"
	@echo "  help     - Show this help message"

.PHONY: all clean install uninstall run debug release valgrind help print-%

-include $(OBJECTS:.o=.d)

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -MM -MT $(@:.d=.o) $< > $@
