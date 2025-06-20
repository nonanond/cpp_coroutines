ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif
ifeq ($(detected_OS),Darwin)
	CXX = /opt/homebrew/bin/g++-14
	LIB_PATH = /opt/homebrew/lib
endif
ifeq ($(detected_OS),Linux)
	CXX = /usr/bin/g++
	LIB_PATH = /usr/lib
        # CXX = /usr/bin/g++
endif


CXX_FLAGS := -D DEBUG -std=c++23

PROJ_DIR := $(CURDIR)
BUILD_DIR := $(PROJ_DIR)/build

directories := $(foreach dir, $(BUILD_DIRS), $(shell [ -d $(dir) ] || mkdir -p $(dir)))

all: $(BUILD_DIR)/main

$(BUILD_DIR)/main: main.cpp coro.cpp
	${CXX} -std=c++23 -fmodules-ts -o $@ $^ -L${LIB_PATH} -lssl -lcrypto -luring

#$(CXX) $(CXX_FLAGS) -c $< -o $@

#-L/usr/lib -lssl -lcrypto





clean:
	rm -rf $(BUILD_DIR)/*