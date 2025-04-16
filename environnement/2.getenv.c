#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

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
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *value;

	/* Test avec quelques variables courantes */
	value = _getenv("PATH");
	printf("PATH = %s\n", value ? value : "Non trouvé");

	value = _getenv("HOME");
	printf("HOME = %s\n", value ? value : "Non trouvé");

	value = _getenv("USER");
	printf("USER = %s\n", value ? value : "Non trouvé");

	/* Test avec une variable inexistante */
	value = _getenv("VARIABLE_INEXISTANTE");
	printf("VARIABLE_INEXISTANTE = %s\n", value ? value : "Non trouvé");

	return (0);
}
