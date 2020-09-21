all: project3.exe

project3.o: project3.cpp ColorClass.h RowColumnClass.h ColorImageClass.h constants.h printMenu.h overcomeFailState.h
	g++ -Wall -c project3.cpp -o project3.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h constants.h
	g++ -Wall -c RowColumnClass.cpp -o RowColumnClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h constants.h ColorClass.h RowColumnClass.h MessageClass.h
	g++ -Wall -c ColorImageClass.cpp -o ColorImageClass.o

MessageClass.o: MessageClass.cpp MessageClass.h constants.h
	g++ -Wall -c MessageClass.cpp -o MessageClass.o

ColorClass.o: ColorClass.cpp ColorClass.h constants.h
	g++ -Wall -c ColorClass.cpp -o ColorClass.o

printMenu.o: printMenu.cpp printMenu.h
	g++ -Wall -c printMenu.cpp -o printMenu.o

overcomeFailState.o: overcomeFailState.cpp overcomeFailState.h
	g++ -Wall -c overcomeFailState.cpp -o overcomeFailState.o

project3.exe: ColorClass.o RowColumnClass.o ColorImageClass.o MessageClass.o project3.o printMenu.o overcomeFailState.o
	g++ -Wall project3.o ColorClass.o RowColumnClass.o ColorImageClass.o MessageClass.o printMenu.o overcomeFailState.o -o project3.exe

clean:
	rm -f *.o *.exe
