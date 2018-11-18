all: threadit threadsched

SOURCE=threadit.c threadsched.c list.c list.h

threadit: threadit.c
	gcc -Wall threadit.c list.c -o $@ -lpthread

threadsched: threadsched.c list.c list.h
	gcc -g -Wall threadsched.c list.c -o $@

submit: $(SOURCE)
	tar czvf blatt04.tgz $(SOURCE)


