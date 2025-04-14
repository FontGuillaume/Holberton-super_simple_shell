#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * main - Prints all arguments passed to the program
 * @ac: The number of arguments passed to the program.
 * @av: An array of strings containing the arguments.
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	(void)ac;

	int i = 0;

	while (av[i] != NULL)
	{
		printf("%s\n", av[i]);
		i++;
	}
	return (0);
}
