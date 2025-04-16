#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

/**
 * _find_env_index - Trouve l'index d'une variable d'environnement
 * @name: Nom de la variable à trouver
 *
 * Return: Index de la variable ou -1 si non trouvée
 */
int _find_env_index(const char *name)
{
	int i;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (-1);

	name_len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			return (i);
		}
	}

	return (-1);
}

/**
 * _unsetenv - Supprime une variable d'environnement
 * @name: Nom de la variable à supprimer
 *
 * Return: 0 en cas de succès, -1 en cas d'erreur
 */
int _unsetenv(const char *name)
{
	int index, i;

	/* Vérification des arguments */
	if (name == NULL || *name == '\0')
		return (-1);

	/* Trouver l'index de la variable à supprimer */
	index = _find_env_index(name);

	/* Si la variable n'existe pas, rien à faire */
	if (index == -1)
		return (0);

	/* Libérer la mémoire de la chaîne supprimée */
	free(environ[index]);

	/* Décaler toutes les variables suivantes */
	for (i = index; environ[i] != NULL; i++)
	{
		environ[i] = environ[i + 1];
	}

	return (0);
}

/**
 * print_env - Affiche toutes les variables d'environnement
 */
void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * main - Programme de test pour _unsetenv
 *
 * Return: 0 en cas de succès
 */
int main(void)
{
	/* Afficher l'environnement initial */
	printf("=== Environnement initial ===\n");
	print_env();

	/* Supprimer quelques variables */
	printf("\n=== Suppression de PATH ===\n");
	_unsetenv("PATH");
	print_env();

	printf("\n=== Suppression de HOME ===\n");
	_unsetenv("HOME");
	print_env();

	/* Tenter de supprimer une variable inexistante */
	printf("\n=== Suppression de VARIABLE_INEXISTANTE ===\n");
	_unsetenv("VARIABLE_INEXISTANTE");
	print_env();

	return (0);
}
