#pragma once

typedef struct s_appointment
{
	char* name;
	char* object;
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int hour_duration;
	int minute_duration;

	struct s_appointment* next;
} t_appointment;

typedef struct
{
	t_appointment** list;
	int size;
} t_appointment_list;

typedef struct s_contact
{
	char* name;
	t_appointment* appointments;
	int level;
	struct s_contact** next;
} t_contact;

typedef struct s_contact_list
{
	t_contact** contacts;
	int size;
} t_contact_list;

t_contact* create_contact(char* name);
t_appointment* create_appointment(char* name, char* object, int day, int month, int year, int hour, int minute, int hour_duration, int minute_duration);
t_appointment* create_appointment_empty();
void add_appointment_contact(t_contact* contact, t_appointment* appointment);
void add_appointment_list(t_appointment_list* list, t_appointment* appointment);
void remove_appointment_contact(t_contact* contact, t_appointment* appointment);
void remove_appointment_list(t_appointment_list* list, t_appointment* appointment);

void display_appointment(t_appointment* appointment);
void display_appointments(t_appointment_list* appointment_list);
void display_appointments_by_contact(t_contact* contact);