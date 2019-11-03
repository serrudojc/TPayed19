//Primero cargo en memoria preguntas.dat y elijo de forma random una.
#include <iostream>
#include <string.h>
#include <stdlib.h>			//para rand
#include <time.h>
#include "funciones.hpp"
using namespace std;

//-------------------------------------------------------------------
int main(){
	//declaro cabeza de lista para preguntas a realizar
	Nodo *lista = NULL;

	//puntero a struct tipo Nodo que uso para guardar el nodo que me interesa de la lista
	Nodo *nodoCat = NULL;

	//declaro array de participante tipo Participantes
	Participantes participante[CANTPART];

	int catRdm, i=0, j=0, k=0;

	//voy a cargar una partida o iniciar una nueva. 
	nuevaPartidaCargarPartida(participante); cout<<endl<<endl;

	//cargo en memoria las preguntas
	lista = leerPreguntasDat(lista);

	//inicializamos semilla para generador random
	srand((int)time(NULL)); 
	
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
			buscarPregunta(nodoCat, participante, j);

			//tengo que guardar la lista de preguntas 
			guardarSaveLista(lista);
		}
	}
	//en caso de empate, debo seguir con los empatados
	//voy a ordenar el vector participantes de mayor a menor por puntaje
	cout<<"***Resultados Ronda***"<<endl;
	mostrar(participante,CANTPART);
	cout<<endl;

	int cantEmpat;
	cantEmpat = cantDeEmpatados(participante, CANTPART);
	
	while(cantEmpat>1){
		//Proceso en caso de empate
		for(k=0; k<CANTPART; k++){
			//busco categoria random, para participantes con flag empatado
			if(participante[k].empatado){
				cout<<"[desempate]["<<participante[k].nombrePart<<"]: ";

				//elijo una categoria random
				catRdm = get_rand(MIN, cantidadNodos(lista));

				//guardo el nodo encontrado para trabajar.
				nodoCat = buscarCat(lista, catRdm);

				//itero hasta encontrar una pregunta
				buscarPregunta(nodoCat, participante, k);	

				//tengo que guardar la lista de preguntas 
				guardarSaveLista(lista);
			}				
		}
		mostrar(participante,CANTPART);
		cantEmpat = cantDeEmpatados(participante, CANTPART);
	}

	//ordeno posiciones y muestro tabla de resultados
	ordenarBurbuja(participante, CANTPART);
	mostrar(participante,CANTPART);

	return 0;
}