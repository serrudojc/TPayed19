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
	bool flag = true;

	//voy a cargar una partida o iniciar una nueva. 
	lista = nuevaPartidaCargarPartida(participante, lista); cout<<endl<<endl;

	//inicializamos semilla para generador random
	srand((int)time(NULL)); 
	
	//empezamos juego. Recorro todos los turnos, no tiene en cuenta caso de empate.
	for(i=0; i<CANTTURNO; i++){
		if(!flag)
			break;
		cout<<"\t*** Ronda nº"<<i+1<<" ***"<<endl<<endl;
		for(j=0; j<CANTPART; j++){
			//recorro lista hasta encontrar la categoria del random
			cout<<"["<<i+1<<"] - "<<participante[j].nombrePart<<" -: "<<endl;

			//verifico que haya categorias habilitadas
			if(!verificadorCategoriasDisponibles(lista)){
				flag = false;
				break;
			}

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
	cout<<"\t*** Resultados Ronda ***"<<endl;
	mostrar(participante,CANTPART);
	cout<<endl;
	int cantEmpat;
	cantEmpat = cantDeEmpatados(participante, CANTPART);
	
	while(cantEmpat>1){
		if(!flag)
			break;
		//Proceso en caso de empate
		for(k=0; k<CANTPART; k++){
			//busco categoria random, para participantes con flag empatado
			if(participante[k].empatado){
				cout<<"[desempate]["<<participante[k].nombrePart<<"]: ";

				//verifico que haya categorias habilitadas
				if(!verificadorCategoriasDisponibles(lista)){
					flag = false;
					break;
				}

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
		cout<<"\t*** Resultados Desempate***"<<endl;
		mostrar(participante,CANTPART);
		cout<<endl;
		cantEmpat = cantDeEmpatados(participante, CANTPART);
	}

	if(!flag)
		cout<<"!!! No hay más categorías disponibles."<<endl<<endl;

	//ordeno posiciones y muestro tabla de resultados
	cout<<"\t*** Tabla de Resultados ***"<<endl;
	ordenarBurbuja(participante, CANTPART);
	mostrar(participante,CANTPART);
	cout<<endl;

	return 0;
}