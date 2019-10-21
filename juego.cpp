//Primero cargo en memoria preguntas.dat y elijo de forma random una.
#include <iostream>
#include <string.h>
#include <stdlib.h>			//para rand
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

	//inicializo id y nombre de participantes.
	for(int j=0; j<CANTPART; j++){
		participante[j].idPart = j+1;
		cout<<"Nombre participante ["<<j+1<<"]: ";
		cin.getline(participante[j].nombrePart, CHARCATEG);
	}
	cout<<endl;

	//empezamos juego. Recorro todos los turnos, no tiene en cuenta caso de empate.
	for(int i=0; i<CANTTURNO; i++){
		for(int j=0; j<CANTPART; j++){
			//recorro lista hasta encontrar la categoria del random
			cout<<"[turno "<<i<<"]["<<participante[j].nombrePart<<"]: ";

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

						//guardo datos en un nodo, para mostrar en tiempo de ejecucion
						agregarNodoPart(participante[j].part, auxReg);

						//guardo datos en consolidado, para guardar en archivo
						cons.puntaje = participante[j].puntaje;
						cons.idPart = participante[j].idPart;
						strcpy(cons.nombrePart, participante[j].nombrePart);
						cons.proxTurno = participante[j].proxTurno;
						cons.info =	auxReg;
						fwrite(&cons, sizeof(Consolidado) ,1, fp);

						//reinicio resultado de pregunta
						strcpy(auxReg.esCorrecta , "Incorrecta");

						//salgo del while, encontré pregunta.
						break;
					}else{
						//la pregunta random ya se usó. Busco otra preg en la categoria
						//cout<<"Repetido: cat:"<<catRdm<<" preg:"<<pregRdm<<endl;				
					}
				}else{
					//Categoria sin preguntas disponibles. vuelvo a elegir categoria
					cout<<"categoria "<<nodoCat->info.id<<" desactivada"<<endl;
					j--;
					//salgo del while, no encontré prgunta disp en esta categoria.
					break;
				}		
			}
			//en caso de empate tengo que seguir con los empatados
		}
	}
	//en caso de empate, debo seguir con los empatados
	//voy a ordenar el vector participantes de mayor a menor por puntaje
	mostrar(participante,CANTPART);
	cout<<endl;
	ordenarBurbuja(participante, CANTPART);
	mostrar(participante,CANTPART);

	//tratando de seguir con los empatados.
	int cantEmpat;
	cantEmpat = cantDeEmpatados(participante, CANTPART);
	cout<<"cantidad de empatados: "<<cantEmpat;
	while(cantEmpat>1){
		//proceso empatados
		for(int j=0; j<cantEmpat; j++){
			//recorro lista hasta encontrar la categoria del random
			cout<<"[desempate]["<<participante[j].nombrePart<<"]: ";

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
						participante[j].proxTurno =  participante[j+1].idPart;

						//guardo datos en un nodo, para mostrar en tiempo de ejecucion
						agregarNodoPart(participante[j].part, auxReg);

						//guardo datos en consolidado, para guardar en archivo
						cons.puntaje = participante[j].puntaje;
						cons.idPart = participante[j].idPart;
						strcpy(cons.nombrePart, participante[j].nombrePart);
						cons.proxTurno = participante[j].proxTurno;
						cons.info =	auxReg;
						fwrite(&cons, sizeof(Consolidado) ,1, fp);

						//reinicio resultado de pregunta
						strcpy(auxReg.esCorrecta , "Incorrecta");

						//salgo del while, encontré pregunta.
						break;
					}else{
						//la pregunta random ya se usó. Busco otra preg en la categoria
						//cout<<"Repetido: cat:"<<catRdm<<" preg:"<<pregRdm<<endl;				
					}
				}else{
					//Categoria sin preguntas disponibles. vuelvo a elegir categoria
					cout<<"categoria "<<nodoCat->info.id<<" desactivada"<<endl;
					j--;
					//salgo del while, no encontré prgunta disp en esta categoria.
					break;
				}		
			}
			//en caso de empate tengo que seguir con los empatados
		}
		ordenarBurbuja(participante, CANTPART);
		mostrar(participante,CANTPART);
		cantEmpat = cantDeEmpatados(participante, CANTPART);
		cout<<"cantidad de empatados = "<<cantEmpat<<endl;
	}

	fclose(fp);
	return 0;
}