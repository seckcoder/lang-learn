all: hello_world

lazy_assoc:
	corebuild lazy_assoc.byte

# Example of build using ocamlfind
hello_world:hello_world.ml
	ocamlfind ocamlopt -c -package core -thread hello_world.ml
	ocamlfind ocamlopt -o hello_world -linkpkg -package core -thread hello_world.cmx

clean:
	rm *.byte
