CPPFLAGS = -O2 -std=c++11 -Wall
CPPC = g++

all: 3_4_1.out 3_4_2.out

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

3_4_1.out: int_cal.cpp
	$(CPPC) $(CPPFLAGS) $< -o $@

3_4_2.out: sci_cal.cpp
	$(CPPC) $(CPPFLAGS) $< -o $@

run1: 
	@./3_4_1.out 

run2: 
	@./3_4_2.out 

include ../../dep/push.make
