//Primero cargo en memoria preguntas.dat y elijo de forma random una.

#include <iostream>
#include <string.h>
#include <stdlib.h>			//para rand
#include <unistd.h>			//sleep
#include "funciones.hpp"
using namespace std;

//-------------------------------------------------------------------
int main(){

	Nodo *lista = NULL;
	Nodo *nodoCat = NULL;
	int catRandom, pregRandom;

//cargo en memoria las preguntas
	lista = leerPreguntasDat(lista);
//	mostrar(lista); //muestra lista cargada en memoria

//inicializamos semilla para generador random
	srand((int)time(NULL)); 	

//	cout<<"Cantidad de nodos de la lista :"<<cantidadNodos(lista)<<endl;

	for(int i=0; i<CANTTURNO; i++){
		for(int j=0; j<CANTPART; j++){
			//recorro lista hasta encontrar la categoria del random
			cout<<"[turno][jugador] i["<<i<<"]j["<<j<<"]: ";
			catRandom = get_rand(MIN, cantidadNodos(lista));
			nodoCat = buscarCat(lista, catRandom);
			while(1){
				if(nodoCat->info.catEnabled){
					pregRandom = get_rand(MIN, CANTPREG);
					if(nodoCat->info.preguntas[pregRandom].pregEnabled){
						cout<<nodoCat->info.preguntas[pregRandom].pregunta<<": ";
						nodoCat->info.preguntas[pregRandom].pregEnabled = false;
						cout<<endl;
						break;
					}else{
						cout<<"Repetido: cat:"<<catRandom<<" preg:"<<pregRandom<<endl;
						if()
						sleep(1);
					}
				}		
			}
			//sleep(2);
			//mostrarUnNodo(buscar(lista, catRandom));
		}

	}
	return 0;
}
