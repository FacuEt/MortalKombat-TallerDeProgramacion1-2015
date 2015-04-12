/*
 * Sprite.h
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#ifndef SRC_VIEW_SPRITE_H_
#define SRC_VIEW_SPRITE_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>

#include "LTexture.h"
#include "Ventana.h"
#include "Frame.h"
#include "../model/CargarImagenException.h"

class Sprite {
	private:
		int frameActual;
		int cantidadFrames;

		bool reverse;
		bool doloop;
		int frameLoop;

		Sprite* spriteSiguiente;

		Rect_Logico* spriteFrames;
		LTexture* SpriteSheetTexture;

	public:
		Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana);
		~Sprite();

		void setSpriteSiguiente(Sprite* nextsprite);
		Sprite* getSpriteSiguiente();

		bool Advance();
		void Reset();
		bool puedeAvanzar();

		void setLoop(int num_frame);
		void doLoop(bool loop);
		void Reverse(bool Reverse);

		bool ultimoFrame();
		float getAncho();

		void render(float x,float y, bool fliped);

		void setRender(SDL_Renderer* Renderer);
		Rect_Logico* getFrame();
		LTexture* getSpriteSheetTexture();
};




#endif /* SRC_VIEW_SPRITE_H_ */
