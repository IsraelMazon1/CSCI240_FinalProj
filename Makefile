CXX := g++
CXXFLAGS := -std=c++11 -Wall -g
TARGET := EigenCalculator
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f $(TARGET) $(OBJ)

