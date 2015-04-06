#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <stdio.h>
#include <fstream>
#include "../../libs/json/json.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "logging.h"
/*#include "Pelea.h"*/
#include "Tiempo.h"
#include "Mundo.h"
#include "../view/LTexture.h"
#include "Capa.h"
#include "CapaPrincipal.h"
#include "Personaje.h"
#include "../view/Sprite.h"
#include "../view/Frame.h"
#include "DefaultSettings.h"
#include "Mundo.h"

using namespace std;

class ParserJSON {

private:
	 string m_ruta_archivo;

public:
	 ParserJSON(string ruta_archivo);
//CrearMundo();

//	 Pelea* generarPelea();

};

#endif /* SRC_MODEL_PARSER_H_ */
