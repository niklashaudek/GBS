#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char *argv [], char *envp []) {
    /**
     * Create new char buffer for 1024 chars.
     **/
    char buffer[1024] = {0};
    int   len;
    int   src_fd = 0;
    int   dst_fd = 1;
    int   c;

    while ((c = getopt (argc, argv, "i:o:")) != -1) {
        switch (c) {
        case 'i':
            /**
             * Open file path stored in "optarg" in readonly mode.
             * (1)
             **/
            if ((src_fd = open(optarg, O_RDONLY)) == -1) {
                perror ("Cannot open input file");
                exit (-1);
            }
            break;
        case 'o':
            /**
             * Open file path stored in "optarg" in write mode with create if not exist and trucecate mode.
             * Use 0644 as additional parameter.
             * (2)
             **/
            if ((dst_fd = open(optarg, O_WRONLY | O_CREAT | O_TRUNC)) == -1) {
                perror ("Cannot open output file");
                exit (-1);
            }
            break;
        default:
            fprintf (stderr, "Usage: %s [-i <infile>] [-o <outfile>]\n", argv [0]);
            exit (-1);
        }
    }
    printf ("Copying %d -> %d\n", src_fd, dst_fd);
    // All files are open, so we can copy now

    /**
     * Read from src_fd into our buffer.
     * (3)
     **/
    while ((len = read(src_fd, buffer, sizeof(buffer))) > 0) {
        /**
         * Write result to dst_fd.
         * (4)
         **/
        if (write(dst_fd, buffer, len) == -1) {
            perror ("Cannot write to output file");
            /**
             * Close all file descriptors.
             * Exit with code -1.
             **/
        }
    }
    if (len < 0) {
        perror ("Cannot read from input file");
        /**
         * Close all file descriptors.
         * Exit with code -1.
         **/
    }
    
    /**
     * Close all file descriptors.
     * Exit with code 0.
     **/
    close(src_fd);
    close(dst_fd);
    exit(0);
}