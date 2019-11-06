#include <iostream>
#include <string.h>
#include <string>		//hora
#include <stdlib.h>		//hora
#include <ctime> 		//hora
#include <unistd.h>		//sleep
#include <iomanip>		//setw
#include "funciones.hpp"
using namespace std;

//-------------------------------------------------------
void agregarNodo(Nodo*& lista, Categoria v){
	Nodo* p = new Nodo(); 
	p->info = v;
	p->sig = NULL;

	if(lista == NULL){	
		lista = p;
	} else {		
		Nodo* aux = lista;
		while(aux->sig != NULL){
			aux = aux->sig;
		}
	aux->sig = p;
	}
}
//-------------------------------------------------------
Categoria eliminarPrimerNodo (Nodo*& lista){
	Nodo* aux = lista; 	//como es por referencia
	Categoria valor; 
	strcpy(valor.categoria,"-1");	//chequear esta parte
	if(aux != NULL){	//chequeo que no sea una lista vacia
		valor = lista->info;
		lista = lista->sig;
		delete aux;
	}
	return valor;	//si la lista esta vacia, devuelvo -1, sino, devuelvo el valor del primer nodo
}
//-------------------------------------------------------
Nodo *nuevaPartidaCargarPartida(Participantes participante[], Nodo *lista, bool &partidaCargada, int &I, int &J){
	int modalidad;
	
	do{
		cout<<"\t\t[0] Nueva partida."<<endl;
		cout<<"\t\t[1] Cargar última partida."<<endl;
		cout<<"Elegir opción..: ";
		cin>>modalidad;
		cin.ignore(); 
		switch(modalidad){
			case 0:{ 
				//nueva partida: abro y cierro save.dat, sobreescribiendo si ya existia
				FILE *fp = fopen("save.dat", "wb"); 
				fclose(fp);

				//inicializo id y nombre de participantes.
				inicializarParticipantes(participante);  

				//cargo en memoria las preguntas
				lista = leerPreguntasDat(lista, "preguntas.dat");

				break;}
			case 1:{ 
				//continuar partida: Tengo que abrir preguntasSave.dat 
				//La partida continua save.dat continua con append en funcion buscarPregunta, asi q no hago nada

				//cargo en memoria las preguntas
				lista = leerPreguntasDat(lista, "preguntasSave.dat");

				recuperarParticipantes(participante, I, J);
				partidaCargada = true;
				break;}
			default: cout<<"Opción incorrecta."<<endl; break;
		}

	}while(modalidad != 0 && modalidad != 1);
	return lista;
}
//--------------------------------------------------------------------------
void inicializarParticipantes(Participantes participante[]){
	for(int j=0; j<CANTPART; j++){
		participante[j].idPart = j+1;
		cout<<"Nombre participante ["<<j+1<<"]: ";
		cin.getline(participante[j].nombrePart, CHARCATEG);
	}
	cout<<endl;
}
//--------------------------------------------------------------------------
Nodo *leerPreguntasDat(Nodo *&lista, const char archivo[]){
	FILE * arch = fopen(archivo,"rb"); 
	Categoria reg;
	fread(&reg, sizeof(Categoria),1,arch);

	//Cargo preguntas.dat en memoria
	while(!feof(arch)){
		//mando a la lista
		agregarNodo(lista, reg);
		fread(&reg, sizeof(Categoria),1,arch);
		}
	fclose(arch);
	return lista;
}
//--------------------------------------------------------------------------
void recuperarParticipantes(Participantes participante[], int &I, int &J){
	int t=0;
	FILE *fp = fopen("save.dat", "rb");
	Participantes reg;
	fread(&reg, sizeof(Participantes),1,fp);
	while(!feof(fp)){
		if(t<CANTPART){
			participante[t] = reg;
			I = participante[t].i;
			J = participante[t].j;
			//cout<<"\tparticipante["<<t<<"]."<<reg.i<<" "<<reg.j<<endl;
			t++;
		}else{
			t=0;
			participante[t] = reg;
			I = participante[t].i;
			J = participante[t].j;
			//cout<<"\tparticipante["<<t<<"]."<<reg.i<<" "<<reg.j<<endl;
			t++;
		}	
		fread(&reg, sizeof(Participantes),1,fp);
	}
	//cout<<"devuelvo I="<<I<<" J="<<J<<" en recuperarParticipantes()"<<endl;
	//cout<<"participante["<<t-1<<"].rondaEmpate: "<<participante[t-1].rondaEmpate<<endl;
	cout<<endl;
	fclose(fp);
}

bool verificarEmpatados(Participantes participante[]){
	int t=0;
	bool hayEmpatados = false;
	FILE *fp = fopen("save.dat", "rb");
	Participantes reg;
	fread(&reg, sizeof(Participantes),1,fp);
	while(!feof(fp)){
		if(reg.rondaEmpate){
			hayEmpatados = true;
		}	
		fread(&reg, sizeof(Participantes),1,fp);
	}
	fclose(fp);
	return hayEmpatados;
}

//--------------------------------------------------------------------------
//devuelve un entero entre min y max
int get_rand(int min, int max){
	return rand()%(max);
}
//-------------------------------------------------------------------------
//devuelve cantidad de nodos de una lista
int cantidadNodos (Nodo* lista){
	Nodo* aux = lista;
	int contador = 0;
	while(aux != NULL){
		contador++;
		aux = aux->sig;
	}
	return contador;
}
//------------------------------------------------------------------------
bool verificadorCategoriasDisponibles(Nodo *lista){
	int cont =0;
	Nodo *aux = lista;
	while(aux != NULL){
		if(!aux->info.catEnabled)
			cont++;
		aux = aux->sig;
	}
	if(cont == cantidadNodos(lista)){
		cout<<"No hay categorias disponibles"<<endl;
		return false;	
	}
	return true;
}
//-------------------------------------------------------------------------
Nodo* buscarCat(Nodo* lista, int v){	
	Nodo* aux = lista;	
	while((aux != NULL) && (aux->info.id != v) ){	
		aux = aux->sig;
	}
	return aux;
}
//-------------------------------------------------------------------------
void buscarPregunta(Nodo *&nodoCat, Participantes participante[], int i, int &j){

	ResPart auxReg; 
	Participantes cons;

	while(1){
		//pregunto si la categoria está habilitada.
		if(nodoCat->info.catEnabled){
			//elijo una pregunta random	
			int pregRdm = get_rand(MIN, CANTPREG);

			//si la pregunta está habilitada, proceso y salgo del while. Sino, sigo en el while
			if(nodoCat->info.preguntas[pregRdm].pregEnabled){
				//realizo la pregunta
				cout<<nodoCat->info.preguntas[pregRdm].pregunta<<": "<<endl;
				cout<<":> ";
									
				//guardo respuesta en auxReg (tipo ResPart)
				cin.getline(auxReg.resp, CHARRESP);								
				
				//desactivo la pregunta
				nodoCat->info.preguntas[pregRdm].pregEnabled = false;
				
				//decremento la cantidad de preguntas disponibles en categoria
				nodoCat->info.catEnabled--;
				
				//guardo pregunta en auxReg
				strcpy(auxReg.pregunta, nodoCat->info.preguntas[pregRdm].pregunta);	
				//comparo respuestas
				if( strcmp(auxReg.resp, nodoCat->info.preguntas[pregRdm].respuesta) == 0){	
					participante[j].puntaje++;
					strcpy(auxReg.esCorrecta , "Correcta");
					//en caso de empate, marco flag empatado con true, para saber q este jugador ya respondió
					if(participante[j].rondaEmpate)
						participante[j].empatado = true;
				}
				//guardo hora
				strcpy(auxReg.tiempo, obtenerHora(auxReg.tiempo));

				//preparo datos para guardar en archivo
				cons.puntaje = participante[j].puntaje;
				cons.idPart = participante[j].idPart;
				strcpy(cons.nombrePart, participante[j].nombrePart);
				cons.info =	auxReg;
				cons.empatado = participante[j].empatado;
				cons.rondaEmpate = participante[j].rondaEmpate;
				
				//guardo el valor de j
				int h = j;
				if(h<CANTPART-1){
					h++;
				}else{
					h = 0;
					i++;
				}

				//guardo próximo turno
				cons.i = i;
				cons.j = h;

				//abro archivo (para tener siempre el ultimo guardado)
				FILE *fp = fopen("save.dat", "a");
				fwrite(&cons, sizeof(Participantes) ,1, fp);
				fclose(fp);

				//reinicio estado de pregunta
				strcpy(auxReg.esCorrecta , "Incorrecta");

				verEstado();

				break;
			}else{
				//la pregunta random ya se usó. Busco otra preg en la categoria
				//cout<<"Repetido: cat:"<<catRdm<<" preg:"<<pregRdm<<endl;				
			}
		}else{
			//Categoria sin preguntas disponibles. vuelvo a elegir categoria
			//cout<<"categoria "<<nodoCat->info.id<<" desactivada"<<endl;
			j--;
			break;
		}		
	}
}
//-------------------------------------------------------------------------
char *obtenerHora(char *fechaChar){
	string fechaString;
        
    // Declaring argument for time() 
    time_t tt; 
  
    // Declaring variable to store return value of localtime() 
    tm* ti; 

    // Applying time() 
    time (&tt); 
  
    // Using localtime() 
    ti = localtime(&tt); 

    fechaString = asctime(ti);
    strcpy(fechaChar, fechaString.c_str()); //or pass &fechaString[0]
    //cout<<fechaChar<<endl;
     
    return fechaChar;
}
//-----------------------------------------------------------------------------
//Guardo las preguntas ya realizadas, para que no se tengan en cuenta en caso de retomar partida
void guardarSaveLista (Nodo* lista){ 
	Nodo *aux = lista;
	Categoria reg;

	FILE *pointer = fopen("preguntasSave.dat", "wb");

	while(aux != NULL){
		
		reg = aux->info;
		fwrite (&reg, sizeof(Categoria), 1, pointer);
		aux = aux->sig;
	}
	fclose(pointer);		
}
//-----------------------------------------------------------------------------
void verEstado(){
	string est;
	cout<<"Ver histórico hasta el momento? [y][n]:";
	cin>>est;
	cin.ignore();
	if (est == "y" || est == "Y")
		leerSave();
	cout<<endl;
}
//-----------------------------------------------------------------------------
void leerSave(){
	FILE * arch = fopen("save.dat","rb");
	Participantes reg;
	fread(&reg, sizeof(Participantes),1,arch);
	cout<<"--------------------------"<<endl;
	while(!feof(arch)){
		cout<<"Id participante:"<<reg.idPart<<" || "<<reg.nombrePart<<" || "<<reg.info.tiempo;
		cout<<"Pregunta: "<<reg.info.pregunta<<endl;
		cout<<"Respuesta: "<<reg.info.resp<<endl;
		cout<<"Es correcta?: "<<"\t\t"<<reg.info.esCorrecta<<endl;
		cout<<"# Puntaje: "<<reg.puntaje<<endl;
		cout<<"i="<<reg.i<<", j="<<reg.j<<endl;
		cout<<"empatado: "<<reg.empatado<<" rondaEmpate: "<<reg.rondaEmpate<<endl;
		cout<<endl;
		fread(&reg, sizeof(Participantes),1,arch);
	}
	fclose(arch);
	cout<<"--------------------------"<<endl;
}
//--------------------------------------------------------------------------

void mostrar (Participantes arr[],int len){
	cout<<setw(38)<<setfill('-')<<'\n'<<setfill(' ');
	cout<<setw(5)<<"id"<<setw(8)<<"Puntaje"<<setw(25)<<"Participante"<<endl;
	cout<<setw(38)<<setfill('-')<<'\n'<<setfill(' ');
	for(int i=0; i<len; i++){
		cout<<setw(5)<<arr[i].idPart<<setw(5)<<arr[i].puntaje<<setw(28)<<arr[i].nombrePart<<endl;
	}
}
//-------------------------------------------------------------------------------
void mostrar (Nodo* lista){ 
	Nodo *aux = lista;
	while(aux != NULL){
		cout<<aux->info.id<<endl;
		cout<<aux->info.categoria<<endl;
		cout<<aux->info.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Pregunta   ["<<i<<"]: "<<aux->info.preguntas[i].pregunta<<endl;
			cout<<"Respuesta  ["<<i<<"]: "<<aux->info.preguntas[i].respuesta<<endl;
			cout<<"Habilitada ["<<i<<"]: "<<aux->info.preguntas[i].pregEnabled<<endl;
		}
		cout<<endl;
		aux = aux->sig;
	}		
}
//--------------------------------------------------------------------------
void mostrarUnNodo(Nodo* lista){ 
	Nodo *aux = lista;
	while(aux != NULL){
		cout<<aux->info.id<<endl;
		cout<<aux->info.categoria<<endl;
		cout<<aux->info.catEnabled<<endl;
		for(int i=0; i<CANTPREG; i++){
			cout<<"Pregunta   ["<<i<<"]: "<<aux->info.preguntas[i].pregunta<<endl;
			cout<<"Respuesta  ["<<i<<"]: "<<aux->info.preguntas[i].respuesta<<endl;
			cout<<"Habilitada ["<<i<<"]: "<<aux->info.preguntas[i].pregEnabled<<endl;
		}
		cout<<endl;		
		aux = NULL;		
	}
}
//----------------------------------------------------------------------------
/* Los empatados tienen dos flags: 
participante[].rondaEmpate que significa que está en una ronda de desempate y hasta que 
todos hayan respondido, seguiran en la ronda.
participante[].empatado significa que dentro de la ronda, respondió bien y sigue.
*/

int cantDeEmpatados(Participantes arr[]){
	int mayorPuntaje = 0, cont =0;
	Participantes cons;

	for(int i=0; i<CANTPART; i++){
		if(arr[i].puntaje>=mayorPuntaje){
			mayorPuntaje = arr[i].puntaje;
		}
	}
	//Activo flag de empatados a los que tienen el mayor puntaje
	for(int i=0; i<CANTPART; i++){
		if(arr[i].puntaje == mayorPuntaje){
			arr[i].rondaEmpate = true;
			cont++;
		}else{
			arr[i].rondaEmpate = false;
		}
		strcpy(arr[i].info.resp,"*** Guardado flags de empatados ***");
		arr[i].empatado = false;	
	}

	FILE *fp = fopen("save.dat", "a");
	for(int i=0; i<CANTPART; i++){
		cons = arr[i];
		fwrite(&cons, sizeof(Participantes) ,1, fp);
	}
	fclose(fp);

	return cont;
}
//---------------------------------------------------------------------------
void ordenarBurbuja (Participantes arr[], int len){
	Participantes aux;
	for(int i=0; i<len-1; i++){
		for(int j=0; j<len-1;j++){
			if(arr[j].puntaje < arr[j+1].puntaje){
				// funcion de swap
				aux = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = aux;
			}
		}
	}
}
//--------------------------------------------------------------------------