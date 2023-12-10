#pragma once

typedef struct s_d_cell
{
	int value;
	int level;
	struct s_d_cell** next;
} t_d_cell;

t_d_cell* create_cell(int value, int level);