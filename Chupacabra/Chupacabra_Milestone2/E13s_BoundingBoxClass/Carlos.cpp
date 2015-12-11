#include "Carlos.h"

Carlos* Carlos::instance; 

Carlos::Carlos()
{
	instance = nullptr; 
	score = 0; 
	objects.push_back("Planets\\00_Sun.obj");
	throwTimer = 0;
	mngr = CameraManagerSingleton::GetInstance();
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
	if (throwTimer <= 0.0f)
	{
		vector3 vel = vector3(coord, -1); 
		vel = vel * 3.0f / (float)vel.length();
		//vel.x = mngr->GetPosition().x + vel.x;
		//vel.y = mngr->GetPosition().y - vel.y;
		Projectile thrown = Projectile(vel, vector3(0.0f, 1.0f, 10.0f), objects.at(0));
		projectiles.push_back(thrown);
		//score++;
		throwTimer = 10.0f;
	}
}

void Carlos::Countdown(float scaledDeltaTime)
{
	if (projectiles.size() > 0) {
		if (projectiles[0].killMe) {
			DeleteFirstProjectile();
		}
	}
	if (throwTimer > 0)
		throwTimer -= scaledDeltaTime;
}

void Carlos::DeleteFirstProjectile() {
	if (projectiles.size() > 0) {
		projectiles.pop_back();
	}
}
