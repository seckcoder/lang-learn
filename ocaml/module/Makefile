
all:freq

freq:freq.ml
	ocamlbuild -verbose 1 -use-ocamlfind -pkg Core counter.ml -lflag -thread -cflag -thread freq.native
