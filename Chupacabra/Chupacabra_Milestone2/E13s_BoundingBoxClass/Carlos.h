#ifndef _CARLOS_H_
#define _CARLOS_H_

#include "RE\ReEngAppClass.h"
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "MyBoundingObjectClass.h"
#include "Projectile.h"

class Carlos{

	static Carlos* instance; 

public:
	std::vector<String> objects; //the arraylist of possible objects to throw 
	std::vector<Projectile> projectiles; //keep track of thrown objects inside of Carlos' singleton
	int health; //the health of the player; detract from it every time a chup catches up
	int score; //just in case someone's keeping score ;P
	int throwTimer; //the timer between throws (no spamming every 0.0001 seconds)
	vector3 position; //this should really just be the camera's position, but I'm including it here for the sake of calculation

	static Carlos* GetInstance(); //make Carlos a singleton. There can be only one. 

	void GenerateObject(); //creates a random object to throw from the list of objects
	void ThrowObject(vector2 coord); //called when the player clicks, calls GenerateObject() internally
	void SetPosition(vector3 pos); //sets the position, used for following the camera
	String ShowScore(); //returns a string to be printed to the screen
	//void RenderThrownObjects(); //render the thrown objects. Duh. 

	String ProveClick(vector2 coords); //DEBUGGING

private: 
	Carlos(); //private constructor
};

#endif