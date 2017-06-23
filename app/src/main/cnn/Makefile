complies = gcc
a.out : matrix.o main.o
	$(complies) matrix.o main.o -o a.out
main.o : main.c
	$(complies) -c main.c
matrix.o : matrix.c
	$(complies) -c matrix.c
clean :
	rm -rf main.o exectute matrix.o
