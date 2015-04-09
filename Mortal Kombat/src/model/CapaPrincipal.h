/*
 * CapaPrincipal.h
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPAPRINCIPAL_H_
#define SRC_MODEL_CAPAPRINCIPAL_H_

#include "Capa.h"
#include "Personaje.h"
#include <SDL2/SDL.h>

class CapaPrincipal: public Capa {

public:
	CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal, Personaje* personaje, Ventana* ventana);
	bool Scrollear();
	virtual ~CapaPrincipal();
	virtual void Renderizar();

private:
	Personaje* m_Personaje;
};


#endif /* SRC_MODEL_CAPAPRINCIPAL_H_ */
