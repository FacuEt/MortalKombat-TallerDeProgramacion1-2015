#include "Ventana.h"
#include "../model/logging.h"


Ventana::Ventana(int screenWidth, int screenHeight, float ratiox,float ratioy)
{
	m_ancho_px = screenWidth;
	m_alto_px = screenHeight;
	ratio_x = ratiox;
	ratio_y = ratioy;
	Window = NULL;
	Renderer = NULL;
	m_vibrar = false;
}

void Ventana::vibrar(){
	for (int i = 0;i < (int)texturas.size() ; i++){
		if (texturas[i] != NULL and !texturas[i]->estaVibrando() ){
			texturas[i]->setVibrar();
		}
	}
}

float Ventana::obtenerRatioX(){
	return ratio_x;
}

float Ventana::obtenerRatioY(){
	return ratio_y;
}

SDL_Window* Ventana::getWindow() {
	return Window;
}

Ventana::~Ventana(){
	m_ancho_px = 0;
	m_alto_px = 0;
	ratio_x = 0;
	ratio_y = 0;
	close_window();

}

LTexture* Ventana::crearTextura(){
	LTexture* m_texture = new LTexture(Renderer);
	m_texture->setRatio(ratio_x,ratio_y);
	m_texture->setDimensionesVentana(m_ancho_px,m_alto_px);
	texturas.push_back(m_texture);
	return m_texture;
}

SDL_Renderer* Ventana::getRenderer(){
	return Renderer;
}

float Ventana::obtenerAncho()
{
	return m_ancho_px/ratio_x;
}
float Ventana::obtenerAlto()
{
	return m_alto_px/ratio_y;
}


bool Ventana::create_window()
{
	//Booleano de inicializacion
	bool success = true;

	//Inicializar SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0 )
	{
		log(string("SDL no puede inicializar! SDL Error: %s\n", SDL_GetError()),LOG_ERROR );
		success = false;
	}
	else
	{
		//Filtrado lineal de textura
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			log("Filtrado lineal de textura no esta habilitado!" ,LOG_WARNING);
		}

		//Crear Ventana
		Window = SDL_CreateWindow( "MK - FIUBA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_ancho_px, m_alto_px, SDL_WINDOW_SHOWN );
		if( Window == NULL )
		{
			log(string( "La ventana no se puede crear! SDL Error: %s\n", SDL_GetError() ),LOG_ERROR);
			success = false;
		}
		else
		{

			//Vsync-renderer for window
			Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( Renderer == NULL )
			{
				log(string( "No se pudo crear la renderizacion! SDL Error: %s\n", SDL_GetError() ),LOG_ERROR);
				success = false;
			}
			else
			{
				//render Color
				SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Cargador de PNG
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					log(string( "SDL_image no pudo inicializarse! SDL_image Errors: %s\n", IMG_GetError() ),LOG_ERROR);
					success = false;
				}
			}

			//agrego icono
			SDL_Surface* Surface = IMG_Load( RUTA_ICONO );
			if( Surface == NULL )
					log( string("No se puede cargar imagen del icono %s! SDL_image Error: %s\n", RUTA_ICONO),LOG_ERROR);
			else
			{
				//Color de Imagen
				SDL_SetColorKey( Surface, SDL_TRUE, SDL_MapRGB( Surface->format, 0, 0xFF, 0xFF ) );

				SDL_SetWindowIcon(Window,Surface);

				SDL_FreeSurface(Surface);
			}
		}
	}

	return success;
}

void Ventana::close_window()
{
	//Liberar imagenes cargadas
	//gSpriteSheetTexture.free();

	//Destruir Ventanas
	SDL_DestroyRenderer( Renderer );
	SDL_DestroyWindow( Window );
	Window = NULL;
	Renderer = NULL;

	//Cerrar SDL
	IMG_Quit();
	SDL_Quit();
}

void Ventana::clear(){
	//Limpiar pantalla
	SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( Renderer );
}

bool Ventana::mostrarImagen(string ruta){
	LTexture* textura = crearTextura();
	if(!textura->loadFromFile(ruta)){
		log(string("No se pudo cargar la ruta de la imagen a mostrar, %s:",ruta.c_str()),LOG_ERROR);
		return false;
	}
	textura->renderImagen();
	Refresh();
	delete textura;
	return true;
}

void Ventana::Refresh(){
	//Actualizar pantalla
	SDL_RenderPresent( Renderer );
}

