#define CANTPREG 	3
#define CANTPART 	3
#define CANTTURNO	3
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;




struct Participante{
	int idParticipante;	//no se si voy a usar esto. Tengo que diferenciar los participantes?
	int puntos = 0;
	Historico *historial[CANTPART];	//esta bien? array de cabezas de listas (punteros)
};
/*
struct Historico{
	char pregunta[120];
	char respuesta[120];
	bool correcta;
	int horaRespuesta;
	Historico *sig;
};
*/
struct Historico{
	InfoHis info;
	Historico *sig;
};

struct InfoHis{
	char pregunta[120];
	char respuesta[120];
	bool correcta;
	int horaRespuesta; //borrador, luego implementar correctamente el tema de la hora
}


//--------------------------------------------------------------------
int main(){

	Participante participantes[CANTPART];
	
	
	char respParticipante[120];

	cout<<"Hace una intro"<<endl;

	//ciclo de preguntas base para todos. Si hay empate, se debe seguir para desempatar
	for(int i=0; i<CANTTURNO; i++){
		for(int j=0; j<CANTPART; j++){
			cout<<"Participante "<<j+1<<", turno nº"<<i+1<<": De alguna forma mágica random tengo que poner la pregunta"<<endl
			cout<<"Tu respuesta es: ";
			cin>>respParticipante;

		}
	}
	
	return 0;
}
//--------------------------------------------------------------------
//coloco idParticipante
void colocarIdParticipante(Participante participantes[]){
	for(int i=0; i<CANTPART; i++){
		participantes[i].idParticipante = i+1;
	}
}
//--------------------------------------------------------------------
