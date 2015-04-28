/*
 * mundo.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include "LTexture.h"

//Walking animation
//const int ANIMATION_IMAGES = 9;
//SDL_Rect gSpriteClips[ ANIMATION_IMAGES ];
//LTexture gSpriteSheetTexture;

LTexture::LTexture(SDL_Renderer* Renderer)
{
	//Inicializar LTexture
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	gRenderer = Renderer;
	ratio_x_ventana = 1;
	ratio_y_ventana = 1;
	w_ventana = 0;
	h_ventana = 0;
}

LTexture::~LTexture()
{
	//Liberar
	free();
}

void LTexture::setRatio(float ratiox , float ratioy){
	ratio_x_ventana = ratiox;
	ratio_y_ventana = ratioy;
}

void LTexture::setDimensionesVentana(int w,int h){
	w_ventana = w;
	h_ventana = h;
}

bool LTexture::loadFromFile( std::string ruta )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* nuevaTexture = NULL;

	//Cargar imagen desde ruta
	SDL_Surface* loadedSurface = IMG_Load( ruta.c_str() );
	if( loadedSurface == NULL )
	{
		log( string("No se puede cargar imagen %s! SDL_image Error: %s\n", ruta.c_str()),LOG_ERROR);
		return false;
	}
	else
	{
		//Color de Imagen
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Crear textura desde Surface por pixer
		nuevaTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( nuevaTexture == NULL )
		{
			log( string("No se puede crear textura desde %s!", ruta.c_str()),LOG_ERROR);
			return false;
		}
		else
		{
			//Dimensiones de imagen
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Liberar la imagen cargada
		SDL_FreeSurface( loadedSurface );
	}

	//Success
	mTexture = nuevaTexture;
	return true;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		gRenderer = NULL;
		ratio_x_ventana = 0;
		ratio_y_ventana = 0;
		w_ventana = 0;
		h_ventana = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modular textura con RGB
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Setear funcion blending
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modular alpha de textura
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::renderObjeto( Rect_Objeto* clip,float x, float y, bool flip)
{
	int x_px = (int)(x*ratio_x_ventana + 0.5);
	int y_px = (int)(y*ratio_y_ventana +0.5);

	SDL_Rect Object = { x_px,y_px, mWidth, mHeight};
	SDL_Rect clip_px;
	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		clip_px = {clip->x, //posicion en pixel horizontal del objeto en la imagen
				clip->y, //posicion en pixel vertical del objeto en la imagen
				clip->w,// ancho en pixel del objeto en la imagen
				clip->h}; //alto en pixel del objeto en la imagen

		Object.w = (int)(clip->w_log*ratio_x_ventana +0.5);	//tamaño logico del objeto por el ratio de ventana
		Object.h = (int)(clip->h_log*ratio_y_ventana +0.5);
	}

	//Renderizar a la pantalla
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	if(flip)
		flipType = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx( gRenderer, mTexture, &clip_px, &Object,  0 , 0, flipType);
}

void LTexture::renderFondo( Rect_Logico* clip)
{
	SDL_Rect camera = { 0,0, w_ventana, h_ventana};
	SDL_Rect clip_px;

	//Setear tamanio de renderizacion
	if( clip != NULL )
	{
		float ratio_x_img = mWidth/clip->w;
		float ratio_y_img =	mHeight/clip->h;

		int ancho_px_ventana = int((w_ventana/ratio_x_ventana)*ratio_x_img + 0.5); //ancho_logico_de_ventana en lo px de la imagen
		int alto_px_ventana = int((h_ventana/ratio_y_ventana)*ratio_y_img + 0.5);

		clip_px = {(int)(clip->x*ratio_x_img  + 0.5), //posicion horizontal de la capa
				(int)(clip->y*ratio_y_img + 0.5), //posicion vertical de la capa
				ancho_px_ventana,//w_ventana , // ancho de la ventana
				alto_px_ventana }; //alto de la ventana


		int ancho = (int)(clip->w*ratio_x_img + 0.5);
		if(clip_px.x > (ancho - ancho_px_ventana))clip_px.x = ancho - ancho_px_ventana;
		if(clip_px.x <0)clip_px.x = 0;

		camera.w = w_ventana;//Siempre el tamaño de la ventana
		camera.h = h_ventana;
	}

	//Renderizar a la pantalla
	SDL_RenderCopy( gRenderer, mTexture, &clip_px, &camera );
}

void LTexture::renderImagen(){
	SDL_Rect camera = { 0,0, w_ventana, h_ventana};
	SDL_Rect clip = {0,0,w_ventana,h_ventana};
	SDL_RenderCopy( gRenderer, mTexture, &clip, &camera);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
