#ifndef PANTALLA_H_
#define PANTALLA_H_

# include <iostream>
# include <string>
# include "constantes.h"
# include "pseudoGrafo.h"
# include "jugadaLight.h"
# include "jugador.h"
# include "listaCircularCursor.h"


class Pantalla{

	public:

		// Llamados desde Juez:

		void playGame();

		char pedirOpcionPasadoFuturo();

		void mostrarJugadaActual(int fila, int columna,char opcion);

		void listarJugadasDisponibles(int fila, int columna,char opcion, uint contador);

		uint pedirJugadaARehacer();

		void noSePuedeRetroceder();

		void mostrarPuntajeDeJugadorQueHaPerdido(char alias, int puntaje);

		void terminoLaPartida();

		void noHayJugadasParaDeshacer();

		void noHayJugadasParaRehacer();

		void imprimirFelicitacionesGanador();

		void imprimirFelicitacionesGanadores();

		void imprimirFelicitacionesHaGanado(char alias, int puntaje);

		void imprimirPuntajeDeJugador(char alias,int puntaje);



		// Llamados desde Menu:

		char imprimirOpcionesDeMenu();

		void imprimirReglasDeJuego();

		void imprimirTitulo();

		void imprimirPidiendoDatos();
	
		void comprobarDatos(char dificultad, uint dimFila, uint dimColumna, uint cantJugadores);

		void pedirDimensiones(uint &filaUser, uint &colUser);

		char pedirDificultad();

		uint pedirCantidadJugadores();


		// Llamados desde Jugador:

		void imprimirTurno(char alias);

		char verSiQuiereModificarJugadas();

		void puntajeInsuficiente();

		void pedirUbicacionAUser(uint &fila, uint &columna);

		char pedirOpcionAUser();


		void imprimirJugadorRevive(char alias);

	
	private:
	
		void imprimirLinea();
	
		void imprimirDatosIngresados(uint dimFila, uint dimColumna, std::string dificultadPalabra,
				int numeroDeMinas, uint cantJugadores);


		void mostrarJugada(int fila, int columna,char opcion);

		void mostrarEncabezadoJugada();

		void mostrarEncabezadoJugadaParalela(uint contador);

};
#endif
