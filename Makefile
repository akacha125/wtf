# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -D_POSIX_C_SOURCE=200809L -O2 -D_GNU_SOURCE

# Source Files and Paths
SRC = src/main.c src/hash_table.c src/file_utils.c src/commands.c
OBJ = build/main.o build/hash_table.o build/file_utils.o build/commands.o
OUTPUT = build/wtf

# File to deploy
DEFINITIONS_FILE = .wtf/res/definitions.txt

# Default Target: Build the binary
all: $(OUTPUT)

# Build the binary from object files
$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUTPUT)

# Compile each source file into an object file
build/%.o: src/%.c
	@mkdir -p build  # Ensure the 'build' directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Clean: Remove object files, the binary, and copied definitions file
clean:
	rm -f build/*.o build/$(DEFINITIONS_FILE) $(OUTPUT)

# Determine the correct home directory
ACTUAL_USER := $(shell who am i | awk '{print $$1}')
ACTUAL_HOME := $(shell eval echo ~$(ACTUAL_USER))

install: all
	@echo "Installing wtf..."
	@sudo mkdir -p /usr/local/bin
	@sudo cp $(OUTPUT) /usr/local/bin/wtf
	@mkdir -p $(ACTUAL_HOME)/.wtf/res
	@cp -r .wtf $(ACTUAL_HOME)/
	@cp $(DEFINITIONS_FILE) $(ACTUAL_HOME)/.wtf/res/
	@sudo chown -R $(ACTUAL_USER):$(ACTUAL_USER) $(ACTUAL_HOME)/.wtf
	@echo "wtf installed successfully with definitions file. You can now run 'wtf' from anywhere."

# Uninstall: Remove the binary and the definitions file from /usr/local/bin
uninstall:
	@echo "Uninstalling wtf..."
	@sudo rm -f /usr/local/bin/wtf 
	@rm -rf $(ACTUAL_HOME)/.wtf
	@echo "wtf and its definitions file uninstalled successfully."
	
# Help: Show available Makefile targets
help:
	@echo "Available targets:"
	@echo "  all       - Build the 'wtf' binary and copy the definitions file"
	@echo "  clean     - Remove all object files, binaries, and the copied definitions file"
	@echo "  install   - Install 'wtf' and the definitions file globally"
	@echo "  uninstall - Uninstall 'wtf'