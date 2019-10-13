//Primero cargo en memoria preguntas.dat y elijo de forma random una.

#include <iostream>
#include <string.h>
#include <stdlib.h>			//para rand
#include <unistd.h>			//sleep
#include "funciones.hpp"
using namespace std;

//-------------------------------------------------------------------
int main(){

	Nodo *listaCat = NULL;

	int catRandom, pregRandom;
	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	Categoria reg;
	fread(&reg, sizeof(Categoria),1,arch);
	Nodo *lista = NULL;

	//Cargo preguntas.dat en memoria
	while(!feof(arch)){
		//mando a la lista
		agregarNodo(lista, reg);
		fread(&reg, sizeof(Categoria),1,arch);
		}
	fclose(arch);
/*	
	cout<<endl<<"\t*-*-*-* Voy a mostrar toda la lista cargada en memoria *-*-*-*"<<endl;
	mostrar(lista);
*/
	cout<<endl<<"\t*-*-*-* Voy a mostrar de forma random una pregunta de la lista cargada *-*-*-*"<<endl;
	srand((int)time(NULL)); 	//inicializamos semilla para generador random

//	cout<<"Cantidad de nodos de la lista :"<<cantidadNodos(lista)<<endl;

	for(int i=0; i<CANTTURNO; i++){
		cout<<"dentro del for i["<<i<<"]";
		for(int j=0; j<CANTPART; j++){
			//voy a recorrer la lista hasta encontrar la categoria que me dice el random
			cout<<"j["<<j<<"]"<<endl;
			catRandom = get_rand(MIN, cantidadNodos(lista));

			listaCat = buscarCat(lista, catRandom);	
			if(listaCat->info.catEnabled){
				cout<<"muestro catRandom= "<<catRandom<<endl;
				pregRandom = get_rand(MIN, CANTPREG);
				if(listaCat->info.preguntas[pregRandom].pregEnabled){
					cout<<listaCat->info.preguntas[pregRandom].pregunta<<": ";
					cout<<endl;
				}
			}		

/*COMPLETAR: tengo que desabilitar las preg y cat que hayan sido contestadas
tengo que ver que pasa si la cat o preg no está habiliatada
*/

			sleep(2);
			//mostrarUnNodo(buscar(lista, catRandom));
		}

	}

	return 0;
}
