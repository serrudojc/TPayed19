#define CANTPREG 2
#include <iostream>
#include <stdio.h>
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


int main(){
	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	structCategoria reg;
	fread(&reg, sizeof(structCategoria),1,arch);
	//me tira segmentation fault a partir de fread
/*
	while(!feof(arch)){
		cout<<reg.categoria<<endl;
		cout<<reg.catHabil<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<reg.preguntas[i].pregunta<<" "<<reg.preguntas[i].respuesta<<" "<<reg.preguntas[i].pregHabil<<endl;
			fread(&reg, sizeof(structCat),1,arch);
		}
	}*/
	fclose(arch);
	return 0;
}