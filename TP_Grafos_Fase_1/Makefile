CPP = g++
CPPFLAGS = -Wall

OBJ = TP1_Main.o TP1.o

TP1_Main: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o TP1_Main

TP1_Main.o: TP1_Main.cpp
	$(CPP) $(CPPFLAGS) -c TP1_Main.cpp -o TP1_Main.o

TP1.o: TP1.cpp TP1.h
	$(CPP) $(CPPFLAGS) -c TP1.cpp -o TP1.o

all: TP1_Main

clean:
	rm -f *.o
