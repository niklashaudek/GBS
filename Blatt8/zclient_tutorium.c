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
    if (inet_aton (argv [1], &sin.sin_addr) == -1) { // Konvertierung der IP Adresse von Dot Format in Byte Format
	perror ("Invalid IP address");
	exit (-1);
    }

	/**
	 * Create an UDP socket for IPv4 communication.
	 * (1)
	 **/
    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { // AF_INET ist IPv4, SOCK_DGRAM ist UDP
	perror ("Cannot create socket");
	exit (-1);
    }
    sin.sin_family = AF_INET; // IPv4
    sin.sin_port   = htons (MYPORT); // Port des Empfänger Systems
    while (1) {
	printf ("> ");
	fflush (stdout);
	if ((fgets (buffer, sizeof (buffer), stdin)) == NULL)
	    break;
	
	
	/**
	 * Send the read buffer to the read ip address.
	 * (2)
	 **/
	if (sendto(sd, buffer, strlen(buffer), 0, (struct sockaddr*) &sin, sizeof (sin)) == -1) {
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
	switch (poll(&pfd, 1, 1000)) {
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
	    if ((len = recv(sd, buffer, sizeof(buffer), 0)) <= 0) {
		perror ("Response reception failed");
		exit (-1);
	    }
	    buffer [len] = '\0';  /* zero padding won't harm */
	    printf ("%s", buffer);
	}
    }
    exit (0);
}