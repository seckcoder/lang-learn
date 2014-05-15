CPP=g++
poj_3264: poj_3264.cpp
	${CPP} $^ -o test
crypt1: crypt1.cpp
	${CPP} $^ -o test
test: test.cpp interval_tree.h
	${CPP} $^ -o test
exc:
	cat data | xargs ./test
