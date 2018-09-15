CXX = g++
CXXFLAGS = -std=c++14 -W -Wall -pthread

TARGET_UNOPTIMIZED = parallel_accumulate_unoptimized
TARGET_OPTIMIZED = parallel_accumulate_optimized

SRCS = parallel_accumulate.cpp

all : target_unoptimized target_optimized

target_unoptimized :
	$(CXX) $(CXXFLAGS) $(SRCS) -O0 -o $(TARGET_UNOPTIMIZED)

target_optimized :
	$(CXX) $(CXXFLAGS) $(SRCS) -O2 -o $(TARGET_OPTIMIZED)

clean :
	rm -f $(TARGET_UNOPTIMIZED) $(TARGET_OPTIMIZED)
