CPP = g++
CPPFLAGS = -Wall

OBJ = TP2Main.o TP2.o

TP2Main: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o TP2Main

TP2Main.o: TP2Main.cpp
	$(CPP) $(CPPFLAGS) -c TP2Main.cpp -o TP2Main.o

TP2.o: TP2.cpp TP2.h
	$(CPP) $(CPPFLAGS) -c TP2.cpp -o TP2.o

all: TP2Main

clean:
	rm -f *.o
