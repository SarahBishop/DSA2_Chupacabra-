#ifndef _CHUPACABRA_H_
#define _CHUPACABRA_H_

#include "RE\ReEngAppClass.h"
#include <time.h>
#include <cstdlib>
#include <math.h>

class Chupacabra {

public: 
	//this is the overall position of the Chupacabra
	vector3 position; 
	//this is for the sine wave
	float baseY; 
	//this is to determine whether the Chupacabra is 
	//chasing the player or has been knocked over
	bool rolling; 
	//this vector is only used when rolling == true
	vector3 velocity;
	//this is to give each chupacabra a random movement pattern
	float moveMod1; 
	//also for determining a unique random  movement pattern
	float moveMod2; 

	//Constructor
	Chupacabra(vector3 pos); 
	//Destructor
	~Chupacabra(); 
	//Updates the chupacabra's position
	void Move(); 
	void SetRolling(); 
	void Bounce(vector3 otherPos); 
};

#endif
