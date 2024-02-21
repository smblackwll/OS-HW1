//Major uses here:
//execvp is used to execute c code - we can essentially just parse the input string from the user, check if the command is exit
// if it's exit run the exit function. Otherwise, we can use execvp and the parsed args to run a command.
//we may need fork?
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Reading in from stdin safely stuff here, just reads it all in as one big string.
// https://alexandra-zaharia.github.io/posts/how-to-read-safely-from-stdin-in-c/

//Once again, CHATGPT helped a lot in figuring out how to pass args. I'm uhhh not great with pointers

//wait stuff from here:
//https://www.baeldung.com/linux/wait-command
//They're great - they essentially just figure out


void execute(char *args[]){
    pid_t pid = fork();
    if (pid == 0) {
        // Execute the command
        if (execvp(args[0], args) == -1) {
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) { // Parent process
        int status;
        wait(&status); // Wait for the child process to finish
    } else {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}





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


        str[strcspn(str, "\r\n")] = 0;



        //Split the parameters on the space... I hope?
        char* sect = strtok(str, " ");

        int i = 0;
        while (sect != NULL){
            args[i] = malloc(sizeof(char)*strlen(sect+1));
            strcpy(args[i], sect);
            sect = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if(strcmp(args[0], "exit()") == 0){
            run = 0;
        } else{
            execute(args);

            for (int j = 0; j < i; j++) {
                free(args[j]);
            }
        }
    }
}