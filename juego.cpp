//Primero cargo en memoria preguntas.dat y elijo de forma random una.
#include <iostream>
#include <string.h>
#include <stdlib.h>			//para rand
#include <time.h>
#include "funciones.hpp"
using namespace std;

//-------------------------------------------------------------------
int main(){
	//cabeza de lista cargada desde preguntas.dat
	Nodo *lista = NULL;

	//cabeza de lista cargada desde save.dat

	//puntero a estructura tipo Nodo que uso para guardar el nodo que me interesa de la lista
	Nodo *nodoCat = NULL;

	Participantes participante[CANTPART];
	ResPart auxReg;

	Consolidado cons;

	int catRdm, i=0, j=0, k=0;

	nuevaPartidaCargarPartida();

	//cargo en memoria las preguntas
	lista = leerPreguntasDat(lista);

	//inicializamos semilla para generador random
	srand((int)time(NULL)); 
	
	//inicializo id y nombre de participantes.
	inicializarParticipantes(participante);

	//empezamos juego. Recorro todos los turnos, no tiene en cuenta caso de empate.
	for(i=0; i<CANTTURNO; i++){
		for(j=0; j<CANTPART; j++){
			//recorro lista hasta encontrar la categoria del random
			cout<<"[turno "<<i<<"]["<<participante[j].nombrePart<<"]: ";

			//elijo una categoria random
			catRdm = get_rand(MIN, cantidadNodos(lista));

			//guardo el nodo encontrado para trabajar.
			nodoCat = buscarCat(lista, catRdm);

			//itero hasta encontrar una pregunta
			buscarPregunta(nodoCat, participante, j, auxReg, cons);			
		}
	}
	//en caso de empate, debo seguir con los empatados
	//voy a ordenar el vector participantes de mayor a menor por puntaje
	mostrar(participante,CANTPART);
	cout<<endl;

	//tratando de seguir con los empatados. 
	int cantEmpat;
	cantEmpat = cantDeEmpatados(participante, CANTPART);
	cout<<"cantidad de empatados: "<<cantEmpat<<endl;
	while(cantEmpat>1){
		//proceso empatados
		for(k=0; k<CANTPART; k++){
			//recorro lista hasta encontrar la categoria del random, para los que tngan flag empatado
			if(participante[k].empatado){
				cout<<"[desempate]["<<participante[k].nombrePart<<"]: ";

				//elijo una categoria random
				catRdm = get_rand(MIN, cantidadNodos(lista));

				//guardo el nodo encontrado para trabajar.
				nodoCat = buscarCat(lista, catRdm);

				//itero hasta encontrar una pregunta
				buscarPregunta(nodoCat, participante, k, auxReg, cons);	
			}
						
		}
		//ordenarBurbuja(participante, CANTPART);
		mostrar(participante,CANTPART);
		cantEmpat = cantDeEmpatados(participante, CANTPART);
		cout<<"cantidad de empatados = "<<cantEmpat<<endl;
	}

	ordenarBurbuja(participante, CANTPART);
	mostrar(participante,CANTPART);

	return 0;
}