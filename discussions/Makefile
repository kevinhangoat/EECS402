all:main.exe: rectangle.o triangle.o
	g++ rectangle.o triangle.o -o main.exe
rectangle.o: rectangle.cpp
	g++ -c rectangle.cpp -o rectangle.o
triangle.o: triangle.cpp tringle.h
	g++ -c triangle.cpp -o triangle.o
clean:
	rm -rf rectangle.o triangle.o main.exe
