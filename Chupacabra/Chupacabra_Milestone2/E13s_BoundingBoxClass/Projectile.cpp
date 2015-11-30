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
	//	Release();  //delete this once it's too far away 
}

void Projectile::Release(void)
{
	//bounding->~MyBoundingObjectClass();
} 

//destroy the bounding object and the object
Projectile::~Projectile(void)
{
	Release();
}