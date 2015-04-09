#include "ParserJSON.h"

#define LOGLVL_DEFAULT 2
#define TIEMPO_DEFAULT 180
#define VENTANA_ANCHO_PX_DEFAULT 512
#define VENTANA_ALTO_PX_DEFAULT 384
#define VENTANA_ANCHO_DEFAULT 200
#define ESCENARIO_ANCHO_DEFAULT 600
#define ESCENARIO_ALTO_DEFAULT 150
#define Y_PISO_DEFAULT 120
#define BACKGROUND_DEFAULT "data/img/default/backgrounds/background.png"
#define CAPA_ANCHO_DEFAULT 600
#define CAPA_Z_INDEX_DEFAULT 0
#define PERSONAJE_Z_INDEX_DEFAULT 3
#define PERSONAJE_CARPETA_SPRITES_DEFAULT "data/img/default/sprites/"
#define PERSONAJE_NOMBRE_DEFAULT "Jugador"

#define SPRITESHEET_PARADO_DEFAULT "data/img/default/sprites/initial.png"
#define SPRITESHEET_CAMINAR_DEFAULT "data/img/default/sprites/walk.png"
#define SPRITESHEET_SALTAR_DEFAULT "data/img/default/sprites/salto.png"
#define SPRITESHEET_SALTAR_DIAGONAL_DEFAULT "data/img/default/sprites/diag.png"
#define SPRITESHEET_AGACHAR_DEFAULT "data/img/default/sprites/agachar.png"

using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	m_ruta_archivo = ruta_archivo;
}

vector<Sprite*> cargarSprites(string ruta_carpeta, Ventana* ventana, float ratio_x, float ratio_y) {

	vector<Sprite*> sprites;

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoConfig;
	archivoConfig.open(ruta_carpeta.c_str() + "sprites.json");

	// Si no se pudo abrir archivo, generar mundo por defecto.
	if ( ! archivoConfig ) {
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo de sprites JSON, se generan sprites por defecto.", LOG_ERROR );
		return GenerarSpritesDefault(ventana, ratio_x, ratio_y);
	}
	log ( "Se abrio el archivo JSON.", LOG_DEBUG );

	// Si no se pudo parsear archivo, generar mundo por defecto.
	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON, se generan sprites por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return GenerarSpritesDefault(ventana, ratio_x, ratio_y);
	} else log( "El archivo JSON es valido.", LOG_DEBUG );

	// Cerrar archivo.
	archivoConfig.close();
	log ( "Se cerro el archivo JSON.", LOG_DEBUG );

	// Creo Sprite para personaje parado.
	Sprite* sprite_parado;
	bool sprite_parado_ok = true;
	if ( ! root.get( "parado", NULL ) ) {
		log( "No se encontro el sprite correspondiente al personaje parado. Se genera el sprite inicial por defecto.", LOG_ERROR );
		sprite_parado = crearSpriteParadoDefault();
		sprite_parado_ok = false;
	} else {
		string spritesheet_parado = root["parado"].get( "ruta", SPRITESHEET_PARADO_DEFAULT ).asString();
		const Json::Value frames_parado = root["frames"];
		vector<Frame*> framesParado( frames_parado.size() );
		for ( unsigned int i=0; i < frames_parado.size(); i++ ) {
			int x = frames_parado[i].get( "x", NULL ).asInt();
			if ( x == NULL ) {
				log( "No se especifico la posicion X del frame. Se genera el sprite inicial por defecto.", LOG_ERROR );
				sprite_parado = crearSpriteParadoDefault();
				sprite_parado_ok = false;
				break;
			}
			int y = frames_parado[i].get( "y", NULL ).asInt();
			if ( y == NULL ) {
				log( "No se especifico la posicion Y del frame. Se genera el sprite inicial por defecto", LOG_ERROR );
				sprite_parado = crearSpriteParadoDefault();
				sprite_parado_ok = false;
				break;
			}
			int alto = frames_parado[i].get( "Alto", NULL ).asInt();
			if ( alto == NULL ) {
				log( "No se especifico el alto del frame. Se genera el sprite inicial por defecto.", LOG_ERROR );
				sprite_parado = crearSpriteParadoDefault();
				sprite_parado_ok = false;
				break;
			}
			int ancho = frames_parado[i].get( "Ancho", NULL ).asInt();
			if ( ancho == NULL ) {
				log( "No se especifico el ancho del frame. Se genera el sprite inicial por defecto.", LOG_ERROR );
				sprite_parado = crearSpriteParadoDefault();
				sprite_parado_ok = false;
				break;
			}
			framesParado[i] = new Frame(x/ratio_x, y/ratio_y, alto/ratio_y, ancho/ratio_x);
			log( "Se creo correctamente un frame del spritesheet del personaje parado.", LOG_DEBUG );
		}
		if ( sprite_parado_ok ) {
			sprite_parado = new Sprite(spritesheet_parado, framesParado, ventana);
			log( "Se creo correctamente el sprite para el personaje parado.", LOG_DEBUG );
			sprites[0] = sprite_parado;
		}
	}

	// Creo Sprite para personaje caminando.
	Sprite* sprite_caminar;
	bool sprite_caminar_ok = true;
	if ( ! root.get( "caminar", NULL ) ) {
		log( "No se encontro el sprite correspondiente al personaje caminando. Se genera el sprite de caminata por defecto.", LOG_ERROR );
		sprite_caminar = crearSpriteCaminarDefault();
		sprite_caminar_ok = false;
	} else {
		string spritesheet_caminar = root["caminar"].get( "ruta", SPRITESHEET_CAMINAR_DEFAULT ).asString();
		const Json::Value frames_caminar = root["frames"];
		vector<Frame*> framesCaminar( frames_caminar.size() );
		for ( unsigned int i=0; i < frames_caminar.size(); i++ ) {
			int x = frames_caminar[i].get( "x", NULL ).asInt();
			if ( x == NULL ) {
				log( "No se especifico la posicion X del frame. Se genera el sprite de caminata por defecto.", LOG_ERROR );
				sprite_caminar = crearSpriteCaminarDefault();
				sprite_caminar_ok = false;
				break;
			}
			int y = frames_caminar[i].get( "y", NULL ).asInt();
			if ( y == NULL ) {
				log( "No se especifico la posicion Y del frame. Se genera el sprite de caminata por defecto", LOG_ERROR );
				sprite_caminar = crearSpriteCaminarDefault();
				sprite_caminar_ok = false;
				break;
			}
			int alto = frames_caminar[i].get( "Alto", NULL ).asInt();
			if ( alto == NULL ) {
				log( "No se especifico el alto del frame. Se genera el sprite de caminata por defecto.", LOG_ERROR );
				sprite_caminar = crearSpriteCaminarDefault();
				sprite_caminar_ok = false;
				break;
			}
			int ancho = frames_caminar[i].get( "Ancho", NULL ).asInt();
			if ( ancho == NULL ) {
				log( "No se especifico el ancho del frame. Se genera el sprite de caminata por defecto.", LOG_ERROR );
				sprite_caminar = crearSpriteCaminarDefault();
				sprite_caminar_ok = false;
				break;
			}
			framesCaminar[i] = new Frame(x/ratio_x, y/ratio_y, alto/ratio_y, ancho/ratio_x);
			log( "Se creo correctamente un frame del spritesheet del personaje caminando.", LOG_DEBUG );
		}
		if ( sprite_caminar_ok ) {
			sprite_caminar = new Sprite(spritesheet_caminar, framesCaminar, ventana);
			log( "Se creo correctamente el sprite para el personaje caminando.", LOG_DEBUG );
		}
	}






}

Mundo* ParserJSON::cargarMundo() {

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoConfig;
	archivoConfig.open(m_ruta_archivo.c_str());

	// Si no se pudo abrir archivo, generar mundo por defecto.
	if ( ! archivoConfig ) {
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo de configuracion JSON, se genera una partida por defecto.", LOG_ERROR );
		return CrearMundoDefault();
	}
	log ( "Se abrio el archivo JSON.", LOG_DEBUG );

	// Si no se pudo parsear archivo, generar mundo por defecto.
	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON, se genera una partida por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return CrearMundoDefault();
	} else log( "El archivo JSON es valido.", LOG_DEBUG );

	// Cerrar archivo.
	archivoConfig.close();
	log ( "Se cerro el archivo JSON.", LOG_DEBUG );

	// Obtener el nivel de detalle de la bitacora. Si no se especifica
	// se considera nivel DEBUG por defecto, que es el mas completo y reporta cada
	// evento del programa.
	int loglvl = root.get( "loglvl", LOGLVL_DEFAULT ).asInt();
	if ( loglvl > 2 ) {
		loglvl = LOGLVL_DEFAULT;
		// Informar al usuario el cambio de nivel.
		log ( " Nivel de logging incorrecto. Los niveles de logging son: 0-ERRORES, 1-WARNINGS/ERRORES, 2-SUCESOS/WARNINGS/ERRORES (DEBUG). Se setea por defecto nivel DEBUG.", LOG_WARNING );
	} else log( "Se cargo correctamente el nivel de logging.", LOG_DEBUG );

	// Setear nivel de logging del programa.
	nivel = loglvl;

	/*
	Tiempo* tiempo_pelea;
	// Obtener tiempo limite del combate.
	float tiempo = root.get( "tiempo", TIEMPO_DEFAULT ).asFloat();
	if ( tiempo < 0 ) {
		tiempo_pelea = tiempoPorDefault();
		// Informar al usuario el cambio de tiempo de la ronda.
		log ( "WARNING: El tiempo no puede ser negativo. Se setea automaticamente en 3 minutos." );
	}
	else {
		// Crear tiempo.
		tiempo_pelea = new Tiempo( tiempo );
		log( "Se cargo correctamente el tiempo del combate." );
	}

	// Cargar tiempo a la pelea.
	nueva_pelea->Tiempo( tiempo_pelea );
	*/ /*** -------------EL TIEMPO TODAVIA NO LO USAMOS -------------- ***/

	// Obtener dimensiones de la ventana. Se setean por defecto en caso de error.
	// El alto se seteara luego dependiendo del escenario.
	int ventana_ancho_px = root["ventana"].get( "ancho-px", VENTANA_ANCHO_PX_DEFAULT ).asInt();
	if ( ventana_ancho_px < 0 ) {
		ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
		// Informar al usuario el cambio de ancho.
		log( "El ancho en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 512px.", LOG_WARNING );
	} else log( "Se cargo correctamente el ancho en pixeles de la ventana.", LOG_DEBUG );
	int ventana_alto_px = root["ventana"].get( "alto-px", VENTANA_ALTO_PX_DEFAULT ).asInt();
	if ( ventana_alto_px < 0 ) {
		ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
		// Informar al usuario el cambio de alto.
		log( "El alto en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 384px.", LOG_WARNING );
	} else log( "Se cargo correctamente el alto en pixeles de la ventana.", LOG_DEBUG );
	int ventana_ancho = root["ventana"].get( "ancho", VENTANA_ANCHO_DEFAULT ).asInt();
	if ( ventana_ancho < 0 ) {
		ventana_ancho = VENTANA_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho logico.
		log( "El ancho logico de la ventana no puede ser negativo. Se setea automaticamente a 200.", LOG_WARNING );
	} else log( "Se cargo correctamente el ancho logico de la ventana.", LOG_DEBUG );

	// Obtener las dimensiones logicas del escenario.
	// En caso de error se setean por defecto.
	int escenario_ancho = root["escenario"].get( "ancho", ESCENARIO_ANCHO_DEFAULT ).asInt();
	if ( escenario_ancho < 0 ) {
		escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho logico.
		log( "El ancho del escenario no puede ser negativo. Se setea automaticamente a 600.", LOG_WARNING );
	} else log( "Se cargo correctamente el ancho logico del escenario.", LOG_DEBUG );
	int escenario_alto = root["escenario"].get( "alto", ESCENARIO_ALTO_DEFAULT ).asInt();
	if ( escenario_alto < 0 ) {
		escenario_alto = ESCENARIO_ALTO_DEFAULT;
		// Informar al usuario el cambio de alto logico.
		log( "WARNING: El alto del escenario no puede ser negativo. Se setea automaticamente a 150.", LOG_WARNING );
	} else log( "Se cargo correctamente el alto logico del escenario.", LOG_DEBUG );
	int y_piso = root["escenario"].get( "y-piso", Y_PISO_DEFAULT ).asInt();
	log ( "Se cargo correctamente la altura del piso.", LOG_DEBUG );

	// Setear alto logico de la ventana de acuerdo al alto del escenario.
	int ventana_alto = escenario_alto;
	log ( "Se fijo el alto logico de la ventana.", LOG_DEBUG );

	// Obtener relaciones entre pixeles y unidades logicas del mundo.
	float ratio_x = ventana_ancho_px / ventana_ancho;
	float ratio_y = ventana_alto_px / ventana_alto;
	log ( "Se calcularon las relaciones para el ancho y el alto entre los pixeles y las unidades logicas del mundo.", LOG_DEBUG );

	// Crear Mundo.
	Mundo* nuevo_mundo = new Mundo(escenario_ancho, escenario_alto);
	log ( "Se creo correctamente un mundo vacio", LOG_DEBUG );

	/************ NO SE USA ESCENARIO
	// Crear Escenario.
	Escenario* escenario = new Escenario();
	*********************************/

	// Crear Ventana y abrirla.
	Ventana* ventana = new Ventana( ventana_ancho, ventana_alto, ratio_x, ratio_y );
	log ( "Se creo correctamente la ventana (camara)", LOG_DEBUG );
	if( ! ventana->create_window() ) {
		log( "No se puede inicializar la ventana. El programa no puede continuar.", LOG_ERROR );
		return NULL;
	}

	// Asigno Ventana al Mundo.
	nuevo_mundo->setVentana(ventana);

	// Obtener las capas del escenario. La primera capa es el fondo del escenario.
	// Se setea por defecto el ancho en caso de error.
	// Si la imagen no existe, se usa una por defecto.
	const Json::Value capas = root["capas"];
	for ( unsigned int i=0; i < capas.size(); i++ ) {
		string background = capas[i].get( "imagen_fondo", BACKGROUND_DEFAULT ).asString();
		int capa_ancho = capas[i].get( "ancho", CAPA_ANCHO_DEFAULT ).asInt();
		if ( capa_ancho < 0 ) {
			capa_ancho = CAPA_ANCHO_DEFAULT;
			// Informar al usuario el cambio de ancho.
			log( "El ancho de la capa no puede ser negativo. Se setea automaticamente en 600.", LOG_WARNING );
		} else if ( capa_ancho > escenario_ancho ) {
			capa_ancho = CAPA_ANCHO_DEFAULT;
			// Informar al usuario el cambio de ancho.
			log ( "El ancho de la capa no puede superar el del escenario. Se setea automaticamente en 600.", LOG_WARNING );
		} else log( "Se cargo correctamente el ancho logico de la capa.", LOG_DEBUG );
		int capa_z_index = capas[i].get( "z-index", CAPA_Z_INDEX_DEFAULT + i ).asInt();
		log ( "Se cargo el z-index de la capa.", LOG_DEBUG );

		// Setear alto logico de la capa de acuerdo al alto del escenario.
		int capa_alto = escenario_alto;
		log ( "Se fijo el alto logico de la capa.", LOG_DEBUG );

		// Creo capas de fondo.
		CapaFondo* capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, background, ventana );
		if ( capa_fondo == NULL ) {
			delete capa_fondo;
			capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, BACKGROUND_DEFAULT, ventana );
			log( "No se pudo cargar la imagen de la capa. Se carga imagen por defecto.", LOG_ERROR );
		} else {
			log( "Se creo correctamente la capa.", LOG_DEBUG );
		}

		// Agrego capa al mundo.
		nuevo_mundo->addCapa(capa_fondo);
		log( "Se agrego la capa al mundo.", LOG_DEBUG );

	}

	// Obtener el personaje.
	// Si no se especifica o no se encuentra la carpeta de sprites del personaje, se usa una por defecto.
	// Si no se especifica el z-index se fija uno por defecto.
	int personaje_z_index = root["personaje"].get( "z-index", PERSONAJE_Z_INDEX_DEFAULT ).asInt();
	log ( "Se cargo correctamente el z-index del personaje.", LOG_DEBUG );
	string personaje_carpeta_sprites = root["personaje"].get( "sprites", PERSONAJE_CARPETA_SPRITES_DEFAULT ).asString();
	vector<Sprite*> sprites = cargarSprites(personaje_carpeta_sprites, ventana, ratio_x, ratio_y);
	string personaje_nombre = root["personaje"].get ( "nombre", PERSONAJE_NOMBRE_DEFAULT ).asString();
	log ( "Se cargo el nombre del personaje.", LOG_DEBUG );


	// Crear personaje.
	Personaje* personaje = new Personaje(personaje_nombre, sprites, PERSONAJE_VELOCIDAD);
	log( "Se creo correctamente el personaje.", LOG_DEBUG );

	// Agrego Personaje al mundo.
	nuevo_mundo->addPersonaje(personaje);
	log( "Se agrego el personaje al mundo", LOG_DEBUG );

	// Crear capa principal, donde estan los personajes y se desarrolla la accion.
	CapaPrincipal* capa_principal = new CapaPrincipal( escenario_alto, escenario_ancho, personaje_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, personaje );
	log( "Se creo correctamente la capa principal.", LOG_DEBUG );

	// Agrego capa principal al mundo.
	nuevo_mundo->addCapa( capa_principal );
	log( "Se agrego la capa principal al mundo.", LOG_DEBUG );

	return nuevo_mundo;


	// PERSONAJE SE LE PASA VELOCIDAD_PERSONAJE POR CONSTRUCTOR PERO NUNCA LO USA.
	// PREGUNTAR SI LAS DIMENSIONES DE LAS CAPAS SE PASAN EN INT O SI LES FALTO PUSHEAR.
	// HACER QUE SI NO SE PUEDE CARGAR IMAGEN DE CAPA SE DEVUELVA NULL.
	// CAPA PRINCIPAL RECIBE DOS VECES EL MISMO PARAMETRO, EL ANCHO DEL ESCENARIO!!!
	// EL MUNDO NO TIENE PARA AGREGAR CAPA PRINCIPAL, TRATA TODAS LAS CAPAS COMO IGUALES.
	// QUE SPRITE DEVUELVA NULL SI NO PUEDE CARGAR EL SPRITESHEET

}

