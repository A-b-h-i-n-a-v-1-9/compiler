CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC      = src/main.cpp src/lexer.cpp src/parser.cpp \
           src/evaluator.cpp src/ir_gen.cpp src/reg_alloc.cpp
TARGET   = compiler

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
