//Programa que me permite leer el contenido del preguntas.dat.

#include <iostream>
#include "funciones.hpp"
using namespace std;

//----------------------------------------------------

int main(){
	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	Categoria reg;
	fread(&reg, sizeof(Categoria),1,arch);

	while(!feof(arch)){
		cout<<"id: "<<reg.id<<endl;
		cout<<"Categoria: "<<reg.categoria<<endl;
		cout<<"Habilitada: "<<reg.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Pregunta   ["<<i<<"]: "<<reg.preguntas[i].pregunta<<endl;
			cout<<"Respuesta  ["<<i<<"]: "<<reg.preguntas[i].respuesta<<endl;
			cout<<"Habilitada ["<<i<<"]: "<<reg.preguntas[i].pregEnabled<<endl;
		}
		cout<<endl;
		fread(&reg, sizeof(Categoria),1,arch);
	}
	fclose(arch);
	return 0;
}