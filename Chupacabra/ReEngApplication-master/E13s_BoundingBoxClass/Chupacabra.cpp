#include "Chupacabra.h"

Chupacabra::Chupacabra(vector3 pos, String mName)
{
	rolling = false; 
	position = pos; 
	baseY = position.y; 
	velocity = vector3(0.0f); 
	srand(time_t(NULL)); //seed the random
	moveMod1 = rand(); 
	moveMod2 = rand(); 
	myBO = nullptr;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	modelName = mName;

	// acceleration forces
	v3Gravity = vector3(0.0f, GRAVITY, 0.0f);
	v3ForwardForce = vector3(0.0f, 0.0f, 0.2f);
	v3Acceleration += v3Gravity;
	v3Acceleration += v3ForwardForce;
}

void Chupacabra::SetRolling()
{
	rolling = true; 
	velocity = vector3(2.0f * rand(), 0.0f, 2.0f * rand()); //start bounding on some random path on the x-z plane; no y-bouncing for now
		//rand() % num+1
}

void Chupacabra::Move()
{
	//if the Chupacabra is not knocked over yet, 
	//advance on a sine wave. 
	//else roll according to velocity 
	/*if (!rolling)
	{
		position = vector3(position.x, position.y + moveMod1 * sinf(moveMod2 * time(time_t(NULL))), position.z); 
	}
	else
	{*/
		// add all forces
		//v3Acceleration += v3Gravity;
		//v3Acceleration += v3ForwardForce;
		velocity += v3Acceleration;
		position += velocity; 
	//}
}

void Chupacabra::Bounce(vector3 otherPos)
{
	float xDif = abs(otherPos.x - position.x); 
	float zDif = abs(otherPos.z - position.z); 
	if (xDif > zDif)
		velocity = vector3(-1.0f * velocity.x, 0.0f, velocity.z);
	else
		velocity = vector3(velocity.x, 0.0f, -1.0f * velocity.z);

	//bounce a step off of the collision target to exit the collision
	position += velocity; 
}

void Chupacabra::Render()
{
	//vector4 tempV4 = vector4(position.x, position.y, position.z, 1);
	//m_pMeshMngr->AddSphereToQueue(glm::translate(position),REWHITE);
	m_pMeshMngr->AddInstanceToRenderList(modelName);
	m_pMeshMngr->SetModelMatrix(glm::translate(position), modelName);
}