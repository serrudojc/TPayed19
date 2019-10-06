#define CANTPREG 	3
#define CANTPART 	3
#define CANTTURNO	3
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;




struct Participante{
	int idParticipante;
	int puntos = 0;
	Historico* historial;
};

struct Historico{
	InfoHis info;
	Historico* sig;
};

struct InfoHis{
	char pregunta[120];
	char respuesta[120];
	bool correcta;
	int horaRespuesta; //borrador, luego implementar correctamente el tema de la hora
}

int main(){

	Participante participantes[CANTPART];
	
	
	cout<<"Hace una intro"<<endl;

	for(int i=0; i<CANTTURNO; i++){
		for(int j=0; j<CANTPART; j++){
			cout<<"simular respuesta de pregunta ["<<j+1<<"] de turno nº"<<i+1<<endl;
			cin>>respParticipante;

		}
	}
	
	return 0;
}

//coloco idParticipante
void colocarIdParticipante(Participante participantes[]){
	for(int i=0; i<CANTPART; i++){
		participantes[i].idParticipante = i+1;
	}
}

