#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD 128
#define MAX_ARGS 10

int main() {
    char comando[MAX_CMD];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        printf("mini-shell> ");
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = '\0';
        if (strcmp(comando, "exit") == 0) {
            break;
        }
        int i = 0;
        char *token = strtok(comando, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        pid = fork();
        if (pid < 0) {
            perror("Erro no fork");
            exit(1);
        } else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Erro no exec");
            }
            exit(1);
        } else {
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}
