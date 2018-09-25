CXX = g++
CXXFLAGS = -std=c++11 -W -Wall -O2

INCPATH = -I.
SRCS = bind_example.cpp

TARGET = high_pass_filter_example

$(TARGET) :
	$(CXX) $(CXXFLAGS) $(INCPATH) $(SRCS) -o $(TARGET)

clean :
	rm -f $(TARGET)
