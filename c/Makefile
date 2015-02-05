all:address_ordering 

address_ordering:address_ordering.cc address_ordering.h test_address_ordering.cc
	gcc address_ordering.cc test_address_ordering.cc -o address_ordering

integer_rep:integer_rep.c address_ordering.h address_ordering.c
	gcc address_ordering.c integer_rep.c -o interp_rep
