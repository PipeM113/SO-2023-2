lab2: funcs.o lab2.c
	@gcc -Wall -g lab2.c funcs.o -o lab2

funcs.o: funcs.c
	@gcc -Wall -g -c funcs.c

.PHONY: clean
clean:
	@rm -rf *.o lab2

.PHONY: run
run: lab2
	@./lab2