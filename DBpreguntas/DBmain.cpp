#define CANTPREG 3
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
		agregarNodo(lista, auxCat);
	}
	while(1);	

	FILE *fp = fopen("preguntas.dat", "wb");
	structCat reg;

	while(lista != NULL){
		reg = eliminarPrimerNodo (lista);
		fwrite(&reg, sizeof(structCat), 1, fp);
	}
	fclose(fp);

	return 0;
}
//------------------------------------------------
void agregarNodo(Nodo*& lista, structCategoria v){

	Nodo* p = new Nodo(); 
	p->info.categoria = v.categoria;
	for (int i =0; i<CANTPREG; i++){
		p->info.preguntas[i] = v.preguntas[i];
	}
	p->sig = NULL;

	if(lista==NULL){	
		lista = p;
	} else {		
		Nodo* aux = lista;
		while(aux->sig != NULL){
			aux= aux->sig;
		}
	aux->sig = p;
	}
}
//-------------------------------------------------
structCat eliminarPrimerNodo (Nodo*& lista){
	Nodo* aux = lista; 	//como es por referencia
	structCat valor; 
	valor.categoria = "-1";
	if(aux!=NULL){	//chequeo que no sea una lista vacia
		valor = lista->info;
		lista = lista->sig;
		delete aux;
	}
	return valor;	//si la lista esta vacia, devuelvo -1, sino, devuelvo el valor del primer nodo
}
//-------------------------------------------------