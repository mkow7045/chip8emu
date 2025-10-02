TARGET = chip8emu

CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC = main.cpp chip8.cpp display.cpp keyboard.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
