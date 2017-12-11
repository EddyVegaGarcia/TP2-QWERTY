#include "antiDestapador.h"

AntiDestapador::AntiDestapador(Mapa* mapaActual,Jugador* jugador){
  this->fila = 0;
  this->columna = 0;
  this->puntaje = 0;
  this->mapa = mapaActual;
  this->jugador = jugador;

}

bool AntiDestapador::tapar(uint filaJugada,uint columnaJugada){
	this->fila = filaJugada;
 	this->columna = columnaJugada;
	bool puntaje = this->puntajeAltapar();
	return puntaje;
}

bool AntiDestapador::puntajeAltapar(){
	bool revive=false;
	if(this->mapa->estaDestapadaLaCasilla(this->fila, this->columna)){
		char valorCasilla = mapa->obtenerValorCasilla(this->fila, this->columna);

		if(valorCasilla == VACIO){
			taparPandemia();
		}
		else{

			if(valorCasilla==MINA){
				this->jugador->asignarEstado(SIGUE_JUGANDO);
				std::cout<<".:JUGADOR " <<this->jugador->obtenerAlias()<<" REVIVE!!!:."<<std::endl;
			}
			this->mapa->eliminarCasillaDestapada(this->fila, this->columna);
			revive = taparCasillaNoVacia(valorCasilla);
		}
	}
	return revive;
}

bool AntiDestapador::validarUbicacion(uint fila, uint columna){

	bool ubicacionValida = true;
	uint dimensionFila = this->mapa->obtenerFila();
	uint dimensionColumna = this->mapa->obtenerColumna();
	if(fila<0 || fila>dimensionFila || columna < 0 || columna>dimensionColumna){
		ubicacionValida = false;
	}
	return ubicacionValida;
}
void AntiDestapador::taparPandemia(){

  this->mapa->eliminarCasillasDestapadasDesde(this->fila,this->columna);

}

// devuelve true si se "antidestapa" una mina, es decir si un jugador revive
bool AntiDestapador::taparCasillaNoVacia(char valorCasilla){

	return (valorCasilla == MINA);

}
