CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)
LINK_FLAGS = 

EXECUTABLE_FILE = router.out

OBJECTS = \
	$(BUILD_DIR)/main.o 	\
	$(BUILD_DIR)/router.o 			

RouterSensitivityList = 	\
	$(SRC_DIR)/router.cpp	\
	$(INCLUDE_DIR)/router.hpp 				

MainSensitivityList = 		\
	$(SRC_DIR)/main.cpp 	\
	$(INCLUDE_DIR)/router.hpp


all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/router.o: $(RouterSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/router.cpp -o $(BUILD_DIR)/router.o

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LINK_FLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out