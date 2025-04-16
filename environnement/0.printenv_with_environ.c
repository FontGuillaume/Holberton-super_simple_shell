#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * main - Affiche l'environnement en utilisant la variable globale environ
 *
 * Return: Toujours 0
 */
int main(void)
{
	/* Déclaration de la variable globale environ */
	extern char **environ;
	int i = 0;

	/* Parcours de toutes les variables d'environnement */
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}
