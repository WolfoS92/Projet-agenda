#pragma once

#include "cell.h"

typedef struct s_d_list 
{
	t_d_cell** heads;
	int max_level;
} t_d_list;

t_d_list* create_list(int max_level);
void insert_cell_at_head(t_d_list* list, t_d_cell* cell);
void display_level(t_d_list* list, int level);
void display_all_levels(t_d_list* list);
void display_all_levels_aligned(t_d_list* list);
void insert_sorted(t_d_list* list, t_d_cell* cell);

// Creer une liste de n niveaux
t_d_list* create_list_n(int n);