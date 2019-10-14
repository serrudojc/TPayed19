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


	//array de punteros a tipo Participantes. Tiene la cabeza de lista que guarda el historial.
	Participantes *part[CANTPART] = {NULL};
	ResPart auxReg;
	FILE *fp = fopen("historialJuego.dat", "wb");


	int catRandom, pregRandom;

//cargo en memoria las preguntas
	lista = leerPreguntasDat(lista);
//	mostrar(lista); //muestra lista cargada en memoria

//inicializamos semilla para generador random
	srand((int)time(NULL)); 	

//empezamos juego. 
	for(int i=0; i<CANTTURNO; i++){
		for(int j=0; j<CANTPART; j++){
			//recorro lista hasta encontrar la categoria del random
			cout<<"[turno][jugador] i["<<i<<"]j["<<j<<"]: ";

			catRandom = get_rand(MIN, cantidadNodos(lista));
			nodoCat = buscarCat(lista, catRandom);
			while(1){
				if(nodoCat->info.catEnabled){
					pregRandom = get_rand(MIN, CANTPREG);
					if(nodoCat->info.preguntas[pregRandom].pregEnabled){
						cout<<nodoCat->info.preguntas[pregRandom].pregunta<<": ";

						cin.getline(auxReg.resp, CHARRESP);								//guardo respuesta en auxReg

						nodoCat->info.preguntas[pregRandom].pregEnabled = false;
						nodoCat->info.catEnabled--;
						cout<<endl;

						
						strcpy(auxReg.pregunta, nodoCat->info.preguntas[pregRandom].pregunta);	//guardo pregunta en auxReg
						
						cout<<"imprimo resp part: "<<auxReg.resp<<endl;
						cout<<"imprimo resp orig: "<<nodoCat->info.preguntas[pregRandom].respuesta<<endl;

						if( strcmp(auxReg.resp, nodoCat->info.preguntas[pregRandom].respuesta) == 0)	//comparo respuestas
							auxReg.esCorrecta = true;
						//faltaria guardar hora y fecha
						agregarNodoJuego(part[j], auxReg);
						fwrite(&auxReg, sizeof(ResPart) ,1, fp);


						//salgo del while
						break;
					}else{
						cout<<"Repetido: cat:"<<catRandom<<" preg:"<<pregRandom<<endl;				
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

