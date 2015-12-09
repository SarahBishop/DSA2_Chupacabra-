#ifndef _CHUPACABRA_H_
#define _CHUPACABRA_H_

#include "RE\ReEngAppClass.h"
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "MyBoundingObjectClass.h"

#define GRAVITY -0.01f

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
	// acceleration and max limit for accel
	glm::vec3 v3Acceleration;
	float fMaxAccel = 0.45f;
	float fVelMag; // magnitude of velocity
	float fMass = 1.0f;
	enum State { SPAWNING, CHASING, BOUNCING };
	State state = SPAWNING;

	//code for rendering multiple objects with the same model
	String modelName;

	// forces
	glm::vec3 v3Gravity;
	glm::vec3 v3ForwardForce;

	// bounding object attribute
	MyBoundingObjectClass* myBO;
	MeshManagerSingleton* m_pMeshMngr;

	// radius for collisions, possibly temporary
	//float fRadius;

	//Constructor
	Chupacabra(vector3 pos, String mName); 
	//Destructor
	//~Chupacabra(); 
	//Updates the chupacabra's position
	void Move(float scaledDeltaTime);
	void SetRolling(); 
	void Bounce(vector3 otherPos); 
	void Render();
};

#endif
