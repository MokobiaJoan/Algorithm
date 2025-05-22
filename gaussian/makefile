# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/usr/include/eigen3

# Files
SRCS = main.cpp gaussian.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = gaussian

TEST_SRCS = test_gaussian.cpp gaussian.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_TARGET = test_gaussian

# Default build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test build and run
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lgtest_main -pthread 

# Clean
clean:
	rm -f *.o $(TARGET) $(TEST_TARGET) 