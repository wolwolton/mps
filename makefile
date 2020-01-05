main: main.o mps.o particle.o mk_particle.o export.o
	g++ -Wall -o main main.o mps.o particle.o mk_particle.o export.o -Ofast
main.o: main.cpp
	g++ -Wall -c main.cpp -I /usr/include/eigen3/ -Ofast
mps.o: mps.cpp
	g++ -Wall -c mps.cpp -I /usr/include/eigen3/ -Ofast
particle.o: particle.cpp
	g++ -Wall -c particle.cpp -I /usr/include/eigen3/ -Ofast
mk_particle.o: mk_particle.cpp
	g++ -Wall -c mk_particle.cpp -I /usr/include/eigen3/ -Ofast
export.o: export.cpp
	g++ -Wall -c export.cpp -I /usr/include/eigen3/ -Ofast
clean:
	rm -f *.o main