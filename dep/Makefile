CPPFLAGS = -O2 -std=c++11 -Wall
CPPC = g++
TARGET = # targets

all: $(TARGET)

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

clean:
	rm $(TARGET)

-include ../../dep/push.make
