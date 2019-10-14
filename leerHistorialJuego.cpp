//Programa que me permite leer el contenido del historialJuego.dat.

#include <iostream>
#include "funciones.hpp"
using namespace std;

//----------------------------------------------------

int main(){
	FILE * arch = fopen("historialJuego.dat","rb"); //ab?+?
	ResPart reg;
	fread(&reg, sizeof(ResPart),1,arch);

	while(!feof(arch)){
		cout<<"Pregunta: "<<"\t\t"<<reg.pregunta<<endl;
		cout<<"Respuesta Participante: "<<reg.resp<<endl;
		cout<<"Es correcta?: "<<"\t\t"<<reg.esCorrecta<<endl;

		cout<<endl;
		fread(&reg, sizeof(ResPart),1,arch);
	}
	fclose(arch);
	return 0;
}