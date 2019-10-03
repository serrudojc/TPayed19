#define CANTPREG 2
#include <iostream>
#include <stdio.h>
using namespace std;

struct structPregunta{
	char pregunta[120];
	char respuesta[120];
	bool pregEnabled = true;
};

struct structCategoria {
	char categoria[20];
	structPregunta preguntas[CANTPREG];
	bool catEnabled = true;
};


int main(){
	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	structCategoria reg;
	fread(&reg, sizeof(structCategoria),1,arch);

	while(!feof(arch)){
		cout<<reg.categoria<<endl;
		cout<<reg.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<reg.preguntas[i].pregunta<<" "<<reg.preguntas[i].respuesta<<" "<<reg.preguntas[i].pregEnabled<<endl;
			fread(&reg, sizeof(structCategoria),1,arch);
		}
	}
	fclose(arch);
	return 0;
}