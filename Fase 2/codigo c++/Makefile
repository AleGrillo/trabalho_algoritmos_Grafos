CPP = g++
CPPFLAGS = -Wall

OBJ = TP2_Main.o TP2.o

TP2_Main: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o TP2_Main

TP2_Main.o: TP2_Main.cpp
	$(CPP) $(CPPFLAGS) -c TP2_Main.cpp -o TP2_Main.o

TP2.o: TP2.cpp TP2.h
	$(CPP) $(CPPFLAGS) -c TP2.cpp -o TP2.o

all: TP2_Main

clean:
	rm -f *.o
