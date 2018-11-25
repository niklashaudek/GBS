all: syncem syncorder

SOURCE=syncem.c list.c list.h syncorder.c

syncem: syncem.c list.c list.h
	gcc -Wall syncem.c list.c -o $@ -lpthread

syncorder: syncorder.c list.c list.h
	gcc -Wall syncorder.c list.c -o $@ -lpthread

submit: $(SOURCE)
	tar czvf blatt05.tgz $(SOURCE)


