all: proj5.exe

random.o: random.h random.cpp constants.h
	g++ -c random.cpp -o random.o

EventClass.o: EventClass.h EventClass.cpp constants.h
	g++ -c EventClass.cpp -o EventClass.o

SimulatorClass.o: SimulatorClass.h SimulatorClass.cpp random.o constants.h
	g++ -c SimulatorClass.cpp -o SimulatorClass.o

proj5.o: project5.cpp constants.h
	g++ -c project5.cpp -o proj5.o

proj5.exe: random.o proj5.o constants.h EventClass.o SimulatorClass.o
	g++ proj5.o random.o EventClass.o SimulatorClass.o -o proj5.exe

clean:
	rm -rf *.o *.exe
