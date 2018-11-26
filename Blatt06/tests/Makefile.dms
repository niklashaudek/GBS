all: parsertest mysh

SOURCE=parsertest.c list.c list.h parser.c mysh.c

parsertest: parsertest.c parser.c list.c list.h
	gcc -Wall parsertest.c parser.c list.c -o $@

mysh: mysh.c list.c list.h parser.c
	gcc -Wall mysh.c list.c parser.c -o $@

submit: $(SOURCE)
	tar czvf blatt06.tgz $(SOURCE)


