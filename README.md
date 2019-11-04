# TPayed19
TP Algoritmos y Estructuras de Datos 2019 C++

### ¿Quién quiere ser billonario?

Han sido convocados para desarrollar un sistema de preguntas y respuestas.

### Categorías y Preguntas

El programa debe brindar de forma aleatoria una categoría de preguntas (Historia,Geografía, etc) y una pregunta dentro de esa categoría para cada turno de cada participante.

Como mínimo habrá 7 categorías de 6 preguntas cada una. 
Una vez que la pregunta es contestada, se deshabilita. 
Y, una vez que todas las preguntas de la categoría hayan sido contestadas, la categoría se deshabilita.

### Participantes y Turnos

En el programa habrá 5 participantes compitiendo, cada uno tendrá 5 turnos. 
Por cada respuesta correcta, el participante sumará 1 punto. 
En caso de terminar los turnos y que hubiera un empate, se seguirá con las preguntas un turno a la vez hasta que haya un ganador (solo uno conteste bien).
Cada vez que un participante contesta una pregunta, se debe recordar el puntaje de todoslos participantes antes de pasar con el próximo participante.

### Histórico y Contingencia

El programa debe ofrecer la posibilidad de obtener un listado histórico hasta el momento con los siguientes datos por cada participante:
- puntaje total.
- preguntas respondidas, cuál fue su respuesta y si ésta es correcta.
- hora en la que respondió la pregunta.

Además, se debe guardar cuál es el participante que tiene el próximo turno para jugar.
También, si por alguna contingencia el programa dejará de funcionar, al reiniciarse deberecordar todos los datos mencionados anteriormente.

Restricciones:
- Las categorías, preguntas y respuestas deben cargarse desde un archivo “.dat”.
- Los archivos “.dat” que se utilicen deben ser entregados junto con los archivos “.cpp”del programa.
- El contenido de los archivos debe entregarse explicitado en un archivo “.xls”.
- Se debe utilizar para la resolución de este trabajo por lo menos un vector y una estructura dinámica.



# USO DEL PROGRAMA
### Archivos make
El projecto tiene archivos make usados para facilitar la compilacion en la terminal. No se usan en caso de compilarse en un IDE.
Ejemplo de uso
`make -f MakeGenPreg`
Me genera el ejecutable genPreg
Para limpiar (borrar) se puede ejecutar
`make -f MakeGenPreg clean`


### Carga de preguntas y respuestas iniciales.
Compilando y ejecutando (hablo desde terminal de Ubuntu) `./genPreg` se accede al programa para la inicialización de preguntas.
Ejecutando `./genPreg<textoPrueba` se carga directamente el txt sin necesidad de estar tipeando en la consola (armar un txt aparte con las categorias, preguntas y respuestas). 
Se me genera un archivo **preguntas.dat**

### Lectura de los archivos preguntas.dat y preguntasSave.dat
Si es necesario leer el contenido de las preguntas, se realizó un programa para tal acción, que se compila con `make -f MakeLeerPreguntasDat`
Se puede leer tanto el **preguntas.dat** con las preguntas en crudo como el **preguntasSave.dat**, que básicamente es el mismo archivo, pero con las preguntas que ya fueron realizadas en la partida, deshabilitadas, de manera que si se retorma la partida, no se vuelvan a realizar las mismas preguntas.

# El JUEGO 
Para ejecutar el juego, se compila desde la termina `make -f Makejuego` y se ejecuta `./juego`.
El juego consta de 5 turnos con 5 jugadores. 
En caso de no haber un ganador en estos ciclos, se procederá a un desempate con los jugadores empatados
Para saber quienes son los empatados, cada jugador tiene una bandera de **empatado** la cual está por defecto en **false**. Una vez terminada la ronda básica, una función **cantDeEmpatados** guarda el mayor puntaje, para luego comparar los jugadores que tengan ese mismo puntaje y asignar **true** a la bandera.
