CXX = g++
CXXFLAGS = -std=c++17 -I./src/include -I./path/to/SDL2/include
LDFLAGS = -L./src/lib -L./path/to/SDL2/lib -lmingw32 -lSDL2main -lSDL2
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = main.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del $(OBJ) $(EXEC)
