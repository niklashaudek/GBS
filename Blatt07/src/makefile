all: mysh

SOURCE=list.c list.h parser.c mysh.c

mysh: mysh.c list.c list.h parser.c
	gcc -g -Wall mysh.c list.c parser.c -o $@

submit: $(SOURCE)
	tar czvf blatt07.tgz $(SOURCE)
