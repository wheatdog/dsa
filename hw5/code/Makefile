CPPFLAGS = -O2 -std=c++11 -Wall -Wno-write-strings
CPPC = g++
TARGET = system hashtest bhtest

all: $(TARGET)

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

system: system.cpp binomial_heap.h
	g++ $(CPPFLAGS) $< -o $@

bhtest: bhtest.cpp binomial_heap.h
	g++ $(CPPFLAGS) $< -o $@

run: 
	time ./system < test/tiera.100.in > test/my.a.100.out
	@diff test/tiera.100.out test/my.a.100.out
	time ./system < test/tiera.20.in > test/my.a.20.out
	@diff test/tiera.20.out test/my.a.20.out
	time ./system < test/tierb.100.in > test/my.b.100.out
	@diff test/tierb.100.out test/my.b.100.out
	time ./system < test/tierb.1000.in > test/my.b.1000.out
	@diff test/tierb.1000.out test/my.b.1000.out

-include ../../dep/push.make
