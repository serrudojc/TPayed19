#define CANTPREG 3

#include <iostream>
using namespace std;


struct structPreg{
	string pregunta;
	string respuesta;
	bool pregHabil = true;
};

//Nodo: base de datos de las preguntas
struct NodoCat {
	string categoria;
	structPreg preguntas[CANTPREG];
	bool catHabil;
	NodoCat *sig;
};

//declaro lista, puntero al primer nodo que apunta a NULL, o sea, lista vacia. 
NodoCat *lista = NULL;

//declaro un auxiliar. Aun no se si lo voy a usar
NodoCat *temporario = NULL;

//------------------------------------------------
void agregarNodo(NodoCat*& lista, string inCategoria, structPreg inPreguntas[]);


//------------------------------------------------
int main (){
	string cat;
	structPreg aux[CANTPREG];

	do{
		cout<<"Ingresar categoria: ";
		getline(cin, cat);
		if(cat == "0")
			break;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Ingresar pregunta \t["<<i+1<<"]: ";
			getline(cin, aux[i].pregunta); 
			cout<<"Ingresar respuesta \t["<<i+1<<"]: ";
			getline(cin, aux[i].respuesta);
		}
		cout<<endl;		
		agregarNodo(lista, cat, aux);
	}
	while(1);	


	return 0;
}
//------------------------------------------------
void agregarNodo(NodoCat*& lista, string inCategoria, structPreg inPreguntas[]){

	NodoCat* p = new NodoCat(); 
	p->categoria = inCategoria;
	for (int i =0; i<CANTPREG; i++){
		p->preguntas[i] = inPreguntas[i];
	}
	p->catHabil = true;
	p->sig = NULL;

	if(lista==NULL){	
		lista = p;
	} else {		
		NodoCat* aux = lista;
		while(aux->sig != NULL){
			aux= aux->sig;
		}
	aux->sig = p;
	}
}
//-------------------------------------------------