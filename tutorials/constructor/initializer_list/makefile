TARGET = initializer_list

CXX = g++
CXXFLAGS = -std=c++14 -W -Wall
LFLAGS = -I.

SRCS = initializer_list.cpp

$(TARGET) :
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LFLAGS)

clean :
	rm -f *.o $(TARGET)
