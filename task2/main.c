#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Using this library to check get the directory entry:
// https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html

//proc stuff from here:
// https://docs.kernel.org/filesystems/proc.html

//Voluntary switch and involuntary switch used a chatgpt response as a base
//and were modified more specifically for my needs.

//strol to pull the number out was found here:
//https://www.tutorialspoint.com/c_standard_library/c_function_strtol.htm


//I feel like there's gotta be a better way to do this
int isProcess(const struct dirent *proc){
    //to look for a number, we can iterate over the possible processes, or proc
    for(int i = 0; i < strlen(proc->d_name);i++){
        //checks if the current char is a digit
        if(!isdigit(proc->d_name[i])){
            return 0;
        }
    }
    return 1;
}

long voluntarySwitch(const char *pid){
    //Create the char array/string for the file path
    char path[256];
    File *file;
    //create a place to save the line
    char line[256];

    //make a long to pull the number out
    long switches;
    //make a char to keep track for extracting the number
    char *ptr;

    snprintf(path, sizeof(path), "/proc/%s/status", pid);

    status = fopen(filepath, "r");
    if (!status){
        perror("Status file could not be found.")
        return;
    }

    //read through each line of the file
    while(fgets(line), sizeof(line), file){
        if (strncmp(line, "voluntary_ctxt_switches", 23) == 0){
            ptr = line;
            while (*ptr && !isdigit(*ptr)) {
                ptr++;
            }

            // If we have found a digit, convert it
            if (isdigit(*ptr)) {
                switches = strtol(ptr, &ptr, 10);
            }
            return switches;
        }
    }
}

long involuntarySwitch(const char *pid){
//Create the char array/string for the file path
    char path[256];
    File *file;
    //create a place to save the line
    char line[256];

    //make a long to pull the number out
    long switches;
    //make a char to keep track for extracting the number
    char *ptr;

    snprintf(path, sizeof(path), "/proc/%s/status", pid);

    status = fopen(filepath, "r");
    if (!status){
        perror("Status file could not be found.")
        return;
    }

    //read through each line of the file
    while(fgets(line), sizeof(line), file){
        if (strncmp(line, "involuntary_ctxt_switches", 23) == 0){
            ptr = line;
            while (*ptr && !isdigit(*ptr)) {
                ptr++;
            }

            // If we have found a digit, convert it
            if (isdigit(*ptr)) {
                switches = strtol(ptr, &ptr, 10);
            }
            return switches;
        }
    }
}




int main(){
    DIR *dir;
    struct dirent *proc;

    //longs for context switching
    long invol = 0;
    long vol = 0;
    dir = opendir("/proc");
    //check error state... how?

    //iterate over each entry in a while loop?
    printf("PID\tInvoluntary Switch\tVoluntary Switch\tExec Path")
    while ((proc = readdir(dir)) != NULL){
        if (isProcess(proc)){
            invol = involuntarySwitch(proc->d_name);
            vol = voluntarySwitch(proc->d_name);
            printf("PID: %s, %lu, %lu, \n", proc->d_name, invol, vol);

        }
    }

}