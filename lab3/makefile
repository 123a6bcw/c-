.PHONY: all clean

all: pose_db

clean:
	rm -rf pose_db 8bin/*.o bin

bin:
	mkdir -p bin

bin/main.o: src/main.c include/clist.h
	gcc -c src/main.c -o bin/main.o
        
bin/clist.o: src/clist.c include/clist.h
	gcc -c src/clist.c -o bin/clist.o
          
pose_db: bin bin/clist.o bin/main.o
	gcc -o pose_db bin/clist.o bin/main.o
