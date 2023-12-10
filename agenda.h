#pragma once

#include "contact.h"

#define MAX_LEVEL 4

typedef struct s_agenda
{
	t_contact** contacts;
} t_agenda;

t_agenda* create_agenda();
void insert_contact(t_agenda* agenda, t_contact* contact);
void insert_contact_at_head(t_agenda* agenda, t_contact* contact);

t_contact* search_contact_classic(t_agenda* agenda, char* name);
t_contact* search_contact_levels(t_agenda* agenda, char* name);
t_contact_list* search_contact(t_agenda* agenda, char* name);

void display_agenda(t_agenda* agenda);
