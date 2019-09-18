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

