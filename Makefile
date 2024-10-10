CXX = g++
CXXFLAGS = -std=c++17 -Wall
CXXFLAGS += -I headers/
SRCS = main.cpp src/keydir.cpp src/logger.cpp src/parser.cpp src/utils.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = fastcask.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
