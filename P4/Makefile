all: proj4.exe

LinkedNodeClass.o: LinkedNodeClass.cpp LinkedNodeClass.h constants.h
	g++ -c LinkedNodeClass.cpp -o LinkedNodeClass.o

SortedListClass.o: SortedListClass.cpp SortedListClass.h constants.h LinkedNodeClass.h
	g++ -c SortedListClass.cpp -o SortedListClass.o

LIFOStackClass.o: LIFOStackClass.cpp LIFOStackClass.h constants.h LinkedNodeClass.h
	g++ -c LIFOStackClass.cpp -o LIFOStackClass.o

FIFOQueueClass.o: FIFOQueueClass.cpp FIFOQueueClass.h constants.h LinkedNodeClass.h
	g++ -c FIFOQueueClass.cpp -o FIFOQueueClass.o

proj4.o: project4.cpp
	g++ -c project4.cpp -o proj4.o

proj4.exe: LinkedNodeClass.o SortedListClass.o LIFOStackClass.o FIFOQueueClass.o proj4.o
	g++ LinkedNodeClass.o SortedListClass.o LIFOStackClass.o FIFOQueueClass.o proj4.o -o proj4.exe

clean:
	rm -rf *.o *.exe
