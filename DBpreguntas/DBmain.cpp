#include <iostream>
using namespace std;
#include "DBfunciones.hpp"

struct preguntas preg[CANTCATEG][CANTPREG];

int main (){

	FILE * arch = fopen("preguntas.dat","wb+"); //ab?+?

	for(int i=0; i<CANTCATEG; i++){
		for(int j=0; j<CANTPREG; j++){
			cout<<"Ingresar categoria\t["<<i<<"]["<<j<<"]: ";
			cin.ignore(); getline(cin, preg[i][j].categoria);
			//cin>>preg[i][j].categoria;
			cout<<"Ingresar pregunta\t["<<i<<"]["<<j<<"]: ";
			cin.ignore(); getline(cin, preg[i][j].pregunta);
			//cin>>preg[i][j].pregunta;
			cout<<"Ingresar respuesta\t["<<i<<"]["<<j<<"]: ";
			cin.ignore(); getline(cin, preg[i][j].respuesta);			
			//cin>>preg[i][j].respuesta;
			preg[i][j].habilitada = true;
			cout<<endl;
		}
	}

	for(int i=0; i<CANTCATEG; i++){
		for(int j=0; j<CANTPREG; j++){
			fwrite(&preg[i][j], sizeof(preg),1, arch);
		}
	}

	fclose(arch);
	return 0;
}