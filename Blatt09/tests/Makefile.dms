all: mem

SOURCE=list.c list.h memory.c memory.h mem.c

mem: $(SOURCE)
	gcc -g -Wall memory.c list.c mem.c -o $@

submit: $(SOURCE)
	tar czvf blatt09.tgz $(SOURCE)
