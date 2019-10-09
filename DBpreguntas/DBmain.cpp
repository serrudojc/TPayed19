//Programa que uso para cargar las preguntas y respuestas del juego. Ver temas mayus y acentos
#define CANTPREG 3
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct Pregunta{
	char pregunta[120];
	char respuesta[120];
	bool pregEnabled = true;
};

struct Categoria {
	int id;
	char categoria[20];
	Pregunta preguntas[CANTPREG];
	bool catEnabled = true;
};

struct Nodo{
	Categoria info;
	Nodo *sig;			
};

//declaro lista, puntero al primer nodo que apunta a NULL, o sea, lista vacia. 
Nodo *lista = NULL;

//------------------------------------------------
void agregarNodo(Nodo*& lista, Categoria v);
Categoria eliminarPrimerNodo (Nodo*& lista);
//------------------------------------------------
int main (){
	Categoria auxCat;
	char preg[120], resp[120], categ[20];
	int k=0;

	do{
		cout<<"Ingresar categoria: ";
		cin.getline(categ,20);
		//salgo con valores igual a cero
		if(strcmp(categ,"0")==0)
			break;
		strcpy(auxCat.categoria, categ);
		auxCat.id = k;
		k++;
		
		for(int i=0; i<CANTPREG; i++){
			cout<<"Ingresar pregunta \t["<<i+1<<"]: ";
			cin.getline(preg,120); 
			strcpy(auxCat.preguntas[i].pregunta, preg);

			cout<<"Ingresar respuesta \t["<<i+1<<"]: ";
			cin.getline(resp,120);
			strcpy(auxCat.preguntas[i].respuesta, resp);
		}
		cout<<endl;	
		agregarNodo(lista, auxCat);
	}
	while(1);	

	FILE *fp = fopen("preguntas.dat", "wb");
	Categoria reg;

	while(lista != NULL){
		reg = eliminarPrimerNodo (lista);	//CONSULTA: me va retornar -1?
		fwrite(&reg, sizeof(Categoria), 1, fp);
	}
	fclose(fp);

	return 0;
}
//------------------------------------------------
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
//-------------------------------------------------
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
//-------------------------------------------------