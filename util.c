#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

//Error cases go here 
static void fail( char const *message ) {
    fprintf( stderr, "%s\n", message );
    exit( 1 );
}

//We want a calendar that can show appointments throughout the month, week, or day depending on user request 
//We have to be aware of what month we are in, so that we can print the right amount of days and weeks on a month request 
//Each day has 24 hours that can be assigned, and there can be more than 1 event each hour 
//We must be able to print all events on a day, or hour 
