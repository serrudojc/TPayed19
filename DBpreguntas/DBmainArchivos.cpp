#define CANTPREG 2
#include <iostream>
using namespace std;

struct structPregunta{
	string pregunta;
	string respuesta;
	bool pregEnabled = true;
};

struct structCategoria {
	string categoria;
	structPregunta preguntas[CANTPREG];
	bool catEnabled = true;
};

struct Nodo{
	structCategoria info;
	Nodo *sig;
};

//declaro lista, puntero al primer nodo que apunta a NULL, o sea, lista vacia. 
Nodo *lista = NULL;

//declaro un auxiliar. Aun no se si lo voy a usar
Nodo *temporario = NULL;

//------------------------------------------------
void agregarNodo(Nodo*& lista, structCategoria v);
structCategoria eliminarPrimerNodo (Nodo*& lista);

//------------------------------------------------
int main (){
	structCategoria auxCat;

	FILE *fp = fopen("preguntas.dat", "wb");
	structCategoria reg;

	do{
		cout<<"Ingresar categoria: ";
		getline(cin, auxCat.categoria);
		//salgo con valores igual a cero
		if(auxCat.categoria == "0")
			break;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Ingresar pregunta \t["<<i+1<<"]: ";
			getline(cin, auxCat.preguntas[i].pregunta); 
			cout<<"Ingresar respuesta \t["<<i+1<<"]: ";
			getline(cin, auxCat.preguntas[i].respuesta);
		}
		cout<<endl;	
		/*
		cout<<"voy a mostrar el auxCat"<<endl;
		cout<<auxCat.categoria<<endl;
		cout<<auxCat.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<auxCat.preguntas[i].pregunta<<" "<<auxCat.preguntas[i].respuesta<<" "<<auxCat.preguntas[i].pregEnabled<<endl;
		}
		*/
		agregarNodo(lista, auxCat);
	}
	while(1);	



	while(lista != NULL){
		reg = eliminarPrimerNodo (lista);	//CONSULTA: me va retornar -1?
		fwrite(&reg, sizeof(structCategoria), 1, fp);
	}
	fclose(fp);

	return 0;
}
//------------------------------------------------
void agregarNodo(Nodo*& lista, structCategoria v){

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
structCategoria eliminarPrimerNodo (Nodo*& lista){
	Nodo* aux = lista; 	//como es por referencia
	structCategoria valor; 
	valor.categoria = "-1";	//chequear esta parte
	if(aux != NULL){	//chequeo que no sea una lista vacia
		valor = lista->info;
		lista = lista->sig;
		delete aux;
	}
	return valor;	//si la lista esta vacia, devuelvo -1, sino, devuelvo el valor del primer nodo
}
//-------------------------------------------------