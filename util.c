#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

//The maximum length of a message. Discord only allows 2000 Characters, and we dont want one event hogging that space. 
#define MAX_EVENT_LENGTH 500

//We can hold events for the whole year 
#define MAX_YEAR_LENGTH 365

//Maximum amount of events you can have per day 
#define MAX_EVENTS_DAILY 5

//Error cases go here 
static void fail( char const *message ) {
    //SUBJECT TO CHANGE, i don't know how exactly we will handle sending errors to user 

    fprintf( stderr, "%s\n", message );
    exit( 1 );
}

//Contains informaiton about our event (day, hour, event)
struct eventInformation {
    char eventDescription[MAX_EVENT_LENGTH]; 
    int day; 
    int hour; 
}; 

//An array of 5, which is the max amount of events at any given hour. use 
struct eventPlacement {
    struct eventInformation eventsAtThisHour[MAX_EVENTS_DAILY]; 
}; 

struct currentSchedule {
    struct eventPlacement numberOfEvents[MAX_YEAR_LENGTH]; 
}; 

//We will read the input arguments passed from index.js here
int main ( int argc, char *argv[] ) {
    //make error check for argc and argv once you know what they are. 

    //Flow will be as follows: 
    //Upon a VALID command, we get the day, hour, and message (or we can cancel an event, but thats later)
    //First make the eventInformation, then add that information to a newly made eventPlacement. 
    //THen, use that eventPlacment inside of the currentSchedule used by all 
    //HOWEVER, before anything is placed in currentSchedule, some things need to be done
    //(1) Apply math on current date to figure out where in the currentSchedule array we are at (0-364) 
            //Note, maybe we can apply currentSchedule array as a stack? Current date on top of stack  
    //(2) Check that the date is valid 
    //(3) Check that we have less than 5 events at current hour  
    //Once we are sure that the current day in currentSchedule is correct, and we can place, we can update or add events to the time 
    //After ALL THAT is done, we can print what the user requests by sending a string to index.js for printing. 


    return 0; 
}