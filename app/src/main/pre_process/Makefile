cc := g++ -O3
target := image.o
test_target := $(target) test.o

test.out: $(test_target)
	$(cc) -o test.out $(test_target)

test.o: test.cpp
	$(cc) -c test.cpp

image.o: image.cpp
	$(cc) -c image.cpp

clean:
	rm *.o *.out
