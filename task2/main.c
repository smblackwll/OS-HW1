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
    FILE *status;
    //create a place to save the line
    char line[256];

    //make a long to pull the number out
    long switches;
    //make a char to keep track for extracting the number
    char *ptr;

    snprintf(path, sizeof(path), "/proc/%s/status", pid);

    status = fopen(path, "r");
    if (!status){
        perror("Status file could not be found.");
        return 1;
    }

    //read through each line of the file
    while(fgets(line, sizeof(line), status)){
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
    FILE *status;
    //create a place to save the line
    char line[256];

    //make a long to pull the number out
    long switches;
    //make a char to keep track for extracting the number
    char *ptr;

    snprintf(path, sizeof(path), "/proc/%s/status", pid);

    status = fopen(path, "r");
    if (!status){
        perror("Status file could not be found.");
        return 1;
    }

    //read through each line of the file
    while(fgets(line, sizeof(line), status)){
        if (strncmp(line, "nonvoluntary_ctxt_switches", 26) == 0){
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

const char* execPath(const char *pid){
    char path[PATH_MAX];
    char exec_path[PATH_MAX];
    //create a place to save the line
    char line[256];

    snprintf(path, sizeof(path), "/proc/%s/exe", pid);
    //note: is not null terminated
    ssize_t len = readlink(path, exec_path, sizeof(exec_path)-1);
    exec_path[len] = '\0';

    return exec_path;
}




int main(){
    DIR *dir;
    struct dirent *proc;

    //longs for context switching
    long invol = 0;
    long vol = 0;
    dir = opendir("/proc");
    char exe_path[256];
    //check error state... how?

    //iterate over each entry in a while loop?
    printf("PID\tInvoluntary Switch\tVoluntary Switch\tExec Path\n");
    while ((proc = readdir(dir)) != NULL){
        if (isProcess(proc)){
            invol = involuntarySwitch(proc->d_name);
            vol = voluntarySwitch(proc->d_name);
//            exe_path = execPath(proc->d_name);
            printf("%s\t%lu\t%lu\tPATH\n", proc->d_name, invol, vol);

        }
    }

}