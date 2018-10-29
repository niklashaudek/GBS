all: lt shellsim 

SOURCE=lt.c list.c list.h shellsim.c

shellsim: shellsim.c
	gcc -Wall shellsim.c -o $@

lt: lt.c list.c list.h
	gcc -Wall lt.c list.c -o $@

submit: $(SOURCE)
	tar czvf blatt02.tar $(SOURCE)


