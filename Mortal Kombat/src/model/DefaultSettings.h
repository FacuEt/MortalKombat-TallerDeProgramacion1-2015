#ifndef SRC_MODEL_DEFAULTSETTINGS_H_
#define SRC_MODEL_DEFAULTSETTINGS_H_

#include <stdio.h>
#include <string>
#include <stdexcept>
#include "../../libs/json/json.h"
#include "logging.h"
#include "Mundo.h"
#include "../controller/KeyboardControl.h"
#include <sys/stat.h>

const int LOGLVL_DEFAULT = 2;
const int TIEMPO_DEFAULT = 180;
const int VENTANA_ANCHO_PX_DEFAULT = 512;
const int VENTANA_ALTO_PX_DEFAULT = 384;
const float VENTANA_ANCHO_DEFAULT = 200.0;
const float ESCENARIO_ANCHO_DEFAULT = 600.0;
const float ESCENARIO_ALTO_DEFAULT = 150.0;
const float Y_PISO_DEFAULT = 135.0;
const char* const BACKGROUND_DEFAULT = "data/img/background/default/unknown.png";
const char* const CAPA_0_BACKGROUND_DEFAULT = "data/img/background/default/background_0.png";
const char* const CAPA_1_BACKGROUND_DEFAULT = "data/img/background/default/background_1.png";
const char* const CAPA_2_BACKGROUND_DEFAULT = "data/img/background/default/background_2.png";
const float CAPA_0_ANCHO_DEFAULT = 200.0;
const float CAPA_1_ANCHO_DEFAULT = 226.6;
const float CAPA_2_ANCHO_DEFAULT = 600.0;
const int CAPA_Z_INDEX_DEFAULT = 0;
const int PERSONAJES_Z_INDEX_DEFAULT = 3;
const char* const PERSONAJE_CARPETA_SPRITES_DEFAULT = "data/players/default/sprites/";
const char* const PERSONAJE_NOMBRE_DEFAULT = "Jugador";
const bool PERSONAJE_FLIPPED_DEFAULT = false;
const int PERSONAJE_ANCHO_PX_DEFAULT = 72;
const int PERSONAJE_ALTO_PX_DEFAULT = 133;
const float PERSONAJE_ANCHO_DEFAULT = 40.0;
const float PERSONAJE_ALTO_DEFAULT = 70.0;
const float PERSONAJE_POS_RESPECTO_CAM = 0.8;

const char* const JSON_SPRITES_DEFAULT = "data/players/default/sprites/sprites.json";

const char* const SPRITESHEET_PARADO_DEFAULT = "initial.png";
const char* const SPRITESHEET_CAMINAR_DEFAULT = "walk.png";
const char* const SPRITESHEET_SALTAR_DEFAULT = "salto.png";
const char* const SPRITESHEET_SALTAR_DIAGONAL_DEFAULT = "diag.png";
const char* const SPRITESHEET_AGACHAR_DEFAULT = "agachar.png";
const char* const SPRITESHEET_AGACHADO_PATADA_ALTA_DEFAULT = "agachadoPatadaAlta.png";
const char* const SPRITESHEET_AGACHADO_PATADA_BAJA_DEFAULT = "agachadoPatadaBaja.png";
const char* const SPRITESHEET_CAER_EN_Z_DEFAULT = "caeEnZ.png";
const char* const SPRITESHEET_CAER_Y_LEVANTAR_DEFAULT = "caeySeLevanta.png";
const char* const SPRITESHEET_CUBRIRSE_DEFAULT = "cubrirse.png";
const char* const SPRITESHEET_CUBRIRSE_AGACHADO_DEFAULT = "cubrirseAgachado.png";
const char* const SPRITESHEET_GANAR_DEFAULT = "gana.png";
const char* const SPRITESHEET_GANCHO_DEFAULT = "gancho.png";
const char* const SPRITESHEET_MORIR_DEFAULT = "muere.png";
const char* const SPRITESHEET_PATADA_ALTA_DEFAULT = "patadaAlta.png";
const char* const SPRITESHEET_PATADA_BAJA_DEFAULT = "patadaBaja.png";
const char* const SPRITESHEET_PATADA_CIRCULAR_DEFAULT = "PatadaConGiro.png";
const char* const SPRITESHEET_PATADA_SALTANDO_DEFAULT = "PatadaEnSalto.png";
const char* const SPRITESHEET_PINA_AGACHADO_DEFAULT = "PinaAgachado.png";
const char* const SPRITESHEET_PINA_ALTA_DEFAULT = "PinaAlta.png";
const char* const SPRITESHEET_PINA_BAJA_DEFAULT = "PinaBaja.png";
const char* const SPRITESHEET_PINA_SALTANDO_DEFAULT = "PinaEnSalto.png";
const char* const SPRITESHEET_RECIBIR_GOLPE_AGACHADO_DEFAULT = "recibeGolpeAgachado.png";
const char* const SPRITESHEET_RECIBIR_GOLPE_ALTO_DEFAULT = "recibeGolpeAlto.png";
const char* const SPRITESHEET_RECIBIR_GOLPE_BAJO_DEFAULT = "recibeGolpeBajo.png";
const char* const SPRITESHEET_RECIBIR_GOLPE_FUERTE_DEFAULT = "recibeGolpeFuerte.png";

const int COMANDO_PINA_BAJA_DEFAULT = 2;
const int COMANDO_PATADA_BAJA_DEFAULT = 1;
const int COMANDO_PINA_ALTA_DEFAULT = 3;
const int COMANDO_PATADA_ALTA_DEFAULT = 0;
const int COMANDO_CUBRIRSE_DEFAULT = 6;
const int COMANDO_LANZAR_ARMA_DEFAULT = 4;

const int COLOR_H_INICIAL_DEFAULT = 40;
const int COLOR_H_FINAL_DEFAULT = 45;
const int COLOR_DESPLAZAMIENTO_DEFAULT = 30;

const char* const IMAGEN_CARGANDO_JUEGO = "data/img/background/inicio.png";


const float PERSONAJE_VELOCIDAD = 7.0;


using namespace std;


Sprite* crearSpritePorDefecto(const char* accion_sprite, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje, bool cambiar_color = false, float h_inicial = COLOR_H_INICIAL_DEFAULT, float h_final = COLOR_H_FINAL_DEFAULT, float h_desplazamiento = COLOR_DESPLAZAMIENTO_DEFAULT);
vector<Sprite*> generarSpritesDefault( Ventana* ventana, float personaje_ancho, float personaje_alto, bool cambiar_color = false, float h_inicial = COLOR_H_INICIAL_DEFAULT, float h_final = COLOR_H_FINAL_DEFAULT, float h_desplazamiento = COLOR_DESPLAZAMIENTO_DEFAULT );
void mapaComandosDefault(map<string, int>* comandos);
Mundo* generarMundoDefault();


#endif /* SRC_MODEL_DEFAULTSETTINGS_H_ */
