#ifndef NODOGRAFO_H_
#define NODOGRAFO_H_

#include "constantes.h"



template<class T>
class NodoGrafo
{
	private:
		T dato;
		NodoGrafo<T>* siguiente;
		NodoGrafo<T>* anterior;
		NodoGrafo<T>* siguienteAbajo;
		NodoGrafo<T>* anteriorArriba;
	public:
		NodoGrafo(T dato);
		T obtenerDato();
		void cambiarDato(T nuevoDato);
		NodoGrafo<T>* obtenerSiguiente();
		NodoGrafo<T>* obtenerAnterior();
		NodoGrafo<T>* obtenerSiguienteAbajo();
		NodoGrafo<T>* obtenerAnteriorArriba();
		void cambiarSiguiente(NodoGrafo<T>* nuevoSiguiente);
		void cambiarAnterior(NodoGrafo<T>* nuevoAnterior);
		void cambiarAnteriorArriba(NodoGrafo<T>* nuevoArriba);
		void cambiarSiguienteAbajo(NodoGrafo<T>* nuevoAbajo);
};


template<class T>
NodoGrafo<T>::NodoGrafo(T dato)
{
	this->dato=dato;
	this->siguiente=NULL;
	this->anterior=NULL;
	this->siguienteAbajo=NULL;
	this->anteriorArriba=NULL;
}

template<class T>
T NodoGrafo<T>::obtenerDato()
{
	return this->dato;
}

template<class T>
void NodoGrafo<T>::cambiarDato(T nuevoDato)
{
	this->dato =nuevoDato;
}

template<class T>
NodoGrafo<T>* NodoGrafo<T>::obtenerSiguiente()
{
	return this->siguiente;
}

template<class T>
NodoGrafo<T>* NodoGrafo<T>::obtenerAnterior()
{
	return this->anterior;
}

template<class T>
NodoGrafo<T>* NodoGrafo<T>::obtenerAnteriorArriba()
{
	return this->anteriorArriba;
}

template<class T>
NodoGrafo<T>* NodoGrafo<T>::obtenerSiguienteAbajo()
{
	return this->siguienteAbajo;
}

template<class T>
void NodoGrafo<T>::cambiarSiguiente(NodoGrafo<T>* nuevoSiguiente)
{
	this->siguiente=nuevoSiguiente;
}

template<class T>
void NodoGrafo<T>::cambiarAnterior(NodoGrafo<T>* nuevoAnterior)
{
	this->anterior=nuevoAnterior;
}

template<class T>
void NodoGrafo<T>::cambiarSiguienteAbajo(NodoGrafo<T>* nuevoSiguienteAbajo)
{
	this->siguienteAbajo=nuevoSiguienteAbajo;
}

template<class T>
void NodoGrafo<T>::cambiarAnteriorArriba(NodoGrafo<T>* nuevoAnteriorArriba)
{
	this->anteriorArriba=nuevoAnteriorArriba;
}

#endif /* NODOGRAFO_H_ */
