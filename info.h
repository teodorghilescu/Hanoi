/*GHILESCU TEODOR-ANDREI 314CB*/
#ifndef _LISTA_H_
#define _LISTA_H_

//definitia celulei generice
typedef struct celulag
{
	void * info; //info contine dimenisunea
	struct celulag *urm;
} Celula, *TLista, **ALista;

//definirea unei cozi
typedef struct coada{
	TLista in;
	TLista sf;
} *TCoada, **ACoada;

//definirea unei mutari ex: A->B
typedef struct mutare
{
	char inceput;
	char sfarsit;
} *Mutare;

//definirea unui sistem Hanoi
typedef struct sisHanoi
{
	char nume[20]; //numele e culoarea
	TLista A;
	TLista B;
	TLista C;
	TCoada mutari; //memoreaza pasii de rezolvare ai sistemului
} *SisHanoi;
#endif
