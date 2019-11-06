//Programa que me permite leer el contenido del historialJuego.dat.

#include <iostream>
#include "funciones.hpp"
using namespace std;

//----------------------------------------------------

int main(){
	FILE * arch = fopen("save.dat","rb");
	Participantes reg;
	fread(&reg, sizeof(Participantes),1,arch);
	cout<<"--------------------------"<<endl;
	while(!feof(arch)){
		cout<<"Id participante:"<<reg.idPart<<" || "<<reg.nombrePart<<" || "<<reg.info.tiempo;
		cout<<"Pregunta: "<<reg.info.pregunta<<endl;
		cout<<"Respuesta: "<<reg.info.resp<<endl;
		cout<<"Es correcta?: "<<"\t\t"<<reg.info.esCorrecta<<endl;
		cout<<"*Puntaje: "<<reg.puntaje<<endl;
		cout<<"valor de i="<<reg.i<<endl;
		cout<<"valor de j="<<reg.j<<endl;
		cout<<"valor de k="<<reg.k<<endl;
		cout<<endl;
		fread(&reg, sizeof(Participantes),1,arch);
	}
	fclose(arch);
	cout<<"--------------------------"<<endl;
	return 0;
}