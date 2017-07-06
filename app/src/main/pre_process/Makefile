targer = image.o
test_target = $(target) test.o

test: $(test_target)
	cc -o test $(test_target)

test.o: test.cpp image.hpp

image.o: image.cpp image.hpp
