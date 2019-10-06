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
	char categoria[20];
	Pregunta preguntas[CANTPREG];
	bool catEnabled = true;
};


int main(){
	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	Categoria reg;
	fread(&reg, sizeof(Categoria),1,arch);

	while(!feof(arch)){
		cout<<"Categoria: "<<reg.categoria<<endl;
		cout<<"Habilitada: "<<reg.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Pregunta   ["<<i+1<<"]: "<<reg.preguntas[i].pregunta<<endl;
			cout<<"Respuesta  ["<<i+1<<"]: "<<reg.preguntas[i].respuesta<<endl;
			cout<<"Habilitada ["<<i+1<<"]: "<<reg.preguntas[i].pregEnabled<<endl;
		}
		cout<<endl;
		fread(&reg, sizeof(Categoria),1,arch);
	}
	fclose(arch);
	return 0;
}