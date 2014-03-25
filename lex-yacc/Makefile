all:calc1 calc2 calc3

.PHONY: clean

calc1:
	bison -y -d calc1.y
	flex calc1.l
	gcc -o calc1 y.tab.c lex.yy.c

calc2:
	bison -y -d calc2.y
	flex calc2.l
	gcc -o calc2 y.tab.c lex.yy.c


calc3:
	bison -y -d calc3.y
	flex calc3.l
	gcc -o calc3a y.tab.c lex.yy.c calc3a.c
	gcc -o calc3b y.tab.c lex.yy.c calc3b.c
	gcc -o calc3g y.tab.c lex.yy.c calc3g.c

clean:
	rm -f calc1 calc2 calc3a calc3b calc3g
	rm -f *.o rm lex.yy.c y.tab.c y.tab.h
