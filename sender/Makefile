CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)
LINK_FLAGS = 

EXECUTABLE_FILE = sender.out

OBJECTS = \
	$(BUILD_DIR)/main.o 	\
	$(BUILD_DIR)/sender.o 			

SenderSensitivityList = 	\
	$(SRC_DIR)/sender.cpp	\
	$(INCLUDE_DIR)/sender.hpp 				

MainSensitivityList = 		\
	$(SRC_DIR)/main.cpp 	\
	$(INCLUDE_DIR)/sender.hpp


all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/sender.o: $(SenderSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/sender.cpp -o $(BUILD_DIR)/sender.o

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LINK_FLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out