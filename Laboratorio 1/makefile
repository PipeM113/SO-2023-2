lab1: funcs.o lab1.c
	@gcc -Wall -g lab1.c funcs.o -o lab1

funcs.o: funcs.c
	@gcc -Wall -g -c funcs.c

.PHONY: clean
clean:
	@rm -rf *.o lab1

.PHONY: run
run: lab1
	@./lab1