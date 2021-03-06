#include "juez.h"

Juez::Juez(unsigned int cantidadJugadores,Mapa* mapaRecibido)
{
	
	this->cantidadDeJugadores = cantidadJugadores;
	this->tableroDeJuego = mapaRecibido;
	this->jugadoresQuePerdieron = 0;
	
	crearYAsignarListaDeJugadores();
	crearYAsignarGrafoDeJugadas();
	
	crearJugadores();

}

void Juez::crearYAsignarListaDeJugadores()
{
	this-> jugadores =  new ListaCircularCursor<Jugador*>;
}
void Juez::crearYAsignarGrafoDeJugadas(){

	this-> jugadas = new PseudoGrafo<JugadaLight*>();
}

void Juez::crearJugadores(){
	char alias = 'A';

	for (int i=0; i<cantidadDeJugadores; i++){

		Jugador* entrante = new Jugador(alias+i,tableroDeJuego);
		this->jugadores->insertar(entrante);

	}
	
	this->jugadores->inicializarCursor();
}


/* Avanzar jugador hasta un jugador que siga jugando.*/
void Juez::avanzarJugador(){

	Jugador* siguiente;
	bool puedeJugar=false;

	this->jugadores->inicializarCursor();

	do{
		this->jugadores->avanzarCursor();
		siguiente = this->jugadores->obtenerCursor();

		if(siguiente->obtenerEstado() == SIGUE_JUGANDO)
			puedeJugar = true;

	}while(!puedeJugar);

}


void Juez::encontrarJugadorQueGanoPorPuntaje(){
	jugadores->inicializarCursor();
	Jugador* jugadorGanador;
	int puntajeMaximo = PUNTAJE_MINIMO;

	int puntajesMostrados=0;

	int puntajesMaximosIguales=0;


	while(this->jugadores->avanzarCursor() && (puntajesMostrados < this->cantidadDeJugadores) ){

		Jugador* jugadorActual;
		jugadorActual = jugadores->obtenerCursor();
		if(jugadorActual->obtenerPuntaje() > puntajeMaximo){
			puntajeMaximo = jugadorActual->obtenerPuntaje();
			jugadorGanador = jugadorActual;
			puntajesMaximosIguales=0;
		}
		else if(jugadorActual->obtenerPuntaje() == puntajeMaximo) puntajesMaximosIguales++;

		puntajesMostrados++;

	}

	mostrarFelicitaciones(jugadorGanador, puntajesMaximosIguales);

	
}
void Juez::crearArchivoConPuntajes(){

	std::ofstream puntajes(archivoDePuntajes);
	int puntajesGuardados=0;

	this->jugadores->inicializarCursor();

       	while(this->jugadores->avanzarCursor() && puntajesGuardados<cantidadDeJugadores){

			char alias;
			int puntaje;
			Jugador* jugadorActual;
			jugadorActual = jugadores->obtenerCursor();
			alias = jugadorActual->obtenerAlias();
			puntaje = jugadorActual->obtenerPuntaje();
			puntajes << "el jugador .:" << alias << ":. obtuvo puntaje de: " << puntaje << std::endl;
			puntajesGuardados++;
	       
       	}	

	puntajes.close();

}


void Juez::inicializarJuego(){
	
	this->casillasOcultas=tableroDeJuego->obtenerCantidadDeCasillasOcultas();
	this->minasPorDescubrir=tableroDeJuego->obtenerTamanioDeLaListaDeMinas();

	uint banderasCorrectas = 0;

	this->jugadores->inicializarCursor();
	Jugador* jugadorActual;
	bool terminoElJuego=false;

	std::cout<<".:PLAY GAME::."<<std::endl;


	while(jugadores->avanzarCursor() && (jugadoresQuePerdieron<cantidadDeJugadores)&& (!terminoElJuego)){

		jugadorActual = this->jugadores->obtenerCursor();

		if(this->casillasOcultas > this->minasPorDescubrir
				&& banderasCorrectas<  this->minasPorDescubrir){

			if (jugadorActual->obtenerEstado() == SIGUE_JUGANDO){
				sigueJugando(jugadorActual, tableroDeJuego);
			}

			banderasCorrectas = buscarBanderasCorrectas();


		}
		else terminoElJuego=true;

	}
	
	terminoLaPartida();
	encontrarJugadorQueGanoPorPuntaje();
	crearArchivoConPuntajes();

}


void Juez::sigueJugando(Jugador* jugadorActual, Mapa* tableroDeJuego){

	Jugada* jugadaActual;

	jugadorActual->iniciarJugada();
	jugadaActual = jugadorActual->obtenerPJugada();

	if(jugadorActual->obtenerEstado() == REALIZANDO_CAMBIOS){

		jugadorActual->modificarPuntaje(COSTO_MODIFICAR);
	}
	
	while(jugadorActual->obtenerEstado() == REALIZANDO_CAMBIOS){

		realizarCambios();
		jugadorActual->iniciarJugada();
		jugadaActual = jugadorActual->obtenerPJugada();
	}

	if(jugadorActual->obtenerEstado() == PERDIO_PARTIDA){

		jugadoresQuePerdieron++;
		this->minasPorDescubrir--;

		jugadorActual->asignarEstado(NO_ESTA_JUGANDO);

		mostrarPuntajeDeJugadorQueHaPerdido(jugadorActual);
		
	}

	JugadaLight* jugadaLiviana = new JugadaLight(jugadaActual->obtenerOpcion(),jugadorActual->obtenerAlias(),
			jugadaActual->obtenerFila(),jugadaActual->obtenerColumna());
	
	this->jugadas->insertar(jugadaLiviana);

	this->casillasOcultas=tableroDeJuego->obtenerCantidadDeCasillasOcultas();

	this->tableroDeJuego->mostrarMapa();

}

void Juez::realizarCambios(){

	bool terminoDeHacerCambios = false;
	char opcionDeUsuario;

	NodoGrafo<JugadaLight*>* actual= this->jugadas->obtenerActual();

	while (!terminoDeHacerCambios){

		std::cout<<"VOLVER AL PASADO 'deshacer' (P) || ";
		std::cout<<"VOLVER AL FUTURO 'rehacer' (F) || "<<std::endl;
		std::cout<<"Ya no realizar JUGADA ESPECIAL (N) : "<<std::endl;

		std::cin>>opcionDeUsuario;

		if(opcionDeUsuario == 'p' || opcionDeUsuario == 'P'){
			if(actual->tieneAnterior() ){
				deshacerJugada();
				tableroDeJuego->mostrarMapa();
			}
			else{
				terminoDeHacerCambios = true;
				std::cout<<"No hay jugadas para deshacer"<<std::endl;
			}
		}
		else if(opcionDeUsuario == 'f' || opcionDeUsuario == 'F'){
			rehacerJugada();
			tableroDeJuego->mostrarMapa();
		}
		else terminoDeHacerCambios = true;
	}

}

void Juez::deshacerJugada(){

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
	

	if (opcion == 'm' || opcion == 'M'){
		Marcador inverso(tableroDeJuego);
		puntaje = inverso.marcar(jugadaADeshacer->obtenerFila(),jugadaADeshacer->obtenerColumna());
		jugadorActual->modificarPuntaje(puntaje);

	}else if (opcion == 'd' || opcion == 'D'){
		AntiDestapador inverso(tableroDeJuego, jugadorActual);
		inverso.tapar(jugadaADeshacer->obtenerFila(),jugadaADeshacer->obtenerColumna());
	}

	this->jugadas->retrocederCursor();
}

void Juez::rehacerJugada(){
	//imprime la siguiente y sus paralelas
	uint contador = 1;
	uint opcionUsuario;

	JugadaLight* actual;

	std::cout<<"jugadas realizadas desde este punto: "<<std::endl;

	this->jugadas->avanzarCursor();
	actual = this->jugadas->obtenerDatoActual();

	std::cout<<"jugada 1: ";
	std::cout<<"fila: "<<actual->obtenerFila()<<" columna: "<<actual->obtenerColumna()
			<<" opcion: "<<actual->obtenerOpcion()<<std::endl;

	while(this->jugadas->avanzarCursorAParalela()){
		contador++;
		actual=this->jugadas->obtenerDatoActual();
		std::cout<<"jugada "<<contador<<": ";
		std::cout<<"fila: "<<actual->obtenerFila()<<" columna: "<<actual->obtenerColumna()
			<<" opcion: "<<actual->obtenerOpcion()<<std::endl;
	}
	this->jugadas->retrocederCursor();

	std::cout<<std::endl<<"elija una de las jugadas para rehacer"<<std::endl;
	std::cin>>opcionUsuario; //falta validar que la opcion este entre 1 y contador

	rehacerParalela(opcionUsuario);

}

void Juez::rehacerParalela(uint posicion){

	JugadaLight* jugadaARehacer;

	this->jugadas->avanzarCursor();

	for(uint i=0;i<(posicion-1);i++)
		this->jugadas->avanzarCursorAParalela();

	jugadaARehacer = this->jugadas->obtenerDatoActual();

	char opcion = jugadaARehacer->obtenerOpcion();

	if (opcion == 'm' || opcion == 'M'){
		Marcador marcador(tableroDeJuego);
		marcador.marcar(jugadaARehacer->obtenerFila(),jugadaARehacer->obtenerColumna());

	}else if (opcion == 'd' || opcion == 'D'){
		Destapador destapador(tableroDeJuego);
		destapador.destapar(jugadaARehacer->obtenerFila(),jugadaARehacer->obtenerColumna());
	}

}

uint Juez::buscarBanderasCorrectas(){

	uint cantidadBanderasCorrectas = 0;

	Lista<Mina>* minas;
	Lista<Bandera>* banderas;

	minas = this->tableroDeJuego->obtenerPunteroMinas();
	banderas = this->tableroDeJuego->obtenerPunteroBanderas();

	minas->iniciarCursor();

	Bandera actual;

	while(banderas->avanzarCursor()){

		actual = banderas->obtenerCursor();
		if(banderaEsCorrecta(actual,minas))
			cantidadBanderasCorrectas++;
	}

	return cantidadBanderasCorrectas;
}

bool Juez::banderaEsCorrecta(Bandera actual,Lista<Mina>*minas){

	bool encontrada = false;
	Mina compatible;

	minas->iniciarCursor();

	while(minas->avanzarCursor() && !encontrada){

		compatible = minas->obtenerCursor();

		if(actual.obtenerFila() == compatible.obtenerFila() &&
				actual.obtenerColumna() == compatible.obtenerColumna()){
			encontrada = true;
		}

	}

	return encontrada;
}

void Juez::mostrarPuntajeDeJugadorQueHaPerdido(Jugador* jugadorActual){
	
	int puntaje = 0;
	char alias;
	alias = jugadorActual->obtenerAlias();
	puntaje = jugadorActual->obtenerPuntaje();
	std::cout<<std::endl;
	std::cout<<".:EL JUGADOR " << alias << " OBTUVO SU GAME OVER:. "<<std::endl;
	std::cout<< "PUNTAJE OBTENIDO: " << puntaje << std::endl;

}

void Juez::terminoLaPartida(){
	
	std::cout<<std::endl;
	std::cout << "\t\t\t.:GAME OVER:." << std::endl;
	std::cout<<std::endl;
	
}

void Juez::mostrarFelicitaciones(Jugador* jugadorActual, int puntajesMaximosIguales){

	if(puntajesMaximosIguales == 0){
		std::cout << jugadorActual->obtenerAlias() << "!!! GANASTE !!!" << std::endl;
		std::cout << "Tu puntaje es: " << jugadorActual->obtenerPuntaje() << "."<< std::endl;
	}

	if(puntajesMaximosIguales > 0)
		std::cout<<"SE OBTUVO UN EMPATE... INTENTEN DE NUEVO."<<std::endl;

	std::cout<<std::endl;
	
}


Juez::~Juez(){
	
	this->jugadores->inicializarCursor();
	Jugador* jugadorActual;

	while( this->jugadores->avanzarCursor() && !(this->jugadores->estaVacia()) ){

		jugadorActual = this->jugadores->obtenerCursor();
		Jugador* jugadorABorrar;
		char alias;
		int puntaje;
		alias = jugadorActual->obtenerAlias();
		puntaje = jugadorActual->obtenerPuntaje();
		std::cout<<"El jugador: " << alias << " tiene " << puntaje << " puntos." << std::endl;
		jugadorABorrar = jugadorActual;
		this->jugadores->avanzarCursor();
		jugadorActual = this->jugadores->obtenerCursor();


		delete jugadorABorrar;
		this->jugadores->remover(1);
		
	}
	
	delete this->jugadores;
}
