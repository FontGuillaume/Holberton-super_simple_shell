#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * _which - Recherche un fichier dans le PATH
 * @filename: Nom du fichier à rechercher
 *
 * Return: 0 si trouvé, 1 sinon
 */
int _which(char *filename)
{
	char *path_env, *path_copy, *path_token, *file_path;
	int path_len, file_len, found = 0;
	struct stat st;

	/* Récupérer la variable d'environnement PATH */
	path_env = getenv("PATH");
	if (path_env == NULL)
		return (1);

	/* Dupliquer PATH pour le manipuler avec strtok */
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (1);

	/* Obtenir la longueur du nom de fichier */
	file_len = strlen(filename);

	/* Parcourir chaque répertoire dans PATH */
	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		/* Calculer la longueur du chemin complet */
		path_len = strlen(path_token);
		file_path = malloc(path_len + file_len + 2); /* +2 pour '/' et '\0' */
		if (file_path == NULL)
		{
			free(path_copy);
			return (1);
		}

		/* Construire le chemin complet */
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, filename);

		/* Vérifier si le fichier existe et est exécutable */
		if (stat(file_path, &st) == 0)
		{
			/* Vérifier les permissions d'exécution */
			if (st.st_mode & S_IXUSR)
			{
				printf("%s\n", file_path);
				found = 1;
				free(file_path);
				break;
			}
		}

		free(file_path);
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return (found ? 0 : 1);
}

/**
 * main - Programme _which
 * @ac: Nombre d'arguments
 * @av: Tableau d'arguments
 *
 * Return: 0 en cas de succès
 */
int main(int ac, char **av)
{
	int i;

	if (ac < 2)
	{
		printf("Usage: %s filename ...\n", av[0]);
		return (1);
	}

	/* Parcourir chaque argument (nom de fichier) */
	for (i = 1; i < ac; i++)
	{
		_which(av[i]);
	}

	return (0);
}
