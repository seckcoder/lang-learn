all: generate typeahead

CFLAGS = -std=c++0x
CFLAGS = -g
generate: generateLarge.cpp
	g++ ${CFLAGS} generateLarge.cpp -o generate

typeahead:typeahead_search.cc
	g++ ${CFLAGS} typeahead_search.cc -o typeahead
clean:
	rm -f generate typeahead
