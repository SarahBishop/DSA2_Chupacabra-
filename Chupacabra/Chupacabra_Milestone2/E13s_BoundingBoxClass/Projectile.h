#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "RE\ReEngAppClass.h"
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "MyBoundingObjectClass.h"

class Projectile{
public:
	vector3 acceleration;
	vector3 velocity;
	vector3 position;
	float fMaxAccel;
	float fMass;
	float fVelMag;
	String model; 
	MyBoundingObjectClass* bounding; //not using this for now, but it's here as a reminder
	MeshManagerSingleton* meshMngr; 

	MyBoundingObjectClass* myBO;

	Projectile(vector3 vel, vector3 pos, String mod); //just to make things less obnoxious, include these in the constructor
	void Move(float scaledDeltaTime); //advance according to velocity


	void Release(void); 
	~Projectile(void); //we need a destructor for these guys 
};

#endif