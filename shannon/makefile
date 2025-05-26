# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Files
SRCS = main.cpp encoder.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = shannon_encoder

DEC_SRCS = main_decoder.cpp decoder.cpp
DEC_OBJS = $(DEC_SRCS:.cpp=.o)
DEC_EXEC = shannon_decoder

TEST_SRC = test_shannon.cpp
TEST_EXEC = test_shannon 

# Default target
all: $(EXEC) $(DEC_EXEC)

# Link
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(DEC_EXEC): $(DEC_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_EXEC): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run tests
test: $(ENC_EXEC) $(DEC_EXEC) $(TEST_EXEC)
	./$(TEST_EXEC)	

# Clean
clean:
	rm -f $(EXEC) $(OBJS) $(DEC_EXEC) $(DEC_OBJS) $(TEST_EXEC) output.bin output.dict decoded.bin test_input.txt

.PHONY: all clean