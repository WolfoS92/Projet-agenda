

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "agenda.h"
#include "contact.h"

t_agenda* create_agenda()
{
	t_agenda* agenda = (t_agenda*)malloc(sizeof(t_agenda));
	agenda->contacts = (t_contact**)malloc(sizeof(t_contact*) * MAX_LEVEL);
	for (int i = 0; i < MAX_LEVEL; i++)
		agenda->contacts[i] = NULL;
	return agenda;
}

t_contact* search_contact_classic(t_agenda* agenda, char* name)
{
	t_contact* current = agenda->contacts[0];

	while (current)
	{
		if (strcmp(current->name, name) == 0)
			return current;

		current = current->next[0];
	}

	return NULL;
}

t_contact* search_contact_levels(t_agenda* agenda, char* name)
{
	t_contact* current = agenda->contacts[MAX_LEVEL - 1];

	for (int i = MAX_LEVEL - 1; i >= 0; i--)
	{
		t_contact* previous = NULL;

		for (int o = 0; o < 3; o++)
		{
			while (current != NULL)
			{
				if (strcmp(current->name, name) == 0)
					return current;
				if (current->name[o] > name[o])
					break;
				previous = current;
				current = current->next[i];
			}

			if (!previous || previous->name[o] != name[o])
			{
				current = agenda->contacts[i - 1];
				continue;
			}

			current = previous;
		}
	}

	return NULL;
}


// cette fonction cree une liste de tous les contact commencant par les 3 premieres lettres specifiees par name
t_contact_list* search_contact(t_agenda* agenda, char* name)
{
	t_contact* current = agenda->contacts[MAX_LEVEL - 1];

	t_contact_list* contact_list = (t_contact_list*)malloc(sizeof(t_contact_list));
	contact_list->size = 0;
	contact_list->contacts = NULL;

	while (current)
	{
		char first_letters[4] = { current->name[0], current->name[1], current->name[2], 0 };
		if (strcmp(first_letters, name) == 0)
		{
			contact_list->contacts = (t_contact**)realloc(contact_list->contacts, sizeof(t_contact*) * (contact_list->size + 1));
			contact_list->contacts[contact_list->size] = current;
			contact_list->size++;
		}

		if (current->name[0] > name[0])
			break;

		current = current->next[MAX_LEVEL - 1];
	}

	return contact_list;

}

void insert_contact_at_head(t_agenda* agenda, t_contact* contact)
{
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		contact->next[i] = agenda->contacts[i];
		agenda->contacts[i] = contact;
	}
}

void insert_contact(t_agenda* agenda, t_contact* contact)
{
	t_contact* next = agenda->contacts[MAX_LEVEL - 1];
	t_contact* current = NULL;
	t_contact* previous = NULL;

	if (!next)
	{
		insert_contact_at_head(agenda, contact);
		contact->level = 3;
		return;
	}

	// trouver le premier contact avec la meme premiere lettre || plus grande
	while (next)
	{
		if (next->name[0] > contact->name[0])
			break;
		previous = current;
		current = next;
		next = next->next[MAX_LEVEL - 1];
	}

	// si la premiere lettre de contact est plus grande que toutes les autres, inserer le contact � la fin et return
	if (!next)
	{
		for (int i = 0; i < MAX_LEVEL; i++)
		{
			contact->next[i] = current->next[i];
			current->next[i] = contact;
		}
		contact->level = 3;
		return;
	}

	// si la premiere lettre de contact est plus petite que toutes les autres, inserer le contact au debut et return
	if (!current && next->name[0] != contact->name[0])
	{
		insert_contact_at_head(agenda, contact);
		contact->level = 3;
		return;
	}

	// dans le cas ou la premiere lettre du contact est la meme que celle du premier contact
	if (!current)
		current = next;

	// Si la premiere lettre est differente, inserer le contact et return
	// car cela signifie qu'il n'y a pas de contact avec la meme premiere lettre
	if (current->name[0] != contact->name[0])
	{
		// trouver le dernier contact avec une premiere lettre plus petite aux niveaux inferieurs
		// current contient le premier contact avec une premiere lettre plus petite
		// le dernier contact (de level i) avec une premiere lettre plus petite sera le dernier avec un level de i
		t_contact* next_level = current;
		t_contact* current_level = NULL;

		contact->level = 3;

		for (int i = 0; i < 4; i++)
		{
			// trouver le dernier contact avant de changer de i-1eme lettre dans ce niveau i
			if (i) // pas besoin de reverif pour la premiere lettre, on veut seulement lier pour le niveau 3
				while (next_level)
				{
					if (next_level->name[0] > contact->name[0])
						break;
					current_level = next_level;
					next_level = next_level->next[MAX_LEVEL - 1 - i];
				}

			// comme on est arrives a la derniere cellule commencant par la meme lettre dans ce niveau, 
			// lier le niveau i a notre nouvelle cellule
			if (!current_level)
				current_level = next_level;

			current_level->next[MAX_LEVEL - 1 - i] = contact;
		}

		current_level->next[0] = contact;

		// lier notre nouveau contact au contact suivant
		for (int i = 0; i < MAX_LEVEL; i++)
			contact->next[i] = next;

		return;
	}


	// si la premiere lettre est la meme, trouver le premier contact avec la meme deuxieme lettre || plus grande
	while (next)
	{
		if (next->name[0] == contact->name[0] && next->name[1] > contact->name[1])
			break;
		if (next->name[0] != contact->name[0])
			break;
		current = next;
		next = next->next[MAX_LEVEL - 2];
	}

	// si la deuxieme lettre de contact est plus grande que toutes les autres, inserer le contact � la fin et return
	if (!next)
	{
		for (int i = 0; i < MAX_LEVEL - 1; i++)
		{
			contact->next[i] = current->next[i];
			current->next[i] = contact;
		}
		contact->level = 2;
		return;
	}

	// si la deuxieme lettre est differente, inserer le contact et return
	if (current->name[1] != contact->name[1] || current->name[0] != current->name[0])
	{
		t_contact* next_level = NULL;
		t_contact* current_level = NULL;

		// lier notre nouveau contact au contact suivant
		if (current->name[1] < contact->name[1])
		{
			next_level = current;
			contact->level = 2;
			// lier tous les niveaux sauf 3 a next
			for (int i = 0; i < MAX_LEVEL - 1; i++)
				contact->next[i] = next;
			contact->next[3] = NULL;
		}
		else
		{
			// on veut lier les contact de la lettre 0 precedents
			next_level = previous;

			// changement des niveaux
			contact->level = 3;
			current->level = 2;
			// ce niveau n'existe plus
			// lier le niveau 3 a next et le reste a current
			for (int i = 0; i < 3; i++)
				contact->next[i] = current;
			contact->next[3] = next;
			if (next_level)
				next_level->next[3] = contact;
			else
			{
				// si next_level est NULL, cela signifie que le contact est le premier de la liste
				// donc il faut le lier a la liste
				for (int i = 0; i < MAX_LEVEL; i++)
					agenda->contacts[i] = contact;
				contact->next[3] = current->next[3];
				return;
			}
			current->next[3] = NULL;
		}

		// lier les contact precedents a notre nouveau contact
		for (int i = 1; i < 4; i++)
		{
			// le niveau 0 ne bouge pas
			if (i > 1)
				while (next_level)
				{
					if (next_level->name[1] > contact->name[1])
						break;
					if (next_level->name[0] != contact->name[0])
						break;
					current_level = next_level;
					next_level = next_level->next[MAX_LEVEL - 1 - i];
				}

			// comme on est arrives a la derniere cellule commencant par la meme lettre dans ce niveau, 
			// lier le niveau i a notre nouvelle cellule
			if (!current_level)
				current_level = next_level;

			current_level->next[MAX_LEVEL - 1 - i] = contact;
		}

		current_level->next[0] = contact;

		return;
	}


	// si la deuxieme lettre est la meme, trouver le dernier contact avec la meme troisieme lettre || plus grande
	while (next)
	{
		if (next->name[0] == contact->name[0] && next->name[1] == contact->name[1] && next->name[2] > contact->name[2])
			break;
		if (next->name[1] != contact->name[1] || next->name[0] != contact->name[0])
			break;
		previous = current;
		current = next;
		next = next->next[MAX_LEVEL - 3];
	}

	// si la troisieme lettre de contact est plus grande que toutes les autres, inserer le contact � la fin et return
	if (!next)
	{
		for (int i = 0; i < MAX_LEVEL - 2; i++)
		{
			contact->next[i] = current->next[i];
			current->next[i] = contact;
		}
		contact->level = 1;
		return;
	}

	// si la troisieme lettre est plus grande, inserer le contact et return
	if (current->name[2] != contact->name[2] || current->name[1] != contact->name[1] || current->name[0] != contact->name[0])
	{
		// trouver le dernier contact avec une troisieme lettre plus petite aux niveaux inferieurs
		// current contient le premier contact avec une troisieme lettre plus petite
		// le dernier contact (de level i) avec une troisieme lettre plus petite sera le dernier avec un level de i
		t_contact* next_level = NULL;
		t_contact* current_level = NULL;

		// lier notre nouveau contact au contact suivant
		if (current->name[2] < contact->name[2])
		{
			next_level = current;
			contact->level = 1;

			// lier tous les niveaux sauf 2 et 3 a next
			for (int i = 0; i < MAX_LEVEL - 2; i++)
				contact->next[i] = next;
		}
		else
		{
			next_level = previous;

			contact->level = 2;
			current->level = 1;

			// lier le niveau 2 a next et le reste a current
			for (int i = 0; i < 2; i++)
				contact->next[i] = current;
			contact->next[2] = next;
			if (next_level)
				next_level->next[2] = contact;
			else
			{
				contact->level = 3;
				for (int i = 0; i < MAX_LEVEL; i++)
					agenda->contacts[i] = contact;
				contact->next[3] = current->next[3];
				contact->next[2] = current->next[2];
				return;
			}

			current->next[2] = NULL;
			current->next[3] = NULL;
		}

		for (int i = 2; i < 4; i++)
		{
			if (i > 2)
				while (next_level)
				{
					if (next_level->name[0] != contact->name[0])
						break;
					if (next_level->name[1] != contact->name[1])
						break;
					if (next_level->name[2] > contact->name[2])
						break;
					current_level = next_level;
					next_level = next_level->next[MAX_LEVEL - 1 - i];
				}

			// comme on est arrives a la derniere cellule commencant par la meme lettre dans ce niveau, 
			// lier le niveau i a notre nouvelle cellule
			if (!current_level)
				current_level = next_level;

			current_level->next[MAX_LEVEL - 1 - i] = contact;
		}

		current_level->next[0] = contact;

		return;
	}

	// l'ordre n'importe plus a ce niveau de ressemblance (3 premieres lettres identiques)
	contact->next[0] = current->next[0];
	current->next[0] = contact;

	contact->level = 0;
}

void display_agenda(t_agenda* agenda)
{
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		t_contact* current = agenda->contacts[i];

		printf("[list head_%d @-]--", i);

		while (current)
		{
			printf(">[ %s |@-]--", current->name);
			current = current->next[i];
		}

		printf(">NULL\n");
	}
}
