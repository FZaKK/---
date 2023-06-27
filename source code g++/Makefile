# Makefile for compiling main.cpp with 1.h, 2.h, and 3.h

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRCS = sudoku.cpp

# Header files
HEADERS = cmdline.h filedeal.h sudoku.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = sudoku.exe

# Default target
all: $(TARGET)

# Compile source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean generated files
clean:
	del $(OBJS) $(TARGET)
