#ifndef SRC_NODOGRAFOINVERSO_H_
#define SRC_NODOGRAFOINVERSO_H_

#include "constantes.h"

template<class T>
class NodoGrafoInverso
{
	private:
		T dato;
		NodoGrafoInverso<T>* paraleloSiguiente;
		NodoGrafoInverso<T>* paraleloAnterior;
		NodoGrafoInverso<T>* siguiente;
	public:
		NodoGrafoInverso(T dato);
		T obtenerDato();
		void cambiarDato(T nuevoDato);
		NodoGrafoInverso<T>* obtenerParaleloSiguiente();
		NodoGrafoInverso<T>* obtenerParaleloAnterior();
		NodoGrafoInverso<T>* obtenerSiguiente();
		void cambiarSiguiente(NodoGrafoInverso<T>* nuevoParaleloSiguiente);
		void cambiarAnterior(NodoGrafoInverso<T>* nuevoParaleloAnterior);
		void cambiarParalelo(NodoGrafoInverso<T>* nuevoSiguiente);

		bool esNodoParalelo();

		bool tieneSiguiente();
};


template<class T>
NodoGrafoInverso<T>::NodoGrafoInverso(T dato)
{
	this->dato=dato;
	this->paraleloSiguiente=NULL;
	this->paraleloAnterior=NULL;
	this->siguiente=NULL;
}

template<class T>
T NodoGrafoInverso<T>::obtenerDato()
{
	return this->dato;
}

template<class T>
void NodoGrafoInverso<T>::cambiarDato(T nuevoDato)
{
	this->dato =nuevoDato;
}

template<class T>
NodoGrafoInverso<T>* NodoGrafoInverso<T>::obtenerParaleloSiguiente()
{
	return this->paraleloSiguiente;
}

template<class T>
NodoGrafoInverso<T>* NodoGrafoInverso<T>::obtenerParaleloAnterior()
{
	return this->paraleloAnterior;
}

template<class T>
NodoGrafoInverso<T>* NodoGrafoInverso<T>::obtenerSiguiente()
{
	return this->siguiente;
}

template<class T>
void NodoGrafoInverso<T>::cambiarSiguiente(NodoGrafoInverso<T>* nuevoSiguiente)
{
	this->siguiente=nuevoSiguiente;
}

template<class T>
void NodoGrafoInverso<T>::cambiarAnterior(NodoGrafoInverso<T>* nuevoAnterior)
{
	this->paraleloAnterior=nuevoAnterior;
}

template<class T>
void NodoGrafoInverso<T>::cambiarParalelo(NodoGrafoInverso<T>* nuevoSiguiente)
{
	this->siguiente=nuevoSiguiente;
}

template<class T>
bool NodoGrafoInverso<T>::tieneSiguiente(){
	return (!(this->siguiente == NULL));
}


template<class T>
bool NodoGrafoInverso::esNodoParalelo(){
	return true;
}

#endif /* SRC_NODOGRAFOINVERSO_H_ */
