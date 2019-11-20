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
	
	mostrarIntro();
	do{
		cout<<"\t\t[0] Nueva partida."<<endl;
		cout<<"\t\t[1] Cargar última partida.\n"<<endl;
		cout<<"\t\tElegir opción: ";
		cin>>modalidad;
		cin.ignore(); 
		switch(modalidad){
			case 0:{ 
				//nueva partida: abro y cierro save.dat, sobreescribiendo si ya existia
				cout<<"\n\t- - - - - - Comenzando partida - - - - - -\n"<<endl;
				FILE *fp = fopen("save.dat", "wb"); 
				fclose(fp);

				//inicializo id y nombre de participantes.
				inicializarParticipantes(participante);  

				//cargo en memoria las preguntas
				lista = leerPreguntasDat(lista, "preguntas.dat");

				break;}
			case 1:{ 
				//verifico que exista un save anterior
				FILE *arch;
				if((arch = fopen("save.dat","rb"))==NULL){
					cout<<"Error, no exite partida guardada. Empezar nueva."<<endl;
					modalidad = 3;
					break;
				}
				cout<<"\n\t- - - - - - Retormando partida - - - - - -\n"<<endl;
				//continuar partida: Tengo que abrir preguntasSave.dat 
				//La partida continua save.dat continua con append en funcion buscarPregunta, asi q no hago nada

				//cargo en memoria las preguntas
				lista = leerPreguntasDat(lista, "preguntasSave.dat");

				recuperarParticipantes(participante, I, J);
				partidaCargada = true;
				break;}
			default: cout<<"\n\tOpción incorrecta !!!\n"<<endl; break;
		}

	}while(modalidad != 0 && modalidad != 1);
	return lista;
}
//--------------------------------------------------------------------------
void inicializarParticipantes(Participantes participante[]){
	Participantes cons;
	for(int i=0; i<CANTPART; i++){
		participante[i].idPart = i+1;
		cons.idPart = i+1;

		cout<<"Nombre participante ["<<i+1<<"]: ";
		
		cin.getline(participante[i].nombrePart, CHARCATEG);
		strcpy(cons.nombrePart, participante[i].nombrePart);

		//coloco "ignorar" como respuesta, para no tener en cuenta este estos registros al mostrar o procesar
		strcpy(cons.info.resp,"ignorar");
		
		FILE *fp = fopen("save.dat", "a");
		fwrite(&cons, sizeof(Participantes) ,1, fp);
		fclose(fp);
	}
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
//En caso de cargar save, tengo que recuperar los iteradores i,j para continuar con el for de los turnos
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
	cout<<"devuelvo I="<<I<<" J="<<J<<" en recuperarParticipantes()"<<endl;
	//cout<<"participante["<<t-1<<"].rondaEmpate: "<<participante[t-1].rondaEmpate<<endl;
	cout<<endl;
	fclose(fp);
}
//no estoy usando esto
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
int get_rand(int max){
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
			int pregRdm = get_rand(CANTPREG);

			//si la pregunta está habilitada, proceso y salgo del while. Sino, sigo en el while
			if(nodoCat->info.preguntas[pregRdm].pregEnabled){
				
				if(participante[j].rondaEmpate == true){
					cout<<"[desempate]["<<participante[j].nombrePart<<"]: ";
				}else{
					cout<<"Ronda ["<<i+1<<"] # "<<participante[j].nombrePart<<" #"<<endl;
				}

				//realizo la pregunta
				cout<<nodoCat->info.preguntas[pregRdm].pregunta<<": "<<endl;
				cout<<":> ";
									
				//guardo respuesta en auxReg (tipo ResPart)
				cin.getline(auxReg.resp, CHARRESP);								
				estandarizarTexto(auxReg.resp);

				//desactivo la pregunta
				nodoCat->info.preguntas[pregRdm].pregEnabled = false;
				
				//decremento la cantidad de preguntas disponibles en categoria
				nodoCat->info.catEnabled--;
				
				//guardo pregunta en auxReg
				strcpy(auxReg.pregunta, nodoCat->info.preguntas[pregRdm].pregunta);	
				
				//uso var auxiliar para no estandarizar la respuesta (al mostrar respuesta, por ej, que los paises empiezen con mayúscula)
				char solucion[CHARRESP]; 
				strcpy(solucion,nodoCat->info.preguntas[pregRdm].respuesta);
				//comparo respuestas
				if( strcmp(auxReg.resp, estandarizarTexto(solucion)) == 0){	
					participante[j].puntaje++;
					strcpy(auxReg.esCorrecta , "Correcta");
					cout<<" :D Respuesta Correcta!"<<endl;
				}else{
					cout<<" :( :( :( incorrecto, la respuesta era: "<<nodoCat->info.preguntas[pregRdm].respuesta<<endl;
				}
				//en caso de empate, marco flag empatado con true, para saber q este jugador ya respondió
				if(participante[j].rondaEmpate)
					participante[j].empatado = true;

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

				verEstado(participante);
				verPuntuacion(participante);

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
void verEstado(Participantes participante[]){
	string est;
	cout<<"Ver histórico hasta el momento? [y][n]:";
	cin>>est;
	cin.ignore();
	if (est == "y" || est == "Y")
		leerSave(participante);
	cout<<endl;
}
//-----------------------------------------------------------------------------
void leerSave(Participantes participante[]){
	FILE * arch = fopen("save.dat","rb");
	Participantes reg;
	int part;
	fread(&reg, sizeof(Participantes),1,arch);
	cout<<"\n\t#############   HISTORIAL   ##################\n"<<endl;
	for(int i=0; i<CANTPART; i++){
		cout<<"\t["<<participante[i].idPart<<"] "<<participante[i].nombrePart<<endl;
	}
	cout<<"\n\tElegir participante: (0 para todos): ";
	cin>>part; 
	cin.ignore();
	cout<<"\n\t..............................................\n";
	
	if(part == 0){
		while(!feof(arch)){
			//si no tiene como respuesta "ignorar, muestro"
			if(strcmp(reg.info.resp,"ignorar")){
				mostrarSave(reg);
			}
			fread(&reg, sizeof(Participantes),1,arch);	
		}
	}else{
		while(!feof(arch) && reg.info.resp != "ignorar"){
			//Muestro el participante elegido y si no tiene como respuesta "ignorar"
			if(reg.idPart == part && strcmp(reg.info.resp,"ignorar")){
				mostrarSave(reg);
			}		
			fread(&reg, sizeof(Participantes),1,arch);
		}	
	}
	fclose(arch);
	cout<<"\t##############################################"<<endl;
}
//--------------------------------------------------------------------------
void mostrarSave(Participantes reg){

	cout<<"* id:"<<reg.idPart<<" || "<<reg.nombrePart<<" || "<<reg.info.tiempo;
	cout<<"#Pregunta: "<<reg.info.pregunta<<endl;
	cout<<"#Respuesta: "<<reg.info.resp<<endl;
	cout<<"* Es correcta?: \t"<<reg.info.esCorrecta<<"\t# Puntaje: "<<reg.puntaje<<endl;
	cout<<"i="<<reg.i<<", j="<<reg.j<<" ";
	cout<<"empatado: "<<reg.empatado<<" rondaEmpate: "<<reg.rondaEmpate<<endl;
	cout<<endl;
}
//--------------------------------------------------------------------------
void verPuntuacion(Participantes participante[]){
	string est;
	cout<<"Ver puntuación? [y][n]:";
	cin>>est;
	cin.ignore();
	if (est == "y" || est == "Y")
		mostrar(participante);
	cout<<endl;
}
//---------------------------------------------------------------------------
void mostrar (Participantes arr[]){
	cout<<setw(38)<<setfill('-')<<'\n'<<setfill(' ');
	cout<<setw(5)<<"id"<<setw(8)<<"Puntaje"<<setw(25)<<"Participante"<<endl;
	cout<<setw(38)<<setfill('-')<<'\n'<<setfill(' ');
	for(int i=0; i<CANTPART; i++){
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
//----------------------------------------------------------------------------
/* Los empatados tienen dos flags: 
participante[].rondaEmpate que significa que está en una ronda de desempate y hasta que 
todos hayan respondido, seguiran en la ronda.
participante[].empatado significa que dentro de la ronda, ya respondió (en caso de retomar partida).
*/

int cantDeEmpatados(Participantes arr[]){
	int mayorPuntaje = 0, cont =0;
	Participantes cons;

	for(int i=0; i<CANTPART; i++){
		if(arr[i].puntaje>=mayorPuntaje){
			mayorPuntaje = arr[i].puntaje;
		}
	}
	//Activo flag de rondaEmpate a los que tienen el mayor puntaje
	for(int i=0; i<CANTPART; i++){
		if(arr[i].puntaje == mayorPuntaje){
			arr[i].rondaEmpate = true;
			cont++;
		}else{
			arr[i].rondaEmpate = false;
		}
		strcpy(arr[i].info.resp,"ignorar");
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
//Convierto de mayús a minúsc. No puedo sacar acentos.
char *estandarizarTexto(char texto[]){
	int i=0;
	char acentos[] = "áéíóú";
	//cout<<acentos<<endl;
	char valor[]= "aeiou";
	//cout<<texto<<endl;
	while(texto[i] != '\0'){
		if(texto[i]>='A' && texto[i]<='Z'){
			texto[i]+=32;
		}/*
		for(int j=0; j<5; j++){
			//cout<<texto[i]<<" == "<<acentos[j]<<endl;
			if(texto[i] == (unsigned char)acentos[j])
				texto[i] = valor[j];
		}*/
		i++;
	}
	return texto;
}
//---------------------------------------------------------------------------
void mostrarIntro (){
	cout<<"\n\t******************************************"<<endl;
	cout<<"\t*                UTN FRBA                *"<<endl;
	cout<<"\t*    Algoritmos y Estructura de Datos    *"<<endl;
	cout<<"\t*                                        *"<<endl;
	cout<<"\t******************************************"<<endl;
	cout<<"\t*         Trabajo Práctico 2019          *"<<endl;
	cout<<"\t*                                        *"<<endl;
	cout<<"\t*      Quién quiere ser billonario?      *"<<endl;
	cout<<"\t******************************************\n"<<endl;
}
//---------------------------------------------------------------------------
int leerRespuestas(){
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
	fclose(arch);
	return 0;
}