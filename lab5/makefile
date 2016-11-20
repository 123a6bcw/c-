.PHONY: all clean

all: main

clean:
	rm -rf main bin/*.o bin

bin:
	mkdir -p bin

bin/main.o: src/main.c include/clist.h include/position.h
	gcc -c src/main.c -o bin/main.o
        
bin/clist.o: src/clist.c
	gcc -c src/clist.c -o bin/clist.o
	
bin/position.o: src/position.c include/clist.h
	gcc -c src/position.c -o bin/position.o
          
main: bin bin/clist.o bin/main.o bin/position.o
	gcc -o main bin/clist.o bin/main.o bin/position.o
