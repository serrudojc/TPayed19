//Primero cargo en memoria todo el preguntas.dat
//Luego, voy a elegir alguna pregunta random  la voy a mostrar

#define CANTPREG 3
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>				//para rand
#include <unistd.h>				//sleep
#define MIN 1
using namespace std;

struct Pregunta{
	char pregunta[120];
	char respuesta[120];
	bool pregEnabled = true;
};

struct Categoria {
	char categoria[20];
	Pregunta preguntas[CANTPREG];
	bool catEnabled = true;
};

struct Nodo{
	Categoria info;
	Nodo *sig;			
};

void agregarNodo(Nodo*& lista, Categoria v);
void mostrar (Nodo* lista);
int get_rand(int min, int max);
int cantidadNodos (Nodo* lista);
//-------------------------------------------------------------------
int main(){
	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	Categoria reg;
	fread(&reg, sizeof(Categoria),1,arch);

	//creo una lista
	Nodo *lista = NULL;

	while(!feof(arch)){
		//mando a la lista
		agregarNodo(lista, reg);
		fread(&reg, sizeof(Categoria),1,arch);
		}
	fclose(arch);
	
	cout<<endl<<"\t*-*-*-* Voy a mostrar toda la lista cargada en memoria *-*-*-*"<<endl;
	mostrar(lista);

	cout<<endl<<"\t*-*-*-* Voy a mostrar de forma random una pregunta de la lista cargada *-*-*-*"<<endl;
	srand((int)time(NULL)); 	//inicializamos semilla para generador random

	cout<<"Cantidad de nodos de la lista :"<<cantidadNodos(lista)<<endl;
	while(1){
		cout<<"nºcategoria: "<<get_rand(MIN, cantidadNodos(lista))<<endl;
		cout<<"nºpregunta: "<<get_rand(MIN, CANTPREG)<<endl<<endl;
		sleep(2);
	}

	return 0;
}
//-----------------------------------------------------------------------
void agregarNodo(Nodo*& lista, Categoria v){
	Nodo* p = new Nodo(); 
	p->info = v;
	p->sig = NULL;

	if(lista == NULL){	
		lista = p;
	} else {		
		Nodo* aux = lista;
		while(aux->sig != NULL){
			aux = aux->sig;
		}
	aux->sig = p;
	}
}
//------------------------------------------------------------------------

void mostrar (Nodo* lista){ 

	Nodo *aux = lista;
	while(aux != NULL){
		cout<<aux->info.categoria<<endl;
		cout<<aux->info.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Pregunta   ["<<i+1<<"]: "<<aux->info.preguntas[i].pregunta<<endl;
			cout<<"Respuesta  ["<<i+1<<"]: "<<aux->info.preguntas[i].respuesta<<endl;
			cout<<"Habilitada ["<<i+1<<"]: "<<aux->info.preguntas[i].pregEnabled<<endl;
		}
		cout<<endl;
		
		aux = aux->sig;		
	}
}
	
//--------------------------------------------------------------------------
//devuelve un entero entre min y max
int get_rand(int min, int max){
	return rand()%(max)+1;
}
//-------------------------------------------------------------------------
//devuelve cantidad de nodos de una lista
int cantidadNodos (Nodo* lista){
	Nodo* aux = lista;
	int contador = 0;

	while(aux != NULL){
		contador++;
		aux = aux->sig;
	}
	return contador;
}
//-------------------------------------------------------------------------