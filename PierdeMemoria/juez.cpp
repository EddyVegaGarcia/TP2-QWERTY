#include "juez.h"

Juez::Juez(unsigned int cantidadJugadores,Mapa* mapaRecibido){
	
	this->cantidadDeJugadores = cantidadJugadores;
	this->tableroDeJuego = mapaRecibido;
	this->jugadoresQuePerdieron = 0;
	
	crearYAsignarListaDeJugadores();
	crearYAsignarGrafoDeJugadas();
	
	crearJugadores();

}

void Juez::crearYAsignarListaDeJugadores(){
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
	
	this->jugadores->inicializarCursor();

	int puntajeMaximo = PUNTAJE_MINIMO;

	int puntajesMostrados=0;

	int puntajesMaximosIguales=1;

	while(this->jugadores->avanzarCursor() && (puntajesMostrados < this->cantidadDeJugadores) ){

		Jugador* jugadorActual;
		jugadorActual = this->jugadores->obtenerCursor();
		if(jugadorActual->obtenerPuntaje() > puntajeMaximo){
			puntajeMaximo = jugadorActual->obtenerPuntaje();
			puntajesMaximosIguales=1;
		}
		else if(jugadorActual->obtenerPuntaje() == puntajeMaximo) puntajesMaximosIguales++;

		puntajesMostrados++;

	}

	this->mostrarFelicitaciones(this->jugadores,puntajeMaximo, puntajesMaximosIguales);

}

void Juez::mostrarFelicitaciones(ListaCircularCursor<Jugador*>* jugadores,
									int puntajeMaximo,int puntajesMaximosIguales){

	Pantalla pantalla;

	if(puntajesMaximosIguales == 1){
		pantalla.imprimirFelicitacionesGanador();
	}
	else pantalla.imprimirFelicitacionesGanadores();

	jugadores->inicializarCursor();

	uint jugadoresImpresos = 0;
	Jugador* actual;

	while(jugadores->avanzarCursor() && jugadoresImpresos<puntajesMaximosIguales){

		actual = jugadores->obtenerCursor();

		if(actual->obtenerPuntaje() == puntajeMaximo)	{
			pantalla.imprimirFelicitacionesHaGanado(actual->obtenerAlias(),actual->obtenerPuntaje());
			jugadoresImpresos++;
		}
	}


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
	
	Pantalla pantalla;
	
	this->casillasOcultas=tableroDeJuego->obtenerCantidadDeCasillasOcultas();
	this->minasPorDescubrir=tableroDeJuego->obtenerMinasPorDescubrir();

	uint banderasCorrectas = 0;

	this->jugadores->inicializarCursor();
	Jugador* jugadorActual;
	bool terminoElJuego=false;

	pantalla.playGame();

	this->tableroDeJuego->mostrarMapa();

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
	
	pantalla.terminoLaPartida();
	encontrarJugadorQueGanoPorPuntaje();
	crearArchivoConPuntajes();

}


void Juez::sigueJugando(Jugador* jugadorActual, Mapa* tableroDeJuego){

	Jugada* jugadaActual;
	Pantalla pantalla;

	jugadorActual->iniciarJugada();
	jugadaActual = jugadorActual->obtenerPJugada();

	while(jugadorActual->obtenerEstado() == REALIZANDO_CAMBIOS){

		realizarCambios(jugadorActual);
		jugadorActual->iniciarJugada();
		jugadaActual = jugadorActual->obtenerPJugada();
	}

	if(jugadorActual->obtenerEstado() == PERDIO_PARTIDA){

		this->jugadoresQuePerdieron++;

		jugadorActual->asignarEstado(NO_ESTA_JUGANDO);

		pantalla.mostrarPuntajeDeJugadorQueHaPerdido(jugadorActual->obtenerAlias(),jugadorActual->obtenerPuntaje());
		
	}

	JugadaLight* jugadaLiviana = new JugadaLight(jugadaActual->obtenerOpcion(),jugadorActual->obtenerAlias(),
			jugadaActual->obtenerFila(),jugadaActual->obtenerColumna());
	
	this->jugadas->insertar(jugadaLiviana);

	this->casillasOcultas=tableroDeJuego->obtenerCantidadDeCasillasOcultas();
	this->minasPorDescubrir=tableroDeJuego->obtenerMinasPorDescubrir();

	this->tableroDeJuego->mostrarMapa();

}

void Juez::realizarCambios(Jugador* jugadorActual){

	Pantalla pantalla;
	
	bool terminoDeHacerCambios = false;
	char opcionDeUsuario;
	bool puedeHacerCambios = true;

	NodoGrafo<JugadaLight*>* actual= this->jugadas->obtenerActual();

	while (!terminoDeHacerCambios &&  puedeHacerCambios && jugadorActual->poseePuntajeSuficiente()){

		opcionDeUsuario = pantalla.pedirOpcionPasadoFuturo();

		if(opcionDeUsuario == 'p' || opcionDeUsuario == 'P'){
			if(actual!=NULL){
				puedeHacerCambios= deshacerJugada();
				tableroDeJuego->mostrarMapa();
			}
			else{
				terminoDeHacerCambios = true;
				pantalla.noHayJugadasParaDeshacer();
			}
		}
		else if(opcionDeUsuario == 'f' || opcionDeUsuario == 'F'){
			puedeHacerCambios = rehacerJugada();
			tableroDeJuego->mostrarMapa();
		}
		else terminoDeHacerCambios = true;
	}
	
	if (!(jugadorActual->poseePuntajeSuficiente())){
		pantalla.puntajeInsuficiente();
	}


}

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
	

	if (opcion == 'm' || opcion == 'M'){
		Marcador inverso(tableroDeJuego);
		puntaje = inverso.marcar(jugadaADeshacer->obtenerFila(),jugadaADeshacer->obtenerColumna());
		jugadorActual->modificarPuntaje(puntaje);

	}else if (opcion == 'd' || opcion == 'D'){
		AntiDestapador inverso(tableroDeJuego, jugadorActual);
		bool revive = inverso.tapar(jugadaADeshacer->obtenerFila(),jugadaADeshacer->obtenerColumna());
		if (revive){
			this->jugadoresQuePerdieron--;
		}
	}

	this->jugadas->retrocederCursor();
	NodoGrafo<JugadaLight*>* jugadaActual = this->jugadas->obtenerActual();
	if(jugadaActual== NULL){

		pantalla.noSePuedeRetroceder();
		puedeDeshacer = false;

	}

	return puedeDeshacer;
}

bool Juez::rehacerJugada(){
	Pantalla pantalla;

	JugadaLight* actual;

	uint opcionUsuario = 0;
	uint contador = 1;

	if(jugadas->avanzarCursor())
		do {
			actual = this->jugadas->obtenerDatoActual();
			pantalla.mostrarJugadaActual(actual->obtenerFila(),actual->obtenerColumna(),actual->obtenerOpcion());

			while(this->jugadas->avanzarCursorAParalela()){
				contador++;
				actual=this->jugadas->obtenerDatoActual();
				pantalla.listarJugadasDisponibles(actual->obtenerFila(),actual->obtenerColumna(),
													actual->obtenerOpcion(),contador);
			}
			this->jugadas->retrocederCursor();

			opcionUsuario = pantalla.pedirJugadaARehacer();
		} while (opcionUsuario < 1|| opcionUsuario > contador);

	if (opcionUsuario !=0){
			rehacerParalela(opcionUsuario);
	}

	return (opcionUsuario != 0);
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
		uint perdio = destapador.destapar(jugadaARehacer->obtenerFila(),jugadaARehacer->obtenerColumna());
		if (perdio){
			this->jugadoresQuePerdieron++;
		}
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


Juez::~Juez(){
	
	Pantalla pantalla;

	this->jugadores->inicializarCursor();
	Jugador* jugadorActual;

	while( this->jugadores->avanzarCursor() && !(this->jugadores->estaVacia()) ){

		jugadorActual = this->jugadores->obtenerCursor();
		Jugador* jugadorABorrar;

		pantalla.imprimirPuntajeDeJugador(jugadorActual->obtenerAlias(),jugadorActual->obtenerPuntaje());

		jugadorABorrar = jugadorActual;
		this->jugadores->avanzarCursor();
		jugadorActual = this->jugadores->obtenerCursor();


		delete jugadorABorrar;
		this->jugadores->remover(1);
		
	}
	
	delete this->jugadores;
	delete this->jugadas;
}
