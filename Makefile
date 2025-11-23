COMPILER = g++
COMPILERFLAGS = -std=c++17

TARGETS = a.out

# SETUP
all: run

run: $(TARGETS)
	./a.out

$(TARGETS): main.o banker.o
	$(COMPILER) $(COMPILERFLAGS) -o a.out main.o banker.o

main.o: main.cpp
	$(COMPILER) $(COMPILERFLAGS) -c main.cpp

banker.o: banker.cpp
	$(COMPILER) $(COMPILERFLAGS) -c banker.cpp

clean:
	rm -f *.o $(TARGETS)