complies = g++ -O3
target = matrix.o neurons.o funofneurons.o cnnnet.o fileofparameter.o functioninit.o
a.out :  $(target) main.o
	$(complies) $^ -lm -o a.out
test.out : test.o matrix.o neurons.o funofneurons.o cnnnet.o fileofparameter.o
	$(complies) $^ -lm -o test.out
test.o : test.c
	$(complies) -c test.c
learnfromfile.out : learnfromfile.o $(target)
	$(complies) $^ -lm -o learnfromfile.out
learnfromfile.o : learnfromfile.c
	$(complies) -c learnfromfile.c
resulttest.out : resulttest.o $(target)
	$(complies) $^ -lm -o resulttest.out
resulttest.o : resulttest.c
	$(complies) -c resulttest.c
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
functioninit.o : functioninit.c
	$(complies) -c $^
testinterface.out : testinterface.o interface.o $(target)
	g++ $^ -o testeinterface.out
interface.o : interface.cpp
	g++ -c $^
testinterface.o : testinterface.cpp
	g++ -c $^
clean :
	rm -rf main.o a.out matrix.o neurons.o funofneurons.o cnnnet.o fileofparameter.o test.o test.out learnfromfile.o learnfromfile.out resulttest.o resulttest.out functioninit.o interface.o testinterface.o testinterface.out
