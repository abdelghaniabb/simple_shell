#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024

int main()
{
    char line[MAX_LINE];
    char *argv[MAX_LINE/2 + 1];
    int should_run = 1;
    pid_t pid;
    int status;

    while (should_run) {
        printf("#cisfun$ ");
        fflush(stdout);
        fgets(line, MAX_LINE, stdin);
        if (line[strlen(line)-1] == '\n') {
            line[strlen(line)-1] = '\0';
        }
        if (strcmp(line, "exit") == 0) {
            should_run = 0;
            break;
        }
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            argv[0] = line;
            argv[1] = NULL;
            if (execve(argv[0], argv, NULL) == -1) {
                perror("execve failed");
                exit(1);
            }
        } else {
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}
