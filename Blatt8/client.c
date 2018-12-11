#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MYPORT    44444

int main (int argc, char *argv [], char *envp []) {
    char                buffer [0x10000];
    struct sockaddr_in  sin;
    int                 sd;
    int                 len;
    struct pollfd       pfd;

    if (argc != 2) {
	fprintf (stderr, "Usage: %s <server address>\n", argv [0]);
	exit (-1);
    }
    if (inet_aton (argv [1], &sin.sin_addr) == -1) {
	perror ("Invalid IP address");
	exit (-1);
    }
	/**
	 * Create an UDP socket for IPv4 communication.
	 * (1)
	 **/
    if ((sd = /**Replace (1)**/) == -1) {
	perror ("Cannot create socket");
	exit (-1);
    }
    sin.sin_family = AF_INET;
    sin.sin_port   = htons (MYPORT);
    while (1) {
	printf ("> ");
	fflush (stdout);
	if ((fgets (buffer, sizeof (buffer), stdin)) == NULL)
	    break;
	/**
	 * Send the read buffer to the read ip address.
	 * (2)
	 **/
	if (/**Replace (2)**/ == -1) {
	    perror ("Sending to socket failed");
	    exit (-1);
	}
	pfd.fd      = sd;
	pfd.events  = POLLIN;
	pfd.revents = 0;
	/**
	 * Poll for an answer with a timeout of 1 second.
	 * (3)
	 **/
	switch (/**Replace (3)**/) {
	case 0:
	    printf ("Timeout.  No response received\n");
	    break;
	case -1:
	    perror ("Poll error");
	    exit (-1);
	default:
		/**
		 * Read the response into the buffer variable.
		 * (4)
		 **/
	    if ((len = /**Replace (4)**/) <= 0) {
		perror ("Response reception failed");
		exit (-1);
	    }
	    buffer [len] = '\0';  /* zero padding won't harm */
	    printf ("%s", buffer);
	}
    }
    exit (0);
}