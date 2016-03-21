CC = cc

all: demon.o manager.o
	$(CC) demon.o -o demon
	$(CC) manager.o -o manager

demon.o: demon.c
	$(CC) -c demon.c

manager.o: manager.c
	$(CC) -c manager.c

clean:
	rm -rf *.o manager demon