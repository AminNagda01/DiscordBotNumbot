#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

//The maximum length of a message. Discord only allows 2000 Characters, and we dont want one event hogging that space. 
#define MAX_EVENT_LENGTH 100

//We can hold events for the whole year 
#define MAX_YEAR_LENGTH 365

//Maximum amount of events you can have per day 
#define MAX_EVENTS_DAILY 5

#define MAX_HOURS_IN_DAY 24

//The maximum length of a line the data file. 
#define MAXIMUM_LINE 12500  
//Now, I know this is not too smart, but I know the upper bound of characters in a string, so this is easier 

//Hours in a day 
#define HOURS_PER_DAY 24

//Error cases go here 
static void fail( char const *message ) {
    //SUBJECT TO CHANGE, i don't know how exactly we will handle sending errors to user 

    fprintf( stderr, "%s\n", message );
    exit( 1 );
}

//The following is structured like: 
//We have an event, inside of an array 5 events long, called maxAllowableEvents
//Which itself is assigned to an array of 24 maxAllowableEvents, creating 5 events for every 24 hours per day 
//And finally make a listOfTheYear 365 days long, each day containing 24 hours and each hour containing 5 max events
struct eventInformation {
    char eventDescription[MAX_EVENT_LENGTH]; 
}; 
struct maximumEvents {
    struct eventInformation maxAllowableEvents[MAX_EVENTS_DAILY]; 
}; 
struct hoursPerDay {
    struct maximumEvents arrayOfHoursPerDay[MAX_HOURS_IN_DAY]
};
struct currentSchedule {
    struct hoursPerDay listOfTheYear[MAX_YEAR_LENGTH]; 
}; 

//We will read the input arguments passed from index.js here
int main ( int argc, char *argv[] ) {
    //make error check for argc and argv once you know what they are (what will be sent from index.js)

    //error check all argv

    //make currentSchedule
    struct currentSchedule toUse; 
    FILE *fp = fopen("/scheduleData.txt", "r+"); 
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    //Populate current schedule with what our data file says it is    
    for (int i = 0; i < MAX_YEAR_LENGTH; i++) {
        bool control = true; 

        //Run through one line (one day) 
        while ( control ) {
            char temp; 
            temp = fgetc( fp ); 

            //If no entries on this day, we can leave it alone 
            if (temp == '\0' || temp == '\n') {
                break; 
            }

            //Otherwise, populate
            
            //When we have a new hour in the same day, denoted by '<', come here 
            newHourCase:

            //Keeps track of how many events in one hour 
            int eventCounter = 0; 
            if (temp == '<') { 

                //Gets the first hour we have an event on 
                int tempHour; 
                if (fscanf(fp, "%d", &tempHour) != 1) {
                    fail("Bad file format, there should be a hour here"); 
                }
                temp = fgetc( fp ); //burns the closing angle bracket '>' 

                //When we have a new event in the same hour, denoted by '#', come here 
                newMessageSameHour:

                if (eventCounter == MAX_EVENTS_DAILY) {
                    fail("Too many events on this day"); //this shouldnt happen on the reading in, but just incase 
                }

                //Create the message, stop when we reach (1) a new event (2) a new hour or (3) end of the line 
                int counter = 0; 
                char descriptionToAdd[MAX_EVENT_LENGTH]; 
                temp = fgetc( fp );
                while (temp != '#' && temp != '<' && temp != '\n' ) {
                    if (counter == MAX_EVENT_LENGTH - 1) {
                        fail("Message too long"); 
                    }

                    descriptionToAdd[counter] = temp; 
                    counter++; 
                    temp = fgetc( fp );
                }

                //Null terminate the message 
                descriptionToAdd[counter] = '\0'; 

                //Copy the message to the proper location in our schedule structure, and increase the count of events on this hour 
                strcpy(toUse.listOfTheYear[i].arrayOfHoursPerDay[tempHour].maxAllowableEvents[eventCounter].eventDescription, descriptionToAdd); 
                eventCounter++;  

                if (temp == '#') {
                    goto newMessageSameHour; 
                }

                else if (temp == '<') {
                    goto newHourCase; 
                }
                else {
                    //If we reach new line, we want to leave the while loop since we are going to next line (next day)
                    control = false;
                }
            }
        }
    }

    //Check command, if cancel event go to place in toUse and replace the event with '\0'. 

    ///if other command, we have to check if there is space to place new event, and place it if so. 
    //Once we have done the command, reprint the entire toUse onto the scheduleData, and close 

    //scheduleData.txt will always be day-number:<hour>Message Here# Hash seperated seperated for >1 events <next-hour>:etc 
    //ex: 123:<14>Event 1a here<22>Event 2a here
    //    345:<3>Event 1a here#Event 1b here#Event 1c here
    //With the example, I have 5 events this year, 3 take place at 3am on 345th day, one at 2pm on 123rd day, and one at 10pm on 123rd day

    //HOWEVER, before anything is placed in currentSchedule, some things need to be done
    //(1) Apply math on current date to figure out where in the currentSchedule array we are at (0-364) 
            //Note, maybe we can apply currentSchedule array as a stack? Current date on top of stack  
    //(2) Check that the date is valid 
            //Also, update eventInformation for the current date so that it can be later printed as an actual date 
            //Ex, if we have day 10/1 entered, we know that day is the 274th day, so insert that. 
            //Inversely, on printing, it will print 10/1 instead of 274  
    //(3) Check that we have less than 5 events at current hour  
    //Once we are sure that the current day in currentSchedule is correct, and we can place, we can update or add events to the time 
    //After ALL THAT is done, we can print what the user requests by sending a string to index.js for printing. 
    //Before the c file closes, update the scheduleData.txt with the updated schedule 


    return 0; 
}