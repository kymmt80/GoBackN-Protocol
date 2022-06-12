CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
INCLUDE_UTILS_DIR = ../utils/include
SRC_UTILS_DIR = ../utils/src
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)
LINK_FLAGS = 

EXECUTABLE_FILE = receiver.out

OBJECTS = \
	$(BUILD_DIR)/main.o 		\
	$(BUILD_DIR)/receiver.o 	\
	$(BUILD_DIR)/socket.o

ReceiverSensitivityList = 			\
	$(SRC_DIR)/receiver.cpp			\
	$(INCLUDE_DIR)/receiver.hpp 	\
	$(INCLUDE_UTILS_DIR)/socket.hpp	\
	$(SRC_UTILS_DIR)/socket.cpp

MainSensitivityList = 		\
	$(SRC_DIR)/main.cpp 	\
	$(INCLUDE_DIR)/receiver.hpp


all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/socket.o: $(SocketSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_UTILS_DIR)/socket.cpp -o $(BUILD_DIR)/socket.o

$(BUILD_DIR)/main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/receiver.o: $(ReceiverSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/receiver.cpp -o $(BUILD_DIR)/receiver.o

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LINK_FLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out