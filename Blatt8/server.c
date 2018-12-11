#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include "list.h"

#define MYPORT    44445

struct timeval* time_init()
{
    struct timeval* timeout_Time = (struct timeval*) malloc(sizeof(struct timeval));
    timeout_Time->tv_sec = 5; // Angabe
    timeout_Time->tv_usec = 0;
    return timeout_Time;
}


int main (int argc, char *argv [], char *envp []) {
    char                buffer [1024];
    struct sockaddr_in  sin;
    struct sockaddr_in  sender;
    int                 sd;
    int                 len, i;
    socklen_t           sender_len;
    list_t* connection_list = list_init();
    if(connection_list == NULL)
    {
        printf ("Cannot allocate memory for Connection List");
        exit(-1);
    }

    if (argc != 1) {
	fprintf (stderr, "Usage: %s\n", argv [0]);
	exit (-1);
    }
    
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { // SOCK_STREAM for TCP
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
    if (bind (sd, (struct sockaddr*) &sin, sizeof(sin)) == -1) {
	perror ("Bind failed");
	exit (-1);
    }
    
    struct timeval* lTime = time_init(); // Methode oben definiert
    list_append(connection_list, sd, sin, *lTime);
    
    while (1) {
	sender_len = sizeof (sender);
    /**
     * Receive data and store it into the buffer variable.
     * Also store the sender in the sender variable.
     * (3)
     **/
	if ((len = recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*) &sender, &sender_len)) == -1) {
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

    printf("Received packet from %s:%d size &d\n", inet_ntoa (sender.sin_addr), ntohs (sender.sin_port), len);
    
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