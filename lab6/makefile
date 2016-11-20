.PHONY: all clean

all: main

clean:
	rm -rf main bin/*.o bin

bin:
	mkdir -p bin

bin/main.o: src/main.c include/phonebook.h
	gcc -c src/main.c -o bin/main.o
        
bin/phonebook.o: src/phonebook.c
	gcc -c src/phonebook.c -o bin/phonebook.o
          
main: bin bin/phonebook.o bin/main.o
	gcc -o main bin/phonebook.o bin/main.o -lexpat
