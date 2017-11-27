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
		NodoGrafo<T>* pararelo;
	public:
		NodoGrafo(T dato);
		T obtenerDato();
		void cambiarDato(T nuevoDato);
		NodoGrafo<T>* obtenerSiguiente();
		NodoGrafo<T>* obtenerAnterior();
		NodoGrafo<T>* obtenerParalelo();
		void cambiarSiguiente(NodoGrafo<T>* nuevoSiguiente);
		void cambiarAnterior(NodoGrafo<T>* nuevoAnterior);
		void cambiarParalelo(NodoGrafo<T>* nuevoPararelo);
};


template<class T>
NodoGrafo<T>::NodoGrafo(T dato)
{
	this->dato=dato;
	this->siguiente=NULL;
	this->anterior=NULL;
	this->pararelo=NULL;
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
NodoGrafo<T>* NodoGrafo<T>::obtenerPararelo()
{
	return this->pararelo;
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
void NodoGrafo<T>::cambiarParalelo(NodoGrafo<T>* nuevoParalelo)
{
	this->paralelo=nuevoPararelo;
}


#endif /* NODOGRAFO_H_ */
