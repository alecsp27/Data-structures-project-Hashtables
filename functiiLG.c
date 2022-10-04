
#include "tlg.h"
typedef struct {
	char* key;
	char* value;
}TInreg;

int InsLG(TLG* aL, void* ae)
{
	TLG aux = malloc(sizeof(TCelulaG));
	TLG el;
	int ok = 0;
	if(!aux)
	    return 0;
	//checking if the element we want to insert isn't already in the list	
	if(*aL !=NULL)
    {	
		//comparing the element that has to be added with the first element of the list
		
        if (strcmp(((TInreg*)((*aL)->info))->key, ((TInreg*)(ae))->key) == 0)
            {
	            return 0;    
            }
		//in the case we are having more than an element in the list we assure we don't add a duplicate	

    	if((*aL)->urm !=NULL)
    	{
    		for(el = (*aL)->urm; el != (*aL); el = el->urm) {
        		if (strcmp(((TInreg*)(el->info))->key, ((TInreg*)(ae))->key) == 0)
            	{
	            	return 0;    
            	}
            
    		}
    	}
    }
	//in case the new element is not already in the list we create aux
	
	aux->info = ae;
	aux->urm = NULL;
	aux->pre = NULL;

	//if the list is empty aux will become the first element of the list by changing the pointer
	
	if(*aL == NULL)
	{
		aux->urm = aux;
		aux->pre = aux;
		*aL= aux;
	}
	else
	{
		//we check if the element added can be placed first, following the lexicographic order
		if(strcmp(((TInreg*)ae)->key,((TInreg*)((*aL)->info))->key) < 0) 
		{
			aux->pre = (*aL)->pre;
			aux->urm = *aL;
			(*aL)->pre->urm = aux;
			(*aL)->pre = aux;
			*aL = aux;
		}
		//the case where the list has only one element
		if(strcmp(((TInreg*)ae)->key,((TInreg*)((*aL)->info))->key) > 0) 
		{
			TLG p;
			if((*aL)->urm == *aL)
			{
				aux->pre = (*aL)->pre;
				aux->urm = *aL;
				(*aL)->urm = aux;
				(*aL)->pre = aux;
				ok = 1;

			}
			//if none of the above cases was true we add the new element in the correct place by
			//going through the elements of the list
			for(p = (*aL)->urm; p != (*aL); p = p->urm)
			{
				if(strcmp(((TInreg*)ae)->key,((TInreg*)(p->info))->key) < 0)	
				{
					aux->pre = p->pre;
					aux->urm = p;
					p->pre->urm = aux;
					p->pre = aux;
					ok = 1;
					return 1;
				}
			}
			//the case when the new element is added at the end of the list
			if(ok == 0)
			{
				p->pre->urm = aux;
				aux->pre = p->pre;
				p->pre = aux;
				aux->urm = p;
				
	
			}
		}
		
	
	}
	return 1;
}