CC = clang++
CXX = clang++
TARGET = test
CXXFLAGS = -Wall
SRCS = Sem.cc SynchronizedQueue.cc SynchronizedQueueTest.cc 
OBJS := $(SRCS:.cc=.o)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS)
