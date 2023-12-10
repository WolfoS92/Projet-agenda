
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "find.h"
#include "list.h"

t_d_list* create_list(int max_level)
{
	t_d_list* list = malloc(sizeof(t_d_list));
	list->heads = malloc(sizeof(t_d_cell*) * (max_level));
	list->max_level = max_level;

	for (int i = 0; i < max_level; i++)
		list->heads[i] = NULL;

	return list;
}

void insert_cell_at_head(t_d_list* list, t_d_cell* cell)
{
	if (cell->level > list->max_level)
		return;

	// Remplacer la premiere cellule par la nouvelle
	int level = cell->level;

	// Ajouter la nouvelle cellule � tous les niveaux
	for (int i = 0; i <= level; i++)
	{
		// La cellule suivante de la cellule est la cellule pr�c�dente
		cell->next[i] = list->heads[i];

		// La nouvelle tete de liste est la cellule
		list->heads[i] = cell;
	}
}

void display_level(t_d_list* list, int level)
{
	if (level > list->max_level)
		return;

	// affiche les cellules une par une
	t_d_cell* cell = list->heads[level];
	printf("[list head_%d @-]-->", level);

	while (cell)
	{
		printf("[ %2d|@-]-->", cell->value);
		cell = cell->next[level];
	}

	printf("NULL\n");
}

void display_all_levels(t_d_list* list)
{
	for (int i = 0; i < list->max_level; i++)
		display_level(list, i);
}

void display_all_levels_aligned(t_d_list* list)
{
	int cells = 0;

	// Pour chaque niveau
	for (int i = 0; i < list->max_level; i++)
	{
		t_d_cell* cell = list->heads[i];
		printf("[list head_%d @-]--", i);

		t_d_cell* prev_cell = list->heads[0];

		// Affichage normal du premier niveau
		if (!i)
		{
			while (cell)
			{
				printf(">[ %2d|@-]--", cell->value);
				cell = cell->next[i];
				cells++;
			}

			printf(">NULL\n");

			continue;
		}

		// Tenir le compte des cellules affich�es pour aligner les NULL
		int printed_cells = 0;

		// Cellules post premier niveau
		while (cell)
		{
			// Aligner avec les cellules du niveau pr�c�dent
			while (prev_cell && prev_cell->value != cell->value)
			{
				printf("-----------");
				prev_cell = prev_cell->next[0];
				printed_cells++;
			}

			if (prev_cell)
				prev_cell = prev_cell->next[0];

			printf(">[ %2d|@-]--", cell->value);
			cell = cell->next[i];

			printed_cells++;
		}

		// Remplir ce qui reste de la ligne avant que tout soit align�
		if (i)
			for (int j = printed_cells; j < cells; j++)
				printf("-----------");

		printf(">NULL\n");
	}
}

void insert_sorted(t_d_list* list, t_d_cell* cell)
{
	if (cell->level > list->max_level)
		return;

	int level = cell->level;


	// Pour chaque niveau concern�
	for (int i = 0; i <= level; i++)
	{
		t_d_cell* current = list->heads[i];
		t_d_cell* previous = NULL;

		// Trouver la cellule pr�c�dente et la cellule suivante
		while (current)
		{
			if (current->value > cell->value)
				break;

			previous = current;
			current = current->next[i];
		}

		// Ins�rer la cellule au niveau i
		if (previous)
			previous->next[i] = cell;
		else
			list->heads[i] = cell;

		cell->next[i] = current;
	}
}

t_d_list* create_list_n(int n)
{
	t_d_list* list = create_list(n); // Cr�er une liste avec n-1 lignes

	int cells = (int)pow(2, n) - 1; // Nombre de cellules � cr�er

	for (int i = cells; i >= 0; i--)
	{
		int level = 0;
		for (int k = n - 1; k >= 0; k--)
		{
			int divisor = pow(2, k);
			if (i % divisor == 0)
			{
				level = k;
				break;
			}
		}

		t_d_cell* cell = create_cell(i, level); // Cr�er une cellule

		insert_cell_at_head(list, cell); // Ins�rer la cellule dans la liste
	}

	return list;
}
