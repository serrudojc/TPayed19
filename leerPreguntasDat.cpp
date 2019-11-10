//Programa que me permite leer el contenido de las preguntas a realizar
//preguntas.dat: son todas las preguntas habilitadas
//preguntasSave.dat son las preguntas disponibles, una vez que el juego estuvo en proceso

#include <iostream>
#include "funciones.hpp"
using namespace std;

//----------------------------------------------------

int main(){
	int opcion;
	FILE *arch;

	cout<<"[0] Leer preguntas.dat"<<endl;
	cout<<"[1] Leer preguntasSave.dat"<<endl;
	cin>>opcion;
	cin.ignore();

	do{
		switch(opcion){
			case 0:	
			{
				if((arch = fopen("preguntas.dat","rb")) == NULL){
					cout<<"Error, no existe preguntas.dat"<<endl;
					return 1;
				}
				break;
			}
			case 1:
			{
				if((arch = fopen("preguntasSave.dat","rb")) == NULL){
					cout<<"Error, no existe preguntasSave.dat"<<endl;
					return 2;
				}
				break;
			}
			default: cout<<"opcion incorrecta"<<endl;
		}						
	} while (opcion != 0 && opcion != 1);
	
	Categoria reg;
	fread(&reg, sizeof(Categoria),1,arch);

	while(!feof(arch)){
		cout<<"id: "<<"\t\t"<<reg.id<<endl;
		cout<<"Categoria: "<<"\t"<<reg.categoria<<endl;
		cout<<"Habilitada: "<<"\t"<<reg.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Pregunta   ["<<i<<"]: "<<reg.preguntas[i].pregunta<<endl;
			cout<<"Respuesta  ["<<i<<"]: "<<reg.preguntas[i].respuesta<<endl;
			cout<<"Habilitada ["<<i<<"]: "<<reg.preguntas[i].pregEnabled<<endl;
		}
		cout<<endl;
		fread(&reg, sizeof(Categoria),1,arch);
	}
	fclose(arch);z
	return 0;
}
