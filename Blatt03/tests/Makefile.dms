all: forkone forkmany

SOURCE=forkone.c forkmany.c list.c list.h

forkone: forkone.c
	gcc -Wall forkone.c -o $@

forkmany: forkmany.c list.c list.h
	gcc -Wall forkmany.c list.c -o $@

submit: $(SOURCE)
	tar czvf blatt03.tgz $(SOURCE)


