#include "Projectile.h"

#define GRAVITY -0.02f

Projectile::Projectile(vector3 vel, vector3 pos, String mod)
{
	velocity = vel; 
	position = pos; 
	acceleration = vector3(0, GRAVITY, 0);
	fMaxAccel = 1.0f;
	fMass = 4.f;
	fVelMag = 1.0f;
	model = mod; 
	meshMngr =  MeshManagerSingleton::GetInstance();
	bounding = new MyBoundingObjectClass(meshMngr->GetVertexList(meshMngr->GetNameOfInstanceByIndex(1)), true);
}

void Projectile::Move(float scaledDT)
{
	velocity += acceleration;
	position += velocity;
	//if (position.z < 20.0f)
	//	Release();  //delete this once it's too far away 

	// left wall
	if (position.x < -5.0f + 1) // -5 is the left canyon wall's position
	{
		position.x = -5.0f + 1;
		velocity.x *= -1.0f;
	}
	// right wall
	else if (position.x > 5.0f - 1)
	{
		position.x = 5.0f - 1;
		velocity.x *= -1.0f;
	}
	// floor
	if (position.y < -1.0f + 1)
	{
		position.y = -1.0f + 1;
		velocity.y *= -1.0f;
	}
	// front wall/camera
	/*if (position.z > 1) // 13 is segmentZLength + cameraDepth from CanyonManager.cpp
	{
		position.z = 1 - 10;
		velocity.z *= -1.0f;
	}*/
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