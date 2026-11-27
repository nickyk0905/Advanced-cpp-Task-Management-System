
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

TARGET = app

SOURCES = main.cpp \
          src/User.cpp \
          src/Project.cpp \
          src/Task.cpp \
          src/TaskManager.cpp \
          src/operations/TaskOperations.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean