#define CANTPREG 	5
#define CANTTURNO	3
#define CANTPART 	4
#define MIN 		0
#define CHARPREG	120
#define CHARRESP	120
#define CHARCATEG	30
//------------------------------------------------
//Estructuras para las preguntas del juego
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
	_________ 		NodoPart
	|       |       _______     ______       ______
	|       |----->|____|_|--->|____|_|---->|____|_|
	|_______|			|       
	|       |			|------->
	|       |					ResPart
	|_______|
	 part[5]
*/

struct ResPart{
	char pregunta[CHARPREG];
	char resp[CHARRESP];
	char esCorrecta[CHARCATEG] = "Incorrecta";
	char tiempo[CHARCATEG]; //no se como hacer esto aun
};

struct NodoPart{
	ResPart info;
	NodoPart *sig;
};

struct Participantes{
	int idPart;
	int puntaje = 0;
	char nombrePart[CHARCATEG];
	int proxTurno = 0;		//guardo algo asi como un contador incremental
	NodoPart *part = NULL;	//se puede hacer esto?incializar?
};
//------------------------------------------------
struct Consolidado{
	int puntaje;
	int idPart;
	char nombrePart[CHARCATEG];
	int proxTurno;
	ResPart info;
};
//------------------------------------------------

void agregarNodo(Nodo*& lista, Categoria v);
void agregarNodoPart(NodoPart *&lista, ResPart v);
Categoria eliminarPrimerNodo (Nodo*& lista);

//------------------------------------------------

void mostrar (Nodo* lista);
void mostrarUnNodo(Nodo* lista);
Nodo *leerPreguntasDat(Nodo *&lista);
int get_rand(int min, int max);
int cantidadNodos (Nodo* lista);
Nodo* buscar(Nodo* lista, int v);
Nodo* buscarCat(Nodo* lista, int v);
char *obtenerHora(char *fechaChar);
void ordenarBurbuja (Participantes arr[], int len);
void mostrar (Participantes arr[],int len);