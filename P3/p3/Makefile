all: proj3.exe

proj3.o: proj3.cpp ColorClass.h RowColumnClass.h ColorImageClass.h constants.h
	g++ -Wall -c proj3.cpp -o proj3.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h constants.h
	g++ -Wall -c RowColumnClass.cpp -o RowColumnClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h constants.h ColorClass.h RowColumnClass.h
	g++ -Wall -c ColorImageClass.cpp -o ColorImageClass.o

ColorClass.o: ColorClass.cpp ColorClass.h constants.h
	g++ -Wall -c ColorClass.cpp -o ColorClass.o

proj3.exe: ColorClass.o RowColumnClass.o ColorImageClass.o proj3.o
	g++ -Wall proj3.o ColorClass.o RowColumnClass.o ColorImageClass.o -o proj3.exe

clean:
	rm -f *.o *.exe
