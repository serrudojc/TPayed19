#define CANTPREG 	3
#define CANTTURNO	3
#define CANTPART 	3
#define MIN 		1

struct Pregunta{
	char pregunta[120];
	char respuesta[120];
	bool pregEnabled = true;
};

struct Categoria {
	int id;
	char categoria[20];
	Pregunta preguntas[CANTPREG];
	bool catEnabled = true;
};

struct Nodo{
	Categoria info;
	Nodo *sig;			
};

//------------------------------------------------
void agregarNodo(Nodo*& lista, Categoria v);
Categoria eliminarPrimerNodo (Nodo*& lista);
//------------------------------------------------
void mostrar (Nodo* lista);
void mostrarUnNodo(Nodo* lista);
int get_rand(int min, int max);
int cantidadNodos (Nodo* lista);
Nodo* buscar(Nodo* lista, int v);
Nodo* buscarCat(Nodo* lista, int v);