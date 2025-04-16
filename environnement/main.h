#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/**
 * struct path_node - Nœud d'une liste chaînée pour les répertoires PATH
 * @directory: Chaîne contenant le chemin du répertoire
 * @next: Pointeur vers le prochain nœud
 */
typedef struct path_node
{
	char *directory;
	struct path_node *next;
} path_node_t;

char *_getenv(const char *name);
int main(int ac, char **av, char **env);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void print_env(void);

#endif

