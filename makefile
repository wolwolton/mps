main: main.o mps.o particle.o mk_particle.o export.o
	g++ -Wall -o main main.o mps.o particle.o mk_particle.o export.o
main.o: main.cpp
	g++ -Wall -c main.cpp -I /usr/include/eigen3/
mps.o: mps.cpp
	g++ -Wall -c mps.cpp -I /usr/include/eigen3/
particle.o: particle.cpp
	g++ -Wall -c particle.cpp -I /usr/include/eigen3/
mk_particle.o: mk_particle.cpp
	g++ -Wall -c mk_particle.cpp -I /usr/include/eigen3/
export.o: export.cpp
	g++ -Wall -c export.cpp -I /usr/include/eigen3/
clean:
	rm -f *.o mps