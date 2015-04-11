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

#include "LTexture.h"
#include "Ventana.h"
#include "Frame.h"

class Sprite {
	private:
		int frameActual;
		int cantidadFrames;
		Rect_Logico* spriteFrames;
		LTexture* SpriteSheetTexture;
		Sprite* spriteSiguiente;

	public:
		Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana);
		~Sprite();

		void setSpriteSiguiente(Sprite* nextsprite);
		void Reset();
		void setRender(SDL_Renderer* Renderer);
		bool Advance();
		bool puedeAvanzar();
		void render(float x,float y);
		float getAncho();
		Sprite* getSpriteSiguiente();
		Rect_Logico* getFrame();
		LTexture* getSpriteSheetTexture();
};




#endif /* SRC_VIEW_SPRITE_H_ */
