#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "agenda.h"
#include "contact.h"
#include "menu.h"

enum menu_choice display_menu()
{
    enum menu_choice choice = 0;
    printf("1. Trouver un contact\n");
    printf("2. Afficher les rdv d'un contact\n");
    printf("3. Ajouter un contact\n");
    printf("4. Ajouter un rendez-vous\n");
    printf("5. Supprimer un rendez-vous\n");
    printf("6. Sauvegarder les rendez-vous\n");
    printf("7. Charger les rendez-vous\n");
    printf("8. Comparer les algos\n");
    printf("9. Quitter\n");

    do {
        printf("Entrez votre choix : ");
        scanf(" %d", &choice);
    } while (choice < 1 || choice > 9);
    return choice;
}

char* scan_string()
{
    char* buffer = (char*)malloc(sizeof(char) * 100);
    scanf("%s", buffer);
    char* string = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(string, buffer);
    return string;
}

t_agenda* load_contacts()
{
    t_agenda* agenda = create_agenda();
    FILE* file = fopen("contacts.txt", "r");
    if (file)
    {
        char buffer[100];
        while (fgets(buffer, 100, file))
        {
            char* name = strtok(buffer, "\n");
            t_contact* contact = create_contact(name);
            insert_contact(agenda, contact);
        }
        fclose(file);
    }
    return agenda;
}

/* structure d'un rendez-vous dans le fichier
 * nom du contact
 * date (jj/mm/aaaa)
 * heure (hh:mm)
 * duree (hh:mm)
 * description
 */
// nom;jj/mm/aaaa;hh:mm;hh:mm;description\n
t_appointment_list* load_appointments(t_agenda* agenda)
{
    t_appointment_list* list = (t_appointment_list*)malloc(sizeof(t_appointment_list));
    list->list = NULL;
    list->size = 0;

    FILE* file = fopen("appointments.txt", "r");

    // creation du fichier s'il n'existe pas
    if (!file)
    {
        file = fopen("appointments.txt", "w");
    }

    // iteration sur toutes les lignes
    char buffer[1000];
    while (fgets(buffer, 1000, file))
    {
        // Creation d'un rendez-vous pour chaque ligne
        list->list = (t_appointment**)realloc(list->list, sizeof(t_appointment*) * (list->size + 1));
        list->list[list->size] = create_appointment_empty();

        int counter = 0;

        char* name = strtok(buffer, ";"); counter += strlen(name) + 1;

        // Recherche/creation du contact associe
        t_contact* contact = search_contact_classic(agenda, name);
        if (!contact)
        {
            contact = create_contact(name);
            insert_contact(agenda, contact);
        }
        add_appointment_contact(contact, list->list[list->size]);

        list->list[list->size]->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(list->list[list->size]->name, name);

        list->list[list->size]->day = atoi(strtok(buffer + counter, "/")); counter += 3;
        list->list[list->size]->month = atoi(strtok(buffer + counter, "/")); counter += 3;
        list->list[list->size]->year = atoi(strtok(buffer + counter, ";")); counter += 5;

        list->list[list->size]->hour = atoi(strtok(buffer + counter, ":")); counter += 3;
        list->list[list->size]->minute = atoi(strtok(buffer + counter, ";")); counter += 3;
        list->list[list->size]->hour_duration = atoi(strtok(buffer + counter, ":")); counter += 3;
        list->list[list->size]->minute_duration = atoi(strtok(buffer + counter, ";")); counter += 3;
        char* object = strtok(buffer + counter, "\n"); counter += strlen(object) + 1;
        list->list[list->size]->object = (char*)malloc(sizeof(char) * strlen(buffer + counter) + 1);
        strcpy(list->list[list->size]->object, object);
        list->list[list->size]->next = NULL;

        list->size++;
    }

    fclose(file);

    return list;
}

void save_appointments(t_appointment_list* appointments)
{
    FILE* file = fopen("appointments.txt", "wb");
    for (int i = 0; i < appointments->size; i++)
    {
        fprintf(file, "%s;%02d/%02d/%04d;%02d:%02d;%02d:%02d;%s\n",
                appointments->list[i]->name,
                appointments->list[i]->day,
                appointments->list[i]->month,
                appointments->list[i]->year,
                appointments->list[i]->hour,
                appointments->list[i]->minute,
                appointments->list[i]->hour_duration,
                appointments->list[i]->minute_duration,
                appointments->list[i]->object);
    }
    fclose(file);
}
