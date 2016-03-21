CC=cc

all: lab3

lab3: main.o word_list.o helpers.o
	$(CC) main.o word_list.o helpers.o -o lab3

main.o: main.c
	$(CC) -c main.c

word_list.o: word_list.c
	$(CC) -c word_list.c

helpers.o: helpers.c
	$(CC) -c helpers.c	

test1: ./lab3
	./lab3 < input1.txt > output.txt
	diff answer1.txt output.txt

test2: ./lab3
	./lab3 < input2.txt > output.txt
	diff answer2.txt output.txt

test: test1 test2

clean:
	rm -rf *.o lab3
