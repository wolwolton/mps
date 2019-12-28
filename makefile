mps: mps.o particle.o mk_particle.o
	g++ -Wall -o mps mps.o particle.o mk_particle.o
mps.o: mps.cpp
	g++ -Wall -c mps.cpp -I /usr/include/eigen3/
particle.o: particle.cpp
	g++ -Wall -c particle.cpp -I /usr/include/eigen3/
mk_particle.o: mk_particle.cpp
	g++ -Wall -c mk_particle.cpp -I /usr/include/eigen3/
clean:
	rm -f *.o mps