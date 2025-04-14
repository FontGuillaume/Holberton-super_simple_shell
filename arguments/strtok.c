#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * split_string - Splits a string into an array of words.
 * @str: The input string to be split.
 *
 * Return: A pointer to an array of strings (words),
 * or NULL if an error occurs.
 */
char **split_string(char *str)
{
	char **array;
	char *token;
	int i = 0;
	int words = 0;
	char *tmp;

	if (str == NULL)
		return (NULL);

	/* Première passe : compter les mots */
	tmp = strdup(str);
	token = strtok(tmp, " \t\n");

	while (token != NULL)
	{
		words++;
		token = strtok(NULL, " \t\n");
	}
	free(tmp);
	/* Allouer l'array */
	array = malloc(sizeof(char *) * (words + 1));

	if (array == NULL)
		return (NULL);
	/* Deuxième passe : remplir l'array */
	token = strtok(str, " \t\n");
	while (token != NULL)
	{
		array[i++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	array[i] = NULL;
	return (array);
}

/**
 * main - Test the split_string function
 *
 * Return: 0 on success
 */
int main(void)
{
	char str[] = "Hello world this is a test";
	char **words;
	int i;

	words = split_string(str);
	if (words == NULL)
	{
		printf("Error: split_string failed\n");
		return (1);
	}

	printf("Words from the string:\n");
	for (i = 0; words[i] != NULL; i++)
	{
		printf("%d: %s\n", i, words[i]);
		free(words[i]);  /* Free each word */
	}
	free(words);  /* Free the array */

	return (0);
}
