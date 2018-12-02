CXX = g++
CXXFLAGS = -std=c++14 -W -Wall
INCFLAGS = -I.

SRCS = bind_variadic_args.cc
TARGET = bind_variadic_args_as_tuple

$(TARGET) :
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(SRCS) -o $(TARGET)

clean :
	rm -f $(TARGET)
