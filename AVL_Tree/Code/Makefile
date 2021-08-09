all:	clean main.o
	@cc -O2 -o main tree.o main.o -lm

main.o:	main.c tree.c
	@cc -c tree.c main.c -I.

run:
	@./main

clean:
	@find -name '*~' | xargs rm -rf {}
	@find -name '*o' | xargs rm -rf {}
