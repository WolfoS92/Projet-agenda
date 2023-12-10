#include <stdlib.h>

#include "cell.h"
#include "find.h"
#include "list.h"

t_d_cell* find_classic(t_d_list* list, int value)
{
	t_d_cell* current = list->heads[0];

	// on itere sur la liste jusqu'a trouver la valeur ou arriver a la fin
	while (current != NULL)
	{
		if (current->value == value)
			return current;
		current = current->next[0];
	}
	return NULL;
}

t_d_cell* find_levels(t_d_list* list, int value)
{
	int level = list->max_level - 1;
	t_d_cell* current = list->heads[level];


	// on itere sur la liste en partant du niveau max
	for (int i = level; i >= 0; i--)
	{
		t_d_cell* previous = NULL;

		// on itere sur le niveau courant jusqu'a trouver la valeur ou arriver a la fin
		// ou jusqu'a trouver une valeur plus grande que la valeur recherchee
		while (current != NULL)
		{
			// trouve
			if (current->value == value)
				return current;
			if (current->value > value)
				break;
			previous = current;
			current = current->next[i];
		}

		// si on a trouve une valeur plus grande que la valeur recherchee
		// ou si on est arrives a la fin
		if (!previous || previous->value > value)
		{
			// on descend d'un niveau
			current = list->heads[i - 1];
			continue;
		}

		// on descend d'un niveau et on repart de la valeur precedente
		current = previous;
	}

	// pas trouve
	return NULL;
}
