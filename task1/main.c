//Major uses here:
//execvp is used to execute c code - we can essentially just parse the input string from the user, check if the command is exit
// if it's exit run the exit function. Otherwise, we can use execvp and the parsed args to run a command.
//we may need fork?
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Reading in from stdin safely stuff here, just reads it all in as one big string.
// https://alexandra-zaharia.github.io/posts/how-to-read-safely-from-stdin-in-c/



void main(void){
    int run = 1;
    char str[256];
    char userIn[256];
    char* args[256];

    while(run == 1){
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



        //Split the parameters on the space... I hope?
        char* token = strtok(userIn, " ");

        i = 0;
        while (token != NULL){
            args[i] = malloc(sizeof(char)*strlen(token+1));
            strcpy(args[i], token);
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if(strcmp(str, "exit()") == 0){
            run = 0;
        } else{
//            printf(str);
//            printf('\0');
            for (int j = 0; j < i; j++) {
                printf("%s\n", args[j]);
            }
        }
    }
}