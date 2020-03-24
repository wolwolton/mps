../build/%.o:	%.cpp
	g++ -Wall -c $*.cpp -I /usr/include/eigen3/ -Ofast -o ../build/$*.o

main: ../build/main.o ../build/mps.o ../build/particle.o ../build/mk_particle.o ../build/export.o
	g++ -Wall -o ../build/main ../build/main.o ../build/mps.o ../build/particle.o ../build/mk_particle.o ../build/export.o -Ofast

clean:
	rm -rf ../build

run:
	../build/main

build:
	make main
	make run

rebuild:
	make clean
	mkdir ../build
	make build
