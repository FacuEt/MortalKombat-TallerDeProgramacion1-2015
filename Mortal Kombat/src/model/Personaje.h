/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: Facu
 */

#ifndef SRC_MODEL_PERSONAJE_H_
#define SRC_MODEL_PERSONAJE_H_

//Constants
#define SPRITE_PARADO = 0;
#define SPRITE_CAMINAR = 1;
#define SPRITE_SALTO = 2;
#define SPRITE_SALTO_DIAGONAL = 3;
#define SPRITE_PUNCHING = 4;
#define SPRITE_KICKING = 5;

class Personaje {
	std::string nombre;
	int vida;
	std::list<std::string> sprites;

public:
	Personaje(std::string nombre_personaje);

	std::list<std::string> Sprites();
	std::string Sprite(int accion);
	int Vida();
	void QuitarVida(int valor);

	virtual ~Personaje();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
