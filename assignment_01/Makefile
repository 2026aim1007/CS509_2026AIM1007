CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = gemm_driver

SRCS = driver/driver.cpp src/gemm_simple.cpp src/gemm_blocking.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) gemm_driver.exe