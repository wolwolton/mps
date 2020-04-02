../build/%.o:	%.cpp
	g++ -Wall -c $*.cpp -I /usr/include/eigen3/ -Ofast -o ../build/$*.o

main: ../build/main.o ../build/mps.o ../build/particle.o ../build/mk_particle.o ../build/export.o ../build/object.o	../build/environment.o	../build/mmm.o
	g++ -Wall -o ../build/main ../build/main.o ../build/mps.o ../build/particle.o ../build/mk_particle.o ../build/export.o ../build/object.o ../build/environment.o ../build/mmm.o -Ofast

clean:
	rm -rf ../build

run:
	rm -rf ../output
	mkdir ../output
	../build/main

build:
	make main
	make run

rebuild:
	make clean
	mkdir ../build
	make build
