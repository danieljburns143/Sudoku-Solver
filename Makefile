main: main.o cell.o
	g++ -std=c++14 main.o cell.o -o main

main.o: main.cpp cell.h
	g++ -std=c++14 -c main.cpp -o main.o

cell.o: cell.cpp cell.h
	g++ -std=c++14 -c cell.cpp -o cell.o

clean:
	rm *.o main
