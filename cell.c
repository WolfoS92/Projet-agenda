

#include <stdlib.h>

#include "cell.h"

t_d_cell* create_cell(int value, int level)
{
	t_d_cell* cell = malloc(sizeof(t_d_cell));
	cell->value = value;
	cell->level = level;
	cell->next = malloc(sizeof(t_d_cell*) * level);

	for (int i = 0; i < level; i++)
		cell->next[i] = NULL;

	return cell;
}