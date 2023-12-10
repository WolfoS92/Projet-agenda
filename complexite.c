

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "find.h"
#include "list.h"
#include "timer.h"


// comparer la complexite des 2 algorithmes
void compare()
{
	FILE* log_file = fopen("log.txt", "w");
	char format[] = "%d\t%s\t%s\n";

	int level;
	char* time_classic;
	char* time_levels;

	// Listes de 4 à 14 niveaux
	for (int i = 4; i < 15; i++)
	{
		// creation de la liste
		t_d_list* list = create_list_n(i);

		// nombre de cellules dans la liste
		int cells = (int)pow(2, i) - 1;

		printf("Liste de %d cellules\n", cells);

		// mesure de complexite de la recherche classique
		startTimer();
		for (int o = 0; o < 100000; o++)
		{
			int val = rand() % cells + 1;
			int var = find_classic(list, val)->value;
		}
		stopTimer();
		time_classic = getTimeAsString();

		// mesure de complexite de la recherche multi-niveaux
		startTimer();
		for (int o = 0; o < 100000; o++)
		{
			int val = rand() % cells + 1;
			int var = find_levels(list, val)->value;
		}
		stopTimer();
		time_levels = getTimeAsString();

		level = i;

		// Ajout des resultats dans le fichier log.txt
		fprintf(log_file, format, level, time_classic, time_levels);
	}

	fclose(log_file);
}

// fonction à appeler pour les parties 1 et 2
int tests()
{
	printf("Tests des fonctions\n"
		"\tcreate_list\n"
		"\tcreate_cell\n"
		"\tinsert_cell_at_head\n"
		"\tdisplay_all_levels\n"
		"\tdisplay_all_levels_aligned\n"
		"\tinsert_sorted\n\n"
	);

	// Créer une liste avec une hauteur maximale de 3 niveaux
	t_d_list* myList = create_list(3);

	// Insérer des cellules dans la liste
	t_d_cell* cell1 = create_cell(1, 0);
	t_d_cell* cell2 = create_cell(2, 1);
	t_d_cell* cell3 = create_cell(3, 0);
	t_d_cell* cell5 = create_cell(5, 2);
	t_d_cell* cell6 = create_cell(6, 1);
	t_d_cell* cell7 = create_cell(7, 0);


	insert_cell_at_head(myList, cell7);
	insert_cell_at_head(myList, cell6);
	insert_cell_at_head(myList, cell5);
	insert_cell_at_head(myList, cell3);
	insert_cell_at_head(myList, cell2);
	insert_cell_at_head(myList, cell1);

	// Afficher tous les niveaux de la liste
	display_all_levels(myList);

	// Afficher tous les niveaux de la liste, en alignant les cellules
	display_all_levels_aligned(myList);

	// Insérer une cellule triée dans la liste
	t_d_cell* cell11 = create_cell(4, 1);
	insert_sorted(myList, cell11);

	// Afficher tous les niveaux de la liste après l'insertion triée


	display_all_levels_aligned(myList);

	printf("\nTests des fonctions\n"
		"\tcreate_list_n\n\n"
	);

	t_d_list* list4 = create_list_n(4);

	display_all_levels_aligned(list4);

	printf("\nTests des fonctions\n"
		"\tfind_classic\n"
		"\tfind_levels\n\n"
	);

	// Comparaison de complexite
	compare();

	return 0;
}
