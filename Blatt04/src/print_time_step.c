// code snippet from Blatt 04, provided in separate file

void print_time_step (int time, int thread_num) {
    static int    first_time = 1;
    int           i;

    if (first_time) {
    printf ("  Time |  1  2  3  4  5  6  7  8  9  10\n");
    printf ("-------+--------------------------------\n");
    first_time = 0;
    }
    printf ("%06d |", time);
    if (thread_num) {
    for (i = 1; i < thread_num; i++)
        printf ("   ");
    printf ("  %d\n", thread_num);
    } else
    printf ("\n");
}