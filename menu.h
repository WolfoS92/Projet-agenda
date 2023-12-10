#pragma once

#include "agenda.h"

enum menu_choice
{
	SEARCH_CONTACT = 1,
	DISPLAY_APPOINTMENTS,
	ADD_CONTACT,
	ADD_APPOINTMENT,
	REMOVE_APPOINTMENT,
	SAVE_APPOINTMENTS,
	LOAD_APPOINTMENTS,
	COMPUTE_TIME,
	QUIT
};

enum menu_choice display_menu();
char* scan_string();
t_agenda* load_contacts();

t_appointment_list* load_appointments(t_agenda* agenda);
void save_appointments(t_appointment_list* appointments);
