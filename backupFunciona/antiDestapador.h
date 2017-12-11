#ifndef ANTIDESTAPADOR_H_
#define ANTIDESTAPADOR_H_

# include "mapa.h"
# include "jugador.h"
# include "constantes.h"


class AntiDestapador{

private:
	Jugador* jugador;
	unsigned int fila;
	unsigned int columna;
	int puntaje;
	Mapa* mapa;

public:

	AntiDestapador(Mapa* mapaActual, Jugador* jugador);

	bool tapar(uint filaJugada,uint columnaJugada);

	bool puntajeAltapar();

	void crearListaCasillasYAsignarPuntero();

	bool validarUbicacion(uint fila, uint columna);

	bool taparCasillaNoVacia(char ValorCasilla);

	void taparPandemia();

};

#endif /* ANTIDESTAPADOR_H_ */
