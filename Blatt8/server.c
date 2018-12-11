#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>

#define MYPORT    44444

int main (int argc, char *argv [], char *envp []) {
    char                buffer [0x10000];
    struct sockaddr_in  sin;
    struct sockaddr_in  sender;
    int                 sd;
    int                 len, i;
    socklen_t           sender_len;

    if (argc != 1) {
	fprintf (stderr, "Usage: %s\n", argv [0]);
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
    sin.sin_family      = AF_INET;
    sin.sin_port        = htons (MYPORT);
    sin.sin_addr.s_addr = INADDR_ANY;
    /**
     * Bind the socket to the address and port stored in sin.
     * (2)
     **/
    if (/**Replace (2)**/) {
	perror ("Bind failed");
	exit (-1);
    }
    while (1) {
	sender_len = sizeof (sender);
    /**
     * Receive data and store it into the buffer variable.
     * Also store the sender in the sender variable.
     * (3)
     **/
	if ((len = /**Replace (3)**/) == -1) {
	    perror ("Receiving from socket failed");
	    exit (-1);
	}
    /**
     * Print the received package in the following format:
     * "Received packet from %s:%d size %d\n"
     * %s = sender IP
     * %d = sender port
     * %d = length of the received buffer
     * (4)
     **/
    /**(4)**/
    
	if (len > 0) {
        /**
         * Process message like described in exercise 2.4 b).
         * (5)
         **/

        /**(5)**/
	    
        /**
         * Send result back to the sender as a UDP packet.
         * (6)
         **/
	    if (/**Replace (6)**/ <= 0) {
		perror ("Failed to send response back to client");
		continue;
	    }
	}
    }
    exit (0);
}