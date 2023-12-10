
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "agenda.h"
#include "menu.h"
#include "timer.h"

int main()
{
	printf("Chargement des contact, veuillez patienter...\n");
	t_agenda* contacts = load_contacts();
	t_appointment_list* appointments = load_appointments(contacts);

	while (1)
	{

		enum menu_choice choice = display_menu();
		switch (choice)
		{
		case SEARCH_CONTACT:
		{
			printf("Veuillez entrer le nom exact du contact, ou entrez 3 lettres pour afficher les contacts correspondants\n");
			char* name = scan_string();
			if (strlen(name) == 3)
			{
				t_contact_list* contact_list = search_contact(contacts, name);
				if (contact_list->size)
				{
					printf("Contacts trouves:\n");
					for (int i = 0; i < contact_list->size; i++)
					{
						printf("%s\n", contact_list->contacts[i]->name);
					}

				}
				else
				{
					printf("Aucun contact trouve\n");
				}
			}
			else
			{
				t_contact* contact = search_contact_classic(contacts, name);
				if (contact)
				{
					printf("Contact trouve: %s\n", contact->name);
				}
				else
				{
					printf("Contact non trouve\n");
				}
			}
			break;
		}
		case DISPLAY_APPOINTMENTS:
		{
			printf("Entrez le nom du contact dont vous voulez connaitre les rendez-vous : \n");
			char* name = scan_string();
			t_contact* contact = search_contact_classic(contacts, name);
			if (contact)
			{
				display_appointments_by_contact(contact);
			}
			else
			{
				printf("Contact non trouve\n");
			}
			break;
		}
		case ADD_CONTACT:
		{
			printf("Entrez le nom de famille : ");
			char* last_name = scan_string();
			printf("Entrez le prenom : ");
			char* first_name = scan_string();

			for (int i = 0; i < strlen(last_name); i++)
				last_name[i] = tolower(last_name[i]);
			for (int i = 0; i < strlen(first_name); i++)
				first_name[i] = tolower(first_name[i]);

			char* name = (char*)malloc(sizeof(char) * (strlen(last_name) + strlen(first_name) + 2));
			strcpy(name, last_name);
			strcat(name, "_");
			strcat(name, first_name);

			t_contact* contact = create_contact(name);
			insert_contact(contacts, contact);

			FILE* file = fopen("contacts.txt", "a");
			fprintf(file, "%s\n", name);
			fclose(file);

			break;
		}
		case ADD_APPOINTMENT:
		{
			printf("Entrez le nom du contact : ");
			char* name = scan_string();
			printf("Entrez le sujet du rendez-vous : ");
			char* object = scan_string();
			printf("Entrez la date du rendez-vous (jj/mm/aaaa) : ");
			char* date = scan_string();
			printf("Entrez l'heure du rendez-vous (hh:mm) : ");
			char* hour = scan_string();
			printf("Entrez la duree du rendez-vous (hh:mm) : ");
			char* duration = scan_string();

			char* day = strtok(date, "/");

			char* month = strtok(NULL, "/");
			char* year = strtok(NULL, "/");
			char* hour_start = strtok(hour, ":");
			char* minute_start = strtok(NULL, ":");
			char* hour_duration = strtok(duration, ":");
			char* minute_duration = strtok(NULL, ":");
			t_appointment* appointment = create_appointment(name, object, atoi(day), atoi(month), atoi(year), atoi(hour_start), atoi(minute_start), atoi(hour_duration), atoi(minute_duration));

			t_contact* contact = search_contact_classic(contacts, name);
			if (!contact)
			{
				contact = create_contact(name);
				insert_contact(contacts, contact);
			}
			add_appointment_contact(contact, appointment);
			add_appointment_list(appointments, appointment);

			break;
		}
		case REMOVE_APPOINTMENT:
		{
			printf("Entrez le nom du contact : ");
			char* name = scan_string();
			t_contact* contact = search_contact_classic(contacts, name);
			if (!contact)
			{
				printf("Contact non trouve\n");
				break;
			}

			printf("Voici les rendez-vous de ce contact :\n");
			display_appointments_by_contact(contact);

			printf("Entrez l'index du rendez-vous : ");
			int index = 0;
			scanf(" %d", &index);
			t_appointment* appointment = contact->appointments;
			for (int i = 0; i < index; i++)
			{
				if (!appointment)
				{
					printf("Rendez-vous non trouve\n");
					break;
				}
				appointment = appointment->next;
			}
			remove_appointment_contact(contact, appointment);
			remove_appointment_list(appointments, appointment);
			free(appointment);
			break;
		}
		case SAVE_APPOINTMENTS:
			save_appointments(appointments);
			printf("Rendez-vous sauvegardes dans appointments.txt\n");
			break;
		case LOAD_APPOINTMENTS:
			appointments = load_appointments(contacts);
			printf("Rendez-vous charges depuis appointments.txt\n");
			break;
		case COMPUTE_TIME:
		{
			// j'ai pas fait mon insertion de la bonne façon pour tester les differentes techniques demandees,
				// donc je fais un test de recherche a la place
			printf("Entrez le nom du contact : ");
			char* name = scan_string();

			printf("comparaison de la recherche de contacts sur 1 niveau et sur 4 niveaux pour 100000 recherches\n");
			startTimer();
			for (int i = 0; i < 100000; i++)
			{
				search_contact_classic(contacts, name);
			}
			stopTimer();
			displayTime();
			startTimer();
			for (int i = 0; i < 100000; i++)
			{
				search_contact_levels(contacts, name);
			}
			stopTimer();
			displayTime();
			break;
		case QUIT:
			return 0;
		default:
			break;
		}
		}
	}
}