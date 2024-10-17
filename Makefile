# Variables
CXX = g++
CXXFLAGS = -g -fopenmp -std=c++17 -O2   # Compiler flags
TARGET = a1                             # Final executable name
SRCS = a1_test.cpp homework.cpp             # List of source files
OBJS = $(SRCS:.cpp=.o)                  # Object files (automatically converts .cpp to .o)

# Default target
all: $(TARGET)

# Rule to build the executable (linking object files)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files and the executable
clean:
	rm -rf $(OBJS) $(TARGET)
