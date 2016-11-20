.PHONY: all clean

all: ms_cli

clean:
	rm -rf ms_cli bin/*.o bin

bin:
	mkdir -p bin

bin/ms_cli.o: src/ms_cli.c include/mergesort.h src/mergesort.c
	gcc -c src/ms_cli.c -o bin/ms_cli.o
        
bin/mergesort.o: src/mergesort.c
	gcc -c src/mergesort.c -o bin/mergesort.o
          
ms_cli: bin bin/mergesort.o bin/ms_cli.o
	gcc -o ms_cli bin/ms_cli.o bin/mergesort.o
