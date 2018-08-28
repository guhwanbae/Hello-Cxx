CXX = g++
CXXFLAGS = -std=c++14 -W -Wall

INCLUDES_FLAGS = -I.

TARGET = hetero_type_tuple

SRCS = variadic_tuple_test.cpp phasor.cpp

$(TARGET) :
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(INCLUDES_FLAGS)

clean :
	rm -f $(TARGET)
