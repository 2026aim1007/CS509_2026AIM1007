# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
TARGET = driver_app
SRCS = driver/driver.cpp src/kruskal.cpp src/prim.cpp ../utility/csr.cpp ../utility/testing_utils.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)