#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(){
    int fd[2];
    pid_t cpid;

    pipe(fd);

    cpid = fork();
    if (cpid == 0){
        dup2(fd[1],STDOUT_FILENO);
        char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
    }

    else {
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        char *argv[] = {"wc", "-l", NULL};
        execv("/bin/wc", argv);
    }
}
