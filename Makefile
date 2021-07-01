fruit:fruit.o
	gcc -g fruit.o -lsqlite3 -o fruit
fruit.o:fruit.c
	gcc -c -g fruit.c -o fruit.o
.PHONY:clean
clean:
	rm *.o
