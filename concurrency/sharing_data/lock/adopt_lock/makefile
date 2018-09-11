CXX = g++
CXXFLAGS = -std=c++11 -W -Wall

UNAME := $(shell uname -s)
ifeq ($(UNAME), Linux)
	CXXFLAGS += -pthread
endif

TARGET = adopt_lock

SRCS = adopt_lock.cpp

target :
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)
clean :
	rm -f $(TARGET) 
