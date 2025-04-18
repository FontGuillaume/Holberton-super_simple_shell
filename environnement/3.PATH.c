#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"


/**
 * print_path_directories - Affiche chaque répertoire du PATH, un par ligne
 *
 * Return: 0 en cas de succès, 1 si PATH n'existe pas
 */
int print_path_directories(void)
{
	char *path, *path_copy, *dir;

	/* Récupérer la variable d'environnement PATH */
	path = _getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "PATH variable not found\n");
		return (1);
	}

	/* Dupliquer la chaîne PATH pour la manipulation avec strtok */
	path_copy = _strdup(path);
	if (path_copy == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		return (1);
	}

	/* Séparer la chaîne PATH en utilisant ":" comme délimiteur */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		printf("%s\n", dir);
		dir = strtok(NULL, ":");
	}

	/* Libérer la mémoire allouée */
	free(path_copy);

	return (0);
}

/**
 * main - Point d'entrée pour tester la fonction
 *
 * Return: 0 si réussi, 1 si échoué
 */
int main(void)
{
	return (print_path_directories());
}
