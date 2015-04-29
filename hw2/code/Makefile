all: demo

demo: demo.cpp
	g++ -Wall -O2 $< -o $@

upload:
	scp -r demo.cpp b03902028@linux7.csie.ntu.edu.tw:dsa/hw2/code/

-include ../../dep/push.make

