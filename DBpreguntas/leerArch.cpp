#include <iostream>
using namespace std;
#define CANTPREG 3

struct structPreg{
	string pregunta;
	string respuesta;
	bool pregHabil = true;
};

struct structCat {
	string categoria;
	structPreg preguntas[CANTPREG];
	bool catHabil = true;
};

int main(){
		cout<<"llegué aca";
	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	structCat reg;
	fread(&reg, sizeof(structCat),1,arch);
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