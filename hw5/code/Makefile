CPPFLAGS = -O2 -std=c++11 -Wall -Wno-write-strings
CPPC = g++
TARGET = system

all: $(TARGET)

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

system: system.cpp
	g++ $(CPPFLAGS) $< -o $@

-include ../../dep/push.make
