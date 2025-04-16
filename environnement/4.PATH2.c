#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 * add_node_end - Ajoute un nouveau nœud à la fin de la liste
 * @head: Pointeur vers le premier nœud
 * @directory: Répertoire à stocker dans le nouveau nœud
 *
 * Return: Adresse du nouveau nœud, NULL en cas d'échec
 */
path_node_t *add_node_end(path_node_t **head, char *directory)
{
	path_node_t *new_node, *last;

	if (head == NULL || directory == NULL)
		return (NULL);

	/* Créer un nouveau nœud */
	new_node = malloc(sizeof(path_node_t));
	if (new_node == NULL)
		return (NULL);

	/* Dupliquer la chaîne du répertoire */
	new_node->directory = strdup(directory);
	if (new_node->directory == NULL)
	{
		free(new_node);
		return (NULL);
	}

	new_node->next = NULL;

	/* Si la liste est vide, le nouveau nœud devient la tête */
	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}

	/* Sinon, ajouter à la fin de la liste */
	last = *head;
	while (last->next != NULL)
		last = last->next;

	last->next = new_node;
	return (new_node);
}

/**
 * build_path_list - Construit une liste chaînée des répertoires PATH
 *
 * Return: Pointeur vers la tête de la liste, NULL en cas d'échec
 */
path_node_t *build_path_list(void)
{
	char *path, *path_copy, *dir;
	path_node_t *head = NULL;

	/* Récupérer la variable d'environnement PATH */
	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);

	/* Dupliquer la chaîne PATH pour manipulation */
	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	/* Découper la chaîne PATH en répertoires */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		/* Ajouter chaque répertoire à la liste chaînée */
		if (add_node_end(&head, dir) == NULL)
		{
			/* En cas d'échec, libérer la liste et sortir */
			free_path_list(head);
			free(path_copy);
			return (NULL);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (head);
}

/**
 * free_path_list - Libère la mémoire utilisée par la liste chaînée
 * @head: Pointeur vers la tête de la liste
 */
void free_path_list(path_node_t *head)
{
	path_node_t *current, *next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->directory);
		free(current);
		current = next;
	}
}

/**
 * print_path_list - Affiche tous les répertoires dans la liste chaînée
 * @head: Pointeur vers la tête de la liste
 */
void print_path_list(const path_node_t *head)
{
	const path_node_t *current = head;
	int i = 0;

	while (current != NULL)
	{
		printf("[%d] %s\n", i++, current->directory);
		current = current->next;
	}
}

/**
 * main - Programme principal pour tester la fonction
 *
 * Return: 0 si succès, 1 si échec
 */
int main(void)
{
	path_node_t *path_list;

	/* Construire la liste chaînée */
	path_list = build_path_list();
	if (path_list == NULL)
	{
		fprintf(stderr, "Failed to build PATH list\n");
		return (1);
	}

	/* Afficher la liste */
	printf("PATH directories:\n");
	print_path_list(path_list);

	/* Libérer la mémoire */
	free_path_list(path_list);

	return (0);
}
