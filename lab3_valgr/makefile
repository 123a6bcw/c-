.PHONY: all clean

all: main

clean:
	rm -rf main bin/*.o bin

bin:
	mkdir -p bin
        
bin/main.o: src/main.c
	gcc -c src/main.c -o bin/main.o
          
main: bin bin/main.o
	gcc -o main bin/main.o
