#include "antiDestapador.h"


//constructor
AntiDestapador::AntiDestapador(Mapa* mapaActual)
{
  this->fila = 0;
  this->columna = 0;
  this->mapa = mapaActual;
  crearListaCasillasYAsignarPuntero();

}

//metodos publicos
uint Destapador::destapar(uint filaJugada,uint columnaJugada)
{
	uint puntaje = 0;
	this->fila = filaJugada;
 	this->columna = columnaJugada;
	puntaje = this->puntajeAlDestapar(); //decía puntajeAlDestapar(*puntaje);
	return puntaje;
}

int Destapador::puntajeAltapar()
{
	int puntaje=0;
	if(this->mapa->estaDestapadaLaCasilla(this->fila, this->columna))
	{
		char valorCasilla = mapa->obtenerValorCasilla(this->fila, this->columna);

		if(valorCasilla == VACIO)
		{
			taparPandemia();
		}
		else
		{
			this->mapa->eliminarCasillaDestapada(this->fila, this->columna);
			puntaje = taparCasillaNoVacia(valorCasilla);
		}
	}
	return puntaje;
}

void Destapador::crearListaCasillasYAsignarPuntero()
{
	//Lista<Casilla> vacios;
	//this->pVacios = &vacios;
	this->pVacios=new Lista<Casilla>;
}

//metodos privados
bool Destapador::validarUbicacion(uint fila, uint columna){
	bool ubicacionValida = true;
	uint dimensionFila = this->mapa->obtenerFila();
	uint dimensionColumna = this->mapa->obtenerColumna();
	if(fila<0 || fila>dimensionFila || columna < 0 || columna>dimensionColumna){
		ubicacionValida = false;
	}
	return ubicacionValida;
}
void Destapador::taparPandemia(){

  this->mapa->eilminarCasillasDestapadasDesde(this->fila,this->columna);

}

uint Destapador::destaparCasillaNoVacia(char valorCasilla)
{
	
	uint puntaje = 0;
  	
	if(valorCasilla == MINA)
	{
		puntaje = PERDIO_PARTIDA;	
	}
	
	return puntaje;
	
	
}

Destapador::~Destapador()
{
	for(uint i = 1; i < this->pVacios->contarElementos()+1; i++){
		this->pVacios->remover(i);
	}
	delete pVacios;
}
