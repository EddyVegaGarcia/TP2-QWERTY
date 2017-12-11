# include "jugador.h"

Jugador::Jugador(char letra, Mapa* punteroAMapa){
	asignarAlias(letra);
	asignarPuntaje(0);
	asignarEstado(SIGUE_JUGANDO);
	inicializarPunteroAJugada(punteroAMapa);
	this->mapa = punteroAMapa;
}


// métodos púbicos
void Jugador::modificarPuntaje(int puntos){
	this->puntaje+=puntos;
}
char Jugador::obtenerAlias(){
	return this->alias;
}
int Jugador::obtenerPuntaje(){
	return this->puntaje;
}
int Jugador::obtenerEstado(){
	return this->estado;
}

// métodos privados
void Jugador::asignarAlias(char letra){
	this->alias=letra;
}

void Jugador::asignarPuntaje(int puntos){
	this->puntaje=puntos;
}

void Jugador::asignarEstado(int estado){
	this->estado=estado;
}
	
	
void Jugador::inicializarPunteroAJugada(Mapa* punteroAMapa){
	this->pJugada = new Jugada(punteroAMapa);
}


bool Jugador::validarOpcionUser( char opcionUser){
	return (opcionUser != 'd' && opcionUser != 'D' && opcionUser != 'm' && opcionUser != 'M' && opcionUser != 'r' && opcionUser != 'R');
}

bool Jugador::validarOpcionUserConfirmacion(char opcionUser){
	return((opcionUser != 's') && (opcionUser != 'S') && (opcionUser != 'n') && (opcionUser != 'N'));
}

bool Jugador::poseePuntajeSuficiente(){
	return(this->puntaje>=PUNTAJE_NECESARIO_PARA_JUGADAS_ESPECIALES);
}

// métodos públicos
void Jugador::iniciarJugada(){
	Pantalla pantalla;
	uint filaUser, columnaUser;

	bool quiereModificarJugadas = false;
	char opcionUser;
	int puntos = 0;

	pantalla.imprimirTurno(this->alias);

	if(this->poseePuntajeSuficiente())
		quiereModificarJugadas = PreguntarSiQuiereModificarJugadas();
	else pantalla.puntajeInsuficiente();


	if (quiereModificarJugadas){
		this->asignarEstado(REALIZANDO_CAMBIOS);
	}
	else{
		do{
			pantalla.pedirUbicacionAUser(filaUser, columnaUser);

		} while( (filaUser<1 || filaUser> mapa->obtenerFila()) || (columnaUser<1 || columnaUser > mapa->obtenerColumna()));


		do{
			opcionUser=pantalla.pedirOpcionAUser();
		}while(this->validarOpcionUser(opcionUser));


		this->pJugada->asignarOpcion(opcionUser);
		this->pJugada->asignarFila(filaUser);
		this->pJugada->asignarColumna(columnaUser);


		puntos = this->pJugada->realizarJugada();

		if (puntos == PERDIO_PARTIDA)
			this->asignarEstado(PERDIO_PARTIDA);
		else if (puntos == SE_RETIRO)
			this->asignarEstado(SE_RETIRO);
		else{
			this->modificarPuntaje(puntos);
			this->asignarEstado(SIGUE_JUGANDO);
		}

	}
}

bool Jugador::PreguntarSiQuiereModificarJugadas(){

	Pantalla pantalla;

	char opcionUser;
	do{
		opcionUser=pantalla.verSiQuiereModificarJugadas();
	}while(this->validarOpcionUserConfirmacion(opcionUser));

	return ((opcionUser == 's') || (opcionUser == 'S'));
}

Jugada* Jugador::obtenerPJugada(){
	return this-> pJugada;

}

Jugador::~Jugador(){
	delete pJugada;
}
