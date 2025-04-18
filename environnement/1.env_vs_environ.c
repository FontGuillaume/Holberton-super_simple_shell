#include <stdio.h>
#include <unistd.h>
#include "main.h"

/**
 * main - Compare les adresses de env et environ
 * @argc: Nombre d'arguments
 * @argv: Tableau d'arguments
 * @env: Environnement passé à main
 *
 * Return: Toujours 0
 */
int main(int argc, char *argv[], char *env[])
{
	/* Affichage des adresses */
	printf("Adresse de env: %p\n", *env);
	printf("Adresse de environ: %p\n", *environ);

	/* Comparaison des adresses */
	if (env == environ)
		printf("env et environ pointent vers la même adresse\n");
	else
		printf("env et environ pointent vers des adresses différentes\n");

	/* Vérifions si le contenu est le même */
	int i = 0;
	int same_content = 1;

	while (env[i] != NULL && environ[i] != NULL)
	{
		if (env[i] != environ[i])
		{
			same_content = 0;
			break;
		}
		i++;
	}

	/* Vérifie que les deux tableaux ont la même longueur */
	if (env[i] != NULL || environ[i] != NULL)
		same_content = 0;

	if (same_content)
		printf("Les tableaux env et environ contiennent les mêmes valeurs\n");
	else
		printf("Les tableaux env et environ sont différents\n");

	return (0);
}
