/*GHILESCU TEODOR-ANDREI 314CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
//aloca memoria pentru lista generica
TLista Aloca(void *x, size_t d){
	TLista aux;
	aux = malloc(sizeof(Celula));
	if(!aux)
		return NULL;
	aux->info = malloc(d);
	if(!aux->info){
		free(aux);
		return NULL;
	}
	memcpy(aux->info, x, d);
	aux->urm = NULL;
	return aux;
}
//scoate discul din varful stive
void Pop(ALista S, ALista disc){
	*disc = *S;
	*S = (*S)->urm;
	(*disc)->urm = NULL;
}
//pune discul in varful stive
void Push(ALista S, ALista disc){
	(*disc)->urm = *S;
	*S = *disc;
	*disc = NULL;
}
//insereaza celula generica in stiva ordonat
int OrdPush(void *x, ALista S, size_t d){
	TLista aux = Aloca(x, d);
	if(!aux)
		return 0;
	//lista e vida
	if(*S == NULL){
		*S = aux;
		return 1;
	}
	//inserare la inceput
	if(*(int*)((*S)->info) >= *((int*)x)){
		aux->urm = *S;
		*S = aux;
		return 1;
	}
	TLista S2 = NULL, disc = NULL;
	//taie stiva pana cand trebuie pus discul
	while(*S != NULL && *(int*)((*S)->info) < *((int*)x)){
		Pop(S, &disc);
		Push(&S2, &disc);
	}
	//discul vine pus in varful stivei
	aux->urm = *S;
	*S = aux;
	//pune elementele inapoi
	while(S2 != NULL){
		Pop(&S2, &disc);
		Push(S, &disc);
	}
	return 1;
}
//initializarea unui sistem hanoi
int InitHanoi(SisHanoi *sistem, char *culoare, int dimensiune){
	strcpy((*sistem)->nume, culoare);
	(*sistem)->A = NULL;
	(*sistem)->B = NULL;
	(*sistem)->C = NULL;
	(*sistem)->mutari = malloc(sizeof(struct coada));
	(*sistem)->mutari->in = NULL;
	(*sistem)->mutari->sf = NULL;
	if(!OrdPush(&dimensiune, &((*sistem)->A), sizeof(int)))
		return 0;
	return 1;
}
//adauga un sistem Hanoi in lista de sisteme
void AdaugaSistemHanoi(ALista Hanoi, char *culoare, int dimensiune){
	TLista p = *Hanoi, ant = NULL;
	//parcurge lista de sisteme hanoi
	while(p != NULL && strcmp(((SisHanoi)(p->info))->nume, culoare) != 0){
		ant = p;
		p = p->urm;
	}
	if(p == NULL){
		SisHanoi sistem = malloc(sizeof(struct sisHanoi));
		if(!InitHanoi(&sistem, culoare, dimensiune))
			return;
		TLista aux = Aloca(sistem, sizeof(struct sisHanoi));
		if(*Hanoi == NULL){
			*Hanoi = aux;
			return;
		}
		ant->urm = aux;
		return;
	}else{
		OrdPush(&dimensiune, &(((SisHanoi)(p->info))->A), sizeof(int));
	}
}
//afiseaza o stiva
void AfiseazaStiva(FILE *f, TLista S){
	TLista S2 = NULL, disc = NULL;
	while(S != NULL){
		Pop(&S, &disc);
		Push(&S2, &disc);
	}
	while(S2 != NULL){
		Pop(&S2, &disc);
		if(S2 == NULL)
			fprintf(f, "%d", *((int*)(disc->info)));
		else
			fprintf(f, "%d ", *((int*)(disc->info)));
		Push(&S, &disc);
	}
	fprintf(f, "\n");
}
//afiseaza sistemul hanoi de [culoare]
void Afiseaza(FILE *f, TLista Hanoi, char *culoare){
	TLista p = Hanoi;
	while(p != NULL && strcmp(((SisHanoi)(p->info))->nume, culoare) != 0){
		p = p->urm;
	}
	char numestiva[20] = "A_";
	//ce se afiseaza daca sistemul e gol
	if(p == NULL){
		strcat(numestiva, culoare);
		fprintf(f, "%s:\n", numestiva);
		strcpy(numestiva, "B_");
		strcat(numestiva, culoare);
		fprintf(f, "%s:\n", numestiva);
		strcpy(numestiva, "C_");
		strcat(numestiva, culoare);
		fprintf(f, "%s:\n", numestiva);
		return;
	}
	//cum trebuie afisat [stiva]_[culoare]
	strcat(numestiva, culoare);
	if(((SisHanoi)(p->info))->A == NULL)
		fprintf(f, "%s:", numestiva);
	else
		fprintf(f, "%s: ", numestiva);
	AfiseazaStiva(f, ((SisHanoi)(p->info))->A);
	strcpy(numestiva, "B_");
	strcat(numestiva, culoare);
	if(((SisHanoi)(p->info))->B == NULL)
		fprintf(f, "%s:", numestiva);
	else
		fprintf(f, "%s: ", numestiva);
	AfiseazaStiva(f, ((SisHanoi)(p->info))->B);
	strcpy(numestiva, "C_");
	strcat(numestiva, culoare);
	if(((SisHanoi)(p->info))->C == NULL)
		fprintf(f, "%s:", numestiva);
	else
		fprintf(f, "%s: ", numestiva);

	AfiseazaStiva(f, ((SisHanoi)(p->info))->C);
}
//numara discurile unei stive
int NrDiscuri(TLista S){
	TLista S2 = NULL, disc = NULL;
	int lg = 0;
	while(S != NULL){
		lg++;
		Pop(&S, &disc);
		Push(&S2, &disc);
	}
	while(S2 != NULL){
		Pop(&S2, &disc);
		Push(&S, &disc);
	}
	return lg;
}
//extrage din coada
void ExtrCoada(ACoada C, ALista el){
	*el = (*C)->in;
	(*C)->in = (*C)->in->urm;
	(*el)->urm = NULL;
}
//insereaza in coada
void InsrCoada(ACoada C, TLista el){
	if((*C)->in == NULL){
		(*C)->in = el;
		(*C)->sf = el;
		return;
	}
	(*C)->sf->urm = el;
	(*C)->sf = el;
}
//initializeaza coada cu solutia sistemului canoi
void RezolvaHanoi(ACoada Coada, int N, char A, char B, char C){
	if(N == 1){
		Mutare muta = malloc(sizeof(struct mutare));
		muta->inceput = A;
		muta->sfarsit = C;
		TLista aux = NULL;
		aux = Aloca(muta, sizeof(struct mutare));
		InsrCoada(Coada, aux);
	}else{
		RezolvaHanoi(Coada, N - 1, A, C, B);
		RezolvaHanoi(Coada, 1, A, B, C);
		RezolvaHanoi(Coada, N - 1, B, A, C);
	}
}
//muta un disc din stiva a in stiva b
void Muta(ALista S1, ALista S2){
	if(!*S1) return;
	TLista disc = NULL;
	Pop(S1, &disc);
	Push(S2, &disc);
}
//joaca primele n mutari din sistemul hanoi
void JoacaHanoi(FILE *f, int mutari, ACoada M, ALista A, 
				ALista B, ALista C, int var, char *nume){
	TLista p;
	TCoada Coada = malloc(sizeof(struct coada));
	Coada->in = NULL;
	Coada->sf = NULL;
	int i = 0;
	char in, sf;
	char muta[20] = "M_";
	strcat(muta, nume);
	//nu exista mutari de afisat
	if(!(*M)->in && !var){
		fprintf(f, "%s:\n", muta);
		return;
	}
	if(!var){
		fprintf(f, "%s: ", muta);
	}
	for(;i < mutari && (*M)->in != NULL; i++){
		ExtrCoada(M, &p);
		in = ((Mutare)(p->info))->inceput;
		sf = ((Mutare)(p->info))->sfarsit;
		if(var){
		switch(in - sf + in % 10){
			case 4:
			if(var)
				Muta(A, B);
				break;
			case 3:
				Muta(A, C);
				break;
			case 7:
				Muta(B, A);
				break;
			case 9:
				Muta(C, A);
				break;
			case 5:
				Muta(B, C);
				break;
			case 8:
				Muta(C, B);
				break;
			default:
				printf("nimic de mutat\n");
		}
		}else{
			if(i + 1 == mutari || (*M)->in == NULL)
				fprintf(f, "%c->%c", in, sf);
			else
				fprintf(f, "%c->%c ", in, sf);
		}
		//elimina mutarea si trece mai departe
		InsrCoada(&Coada, p);
	}
	//elimina elementele din coada auxiliara in cazul procesului de mutare
	if(var){
		while(Coada->in != NULL){
			ExtrCoada(&Coada, &p);
			free(p);
		}
	}else{
		fprintf(f, "\n");
		Coada->sf->urm = (*M)->in;
		(*M)->in = Coada->in;
	}
}
void Joaca(FILE *f, ALista Hanoi, char* culoare, int mutari, int var){
	TLista p = *Hanoi;
	while(p != NULL && strcmp(((SisHanoi)(p->info))->nume, culoare) != 0){
		p = p->urm;
	}
	SisHanoi s = (SisHanoi)(p->info);
	if(s->mutari->in == NULL && !NrDiscuri(((SisHanoi)(p->info))->B) && 
								!NrDiscuri(((SisHanoi)(p->info))->C)){

		int nr = NrDiscuri(((SisHanoi)(p->info))->A);
		RezolvaHanoi(&(s->mutari), nr, 'A', 'B', 'C');
	}
	JoacaHanoi(f, mutari, &(s->mutari), &(s->A), &(s->B), &(s->C), var, s->nume);
}



