CC=clang++
CXX_FLAGS=-Wall -Werror -Wpedantic -Wextra
DEST_DIR=./build
CXX_STD=c++14
SRC_DIR=./src
TEST_DIR=./test

APP_NAME=analyser

SRC_FILES=$(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJS=$(SRC_FILES:$(SRC_DIR)/%.cpp=$(DEST_DIR)/%.o)

INCLUDE_PATHS=
LIBRARIES=
LIBRARY_PATHS=


clean:
	rm -r $(DEST_DIR)

env:
	mkdir -p $(DEST_DIR)

$(DEST_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $@ $(CXX_FLAGS)

app: $(SRC_OBJS)
	$(CC) -o $(DEST_DIR)/$(APP_NAME) $^ $(CXX_FLAGS) $(LIBRARY_PATHS) $(LIBRARIES) $(INCLUDE_PATHS) -std=$(CXX_STD) $(CXX_FLAGS)
