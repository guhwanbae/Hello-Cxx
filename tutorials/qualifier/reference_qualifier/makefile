CXX = g++
CXX_FLAGS = -std=c++11 -W -Wall

TARGET = ref_qualifier
SRCS = main.cpp movie.cpp
INCLUDES = -I.

$(TARGET) :
	$(CXX) $(CXX_FLAGS) -o $(TARGET) $(SRCS) $(INCLUDES)

clean :
	rm -f $(TARGET)
