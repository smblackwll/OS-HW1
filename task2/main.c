#include <stdio.h>
#include <dirent.h>
#include <string.h>

//Using this library to check get the directory entry:
// https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html

int isProcess(const struct dirent *proc){
    //to look for a number, we can iterate over the possible processes, or proc
    printf("Iterating")
    for(int i = 0; i < strlen(entry->d_name);i++){
        //checks if the current char is a digit
        if(!isDigit(entry->d_name[i])){
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

}