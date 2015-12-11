#include "Chupacabra.h"

Chupacabra::Chupacabra(vector3 pos, String mName, String mFLName, String mBLName)
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
	frontLegModelName = mFLName;
	backLegModelName = mBLName;

	// acceleration forces
	v3Gravity = vector3(0.0f, GRAVITY, 0.0f);
	v3ForwardForce = vector3(0.0f, 0.0f, 0.0f);
	v3Acceleration += v3Gravity;
	v3Acceleration += v3ForwardForce;
	
	// default vel
	velocity = vector3(0.1f);
}

void Chupacabra::SetRolling()
{
	rolling = true; 
	//velocity = vector3(2.0f * rand(), 0.0f, 2.0f); //start bounding on some random path on the x-z plane; no y-bouncing for now
		//rand() % num+1
}

void Chupacabra::Move(float scaledDeltaTime)
{
	velocity += v3Acceleration * scaledDeltaTime;
	position += velocity * scaledDeltaTime;

	// animate legs
	if (frontLegsForward) {
		frontLegAngle += 5 * scaledDeltaTime;
		backLegAngle -= 5 * scaledDeltaTime;
	}
	else {
		frontLegAngle -= 5 * scaledDeltaTime;
		backLegAngle += 5 * scaledDeltaTime;
	}

	if (frontLegAngle > 70) {
		frontLegsForward = false;
	}
	if (frontLegAngle < 20) {
		frontLegsForward = true;
	}
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
	m_pMeshMngr->AddInstanceToRenderList(frontLegModelName);
	m_pMeshMngr->AddInstanceToRenderList(backLegModelName);
	m_pMeshMngr->SetModelMatrix(glm::translate(position), modelName);
	m_pMeshMngr->SetModelMatrix(glm::translate(position)*glm::rotate(frontLegAngle, vector3(1, 0, 0)), frontLegModelName);
	m_pMeshMngr->SetModelMatrix(glm::translate(position)*glm::rotate(backLegAngle, vector3(1, 0, 0)), backLegModelName);
}