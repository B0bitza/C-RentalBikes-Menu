#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define red_color    "\x1b[31m"
#define green_color   "\x1b[32m"
#define yellow_color  "\x1b[33m"
#define blue_color    "\x1b[34m"
#define magenta_color "\x1b[35m"
#define cyan_color    "\x1b[36m"
#define reset_color   "\x1b[0m"
#define orange_color  "\x1b[38;5;208m"

typedef struct Client {
	char *bicicleta;
	char *zona;
	int nr;
	struct Client *urmatorul;
}node;

node *linkedlist(node *head, char *bicicleta, char *zona, int nr)
{
	node *p, *q;
	p = (node*)malloc(sizeof(node));
	p->bicicleta = (char*)malloc(strlen(bicicleta) + 1);
	p->zona = (char*)malloc(strlen(zona) + 1);
	strcpy(p->bicicleta, bicicleta);
	strcpy(p->zona, zona);
	p->nr = nr;
	p->urmatorul = NULL;
	if (p == NULL || p->bicicleta == NULL)
	{
		printf(red_color "Aloca memoria cum trebuie!" reset_color);
		exit(0);
	}

	if (head == NULL)
		return p;
	else
	{
		if (strcmp(head->bicicleta, p->bicicleta) > 0)
		{
			p->urmatorul = head;
			return p;
		}
		else
		{
			q = head;
			while (q->urmatorul != NULL && strcmp(q->urmatorul->bicicleta, p->bicicleta) < 0)
				q = q->urmatorul;
			p->urmatorul = q->urmatorul;
			q->urmatorul = p;
			return head;
		}
	}
}

node *citire_fisier(node *head)
{
	FILE *f;
	char bicicleta[30], zona[30];
	int nr;
	head = NULL;
	f = fopen("bicicleta.txt", "rt");
	if(f == NULL)
		puts(red_color "Eroare la deschiderea fisierului!" reset_color);
	else
		{
			while(fscanf(f, "%s", bicicleta) != EOF)
			{
				fscanf(f, "%s %d", zona, &nr);
				head = linkedlist(head, bicicleta, zona, nr);
			}
		}
	fclose(f);
	return head;
}

void salveaza_fisier(node *head)
{
	node *p;
	FILE *f;
	f = fopen("bicicleta.txt", "wt");
	if(f == NULL)
		puts(red_color "Eroare la deschiderea sau la crearea fisierului!" reset_color);
	else
		{
			p = head;
			while(p != NULL){
				fprintf(f, "%s %s %d \n", p->bicicleta, p->zona, p->nr);
				p = p->urmatorul;
			}
			fclose(f);
		}
}

void afisare(node *head)
{
	node *p;
	for (p = head; p != NULL; p = p->urmatorul)
		printf(orange_color "Tip bicicleta: %s\nZona: %s\nNr: %d\n\n" reset_color, p->bicicleta, p->zona, p->nr);
}

void adaugare_b(node *head,char s[30],char s1[30])
{
	node *p;
	for (p = head; p != NULL; p = p->urmatorul)
	{
		if (strcmp(s, p->bicicleta) == 0 && strcmp(s1, p->zona) == 0)
			p->nr += 1;
	}
}

void inchiriaza_b(node *head,char s[30],char s1[30])
{
	node *p;
	for (p = head; p != NULL; p = p->urmatorul)
	{
		if (strcmp(s, p->bicicleta) == 0 && strcmp(s1, p->zona) == 0)
			p->nr -= 1;
	}
}

void cautare_nume(node *head, char s[30])
{
	node *p;
	for (p = head; p != NULL; p = p->urmatorul)
		if (strcmp(p->bicicleta,s) == 0)
			printf(orange_color "Tip bicicleta: %s\nZona: %s\nNr: %d\n\n" reset_color, p->bicicleta, p->zona, p->nr);
}

void cautare_zona(node *head, char nr[30])
{
	node *p;
	for (p = head; p != NULL; p = p->urmatorul)
		if (strcmp(p->zona, nr) == 0)
			printf(orange_color "Tip bicicleta: %s\nZona: %s\nNr: %d\n\n" reset_color, p->bicicleta, p->zona, p->nr);
}

void timer(){
   int h=10,m=0,s=0;
   system("clear");
   printf(orange_color "Timp ramas: %d:%d%d:%d%d\n" reset_color,h,m,m,s,s);
   sleep(1);
   system("clear");
   while(h>0)
   {
      while(m>0)
      {
         while(s>0)
         {
            printf(orange_color "Timp ramas: %d:%d:%d\n" reset_color,h,m,s);
            s--;
            sleep(1);
            system("clear");
         }
         m--;
         s=59;
      }
      h--;
      m=59;
      s=59;
   }
}

int main() {
	node *head;
	int x,nr,nr1,nr2;
	char bicicleta[30],zona[30],a[30],s[30],s1[30], s2[30], s3[30];
	head = NULL;
	do
	{
		puts(green_color "/=================================================================\\" reset_color);
        puts(green_color "               Sistem pentru rezervarea bicicletelor               " reset_color);
        puts(green_color "/=================================================================\\" reset_color);
		puts("");
		puts(yellow_color "Apasa 1 pentru a vedea bicicletele disponibile" reset_color);
        puts(yellow_color "Apasa 2 pentru a adauga bicicleta" reset_color);
        puts(yellow_color "Apasa 3 pentru a inchiria bicicleta" reset_color);
		puts(yellow_color "Apasa 4 pentru a returna bicicleta" reset_color);
        puts(yellow_color "Apasa 5 pentru a cauta bicicleta dupa nume" reset_color);
        puts(yellow_color "Apasa 6 pentru a cauta bicicleta dupa zona" reset_color);
        puts(yellow_color "Apasa 7 pentru a salva bicicletele in fisier" reset_color);
        puts(red_color "Apasa 0 pentru a iesi" reset_color);
		printf(cyan_color "Tasta: " reset_color);
		if (scanf("%d", &x) != 1)
		{
			printf(red_color "Eroare!" reset_color);
			exit(0);
		}
		switch (x)
		{
        case 1:
            head = citire_fisier(head);
			printf("\n");
			salveaza_fisier(head);
            afisare(head);
            break;
		case 2:
			head = citire_fisier(head);
			printf(orange_color "Tip bicicleta: " reset_color);
			scanf("%s", s1);
			printf(orange_color "Zona: " reset_color);
			scanf("%s", s2);
			adaugare_b(head,s1,s2);
			salveaza_fisier(head);
			puts(green_color "Felicitari! Bicicleta a fost adaugata cu succes!\n" reset_color);
			break;
		case 3:
			head = citire_fisier(head);
			printf(orange_color "Tip bicicleta: " reset_color);
			scanf("%s", s1);
			printf(orange_color "Zona: " reset_color);
			scanf("%s", s2);
			inchiriaza_b(head,s1,s2);
			salveaza_fisier(head);
			puts(green_color "Felicitari! Tocmai ati inchiriat o bicicleta, aveti 10 ore la dispozitie sa o returnati!" reset_color);
			puts("");
			puts(green_color "Apasa 1 pentru a continua" reset_color);
			puts(red_color "Apasa 2 pentru a vedea timpul ramas" reset_color);
			printf(cyan_color "Tasta: " reset_color);
			scanf("%d", &nr2);
			switch(nr2){
				case 1:
					break;
				case 2:
					timer();
					break;
				default:
					printf("Eroare!");
					break;
			}
			break;
		case 4:
			head = citire_fisier(head);
			printf(orange_color "Tipul bicicletei: " reset_color);
			scanf("%s", s1);
			printf(orange_color "Zona: " reset_color);
			scanf("%s", s2);
			adaugare_b(head,s1,s2);
			salveaza_fisier(head);
			puts(green_color "Felicitari! Bicicleta a fost returnata cu succes!\n" reset_color);
			break;
		case 5:
			head = citire_fisier(head);
			printf(orange_color "Tipul bicicletei: " reset_color);
			scanf("%s", s);
			printf("\n");
			cautare_nume(head, s);
			break;
		case 6:
			head = citire_fisier(head);
			printf(orange_color "Zona din care vrei sa ridici bicicleta: " reset_color);
			scanf("%s", a);
			printf("\n");
			cautare_zona(head, a);
			break;
		case 7:
			head = citire_fisier(head);
			salveaza_fisier(head);
			puts(green_color "Datele au fost salvate cu succes!\n" reset_color);
            break;
        case 0:
            exit(0);
            break;
		default:
			printf(red_color "Invalid alege din nou!" reset_color);
			break;
		}
		puts(green_color "Apasa 1 pentru a reveni la meniul principal" reset_color);
		puts(red_color "Apasa 0 pentru a iesi" reset_color);
		printf(cyan_color "Tasta: " reset_color);
		scanf("%d", &nr1);
		printf("\n");
		if(nr1 ==  0)
			exit(0);
	} while (1);
	return 0;
}