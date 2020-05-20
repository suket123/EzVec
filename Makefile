
output: main.o
	g++ main.o -o output

main.o: main.cpp EzVec.h EzVecTester.h
	g++ -c main.cpp

clean:
	rm *.o output*