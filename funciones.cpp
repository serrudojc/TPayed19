#include <iostream>
#include <string.h>
#include "funciones.hpp"
using namespace std;

//-------------------------------------------------------
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
//-------------------------------------------------------
void agregarNodoJuego(Participantes *&lista, ResPart v){
	Participantes* p = new Participantes(); 
	p->info = v;
	p->sig = NULL;

	if(lista == NULL){	
		lista = p;
	} else {		
		Participantes* aux = lista;
		while(aux->sig != NULL){
			aux = aux->sig;
		}
	aux->sig = p;
	}
}
//-------------------------------------------------------
Categoria eliminarPrimerNodo (Nodo*& lista){
	Nodo* aux = lista; 	//como es por referencia
	Categoria valor; 
	strcpy(valor.categoria,"-1");	//chequear esta parte
	if(aux != NULL){	//chequeo que no sea una lista vacia
		valor = lista->info;
		lista = lista->sig;
		delete aux;
	}
	return valor;	//si la lista esta vacia, devuelvo -1, sino, devuelvo el valor del primer nodo
}
//--------------------------------------------------------
void mostrar (Nodo* lista){ 
	Nodo *aux = lista;
	while(aux != NULL){
		cout<<aux->info.id<<endl;
		cout<<aux->info.categoria<<endl;
		cout<<aux->info.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Pregunta   ["<<i<<"]: "<<aux->info.preguntas[i].pregunta<<endl;
			cout<<"Respuesta  ["<<i<<"]: "<<aux->info.preguntas[i].respuesta<<endl;
			cout<<"Habilitada ["<<i<<"]: "<<aux->info.preguntas[i].pregEnabled<<endl;
		}
		cout<<endl;
		aux = aux->sig;
	}		
}
//--------------------------------------------------------------------------
void mostrarUnNodo(Nodo* lista){ 
	Nodo *aux = lista;
	while(aux != NULL){
		cout<<aux->info.id<<endl;
		cout<<aux->info.categoria<<endl;
		cout<<aux->info.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Pregunta   ["<<i<<"]: "<<aux->info.preguntas[i].pregunta<<endl;
			cout<<"Respuesta  ["<<i<<"]: "<<aux->info.preguntas[i].respuesta<<endl;
			cout<<"Habilitada ["<<i<<"]: "<<aux->info.preguntas[i].pregEnabled<<endl;
		}
		cout<<endl;		
		aux = NULL;		
	}
}
//--------------------------------------------------------------------------
Nodo *leerPreguntasDat(Nodo *&lista){
	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	Categoria reg;
	fread(&reg, sizeof(Categoria),1,arch);

	//Cargo preguntas.dat en memoria
	while(!feof(arch)){
		//mando a la lista
		agregarNodo(lista, reg);
		fread(&reg, sizeof(Categoria),1,arch);
		}
	fclose(arch);
	return lista;
}
//--------------------------------------------------------------------------
//devuelve un entero entre min y max
int get_rand(int min, int max){
	return rand()%(max);
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
Nodo* buscar(Nodo* lista, int v){	
	Nodo* aux;
	aux=lista;	
	while((aux != NULL)&&(aux->info.id != v) ){	
		aux = aux->sig;
	}
	return aux;
}
//-------------------------------------------------------------------------
Nodo* buscarCat(Nodo* lista, int v){	
	Nodo* aux = lista;	
	while((aux != NULL) && (aux->info.id != v) ){	
		aux = aux->sig;
	}
	return aux;
}
//-------------------------------------------------------------------------
