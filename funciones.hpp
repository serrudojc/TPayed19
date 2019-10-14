#define CANTPREG 	5
#define CANTTURNO	3
#define CANTPART 	4
#define MIN 		0
#define CHARPREG	120
#define CHARRESP	120
#define CHARCATEG	120
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
	_________ 		Participantes
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
	bool esCorrecta = false;
	char tiempo[30]; //no se como hacer esto aun
};

struct Participantes{
	ResPart info;
	Participantes *sig;
};

//------------------------------------------------

void agregarNodo(Nodo*& lista, Categoria v);
void agregarNodoJuego(Participantes *&lista, ResPart v);
Categoria eliminarPrimerNodo (Nodo*& lista);

//------------------------------------------------

void mostrar (Nodo* lista);
void mostrarUnNodo(Nodo* lista);
Nodo *leerPreguntasDat(Nodo *&lista);
int get_rand(int min, int max);
int cantidadNodos (Nodo* lista);
Nodo* buscar(Nodo* lista, int v);
Nodo* buscarCat(Nodo* lista, int v);