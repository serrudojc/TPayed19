#include <iostream>
using namespace std;

#define CANTCATEG 2
#define CANTPREG 2

struct preguntas {
	string categoria;
	string pregunta;
	string respuesta;
	bool habilitada;
};

struct preguntas preg;

int main (){

	FILE * arch = fopen("preguntas.dat","rb"); //ab?+?
	
	fread(&preg, sizeof(preg),1,arch);
/*
	while(!feof(arch)){
		for(int i=0; i<CANTCATEG; i++){
			for(int j=0; j<CANTPREG; j++){
				
				cout<<"llegue aca"<<endl;
				cout<<preg.categoria<<" || "<<preg.pregunta<<" || "<<preg.respuesta<<endl;
				cout<<"llegue aca 2"<<endl;
				fread(&preg, sizeof(preg),1,arch);
			}
		}
	}
*/
	while(!feof(arch){
		for(int i=0; i<CANTPREG*CANTCATEG; i++){
			cout<<preg.categoria<<" "<<preg.pregunta<<" "<<pre.respuesta<<endl;
			fread(&preg, sizeof(preg),1,arch);
		}
	}

	fclose(arch);
	return 0;
}