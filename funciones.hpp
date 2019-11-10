#define CANTPREG 	6
#define CANTTURNO	5
#define CANTPART 	5
#define MIN 		0
#define CHARPREG	140
#define CHARRESP	140
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
	char tiempo[CHARCATEG]; 
};

struct Participantes{
	int idPart;
	int puntaje = 0;
	char nombrePart[CHARCATEG];
	ResPart info;	
	bool empatado = false;
	bool rondaEmpate = false;
	int i;
	int j;
	int k;
};

//------------------------------------------------
//funciones para app de crear las preguntas
void agregarNodo(Nodo*& lista, Categoria v);
Categoria eliminarPrimerNodo (Nodo*& lista);

//------------------------------------------------
//funciones para el juego (algunas se usan en caso de debugger, no se usan ingame)
Nodo *nuevaPartidaCargarPartida(Participantes participante[], Nodo *lista, bool &partidaCargada, int &I, int &J);
void inicializarParticipantes(Participantes participante[]);
Nodo *leerPreguntasDat(Nodo *&lista, const char archivo[CHARCATEG]);
void recuperarParticipantes(Participantes participante[], int &I, int &J);
int get_rand(int max);
int cantidadNodos (Nodo* lista);
bool verificadorCategoriasDisponibles(Nodo *lista);
Nodo* buscar(Nodo* lista, int v);
Nodo* buscarCat(Nodo* lista, int v);
void buscarPregunta(Nodo *&nodoCat, Participantes participante[], int i, int &j);
char *obtenerHora(char *fechaChar);
void guardarSaveLista(Nodo *lista);
void verEstado(Participantes participante[]);
void leerSave(Participantes participante[]);
void mostrarSave(Participantes reg);
void mostrar (Participantes arr[]);
void mostrar (Nodo* lista);
void mostrarUnNodo(Nodo* lista);
int cantDeEmpatados(Participantes arr[]);
void ordenarBurbuja (Participantes arr[], int len);
void estandarizarTexto(char texto[]);
void mostrarIntro ();