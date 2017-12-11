Hola hola


El juez.cpp, en deshacerJugada al principio de todo hay un do while.
Se llamó a deshacer, así que lo que se tiene que deshacer es lo que hizo el jugador "anterior".

De la jugadalight se obtiene el alias de ese jugador anterior.
Ahora el do while se supone que busca al jugador que tenga ese alias en la lista de jugadores
y deja el cursor apuntandole.
Eso tiene que haer pero no lo hace.

Así como está ahora está mal, lo intento cambiar y tengo tanto sueño que no encuentro el error
y escribo un archivo aparte, xD
Fíjense si les anda, no sé


Ahora dice esto:

bool Juez::deshacerJugada(){
	Pantalla pantalla;
  bool puedeDeshacer = true;
	
  JugadaLight* jugadaADeshacer = this->jugadas->obtenerDatoActual();
	char opcion = jugadaADeshacer->obtenerOpcion();
	char alias = jugadaADeshacer->obtenerJugador();
  
	Jugador* jugadorActual;
	this->jugadores->inicializarCursor2();
	int puntaje;

	do{
		this->jugadores->avanzarCursor2();
		jugadorActual = this->jugadores->obtenerCursor2();
		alias = jugadorActual->obtenerAlias();
	} while(jugadorActual->obtenerAlias() != alias);
	

Debería decir esto:

bool Juez::deshacerJugada(){
	Pantalla pantalla;
  bool puedeDeshacer = true;
	JugadaLight* jugadaADeshacer = this->jugadas->obtenerDatoActual();
	char opcion = jugadaADeshacer->obtenerOpcion();
	int puntaje;

	Jugador* jugadorActual;
	this->jugadores->inicializarCursor2();
	char aliasJugadaADeshacer = jugadaADeshacer->obtenerJugador();
	char alias;
	do{
		this->jugadores->avanzarCursor2();
		jugadorActual = this->jugadores->obtenerCursor2();
		alias = jugadorActual->obtenerAlias();
	} while(alias != aliasJugadaADeshacer);
	

Porque de la primera forma siempre se revive al jugador A (hace una sola vez lo que está dentro del do while,
xq está pisando el "alias")
Pero de la segunda forma tampoco funciona (se queda eternamente pensando y el debugger pe dice que siempre
queda 'estancado' en el último jugador y no vuelve a empezar por el jugador A (no entiendo por qué si ese
cursor2 es copipaste del cursor que sí funciona) (tengo sueño, no sé)).
