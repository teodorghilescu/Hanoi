/*GHILESCU TEODOR-ANDREI 314CB*/
#include <stdio.h>
#include <stdlib.h>
#include "functii.h"
#include "info.h"

int main(int argc, char *argv[]){

	FILE *f = fopen(argv[1], "r+");
	FILE *h = fopen(argv[2], "w+");
	int N;
	fscanf(f, "%d", &N);
	int i, dimensiune, mutari;
	char operatie[20], culoare[20];
	//initializeaza lista de sisteme Hanoi
	TLista Hanoi = NULL;
	for(i = 0;i < N;i++){
		fscanf(f, "%s", operatie);
		if(strcmp("add", operatie) == 0){
			fscanf(f, "%s", culoare);
			fscanf(f, "%d", &dimensiune);
			AdaugaSistemHanoi(&Hanoi, culoare, dimensiune);
		}else if(strcmp("show", operatie) == 0){
			fscanf(f, "%s", culoare);
			Afiseaza(h, Hanoi, culoare);
		}else if(strcmp("play", operatie) == 0){
			fscanf(f, "%s", culoare);
			fscanf(f, "%d", &mutari);
			Joaca(h, &Hanoi, culoare, mutari, 1);
		}else if(strcmp("show_moves", operatie) == 0){
			fscanf(f, "%s", culoare);
			fscanf(f, "%d", &mutari);
			Joaca(h, &Hanoi, culoare, mutari, 0);
		}
	}
	free(Hanoi);
	fclose(f);
	fclose(h);
	return 0;
}
	