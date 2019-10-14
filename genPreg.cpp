//Programa generador de preguntas.dat

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "funciones.hpp"
using namespace std;

//-------------------------------------------------------

int main (){
	Nodo *lista = NULL;

	Categoria auxCat;
	
	char categ[CHARCATEG];
	int k=0;

	do{
		cout<<"Ingresar categoria: ";
		cin.getline(categ,CHARCATEG);
		//salgo con valores igual a cero
		if(strcmp(categ,"0")==0)
			break;
		strcpy(auxCat.categoria, categ);
		auxCat.id = k;
		k++;
		
		for(int i=0; i<CANTPREG; i++){
			cout<<"Ingresar pregunta \t["<<i<<"]: ";
			cin.getline(auxCat.preguntas[i].pregunta,CHARPREG); 
			//cin.ignore();
			cout<<"Ingresar respuesta \t["<<i<<"]: ";
			cin.getline(auxCat.preguntas[i].respuesta,CHARRESP);
			//cin.ignore();
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