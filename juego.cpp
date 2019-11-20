//Primero cargo en memoria preguntas.dat y elijo de forma random una.
#include <iostream>
#include <string.h>
#include <stdlib.h>			//para rand
#include <time.h>
#include "funciones.hpp"
using namespace std;
//INTENTANDO CON UNA BANDERA DE CARGA DE PARTIDA
//-------------------------------------------------------------------
int main(){
	//declaro cabeza de lista para preguntas a realizar
	Nodo *lista = NULL;

	//puntero a struct tipo Nodo que uso para guardar el nodo que me interesa de la lista
	Nodo *nodoCat = NULL;

	//declaro array de participante tipo Participantes
	Participantes participante[CANTPART];

	int catRdm, i, j, k, I, J;

	//Este flagCatDisp me indica si tengo categorias disponibles
	bool flagCatDisp = true;

	//estos flags los uso en caso de cargar una partida.
	bool partidaCargada = false, ialcanzado = false, jalcanzado = false, desempatar = false;

	//voy a cargar una partida o iniciar una nueva. 
	//Si cargo una partida, partidaCargada=true y recupero iteradores i,j
	lista = nuevaPartidaCargarPartida(participante, lista, partidaCargada, I, J); 

	//inicializamos semilla para generador random
	srand((int)time(NULL)); 
	
	//en caso de cargar una partida, verifico que no sea una partida empatada
	for(int s=0; s<CANTPART; s++){
		if(participante[s].rondaEmpate){
			desempatar = true;
			break;
		}		
	}

	//empezamos juego. Recorro todos los turnos. Antes pregunto si viene de un empate previo.
	if(!desempatar){		

		//en caso de cargar partida, voy a cargar el iterador i para continuar con el I turno del save
		for(i=0; i<CANTTURNO; i++){
			//si la partida está cargada y 
			if(partidaCargada && !ialcanzado){
				while(i<I){
					i++;
				}
				ialcanzado = true;
			}

			//En caso de no tener más categorias disponibles, salgo.
			if(!flagCatDisp)
				break;
			
			cout<<"\t- - - - - - - Ronda nº"<<i+1<<" - - - - - - -"<<endl<<endl;

			for(j=0; j<CANTPART; j++){
				//en caso de cargar partida, voy a cargar el iterador j para continuar
				if(partidaCargada && !jalcanzado){
					while(j<J){
						j++;
					}
					jalcanzado = true;
				}

				//verifico que haya categorias habilitadas
				if(!verificadorCategoriasDisponibles(lista)){
					flagCatDisp = false;
					break;
				}

				//elijo una categoria random
				catRdm = get_rand(cantidadNodos(lista));

				//guardo el nodo encontrado para trabajar.
				nodoCat = buscarCat(lista, catRdm);

				//itero hasta encontrar una pregunta
				buscarPregunta(nodoCat, participante, i, j);

				//tengo que guardar la lista de preguntas 
				guardarSaveLista(lista);
			}
		}
	}
	cout<<"\t*** Resultados Ronda ***"<<endl;
	mostrar(participante);
	cout<<endl;

	//en caso de empate, debo seguir con los empatados
	//Antes pregunto si viene de un empate previo.
	int cantEmpat;
	if(!desempatar){
		cantEmpat = cantDeEmpatados(participante);
	}
	while(cantEmpat>1){
		//verifico que haya categorias disponibles.
		if(!flagCatDisp)
			break;

		//Proceso en caso de empate
		for(k=0; k<CANTPART; k++){
			//busco categoria random, para participantes con flag empatado
			//pregunto si el participante k está habilitado para la ronda de desempate
			if(participante[k].rondaEmpate){
				//pregunto si el participante k de la ronda de desempate, ya respondió (en caso de cargar save)
				if(!participante[k].empatado){

					//verifico que haya categorias habilitadas
					if(!verificadorCategoriasDisponibles(lista)){
						flagCatDisp = false;
						break;
					}

					//elijo una categoria random
					catRdm = get_rand(cantidadNodos(lista));

					//guardo el nodo encontrado para trabajar.
					nodoCat = buscarCat(lista, catRdm);

					//itero hasta encontrar una pregunta
					buscarPregunta(nodoCat, participante, i, k);	

					//tengo que guardar la lista de preguntas 
					guardarSaveLista(lista);
				}
			}				
		}
		cout<<"\n\t*** Resultados Desempate ***"<<endl;
		mostrar(participante);
		cout<<endl;
		cantEmpat = cantDeEmpatados(participante);
	}

	if(!flagCatDisp)
		cout<<"!!! No hay más categorías disponibles."<<endl<<endl;

	//ordeno posiciones y muestro tabla de resultados
	cout<<"\n\t*** Tabla de Resultados ***"<<endl;
	ordenarBurbuja(participante, CANTPART);
	mostrar(participante);
	mostrarGanador(participante);
	cout<<endl;

	char leer;
	cout<<"\tLeer Respuestas de Preguntas.dat o PreguntasSave.dat? [s][n]: ";
	cin>>leer;
	if (leer == 's')
		leerRespuestas();

	return 0;
}