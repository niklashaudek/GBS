all: hw asc rotup hd

SOURCE=hw.c asc.c rotup.c hd.c hexdump.c

hw: hw.c
	gcc -Wall hw.c -o $@

asc: asc.c
	gcc -Wall asc.c -o $@

rotup: rotup.c
	gcc -Wall rotup.c -o $@

hd: hd.c hexdump.c
	gcc -Wall hd.c hexdump.c -o $@

submit: $(SOURCE)
	tar czvf blatt01.tar $(SOURCE)


