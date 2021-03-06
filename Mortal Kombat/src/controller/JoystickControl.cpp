/*
 * JoystickControl.cpp
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#include "JoystickControl.h"

JoystickControl::JoystickControl(SDL_Event* e,int id_joystick,Personaje* un_personaje,map<string, int>* mapa_comandos) {
	personaje = un_personaje;
	evento = e;
	pausa = false;
	comandos = mapa_comandos;
	_Init(id_joystick);
	_verificarMapaComandos();
}

bool JoystickControl::pause(){
	return pausa;
}

void JoystickControl::_verificarMapaComandos(){
	bool mapa_correcto = false;
	if (comandos != NULL && joystick != NULL){
		mapa_correcto = true;
		for (std::map<string,int>::const_iterator it=comandos->begin(); it!=comandos->end(); ++it){
			//si supera la cantidad de botones del joystick
			if(it->second >= SDL_JoystickNumButtons(joystick))
				mapa_correcto = false;
			if (it->first != PINA_BAJA || it->first != PATADA_BAJA || it->first != PINA_ALTA || it->first != PATADA_ALTA || it->first != CUBRIRSE ||it->first != LANZAR_ARMA)
				mapa_correcto = false;
		}
	}

	//si no es correcto hago uno propio
	if(!mapa_correcto){
		log("Los botones del joystick especificados en el Json no son correctos, se crean unos por defecto",LOG_WARNING);
		std::map<std::string, int>* mapita = new std::map<std::string,int>;
		mapita->operator[](PINA_BAJA) = JOY_X;
		mapita->operator[](PATADA_BAJA) = JOY_CIRCULO;
		mapita->operator[](PINA_ALTA) = JOY_CUADRADO;
		mapita->operator[](PATADA_ALTA) = JOY_TRIANGULO;
		mapita->operator[](CUBRIRSE)= JOY_R1;
		mapita->operator[](LANZAR_ARMA) = JOY_L1;
		comandos = mapita;
	}
}

void JoystickControl::_Init(int id){
	joystick =	NULL;
	joystickHaptic = NULL;
	if(SDL_NumJoysticks() < id +1) log("No se puede abrir el joystick",LOG_ERROR);
	else joystick = SDL_JoystickOpen( id );
	if( joystick == NULL ) log(string("No se puede leer el joystick! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
	else{
		log("Joystick cargado correctamente",LOG_DEBUG);
		//joystickHaptic = SDL_HapticOpenFromJoystick( joystick );
		if( joystickHaptic == NULL ){
			log(string("El Joystick no soporta haptics! SDL Error:" + string(SDL_GetError())),LOG_WARNING);
		}
		else{
			//Get initialize rumble
			if( SDL_HapticRumbleInit( joystickHaptic ) < 0 ){
				log(string("Unable to initialize rumble! SDL Error:" + string(SDL_GetError())),LOG_WARNING);
			}
		}
	}
}

void JoystickControl::JoyPressed(){
	//X axis motion
	if(evento->type == SDL_JOYAXISMOTION){
		if( evento->jaxis.axis == 0 ){
			//Left of dead zone
			if( evento->jaxis.value < -JOYSTICK_DEAD_ZONE ){
				personaje->CaminarIzquierda();
			}
			//Right of dead zone
			else if( evento->jaxis.value > JOYSTICK_DEAD_ZONE ){
				personaje->CaminarDerecha();
			}
			else{
				//NO SE
			}
		}
		//Y axis motion
		else if( evento->jaxis.axis == 1 ){
			//arriba
			if( evento->jaxis.value < -JOYSTICK_DEAD_ZONE ){
				personaje->Saltar();
			}
			//abajo
			else if( evento->jaxis.value > JOYSTICK_DEAD_ZONE){
				personaje->Agachar();
			}
			else{
				//NADA
			}
		}
	}
	//Boton
	else if (evento->type == SDL_JOYBUTTONUP){
		int boton = evento->jbutton.button;
		if (boton == comandos->operator[](PATADA_BAJA) )
			personaje->pinaBaja();
		else if( boton == comandos->operator [](PINA_ALTA)){
			personaje->pinaAlta();
			if (SDL_JoystickGetAxis(joystick,1) > JOYSTICK_DEAD_ZONE )
				if (joystickHaptic != NULL)
					SDL_HapticRumblePlay( joystickHaptic, 0.75, 700 );
		}
		else if ( boton == comandos->operator [](PATADA_BAJA)){
			personaje->patadaBaja();
		}
		else if ( boton == comandos->operator [](PATADA_ALTA)){
				personaje->patadaAlta();
		}
		else if ( boton == comandos->operator [](CUBRIRSE)){
				personaje->cubrirse();
		}
		else if ( boton == comandos->operator [](LANZAR_ARMA)){
				//personaje->lanzarObjeto();
		}
		else if ( boton == JOY_START){
			pausa = !pausa;
		}
	}
}
void JoystickControl::JoyState(){
	Sint16 x_mov = SDL_JoystickGetAxis(joystick,0);
	Sint16 y_mov = SDL_JoystickGetAxis(joystick,1);
	int sentido_personaje = personaje->getSentidoDeMovimiento();

	//frena si no se esta manteniendo para un lado el analogico
	if ( ( sentido_personaje > 0 && x_mov < JOYSTICK_DEAD_ZONE ) || (sentido_personaje < 0 && x_mov > -JOYSTICK_DEAD_ZONE)  )
		personaje->Frenar();

	//se levanta si no esta manteniendo para abajo el analogico
	if (!(y_mov > JOYSTICK_DEAD_ZONE))
		personaje->Levantarse();

	//se deja de cubrir si no esta apretado
	if (SDL_JoystickGetButton(joystick,JOY_R1) == BUTTON_UNPRESSED)
		personaje->dejarDeCubrirse();

}

JoystickControl::~JoystickControl() {
	personaje = NULL;
	if (joystick != NULL && SDL_JoystickGetAttached(joystick)){
		SDL_JoystickClose( joystick );
		joystick = NULL;
	}
	if (joystickHaptic != NULL){
		SDL_HapticClose(joystickHaptic);
		joystickHaptic = NULL;
	}
	if (comandos != NULL)
		comandos->clear();
}

