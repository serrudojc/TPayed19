#define CANTPREG 	5
#define CANTTURNO	3
#define CANTPART 	4
#define MIN 		0
#define CHARPREG	120
#define CHARRESP	120
#define CHARCATEG	30
//------------------------------------------------
//Estructuras para preguntas.dat
struct Pregunta{
	char pregunta[CHARPREG];
	char respuesta[CHARRESP];
	bool pregEnabled = true;
};

struct Categoria {
	int id;
	char categoria[CHARCATEG];
	Pregunta preguntas[CANTPREG];
	int catEnabled = CANTPREG;
};

struct Nodo{
	Categoria info;
	Nodo *sig;			
};

//-----------------------------------------------
//Estructura para las respuestas de los participantes
/*
   Participantes
	_________ 		 
	|_______|			       
	|       |			
	|       |					
	|_______|
   participante[5]
*/

struct ResPart{
	char pregunta[CHARPREG];
	char resp[CHARRESP];
	char esCorrecta[CHARCATEG] = "Incorrecta";
	char tiempo[CHARCATEG]; //no se como hacer esto aun
};
/*
struct NodoPart{
	ResPart info;
	NodoPart *sig;
};*/

struct Participantes{
	int idPart;
	int puntaje = 0;
	char nombrePart[CHARCATEG];
	ResPart info;	
	bool empatado = false;
	bool rondaEmpate = false;
	bool sigTurno = false;
	int i;
	int j;
	int k;
};

//------------------------------------------------
//estructura para guardar en archivo
/*
struct Consolidado{
	int idPart;
	int puntaje;
	char nombrePart[CHARCATEG];
	ResPart info;
	bool empatado = false;
	bool sigTurno = false;
};
*/



//------------------------------------------------
//funciones para app de crear las preguntas
void agregarNodo(Nodo*& lista, Categoria v);
Categoria eliminarPrimerNodo (Nodo*& lista);

//------------------------------------------------
//funciones para el juego (algunas se usan en caso de debugger, no se usan ingame)
Nodo *nuevaPartidaCargarPartida(Participantes participante[], Nodo *lista, int &i, int &j, int &k);
void inicializarParticipantes(Participantes participante[]);
Nodo *leerPreguntasDat(Nodo *&lista, const char archivo[CHARCATEG]);
void recuperarParticipantes(Participantes participante[], int &i, int &j, int &k);
int get_rand(int min, int max);
int cantidadNodos (Nodo* lista);
bool verificadorCategoriasDisponibles(Nodo *lista);
Nodo* buscar(Nodo* lista, int v);
Nodo* buscarCat(Nodo* lista, int v);
void buscarPregunta(Nodo *&nodoCat, Participantes participante[], int i, int &j, int k);
char *obtenerHora(char *fechaChar);
void guardarSaveLista(Nodo *lista);
void verEstado();
void leerSave();
void mostrar (Participantes arr[],int len);
void mostrar (Nodo* lista);
void mostrarUnNodo(Nodo* lista);
int cantDeEmpatados(Participantes arr[], int len);
void ordenarBurbuja (Participantes arr[], int len);





