CPPFLAGS = -O2 -std=c++11 -Wall
CPPC = g++
TARGET = tree forest

all: $(TARGET)

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

tree: tree.cpp dtree.h dtree.cpp
	g++ $(CPPFLAGS) tree.cpp dtree.cpp -o $@

forest: forest.cpp dtree.h dtree.cpp
	g++ $(CPPFLAGS) forest.cpp dtree.cpp -o $@

-include ../../dep/push.make
