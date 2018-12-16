#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <poll.h>
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
    int                 iBacklog = 10; // Anzahl übrige Verbindungen
    struct sockaddr_in  sin;
    struct sockaddr_in  sender;
    struct sockaddr*    newSock = NULL;
    int                 sd;
    int                 len, i;
    socklen_t           sender_len;
    list_t* connection_list = list_init();
    if(connection_list == NULL)
    {
        printf ("Cannot allocate memory for Connection List");
        exit(-1);
    }

    if (argc != 1) 
    {
        fprintf (stderr, "Usage: %s\n", argv [0]);
        exit (-1);
    }
    
    sd = socket(AF_INET, SOCK_STREAM, 0); // socket erzeugen, SOCK_STREAM für TCP

    if (sd == -1) 
    {
        perror ("Cannot create socket");
        return -1;
    }
    
    sin.sin_family      = AF_INET;
    sin.sin_port        = htons (MYPORT);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    /**
     * Bind the socket to the address and port stored in sin.
     * (2)
     **/
    
    int iTestBind = bind (sd, (struct sockaddr *) &sin, sizeof(sin)); 

    if (iTestBind == -1) 
    {
        perror ("Bind failed");
        return -1;
    }
    
    





    while (1) {
		sender_len = sizeof(sender);
        len = recvfrom(sd, buffer, sizeof(buffer), 0,
				(struct sockaddr * ) & sender, & sender_len);
		if (len == -1) {
			perror("Receiving from socket failed");
			exit(-1);
		}
		printf("Received packet from %s:%d size %d\n",
			inet_ntoa(sender.sin_addr), ntohs(sender.sin_port), len);
		if (len > 0) {
			for (i = 0; i < len; i++) {
				if (isalpha(buffer[i]))
					buffer[i] ^= 0x20;
				else if (isdigit(buffer[i]))
					buffer[i] = (9 - (buffer[i] - '0')) + '0';
			}
			if (sendto(sd, buffer, len, 0, (struct sockaddr * ) & sender, sender_len) <= 0) {
				perror("Failed to send response back to client");
				continue;
			}
		}
	}












    /*
    while(1)
    {
        i = accept(sd, NULL, NULL);
        send(i, buffer, strlen(buffer), 0);
        close(i); // Example from Slides for TCP
    }

    
        int* iTestAccept = accept(sd, (struct sockaddr*) &sender, &sender_len);
        if(iTestAccept <= 0)
        {
            perror("Accept failed.");
            exit(-2);
        }

        int iTestConnect = connect(sd, (struct sockaddr*) &sender, sender_len);
        if(iTestConnect == -1)
        {
            perror("Connection of sockets failed.");
            exit(-2);
        }
        iBacklog -= 1;
    

    
    
    struct timeval* lTime = time_init(); // Methode oben definiert
    struct list_elem* eTest = list_append(connection_list, sd, sin, *lTime);
    
    if(eTest == NULL)
    {
        perror("List append returned NULL.");
        exit(-2);
    }
    */
    
    // while (1) 
    // {
    //     sender_len = sizeof (sender);
    //     /**
    //      * Receive data and store it into the buffer variable.
    //      * Also store the sender in the sender variable.
    //      * (3)
    //      **/

    //     len = recvfrom(sd, buffer, sizeof(buffer), 0, (struct sockaddr*) &sender, &sender_len);
    //     // recvfrom gibt Anzahl der eingelesenen Zeichen zurück
    //     if (len == -1) {
    //         perror ("Receiving from socket failed");
    //         exit (-1);
    //     }
    //     /**
    //      * Print the received package in the following format:
    //      * "Received packet from %s:%d size %d\n"
    //      * %s = sender IP
    //      * %d = sender port
    //      * %d = length of the received buffer
    //      * (4)
    //      **/
    //     /**(4)**/

    //     printf("Received packet from %s:%d size &d\n", inet_ntoa (sender.sin_addr), ntohs (sender.sin_port), len);
        
    //     if (len > 0) 
    //     {
    //         // So something with text or leave it
    //         /**
    //          * Send result back to the sender as a TCP packet.
    //          * (6)
    //          **/
    //         if (1 <= 0) { // 1 MUSS ERSETZT WERDEN !!!
    //         perror ("Failed to send response back to client");
    //         continue;
    //         }
    //     }
    
    //close(sd);
    return 0;
}