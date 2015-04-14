/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: Facu
 */

#ifndef SRC_MODEL_PERSONAJE_H_
#define SRC_MODEL_PERSONAJE_H_

//Constants
const int SPRITE_INICIAL=         0;
const int SPRITE_CAMINAR=         1;
const int SPRITE_SALTAR=          2;
const int SPRITE_SALTAR_DIAGONAL= 3;
const int SPRITE_AGACHAR=         4;

const int TIEMPOTOTALDESALTO = 10;

#include <stdio.h>
#include <iostream>
#include <vector>
#include "../view/Sprite.h"


class Personaje {
private:
	std::string nombre;

	float vida;
	float m_xActual;
	float m_yActual;
	float m_xInicial;
	float m_yInicial;
	float maxAlturaDeSalto;
	int tiempoDeSalto;
	short _estaSaltando;
	bool m_fliped;

	float velocidadAdelante;
	float velocidadAtras;
	float m_velocidad;

	Sprite* spriteActual;
	std::vector<Sprite*> sprites;

	float m_AltoMundo;
	float m_AnchoMundo;

	void _cambiarSprite(int accion);

	void _SaltarHorizontal();
	void _SaltarDerecha();
	void _SaltarIzquierda();

	bool _estaAgachado();


	void _parabola();
	void _actualizarY();
	float _yDeSalto(float currentY, float currentT);

public:
	Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites,float velocidad, bool fliped = false);

	std::vector<Sprite*> getSprites();
	Sprite* getSpriteActual();
	void AvanzarSprite();
	bool enMovimiento();
	void renderizar(float x_dist_ventana);

	void setPosition(float x, float y);
	void setDimensiones(float h, float w);
	float getX();
	float getY();
	float getVida();
	int getSentidoDeMovimiento();
	float getVelocidadDerecha();
	float getVelocidadIzquierda();
	void QuitarVida(int valor);
	float getAncho();
	float getAlto();

	void Inicial();
	void Frenar();
	void Saltar();
	void Agachar();
	void Levantarse();
	void CaminarDerecha();
	void CaminarIzquierda();

	virtual ~Personaje();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
