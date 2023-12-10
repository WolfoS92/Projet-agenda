#pragma once

#include "cell.h"
#include "list.h"

// La recherche simple en utilisant le niveau 0
t_d_cell* find_classic(t_d_list* list, int value);

// La recherche multi-niveaux
t_d_cell* find_levels(t_d_list* list, int value);