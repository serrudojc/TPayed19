//Primero cargo en memoria preguntas.dat y elijo de forma random una.
#include <iostream>
#include <string.h>
#include <stdlib.h>			//para rand
#include <unistd.h>			//sleep
#include "funciones.hpp"
using namespace std;

//-------------------------------------------------------------------
int main(){
	//cabeza de lista cargada desde preguntas.dat
	Nodo *lista = NULL;

	//puntero a estructura tipo Nodo que uso para guardar el nodo que me interesa de la lista
	Nodo *nodoCat = NULL;

	Participantes participante[CANTPART];
	ResPart auxReg;

	Consolidado cons;

	FILE *fp = fopen("historialJuego.dat", "wb");

	int catRdm, pregRdm;

	//cargo en memoria las preguntas
	lista = leerPreguntasDat(lista);

	//inicializamos semilla para generador random
	srand((int)time(NULL)); 	

	//empezamos juego. Recorro todos los turnos, no tiene en cuenta caso de empate.
	for(int i=0; i<CANTTURNO; i++){
		for(int j=0; j<CANTPART; j++){
			//recorro lista hasta encontrar la categoria del random
			cout<<"[turno][jugador] i["<<i<<"]j["<<j<<"]: ";

			//elijo una categoria random
			catRdm = get_rand(MIN, cantidadNodos(lista));

			//guardo el nodo encontrado para trabajar.
			nodoCat = buscarCat(lista, catRdm);

			//itero hasta encontrar una pregunta
			while(1){
				//pregunto si la categoria está habilitada.
				if(nodoCat->info.catEnabled){
					//elijo una pregunta random	
					pregRdm = get_rand(MIN, CANTPREG);

					//si la pregunta está habilitada, proceso y salgo del while. Sino, vuelvo entrar al while.
					if(nodoCat->info.preguntas[pregRdm].pregEnabled){
						cout<<nodoCat->info.preguntas[pregRdm].pregunta<<": ";
						
						//guardo respuesta en auxReg
						cin.getline(auxReg.resp, CHARRESP);								
						
						//desactivo la pregunta
						nodoCat->info.preguntas[pregRdm].pregEnabled = false;
						
						//decremento la cantidad de preguntas disponibles en categoria
						nodoCat->info.catEnabled--;
						cout<<endl;
						
						//guardo pregunta en auxReg
						strcpy(auxReg.pregunta, nodoCat->info.preguntas[pregRdm].pregunta);	
						
						//comparo respuestas
						if( strcmp(auxReg.resp, nodoCat->info.preguntas[pregRdm].respuesta) == 0){	
							participante[j].puntaje++;
							strcpy(auxReg.esCorrecta , "Correcta");
						}
						//guardo hora
						strcpy(auxReg.tiempo, obtenerHora(auxReg.tiempo));

						//guardo jugador proximo turno
						participante[j].proxTurno =  ((j+1)%CANTPART)+1;

						agregarNodoPart(participante[j].part, auxReg);

						cons.puntaje = participante[j].puntaje;
						cons.proxTurno = participante[j].proxTurno;
						cons.info =	auxReg;
						fwrite(&cons, sizeof(Consolidado) ,1, fp);

						//reinicio resultado de pregunta
						strcpy(auxReg.esCorrecta , "Incorrecta");

						//salgo del while
						break;
					}else{
						cout<<"Repetido: cat:"<<catRdm<<" preg:"<<pregRdm<<endl;				
					}
				}else{
					//Categoria sin preguntas disponibles. vuelvo a elegir categoria
					cout<<"categoria "<<nodoCat->info.id<<" desactivada"<<endl;
					j--;
					//salgo del while
					break;
				}		
			}
		}
	}
	fclose(fp);
	return 0;
}