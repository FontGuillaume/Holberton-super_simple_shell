#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * main - Display prompt, wait for user input, and print the command
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	printf("$ ");
	nread = getline(&line, &len, stdin);

	if (nread != -1)
		fprintf(stderr, "%s: command not found", line);

	else
		printf("\n");

	free(line);
	return (0);
}
