//Programa que me permite leer el contenido del historialJuego.dat.

#include <iostream>
#include "funciones.hpp"
using namespace std;

//----------------------------------------------------

int main(){
	FILE * arch = fopen("historialJuego.dat","rb"); //ab?+?
	Consolidado reg;
	fread(&reg, sizeof(Consolidado),1,arch);

	while(!feof(arch)){
		cout<<"Participante "<<reg.idPart<<" "<<reg.nombrePart<<endl;
		cout<<reg.info.tiempo;
		cout<<"Pregunta: "<<"\t\t"<<reg.info.pregunta<<endl;
		cout<<"Respuesta Participante: "<<reg.info.resp<<endl;
		cout<<"Es correcta?: "<<"\t\t"<<reg.info.esCorrecta<<endl;
		cout<<"Puntaje: "<<reg.puntaje<<endl;
		cout<<"Próximo jugador: "<<reg.proxTurno<<endl;

		cout<<endl;
		fread(&reg, sizeof(Consolidado),1,arch);
	}
	fclose(arch);
	return 0;
}