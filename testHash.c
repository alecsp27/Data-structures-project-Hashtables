
#include <stdio.h>
#include "tlg.h"
#include "thash.h"
#include <string.h>

typedef struct {
	char* key;
	char* value;
}TInreg;

//codHash function will get the sum of the characters and return the specific hashcode of the given element

int codHash(void * element, int M)
{
	int suma = 0, i;
	TInreg * pers = (TInreg *) element;
	char * nume = pers->key;
	for(i = 0; i < strlen(nume); i++)
	{
		suma = suma + nume[i];
	}
	suma = suma - '\0';
	return suma % M;
}

TLG citesteListaInreg(char * numeFisier, char * fisier_iesire, int M) {
	FILE *f, *out;
	char  line[200];
	size_t len = 0;
	char k = 'a';
	int w = 0;
	TLG L = NULL, el,ultim;
	TH* h = NULL;
	h = (TH *) IniTH(M, codHash);
	if(h == NULL)
		return NULL;
	//opening the read and write files
	f = fopen(numeFisier, "rt");
	if (f == NULL)
		return NULL;
	out = fopen(fisier_iesire, "a");
	if (out == NULL)
		return NULL;
	
	while (fgets(line, sizeof(line), f) != NULL) 
	{
		if(line[0]!='\n') {
		char * tip_functie = malloc(100*sizeof(char));
		tip_functie = strtok(line, " ");

		//making sure we are not having unwante charcters after using strtok

		while(tip_functie[strlen(tip_functie)-1] < 'a' || tip_functie[strlen(tip_functie)-1] > 'z') {
			tip_functie[strlen(tip_functie)-1] = '\0';
		}

		if(strcmp(tip_functie,"print")==0)
		{
			
			char * afisare = malloc(1000* sizeof(char));
			int i;
			TLG el, p;
			//parcurgem vectorul din tab hash
			for(i = 0; i < h->M ; i++) {
        	p = h->v[i];
			if(p!=NULL)
			{fprintf(out,"%d: ", i);
			//printing the index of the list
			TInreg* pers = (TInreg*)(p->info);
			strcat(afisare,pers->value);
			strcat(afisare," ");
			//getting the elements of the list and introducing them in the array
			for(el = p->urm; el != p; el = el->urm)
			{
				strcat(afisare,((TInreg*)(el->info))->value);
				strcat(afisare," ");
			}
			fputs(afisare,out);
			fputs("\n",out);}
			strcpy(afisare,"");
			}
		}
		if(strcmp(tip_functie,"put")==0)
		{
		char * key = strtok(NULL, " ");
		char * value = strtok(NULL, " ");
		TInreg * pers = malloc(sizeof(TInreg));
		if (pers == NULL)
			return L;
		pers->value = malloc(50*sizeof(char));
		pers->key = malloc(50*sizeof(char));
		//getting rid of unwanted characters for value and key
		while(key[strlen(key)-1] < 'a' || key[strlen(key)-1] > 'z') {
			key[strlen(key)-1] = '\0';
		}
		while(value[strlen(value)-1] < 46 || value[strlen(value)-1] > 57){
			value[strlen(value)-1] = '\0';
		}
		strcpy(pers->key, key);
		strcpy(pers->value, value);
		ultim = L;
		int ok = 0;
		//calling the InsTH functin in order to introduce the pers element
		InsTH(h, (void*)pers);
		}

		if(strcmp(tip_functie,"remove")==0)
		{
			int val = 0, i;
			TLG p,aux;

			//key is the element we have to remove and we get its hashcode
			char * key = strtok(NULL, " ");
			while(key[strlen(key)-1] < 'a' || key[strlen(key)-1] > 'z')
			{key[strlen(key)-1] = '\0';}
			
			for(i = 0; i < strlen(key); i++)
			{
				val = val + key[i];
			}
			val = val - '\0';
			val = val % M;
			p = h->v[val];
			
			if(h->v[val]!=NULL)
			{	
				//in case we have to delete the only element of the list we set the pointer to NULL
				
				if(strcmp(((TInreg*)(h->v[val]->info))->key,key) == 0 && p->urm == p )
				{
					h->v[val] = NULL;
					
				}
				//in case the element that has to be removed is the first one we free the memory and change the pointer
				//to the next element of the list
				else if ( strcmp(((TInreg*)(h->v[val]->info))->key,key) == 0 )
				{
					
					p->pre->urm = p->urm;
					p->urm->pre = p->pre;
					h->v[val] = p->urm;
					p->urm = NULL;
					p->pre = NULL;
					free(p->info);
					free(p);
					
				}
				else
				{	
					//going through the elements of the list until we find the element that has to be removed
					
					for(p = h->v[val]->urm; p!=h->v[val]; p = p->urm)
					{
						if( strcmp(((TInreg*)(p->info))->key,key) == 0)
						{
							p->pre->urm = p->urm;
							p->urm->pre = p->pre;
							free(p->info);
						}
					}
				}
			}
		}
		if(strcmp(tip_functie,"print_bucket")==0)
		{
			int indice = 0;
			char* afisare = malloc(1000 * sizeof(char));
			TLG p;
			char * index = strtok(NULL, " ");
			while(index[strlen(index)-1] < 46 || index[strlen(index)-1] > 57)
			{
				index[strlen(index)-1] = '\0';
			}
			//finding out the index of the list that has to be printed
			indice = atoi(index);
			if(indice < h->M)
			{
				p = h->v[indice];
				//printing the elements by going through the wanted list
				if(p!=NULL)
				{
					TInreg* pers = (TInreg*)(p->info);
					strcat(afisare,pers->value);
					strcat(afisare," ");
					for(el = p->urm; el != p; el = el->urm)
					{
						strcat(afisare,((TInreg*)(el->info))->value);
						strcat(afisare," ");
					}
					fputs(afisare, out);
					fputs("\n",out);
				}
				else
				{
					fprintf(out, "VIDA\n");
				}
			}
		}
		

		
		if(strcmp(tip_functie,"find")==0)
		{
			int val,suma = 0, i, ok = 0;
			TLG p;
			char * key = strtok(NULL, " ");
			while(key[strlen(key)-1] < 'a' || key[strlen(key)-1] > 'z') {
				key[strlen(key)-1] = '\0';
			}
			//finding the hashcode of the element that has to be found
			for(i = 0; i < strlen(key); i++)
			{
				suma = suma + key[i];
			}
			suma = suma - '\0';
			val = suma % M;
			
			//looking for the element that has to be found going through the right list

			if(h->v[val]!=NULL)
			{if(strcmp(((TInreg*)(h->v[val]->info))->key,key)==0)
			{
				fprintf(out,"True\n");
				ok = 1;
				
			}
			for(p = h->v[val]->urm; p!=h->v[val]; p = p->urm)
			{
				if(strcmp(((TInreg*)(p->info))->key,key)==0)
				{
					fprintf(out,"True\n");
					ok = 1;
					
				}
			}}
			if(ok == 0)
			fprintf(out,"False\n");

		}
		if(strcmp(tip_functie,"get")==0)
		{
			int val,suma = 0, i, ok = 0;
			TLG p;
			char * key = strtok(NULL, " ");
			while(key[strlen(key)-1] < 'a' || key[strlen(key)-1] > 'z') {
				key[strlen(key)-1] = '\0';
			}

			//finding the hashcode for key

			for(i = 0; i < strlen(key); i++)
			{
				suma = suma + key[i];
			}
			val = suma % M;
			//going through the list in order to find the wanted element
			if(h->v[val]!=NULL) {
				if(strcmp(((TInreg*)(h->v[val]->info))->key,key)==0) {
					fprintf(out,"%s\n",((TInreg*)(h->v[val]->info))->value);
					ok = 1;
				}
				for(p = h->v[val]->urm; p!=h->v[val]; p = p->urm) {
					if(strcmp(((TInreg*)(p->info))->key,key)==0)
					{
						fprintf(out,"%s\n",((TInreg*)(p->info))->value);
						ok = 1;
					
					}
				}
			}
			if(ok == 0)
			fprintf(out, "NULL\n");

		}
		
		strcpy(tip_functie,"");}
    }
	fclose(f);
	return L;
}





int main( int argc, char* argv[])
{
	//read a list of commands from a given file
	int M;
	char *fisier_intrare, *fisier_iesire;
	M = atoi(argv[1]);
	fisier_intrare = argv[2];
	fisier_iesire = argv[3];
	TLG listaInreg = citesteListaInreg(fisier_intrare, fisier_iesire, M);
	if (listaInreg == NULL) {
		printf("Lista nu a putut fi generata\n");
        return 0;
	}
	
  return 0;
}
