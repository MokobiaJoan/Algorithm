# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Files
SRCS = main.cpp encoder.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = shannon_encoder

# Default target
all: $(EXEC)

# Link
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(EXEC) $(OBJS) output.bin output.dict

.PHONY: all clean