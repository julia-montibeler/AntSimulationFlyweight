SRC_DIR = ./src
BUILD_DIR = ./build
INCLUDIR_DIR = ./include

PROG_SOURCES = $(wildcard  $(SRC_DIR)/*)

CXX = g++
CXXFLAGS = -Iinclude
RM = rm -f

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(PROG_SOURCES))

.PHONY: all clean main

all: $(OBJECTS)
	$(CXX) $(OBJECTS) -lSDL2 -lSDL2_image -o main

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $<
	
clean:
	@echo Removing build files
	@$(RM) $(OBJECTS)
	@$(RM) main