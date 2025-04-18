#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

extern char **environ;

/**
 * _getenv - Récupère la valeur d'une variable d'environnement
 * @name: Nom de la variable d'environnement à rechercher
 *
 * Return: Pointeur vers la valeur de la variable, ou NULL si non trouvée
 */
char *_getenv(const char *name)
{
	int i;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (NULL);

	name_len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			return (&environ[i][name_len + 1]);
		}
	}

	return (NULL);
}

/**
 * _find_env_index - Trouve l'index d'une variable d'environnement
 * @name: Nom de la variable à trouver
 *
 * Return: Index de la variable ou -1 si non trouvée
 */
int find_env_index(const char *name)
{
	int i;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (-1);

	name_len = _strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			return (i);
		}
	}

	return (-1);
}

/**
 * _setenv - Modifie ou ajoute une variable d'environnement
 * @name: Nom de la variable
 * @value: Valeur à assigner
 * @overwrite: Flag indiquant s'il faut écraser une variable existante
 *
 * Return: 0 en cas de succès, -1 en cas d'erreur
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int index, env_count, i;
	char *new_entry, **new_environ;
	size_t entry_len;

	/* Vérification des arguments */
	if (name == NULL || *name == '\0' || _strchr(name, '=') != NULL)
		return (-1);

	/* Vérifier si la variable existe déjà */
	index = _find_env_index(name);

	/* Si la variable existe et overwrite est 0, on ne fait rien */
	if (index >= 0 && overwrite == 0)
		return (0);

	/* Créer la nouvelle entrée name=value */
	entry_len = _strlen(name) + _strlen(value) + 2; /* +2 pour '=' et '\0' */
	new_entry = malloc(entry_len);
	if (new_entry == NULL)
		return (-1);

	sprintf(new_entry, "%s=%s", name, value);

	/* Si la variable existe, remplacer la valeur */
	if (index >= 0)
	{
		free(environ[index]);
		environ[index] = new_entry;
		return (0);
	}

	/* Compter le nombre de variables d'environnement */
	for (env_count = 0; environ[env_count] != NULL; env_count++)
		;

	/* Créer un nouveau tableau environ avec un emplacement de plus */
	new_environ = malloc((env_count + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		free(new_entry);
		return (-1);
	}

	/* Copier les anciennes variables */
	for (i = 0; i < env_count; i++)
		new_environ[i] = environ[i];

	/* Ajouter la nouvelle variable et le NULL final */
	new_environ[env_count] = new_entry;
	new_environ[env_count + 1] = NULL;

	/* Remplacer l'ancien environ par le nouveau */
	environ = new_environ;

	return (0);
}

/**
 * main - Programme de test pour _setenv
 *
 * Return: 0 en cas de succès
 */
int main(void)
{
	char *value;

	/* Tester avec une variable existante */
	value = _getenv("HOME");
	printf("HOME avant = %s\n", value ? value : "Non trouvé");

	_setenv("HOME", "/tmp", 1);
	value = _getenv("HOME");
	printf("HOME après = %s\n", value ? value : "Non trouvé");

	/* Tester l'ajout d'une nouvelle variable */
	value = _getenv("TEST_VAR");
	printf("TEST_VAR avant = %s\n", value ? value : "Non trouvé");

	_setenv("TEST_VAR", "Test Réussi", 1);
	value = _getenv("TEST_VAR");
	printf("TEST_VAR après = %s\n", value ? value : "Non trouvé");

	return (0);
}
