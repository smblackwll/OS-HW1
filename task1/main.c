//Major uses here:
//execvp is used to execute c code - we can essentially just parse the input string from the user, check if the command is exit
// if it's exit run the exit function. Otherwise, we can use execvp and the parsed args to run a command.
//we may need fork?
#include <stdio.h>

// Reading in from stdin safely stuff here, just reads it all in as one big string.
// https://alexandra-zaharia.github.io/posts/how-to-read-safely-from-stdin-in-c/
void main(void){
    int run = 1;
    char str[256];
    char userIn[256];
    char args[256];

    while(run == 1){
        str[0] = '\0';
        char userIn = fgets(str, sizeof(str), stdin);
        if(!userIn){
            return;
        }
        int i = 0;
        while (str[i] != '\n' && str[i] != '\0')
            i++;

        if (str[i] == '\n'){
            str[i] = '\0';

        }

        printf(userIn);

        if(strcmp(str, "exit()") == 0){
            run = 0;
        }
    }
}