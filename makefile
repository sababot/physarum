physarum: main.o utils.o particle.o trailmap.o
	g++ main.o utils.o particle.o trailmap.o -o sim -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

main.o: main.cpp
	g++ -c main.cpp

utils.o: src/utils.cpp include/utils.h
	g++ -c src/utils.cpp

particle.o: src/particle.cpp include/particle.h
	g++ -c src/particle.cpp

trailmap.o: src/trailmap.cpp include/trailmap.h
	g++ -c src/trailmap.cpp

clean:
	rm *.o
	rm sim
