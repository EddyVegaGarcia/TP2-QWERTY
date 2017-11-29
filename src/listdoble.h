/*
 * listdoble.h
 *
 *  Created on: 29/11/2017
 *      Author: alumno
 */


#ifndef LISTADOBLE_H_
#define LISTADOBLE_H_

#include <iostream>
#include "nodografo.h"

template <class T>


class ListaDoble {
   public:
    ListaDoble();
    ~ListaDoble();

    void Insertar(T dato);
    void Insertar(T dato,  unsigned int posicion);
    NodoGrafo<T>* ListaDoble<T>::obtenerNodo(unsigned int posicion);
    void Borrar(T dato);
    bool ListaVacia() { return primero == NULL; }
    void Primero();
    bool Actual() { return primero != NULL; }
    void iniciarCursor();
    bool avanzarCursor();
    bool retrocederCursor();
    T obtenerCursor();

   private:

    NodoGrafoParalelo<T>* primero;
    unsigned int tamanio;
    NodoGrafoParalelo<T>* cursor;


};

template <class T>
ListaDoble<T>::ListaDoble()
{
		this->primero=NULL;
		this->cursor=NULL;
		this->tamanio = 0;

}

template <class T>
ListaDoble<T>::~ListaDoble() {
   NodoGrafoParalelo<T> aux;

   Primero();
   while(primero) {
      aux = primero;
      primero = primero->obtenerSiguiente;
      delete aux;
   }
}

template <class T>
void ListaDoble<T>::Insertar(T dato) {
	this->Insertar(dato, this->tamanio+1);
}
template <class T>
NodoGrafo<T>* ListaDoble<T>::obtenerNodo(unsigned int posicion)
{
	NodoGrafo<T>* actual=this->primero;
	for(unsigned int i = 1; i<posicion; i++){
		actual=actual->obtenerSiguiente();
	}
	return actual;
}

template <class T>
void ListaDoble<T>::Insertar(T dato,  unsigned int posicion){

	if((posicion>0)&&(posicion<=this->tamanio+1))
			{
				NodoGrafo<T>* nuevo = new NodoGrafo<T>(dato);
				if(posicion==1)
				{
					nuevo->cambiarAnterior(this->primero);
					nuevo->cambiarSiguiente(this->primero);
					this->primero=nuevo;
					this->primero->indicarQueEsElPrimero();
				}
				else
				{
					NodoGrafo<T>* anterior = this->obtenerNodo(posicion-1);
					anterior->cambiarSiguiente(nuevo);
					NodoGrafo<T>* siguiente = this->obtenerNodo(posicion+1);
					siguiente->cambiarAnterior(nuevo);
					nuevo->cambiarAnterior(anterior);
					nuevo->cambiarSiguiente(siguiente);
					anterior->cambiarParaleloDer(nuevo);
				}
				this->tamanio++;
				this->iniciarCursor();
			}

}
template <class T>
void ListaDoble<T>::Borrar(T dato) {
   NodoGrafoParalelo<T> nodo;

   nodo = primero;
      while( nodo && nodo->obtenerDato != dato)
         nodo = nodo->obtenerSiguiente;
      if(nodo->obtenerDato == dato){
         NodoGrafoParalelo<T> anterior = nodo->obtenerAnterior;
         NodoGrafoParalelo<T> siguiente = nodo->obtenerSiguiente;
         anterior->cambiarSiguiente(siguiente);
         siguiente->cambiarAnterior(anterior);
         delete nodo;
      }

}
template<class T>
void ListaDoble<T>::iniciarCursor()
{
	this->cursor=NULL;
}

template<class T>
bool ListaDoble<T>::avanzarCursor()
{
	if(this->cursor==NULL)
	{
		this->cursor=this->primero;
	}
	else
	{
		this->cursor=this->cursor->obtenerSiguiente();
	}
	return (this->cursor != NULL);
}
template<class T>
T ListaDoble<T>::obtenerCursor()
{
	T elemento;
	if(this->cursor!=NULL)
	{
		elemento=this->cursor->obtenerDato();
	}
	return elemento;
}
template<class T>
bool ListaDoble<T>::retrocederCursor(){
	if(this->cursor!=NULL)

	{
		this->cursor=this->cursor->obtenerAnterior();
	}
	return (this->cursor != NULL);
}




