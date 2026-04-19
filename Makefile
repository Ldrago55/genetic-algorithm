CC = g++
CXXFLAGS = -Wall -Wextra -I$(INCLUDE_DIR)
LDFLAGS = -lraylib -lglfw -lGL

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

$(BUILD_DIR)/main: $(SRC_DIR)/main.cpp $(BUILD_DIR)/neural_network.o $(BUILD_DIR)/Agent.o $(BUILD_DIR)/populationManager.o $(BUILD_DIR)/Environment.o
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/neural_network.o : $(SRC_DIR)/neural_network.cpp $(INCLUDE_DIR)/neural_network.hpp
	$(CC) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILD_DIR)/Agent.o : $(SRC_DIR)/agent/Agent.cpp $(SRC_DIR)/agent/Agent.h
	$(CC) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILD_DIR)/Environment.o : $(SRC_DIR)/env/Environment.cpp $(SRC_DIR)/env/Environment.h
	$(CC) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(BUILD_DIR)/populationManager.o : $(SRC_DIR)/population/populationManager.cpp $(SRC_DIR)/population/populationManager.h
	$(CC) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@



clean:
	rm -f $(BUILD_DIR)/*

.PHONY: all clean