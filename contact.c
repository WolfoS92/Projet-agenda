

#include <stdlib.h>
#include <string.h>

#include "contact.h"

#define MAX_LEVEL 4

t_contact* create_contact(char* name)
{
	t_contact* contact = (t_contact*)malloc(sizeof(t_contact));
	contact->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(contact->name, name);
	contact->appointments = NULL;
	contact->level = 0;
	contact->next = (t_contact**)malloc(sizeof(t_contact*) * MAX_LEVEL);
	return contact;
}

t_appointment* create_appointment(char* name, char* object, int day, int month, int year, int hour, int minute, int duration_hours, int duration_minutes)
{
	t_appointment* appointment = (t_appointment*)malloc(sizeof(t_appointment));
	appointment->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(appointment->name, name);
	appointment->object = (char*)malloc(sizeof(char) * (strlen(object) + 1));
	strcpy(appointment->object, object);
	appointment->day = day;
	appointment->month = month;
	appointment->year = year;
	appointment->hour = hour;
	appointment->minute = minute;
	appointment->hour_duration = duration_hours;
	appointment->minute_duration = duration_minutes;
	appointment->next = NULL;
	return appointment;
}

t_appointment* create_appointment_empty()
{
	t_appointment* appointment = (t_appointment*)malloc(sizeof(t_appointment));
	appointment->name = NULL;
	appointment->object = NULL;
	appointment->day = 0;
	appointment->month = 0;
	appointment->year = 0;
	appointment->hour = 0;
	appointment->minute = 0;
	appointment->hour_duration = 0;
	appointment->minute_duration = 0;
	appointment->next = NULL;
	return appointment;
}

void add_appointment_contact(t_contact* contact, t_appointment* appointment)
{
	t_appointment* current = contact->appointments;
	while (current)
	{
		if (current->next == NULL)
			break;
		current = current->next;
	}

	if (current)
		current->next = appointment;
	else
		contact->appointments = appointment;
}

void add_appointment_list(t_appointment_list* list, t_appointment* appointment)
{
	list->list = (t_appointment**)realloc(list->list, sizeof(t_appointment*) * (list->size + 1));
	list->list[list->size] = appointment;
	list->size++;
}

void remove_appointment_contact(t_contact* contact, t_appointment* appointment)
{
	t_appointment* current = contact->appointments;
	t_appointment* previous = NULL;

	while (current)
	{
		if (current == appointment)
		{
			if (previous)
				previous->next = current->next;
			else
				contact->appointments = current->next;
			break;
		}
		previous = current;
		current = current->next;
	}
}

void remove_appointment_list(t_appointment_list* list, t_appointment* appointment)
{
	for (int i = 0; i < list->size; i++)
	{
		if (list->list[i] == appointment)
		{
			for (int j = i; j < list->size - 1; j++)
				list->list[j] = list->list[j + 1];
			list->size--;
			break;
		}
	}
}

void display_appointment(t_appointment* appointment)
{
	printf("Appointment: %s\n", appointment->name);
	printf("Object: %s\n", appointment->object);
	printf("Date: %d/%d/%d\n", appointment->day, appointment->month, appointment->year);
	printf("Time: %d:%d\n", appointment->hour, appointment->minute);
	printf("Duration: %d:%d\n", appointment->hour_duration, appointment->minute_duration);
}

void display_appointments_by_contact(t_contact* contact)
{
	t_appointment* current = contact->appointments;

	while (current)
	{
		display_appointment(current);
		current = current->next;
	}
}

void display_appointments(t_appointment_list* appointment_list)
{
	if (!appointment_list)
		printf("No appointment found.\n");
	return;
	t_appointment* current = appointment_list->list;

	while (current)
	{
		display_appointment(current);
		current = current->next;
	}
}