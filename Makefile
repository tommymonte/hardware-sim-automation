output: main.o sim.o
	g++ main.o sim.o -o output

main.o: main.cpp
	g++ -c main.cpp

sim.o: sim.cpp sim.h
	g++ -c sim.cpp

clean:
	rm *.o output
