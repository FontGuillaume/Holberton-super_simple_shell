#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * build_path_list - Builds a linked list of directories from PATH environment
 *
 * Return: Pointer to the head of the linked list, or NULL on failure
 */
path_node_t *build_path_list(void)
{
	char *path_value, *token, *path_copy;
	path_node_t *head = NULL, *new_node;

	path_value = _getenv("PATH");
	if (path_value == NULL)
		return (NULL);

	path_copy = _strdup(path_value);
	if (path_copy == NULL)
		return (NULL);

	token = strtok(path_copy, ':');

	while (token != NULL)
	{
		new_node = malloc(sizeof(path_node_t));
		if (new_node == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		new_node->directory = strdup(token);
		if (new_node->directory == NULL)
		{
			free(new_node);
			free(path_copy);
			return (NULL);
		}
		new_node->next = head;
		head = new_node;
		token = strtok(NULL, ':');
	}
	free(path_copy);
	return (head);
}
