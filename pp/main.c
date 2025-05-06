#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>

#define MAX_SALI 200
#define MAX_REZERVARI 150

// Structura pentru sala
typedef struct
{
    int numar;
    int capacitate;
    char nume[50];
} Sala;

// Structura pentru rezervare
typedef struct
{
    int numar_sala;
    char client[50];
    char data[20];
    char interval[20];
} Rezervare;

Sala lista_sali[MAX_SALI];
Rezervare lista_rezervari[MAX_REZERVARI];
Sala sali[MAX_SALI];
Rezervare rezervari[MAX_REZERVARI];
int numar_sali = 0, numar_rezervari = 0;


//meniu
void afisare_header_1();
void afisare_header_2();
void afisare_header_3();
void clrscr();
int main();
int sali_f();
int rezervari_f();
int gestionare_sali();

void set_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
//Submeniuri

int sali_disponibile();
int cautare_sala();
int afisare_rezervari();

//alte functii
void incarcate_sali_din_fisier();
void incarcate_rezervari_din_fisier();
void salvare_sali_in_fisier();
void salvare_rezervari_in_fisier();
void afisare_sali();
int afisare_rezervari();
void adauga_rezervare();
void adauga_sala();
int sterge_sala();
int sterge_rezervare();
int autentificare();

int main() {
    incarcate_sali_din_fisier();
    incarcate_rezervari_din_fisier();

    set_color(7);
    printf("____________________________________________________________________________________________________                    ");
    printf("|__________________________________________________________________________________________________|                    ");
    printf("|                            |                                                                     |\n");
    printf("|          ");
    set_color(9);
    printf("Meniu");
    set_color(7);
    printf("             |                             Sali sedinta                            |\n");
    printf("|      Alege o optiune:      |                                                                     |\n");
    printf("|____________________________|_____________________________________________________________________|");
    printf("\n");
    printf("|____________________________|\n");
    printf("| ");
    set_color(9);
    printf("1");
    set_color(7);
    printf(". Sali                    |\n");
    printf("|____________________________|\n");
    printf("| ");
    set_color(9);
    printf("2");
    set_color(7);
    printf(". Rezervari               |\n");
    printf("|____________________________|\n");
    printf("| ");
    set_color(9);
    printf("3");
    set_color(7);
    printf(". Gestionare sali         |\n");
    printf("|____________________________|\n");
    printf("| ");
    set_color(9);
    printf("0");
    set_color(7);
    printf(". Iesire si salvare       |\n");
    printf("|____________________________|");
    printf("\n\n ");
    int valoare;
    while (scanf("%d", &valoare) != 1) {
        while (getchar() != '\n');
        printf("Optiune invalida! Incearca din nou: ");
    }

    if (valoare == 0) {
        return 0;
    }

    switch (valoare) {
        case 1:
            clrscr();
            sali_f();
            break;
        case 2:
            clrscr();
            rezervari_f();
            break;
        case 3:
            clrscr();
            if (autentificare()) {
                clrscr();
                gestionare_sali();
            } else {
                clrscr();
                main();
            }
            break;
        case 0:
            salvare_sali_in_fisier();
            salvare_rezervari_in_fisier();
            printf("Iesire din program.\n");
            break;
        default:
            clrscr();
            printf("Optiune invalida. Incearca din nou.\n");
            break;
    }

    return 0;
}
void clrscr()
{
    system("cls||clear");
}

int sali_f()

{
    int valoare;
    set_color(7);
    printf("\n");
    afisare_header_1("SALI\n");
    set_color(9);
    printf(" 1");
    set_color(7);
    printf(". Sali disponibile\n");
    set_color(9);
    printf(" 2");
    set_color(7);
    printf(". Cautare sala\n");
    set_color(9);
    printf(" 0");
    set_color(7);
    printf(". Revenire la meniu\n\n");
    printf(" Alege o optiune");
    printf("\n\n ");
    scanf("%d", &valoare);

    switch (valoare)
    {
    case 1:
        if(valoare == 1)
        {
            clrscr();
            afisare_sali();
        }

        break;

    case 2:
        if(valoare == 2)
        {
            clrscr();
            cautare_sala();

        }
        break;

    case 0:
        clrscr();
        return main();

    default:
        return -1;
    }
    return 1;
}

int cautare_sala()
{
    int numar_sala;
    printf("Introduceti numarul salii pe care doriti sa o cautati: ");
    scanf("%d", &numar_sala);

    int gasit = 0;
    for (int i = 0; i < numar_sali; i++)
    {
        if (sali[i].numar == numar_sala)
        {
            printf("Sala gasita:\n");
            printf("Numar sala: ");
            set_color(1);
            printf("%d\n",sali[i].numar);
            set_color(7);
            printf("Capacitate: ");
            set_color(13);
            printf("%d\n", sali[i].capacitate);
            set_color(7);
            printf("Nume sala: ");
            printf("%s\n", sali[i].nume);
            gasit = 1;
            break;
        }
    }

    if (!gasit)
    {
        printf("Sala cu numarul %d nu a fost gasita.\n", numar_sala);
    }

    printf("-------------------------------------------------------------\n");
    set_color(9);
    printf("\n1");
    set_color(7);
    printf(". Inchide\n");
    set_color(9);
    printf("0");
    set_color(7);
    printf(". Revenire la meniu\n\n");
    printf("Alege o optiune: ");
    int valoare;
    scanf("%d", &valoare);

    switch(valoare)
    {
    case 0:
        clrscr();
        sali_f();
        break;
    case 1:
        printf("Program inchis.\n");
        exit(0);
    default:
        printf("Optiune invalida. Alege din nou.\n");
        cautare_sala();
    }
}

int rezervari_f()
{
    int valoare;
    printf("\n");
    afisare_header_2("REZERVARI\n");
    set_color(9);
    printf(" 1");
    set_color(7);
    printf(". Afisare rezervari\n");
    set_color(9);
    printf(" 2");
    set_color(7);
    printf(". Rezerva sala\n");
    set_color(9);
    printf(" 0");
    set_color(7);
    printf(". Revenire la meniu\n\n");
    printf(" Alege o optiune");
    printf("\n\n ");
    scanf("%d", &valoare);

    switch (valoare)
    {
    case 1:
        if(valoare == 1)
        {
            clrscr();
            afisare_rezervari();
        }

        break;

    case 2:
        if(valoare == 2)
        {
            clrscr();
            adauga_rezervare();

        }
        break;
    case 0:
        clrscr();
        return main();

    default:
        return -1;
        break;
    }

    return 1;

}
int afisare_rezervari() {
    int alegere;
    while (1) {
        clrscr();
        set_color(7);
        if (numar_rezervari == 0) {
            printf("Nu exista rezervari.\n");
        } else {
            printf("\nLista rezervarilor:\n");
            for (int i = 0; i < numar_rezervari; i++) {
                printf("Rezervare %d:\n", i + 1);
                printf("Numar sala: ");
                set_color(1);
                printf("%d\n", rezervari[i].numar_sala);
                set_color(7);
                printf("Client: %s\n", rezervari[i].client);
                printf("Data: ");
                set_color(13);
                printf("%s\n", rezervari[i].data);
                set_color(7);
                printf("Interval orar: ");
                set_color(5);
                printf("%s\n", rezervari[i].interval);
                set_color(7);
                printf("------------------------------------------\n");
            }
        }

        printf("\n");
        set_color(9);
        printf("1");
        set_color(7);
        printf(". Inchide\n");
        set_color(9);
        printf("0");
        set_color(7);
        printf(". Revenire la meniu\n");

        printf("Alege o optiune: ");

        scanf("%d", &alegere);

        switch(alegere) {
            case 0:
                clrscr();
                rezervari_f();
            case 1:
                clrscr();
                printf("Program inchis.\n");
                exit(0);
            default:
                printf("Optiune invalida. Alege din nou.\n");
        }
    }

    return 1;
}



int gestionare_sali()
{

    int valoare;
    set_color(7);
    printf("\n");
    afisare_header_3("GESTIONARE SALI\n");
    set_color(1);
    printf(" 1");
    set_color(7);
    printf(". Adauga sala\n");
    set_color(1);
    printf(" 2");
    set_color(7);
    printf(". Sterge sala\n");
    set_color(1);
    printf(" 3");
    set_color(7);
    printf(". Sterge rezervare\n");
    set_color(1);
    printf(" 0");
    set_color(7);
    printf(". Revenire la meniu\n\n");
    printf(" Alege o optiune:\n\n ");
    scanf("%d", &valoare);

    switch (valoare)
    {
    case 1:
    {
        adauga_sala();
    }
    break;

    case 2:
    {
        sterge_sala();
    }
    break;
    case 3:
        clrscr();
        sterge_rezervare();
        break;

    case 0:
        clrscr();
        return main();
        break;

    default:
        printf(" Optiune invalida! Incearca din nou.\n");
    }


    return gestionare_sali();
}
int autentificare()
{
    char parola[20];
    const char parola_corecta[] = "admin10";

    printf("Parola pentru acces la Gestionare Sali: ");
    scanf("%s", parola);

    if (strcmp(parola, parola_corecta) == 0)
    {
        return 1;
    }
    else
    {
        printf("Parola gresita! Acces interzis.\n");
        getchar();
        getchar();
        return 0;
    }
}

void adauga_sala()
{
    if (numar_sali >= MAX_SALI)
    {
        printf("Nu mai sunt locuri pentru sali!\n");
        return;
    }

    printf("Introduceti numarul salii: ");
    scanf("%d", &sali[numar_sali].numar);
    printf("Introduceti capacitatea salii: ");
    scanf("%d", &sali[numar_sali].capacitate);

    getchar();
    printf("Introduceti numele salii: ");
    fgets(sali[numar_sali].nume, sizeof(sali[numar_sali].nume), stdin);

    sali[numar_sali].nume[strcspn(sali[numar_sali].nume, "\n")] = '\0';

    FILE *f = fopen("sali.txt", "a");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului sali.txt\n");
        return;
    }

    fprintf(f, "%d %d %s\n", sali[numar_sali].numar, sali[numar_sali].capacitate, sali[numar_sali].nume);
    fclose(f);

    numar_sali++;

    clrscr();
    printf("\nSala a fost adaugata cu succes!\n");
}

void adauga_rezervare()
{
    if (numar_rezervari >= MAX_REZERVARI)
    {
        printf("Nu se mai pot adauga rezervari.\n");
        getchar();
        clrscr();
        return;
    }

    int nr_sala, exista = 0;
    printf("Numar sala: ");
    scanf("%d", &nr_sala);
    getchar();


    for (int i = 0; i < numar_sali; i++)
    {
        if (sali[i].numar == nr_sala)
        {
            exista = 1;
            break;
        }
    }

    if (!exista)
    {
        printf("Sala nu exista.\n");
        getchar();
        clrscr();
        return ;
    }

    rezervari[numar_rezervari].numar_sala = nr_sala;

    printf("Nume client: ");
    fgets(rezervari[numar_rezervari].client, sizeof(rezervari[numar_rezervari].client), stdin);
    rezervari[numar_rezervari].client[strcspn(rezervari[numar_rezervari].client, "\n")] = '\0';

    printf("Data: ");
    fgets(rezervari[numar_rezervari].data, sizeof(rezervari[numar_rezervari].data), stdin);
    rezervari[numar_rezervari].data[strcspn(rezervari[numar_rezervari].data, "\n")] = '\0';

    printf("Interval: ");
    fgets(rezervari[numar_rezervari].interval, sizeof(rezervari[numar_rezervari].interval), stdin);
    rezervari[numar_rezervari].interval[strcspn(rezervari[numar_rezervari].interval, "\n")] = '\0';

    numar_rezervari++;

    salvare_rezervari_in_fisier();

    printf("Rezervare adaugata cu succes.\n");
    getchar();
    clrscr();
        return;


}

void afisare_sali()
{
    set_color(7);
    int valoare;

    if (numar_sali == 0)
    {
        printf("Nu sunt sali disponibile.\n");
        return;
    }

    printf("\nLista salilor disponibile:\n");
    for (int i = 0; i < numar_sali; i++)
    {
        if (sali[i].numar <= 0 || sali[i].capacitate <= 0 || sali[i].nume[0] == '\0') {
            printf("Sala %d are date invalide!\n", i + 1);
            continue;
        }

        printf("Sala ");
        set_color(1);
        printf("%d", sali[i].numar);
        set_color(7);
        printf(" Capacitate: ");
        set_color(13);
        printf("%d", sali[i].capacitate);
        set_color(7);
        printf(" Nume: %s\n", sali[i].nume);
    }


    set_color(7);
    printf("-------------------------------------------------------------\n");

    set_color(9);
    printf("\n 1");
    set_color(7);
    printf(". Inchide\n");
    set_color(9);
    printf(" 0");
    set_color(7);
    printf(". Revenire la meniu\n\n");

    printf(" Alege o optiune: ");

    while (scanf("%d", &valoare) != 1 || (valoare != 0 && valoare != 1))
    {
        while (getchar() != '\n');
        printf("Optiune invalida! Te rog alege 0 sau 1: ");
    }

    switch(valoare)
    {
    case 0:
        clrscr();
        sali_f();
        break;
    case 1:
    default:
        printf("Program inchis.\n");
        exit(0);
    }
}
void salvare_sali_in_fisier()
{
    FILE *f = fopen("sali.txt", "w");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului sali.txt\n");
        return;
    }

    for (int i = 0; i < numar_sali; i++)
    {
        fprintf(f, "%d %d %s\n", sali[i].numar, sali[i].capacitate, sali[i].nume);
    }

    fclose(f);
}


void salvare_rezervari_in_fisier() {
    FILE *f = fopen("rezervari.txt", "w");
    if (f == NULL) {
        printf("Eroare la scrierea in fisier.\n");
        return;
    }

    for (int i = 0; i < numar_rezervari; i++) {
        fprintf(f, "%d|%s|%s|%s\n",
                rezervari[i].numar_sala,
                rezervari[i].client,
                rezervari[i].data,
                rezervari[i].interval);
    }

    fclose(f);
}


void incarcate_sali_din_fisier() {
    FILE *fisier = fopen("sali.txt", "r");
    if (fisier == NULL) {
        printf("Nu s-a putut deschide fisierul sali.txt\n");
        return;
    }

    while (fscanf(fisier, "%d %d %[^\n]", &sali[numar_sali].numar, &sali[numar_sali].capacitate, sali[numar_sali].nume) == 3) {
        numar_sali++;
        if (numar_sali >= 100) break;
    }

    fclose(fisier);
}


void incarcate_rezervari_din_fisier() {
    FILE *f = fopen("rezervari.txt", "r");
    if (f == NULL) return;

    char linie[200];
    while (fgets(linie, sizeof(linie), f)) {
        char *token = strtok(linie, "|");
        if (token != NULL) rezervari[numar_rezervari].numar_sala = atoi(token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(rezervari[numar_rezervari].client, token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(rezervari[numar_rezervari].data, token);

        token = strtok(NULL, "|\n");
        if (token != NULL) strcpy(rezervari[numar_rezervari].interval, token);

        numar_rezervari++;
    }

    fclose(f);
}



int sterge_sala()
{
    int numar_de_sters;
    printf("Introduceti numarul salii de sters: ");
    scanf("%d", &numar_de_sters);

    int gasita = 0;

    for (int i = 0; i < numar_sali; i++)
    {
        if (sali[i].numar == numar_de_sters)
        {
            gasita = 1;

            sali[i] = sali[numar_sali - 1];
            numar_sali--;

            salvare_sali_in_fisier();

            printf("Sala %d a fost stearsa cu succes.\n", numar_de_sters);
            break;
        }
    }

    if (!gasita)
    {
        printf("Sala cu numarul %d nu a fost gasita.\n", numar_de_sters);
    }

    return gasita;
}
int sterge_rezervare()
{
    int nr_sala;
    char nume_client[50];
    int gasita = 0;

    printf("Introduceti numarul salii pentru rezervarea de sters: ");
    scanf("%d", &nr_sala);
    getchar();

    printf("Introduceti numele clientului: ");
    fgets(nume_client, sizeof(nume_client), stdin);
    nume_client[strcspn(nume_client, "\n")] = '\0';

    for (int i = 0; i < numar_rezervari; i++)
    {
        if (rezervari[i].numar_sala == nr_sala &&
            strcmp(rezervari[i].client, nume_client) == 0)
        {
            gasita = 1;

            rezervari[i] = rezervari[numar_rezervari - 1];
            numar_rezervari--;
            salvare_rezervari_in_fisier();
            printf("Rezervarea a fost stearsa cu succes.\n");
            break;
        }
    }

    if (!gasita)
    {
        printf("Rezervarea nu a fost gasita.\n");
    }

    return gasita;
}


void afisare_header_1(const char *titlu)
{
    printf("__________________________________\n");
    printf("              ");
    set_color(1 | (7 << 4));
    printf("%s", titlu);
    set_color(7);
    printf("|________________________________|\n\n");

}
void afisare_header_2(const char *titlu)
{
    printf("__________________________________\n");
    set_color(1);
    printf("            ");
    set_color(1 | (7 << 4));
    printf("%s", titlu);
    set_color(7);
    printf("|________________________________|\n\n");

}
void afisare_header_3(const char *titlu)
{
    printf("__________________________________\n");
    set_color(1);
    printf("         ");
    set_color(1 | (7 << 4));
    printf("%s", titlu);
    set_color(7);
    printf("|________________________________|\n\n");

}
