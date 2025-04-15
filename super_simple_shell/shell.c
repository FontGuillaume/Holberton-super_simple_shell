#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Super simple shell
 *
 * Return: Always 0
 */
int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    pid_t child_pid;
    int status;
    char *argv[2];

    while (1)
    {
        printf("$ ");
        characters = getline(&buffer, &bufsize, stdin);

        if (characters == -1) /* Handle EOF (Ctrl+D) */
        {
            printf("\n");
            break;
        }

        /* Remove newline character at the end */
        if (buffer[characters - 1] == '\n')
            buffer[characters - 1] = '\0';

        /* Skip if empty line */
        if (strlen(buffer) == 0)
            continue;

        /* Prepare arguments for execve */
        argv[0] = buffer;
        argv[1] = NULL;

        /* Create child process */
        child_pid = fork();

        if (child_pid == -1)
        {
            perror("Error:");
            continue;
        }

        if (child_pid == 0) /* Child process */
        {
            /* Execute command */
            if (execve(argv[0], argv, NULL) == -1)
            {
                perror(argv[0]);
                exit(1);
            }
        }
        else /* Parent process */
        {
            /* Wait for child to complete */
            wait(&status);
        }
    }

    /* Free allocated memory */
    free(buffer);
    return (0);
}
