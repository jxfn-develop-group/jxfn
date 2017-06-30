complies = gcc -O3
a.out : matrix.o neurons.o funofneurons.o cnnnet.o fileofparameter.o main.o
	$(complies) $^ -lm -o a.out
main.o : main.c
	$(complies) -c main.c
matrix.o : matrix.c
	$(complies) -c matrix.c
neurons.o : neurons.c
	$(complies) -c neurons.c
funofneurons.o : funofneurons.c
	$(complies) -c -lm funofneurons.c
cnnnet.o : cnnnet.c
	$(complies) -c $^
fileofparameter.o : fileofparameter.c
	$(complies) -c $^
clean :
	rm -rf main.o a.out matrix.o neurons.o funofneurons.o cnnnet.o fileofparameter.o
