#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Exécute ls -l /tmp dans 5 processus enfants différents
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	int status;
	int i;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};

	for (i = 0; i < 5; i++)
	{
		printf("Création du processus enfant #%d\n", i + 1);

		/* Création du processus enfant */
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Erreur lors de la création du processus");
			return (1);
		}
		if (child_pid == 0)
		{
			/* Code exécuté par le processus enfant */
			printf("Enfant #%d (PID: %d) exécute 'ls -l /tmp'\n", i + 1, getpid());
			/* Exécution de la commande ls -l /tmp sans environnement */
			if (execve("/bin/ls", argv, NULL) == -1)
			{
				perror("Erreur lors de l'exécution de la commande");
				return (1);
			}
			/* Ce code ne sera jamais exécuté si execve réussit */
			return (0);
		}
		else
		{
			/* Code exécuté par le processus parent */
			wait(&status);
			printf("Enfant #%d a terminé\n", i + 1);
		}
	}
	printf("Tous les processus enfants ont terminé\n");
	return (0);
}
