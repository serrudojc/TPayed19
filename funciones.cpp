#include <iostream>
#include <string.h>
#include <string>		//hora
#include <stdlib.h>		//hora
#include <ctime> 		//hora
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
void agregarNodoPart(NodoPart *&lista, ResPart v){
	NodoPart* p = new NodoPart(); 
	p->info = v;
	p->sig = NULL;

	if(lista == NULL){	
		lista = p;
	} else {		
		NodoPart* aux = lista;
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
char *obtenerHora(char *fechaChar){
	string fechaString;
    //char fechaChar[CHARCATEG];
        
    // Declaring argument for time() 
    time_t tt; 
  
    // Declaring variable to store return value of localtime() 
    tm* ti; 

    // Applying time() 
    time (&tt); 
  
    // Using localtime() 
    ti = localtime(&tt); 

    fechaString = asctime(ti);
    strcpy(fechaChar, fechaString.c_str()); //or pass &fechaString[0]
    //cout<<fechaChar<<endl;
     
    return fechaChar;
}
//--------------------------------------------------------------------------
void ordenarBurbuja (Participantes arr[], int len){
	Participantes aux;
	for(int i=0; i<len-1; i++){
		for(int j=0; j<len-1;j++){
			if(arr[j].puntaje < arr[j+1].puntaje){
				// funcion de swap
				aux = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = aux;
			}
		}
	}
}
//--------------------------------------------------------------------------
void mostrar (Participantes arr[],int len){
	cout<<"id\tPuntos\tParticipante\tSig. turno"<<endl;
	for(int i=0; i<len; i++){
		cout<<arr[i].idPart<<"\t"<<arr[i].puntaje;
		cout<<"\t"<<arr[i].nombrePart<<"\t"<<arr[i].proxTurno<<endl;
	}
	cout<<endl;
	return ;
}
//---------------------------------------------------------------------------
int cantDeEmpatados(Participantes arr[], int len){
	int mayorPuntaje = 0, cont =0;
	for(int i=0; i<len; i++){
		if(arr[i].puntaje>=mayorPuntaje){
			mayorPuntaje = arr[i].puntaje;
			cont++;
		}
	}
	return cont++;
}