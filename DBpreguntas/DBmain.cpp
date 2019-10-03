#define CANTPREG 3
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct sPregunta{
	char pregunta[120];
	char respuesta[120];
	bool pregEnabled = true;
};

struct sCategoria {
	char categoria[20];
	sPregunta preguntas[CANTPREG];
	bool catEnabled = true;
};

struct Nodo{
	sCategoria info;
	Nodo *sig;			
};

//declaro lista, puntero al primer nodo que apunta a NULL, o sea, lista vacia. 
Nodo *lista = NULL;

//------------------------------------------------
void agregarNodo(Nodo*& lista, sCategoria v);
sCategoria eliminarPrimerNodo (Nodo*& lista);
//------------------------------------------------
int main (){
	sCategoria auxCat;
	char pre[120], res[120], categ[20];

	do{
		cout<<"Ingresar categoria: ";
		cin.getline(categ,20);
		//salgo con valores igual a cero
		if(strcmp(categ,"0")==0)
			break;
		strcpy(auxCat.categoria, categ);
		
		for(int i=0; i<CANTPREG; i++){
			cout<<"Ingresar pregunta \t["<<i+1<<"]: ";
			cin.getline(pre,120); 
			strcpy(auxCat.preguntas[i].pregunta, pre);

			cout<<"Ingresar respuesta \t["<<i+1<<"]: ";
			cin.getline(res,120);
			strcpy(auxCat.preguntas[i].respuesta, res);
		}
		cout<<endl;	
		agregarNodo(lista, auxCat);
	}
	while(1);	

	FILE *fp = fopen("preguntas.dat", "wb");
	sCategoria reg;

	while(lista != NULL){
		reg = eliminarPrimerNodo (lista);	//CONSULTA: me va retornar -1?
		fwrite(&reg, sizeof(sCategoria), 1, fp);
	}
	fclose(fp);

	return 0;
}
//------------------------------------------------
void agregarNodo(Nodo*& lista, sCategoria v){
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
sCategoria eliminarPrimerNodo (Nodo*& lista){
	Nodo* aux = lista; 	//como es por referencia
	sCategoria valor; 
	strcpy(valor.categoria,"-1");	//chequear esta parte
	if(aux != NULL){	//chequeo que no sea una lista vacia
		valor = lista->info;
		lista = lista->sig;
		delete aux;
	}
	return valor;	//si la lista esta vacia, devuelvo -1, sino, devuelvo el valor del primer nodo
}
//-------------------------------------------------