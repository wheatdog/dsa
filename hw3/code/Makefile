CPPFLAGS = -O2 -std=c++11 -Wall
CPPC = g++

all: int_cal sci_cal

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

int_cal: int_cal.cpp
	$(CPPC) $(CPPFLAGS) $< -o $@

sci_cal: sci_cal.cpp
	$(CPPC) $(CPPFLAGS) $< -o $@

run1: 
	@./int_cal

run2: 
	@./sci_cal

include ../../dep/push.make
