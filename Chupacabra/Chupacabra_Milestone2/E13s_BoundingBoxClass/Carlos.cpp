#include "Carlos.h"

Carlos* Carlos::instance; 

Carlos::Carlos()
{
	instance = nullptr; 
	score = 0; 
	objects.push_back("Planets\\00_Sun.obj");
	throwTimer = 0;
	mngr = CameraManagerSingleton::GetInstance();;
}

Carlos* Carlos::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Carlos();
	}
	return instance;
}

String Carlos::ShowScore()
{
	return "SCORE: " + std::to_string(score); 
}

String Carlos::ProveClick(vector2 coord)
{
	return "Clicked at: " + std::to_string(coord.x) + " , " + std::to_string(coord.y); 
}

void Carlos::GenerateObject()
{

}

void Carlos::ThrowObject(vector2 coord)
{
	if (throwTimer <= 0)
	{
		vector3 vel = vector3(coord, -1); 
		//vel.x = mngr->GetPosition().x + vel.x;
		//vel.y = mngr->GetPosition().y - vel.y;
		Projectile thrown = Projectile(vel, vector3(0.0f, 0.0f, -1.0f), objects.at(0));
		projectiles.push_back(thrown);
		score++;
		throwTimer = 30;
	}
}

void Carlos::Countdown()
{
	if (throwTimer > 0)
		throwTimer--; 
}
