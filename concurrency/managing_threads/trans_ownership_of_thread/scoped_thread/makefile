CXX = g++
CXXFLAGS = -std=c++11 -W -Wall -pthread

INCLUDES_FLAGS = -I.

TARGET = test_scoped_thread
SRCS = main.cpp

$(TARGET) :
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(INCLUDES_FLAGS)

clean :
	rm -f $(TARGET)

