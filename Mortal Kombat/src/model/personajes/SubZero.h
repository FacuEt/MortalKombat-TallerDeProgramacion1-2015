/*
 * SubZero.h
 *
 *  Created on: 8/6/2015
 *      Author: tomi
 */

#ifndef SRC_MODEL_PERSONAJES_SUBZERO_H_
#define SRC_MODEL_PERSONAJES_SUBZERO_H_

namespace std {

class SubZero : public Personaje{
public:
	SubZero(string nombre_personaje,vector<Sprite*> Sprites,vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped=false);
	virtual ~SubZero();

	void poder2();
	void fatality1(Personaje* personajeQueRecibe);

};

} /* namespace std */

#endif /* SRC_MODEL_PERSONAJES_SUBZERO_H_ */