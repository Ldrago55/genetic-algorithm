CC = g++
CXXFLAGS = -Wall -Wextra -I$(INCLUDE_DIR)
LDFLAGS = -lraylib -lGL -lpthread -ldl -lrt -lX11

DEBUG = 1
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g -O0
else
	CXXFLAGS += -O3
endif

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# $@: The target name
# $<: The first prerequisite
# $^: All prerequisites
# $?: Prerequisites newer than the target

all: $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(SRC_DIR)/main.cpp $(BUILD_DIR)/neural_network.o $(BUILD_DIR)/agent.o
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ -o $@


$(BUILD_DIR)/agent.o : $(SRC_DIR)/agent.cpp $(INCLUDE_DIR)/agent.hpp
	$(CC) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILD_DIR)/neural_network.o : $(SRC_DIR)/neural_network.cpp $(INCLUDE_DIR)/neural_network.hpp
	$(CC) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*

.PHONY: all clean