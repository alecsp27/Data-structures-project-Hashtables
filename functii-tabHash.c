

#include "thash.h"

//function used to intialize the hashtable

TH* IniTH(size_t M, TFHash fh)
{
    //memory allocation of the hashtable
    TH* h = (TH *) calloc(sizeof(TH), 1);
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }
    //memory allocation for the elemnts of v
    h->v = (TLG *) calloc(M, sizeof(TLG));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }
    //setting the elements of the table
    h->M = M;
    h->fh = fh;
    return h;
}

//this function generates the hashcode and calls the list insertion function

int InsTH(TH*a, void* ae)
{
    int cod = a->fh(ae, a->M), rez;
    TLG el,p,aux;
    p = a->v[cod];
    rez = InsLG(a->v+cod, ae);
    return rez;
}
