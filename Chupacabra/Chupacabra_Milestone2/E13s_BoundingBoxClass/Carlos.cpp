#include "Carlos.h"

Carlos* Carlos::instance; 

Carlos::Carlos()
{
	instance = nullptr; 
	score = 0; 
	objects.push_back("Planets\\00_Sun.obj");
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
	Projectile thrown = Projectile(vector3(coord, -1.0f), vector3(coord, -1.0f), objects.at(0));
	projectiles.push_back(thrown); 
	score++; 
}
