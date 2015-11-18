#include "Projectile.h"

Projectile::Projectile(vector3 vel, vector3 pos, String mod)
{
	velocity = vel; 
	position = pos; 
	model = mod; 
}

void Projectile::Move()
{
	position += velocity; 
	//if (position.z < 20.0f)
	//	Destroy(this); //bad code is bad, but you get the picture
}