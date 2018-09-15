CXX = g++
CXXFLAGS = -std=c++11 -W -Wall -pthread

TARGET_UNOPTIMIZED = accumulate_unoptimized
TARGET_OPTIMIZED = accumulate_optimized

SRCS = accumulate_vs_manual.cpp

all : target_unoptimized target_optimized

target_unoptimized :
	$(CXX) $(CXXFLAGS) $(SRCS) -O0 -o $(TARGET_UNOPTIMIZED)

target_optimized :
	$(CXX) $(CXXFLAGS) $(SRCS) -O2 -o $(TARGET_OPTIMIZED)

clean :
	rm -f $(TARGET_UNOPTIMIZED) $(TARGET_OPTIMIZED)
