all:calc1 calc2 calc3a calc3b calc3g

.PHONY: clean

calc1:calc1.y calc1.l
	bison -y -d calc1.y
	flex calc1.l
	gcc -o calc1 y.tab.c lex.yy.c

calc2:calc2.y calc2.l
	bison -y -d calc2.y
	flex calc2.l
	gcc -o calc2 y.tab.c lex.yy.c

calc3:calc3.y calc3.l
	bison -y -d calc3.y
	flex calc3.l

calc3a:calc3
	gcc -o calc3a y.tab.c lex.yy.c calc3a.c

calc3b:calc3
	gcc -o calc3b y.tab.c lex.yy.c calc3b.c

calc3g:calc3
	gcc -o calc3g y.tab.c lex.yy.c calc3g.c

shell:shell.l shell.y shell.c shell.h
	bison -y -d shell.y
	flex shell.l
	gcc -o shell y.tab.c lex.yy.c shell.c

clean:
	rm -f calc1 calc2 calc3a calc3b calc3g shell
	rm -f *.o rm lex.yy.c y.tab.c y.tab.h
