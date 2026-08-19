CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14 -O3
TARGET = driver_app.exe
SRCS = driver/driver.cpp \
       src/gemm_simple.cpp \
       src/gemm_blocking.cpp \
       ../utility/testing_utils.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)