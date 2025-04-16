#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"


/**
 * _getenv - Récupère la valeur d'une variable d'environnement
 * @name: Nom de la variable d'environnement à rechercher
 *
 * Return: Pointeur vers la valeur de la variable, ou NULL si non trouvée
 */
char *_getenv(const char *name)
{
	extern char **environ;
	int i;
	size_t name_len;

	/* Vérification des paramètres */
	if (name == NULL || *name == '\0')
		return (NULL);

	/* Longueur du nom de la variable */
	name_len = strlen(name);

	/* Parcourir l'environnement */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Vérifie si cette entrée commence par le nom recherché suivi de '=' */
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			/* Retourne un pointeur vers la valeur (juste après le '=') */
			return (&environ[i][name_len + 1]);
		}
	}

	/* Variable non trouvée */
	return (NULL);
}

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
	path_copy = strdup(path);
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
