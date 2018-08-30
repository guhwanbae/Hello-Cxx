CXX = g++
CXXFLAGS = -std=c++11 -W -Wall -pthread

INCLUDE_FLAGS = -I.

TARGET = test_threadsafe_stack

SRCS = main.cpp

$(TARGET) :
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(INCLUDE_FLAGS)

clean :
	rm -f $(TARGET)

