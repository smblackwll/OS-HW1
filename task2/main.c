#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Using this library to check get the directory entry:
// https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html

//proc stuff from here:
// https://docs.kernel.org/filesystems/proc.html

//I feel like there's gotta be a better way to do this
int isProcess(const struct dirent *proc){
    //to look for a number, we can iterate over the possible processes, or proc
    printf(proc + "\n")
    for(int i = 0; i < strlen(proc->d_name);i++){
        //checks if the current char is a digit
        if(!isdigit(proc->d_name[i])){
            printf(d_name[i] + "\n")
            return 0;
        }
    }
    return 1;
}


int main(){
    DIR *dir;
    struct dirent *proc;

    dir = opendir("/proc");
    //check error state... how?

    //iterate over each entry in a while loop?
    while ((proc = readdir(dir)) != NULL){
        if (isProcess(proc)){
            printf("PID: %s\n", proc->d_name);
        }
    }

}