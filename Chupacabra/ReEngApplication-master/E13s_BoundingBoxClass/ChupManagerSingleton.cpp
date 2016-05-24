#include "ChupManagerSingleton.h"

ChupManagerSingleton* ChupManagerSingleton::instance; 

ChupManagerSingleton* ChupManagerSingleton::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ChupManagerSingleton();
	}
	return instance;
}

ChupManagerSingleton::ChupManagerSingleton()
{
	instance = nullptr; 
}
void ChupManagerSingleton::GenerateChupacabras(uint numOfChupas, bool isSphere)
{
	//code for rendering multiple chups with one model
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	for (int i = 0; i < numOfChupas; i++)
	{
		m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Chupacabra");
	}
	
	//m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Chupacabra");
	for (int i = 0; i < numOfChupas; i++)
	{
		chups.push_back(Chupacabra(vector3((i + 1.0f)), m_pMeshMngr->GetInstanceByIndex(i)->GetName()));
		chups[i].myBO = new MyBoundingObjectClass(m_pMeshMngr->GetVertexList(m_pMeshMngr->GetNameOfInstanceByIndex(i)), isSphere);
	}
}
void ChupManagerSingleton::Update()
{
	// move the chupacabras
	for (int i = 0; i < chups.size(); i++)
	{
		chups[i].Move();
	}

	for (int i = 0; i < chups.size(); i++)
	{
		// keep chups inside canyon
		// left wall
		if (chups[i].position.x < -5.0f + chups[i].myBO->fRadius) // -5 is the left canyon wall's position
		{
			chups[i].position.x = -5.0f + chups[i].myBO->fRadius;
			chups[i].velocity.x *= -1.0f;
		}
		// right wall
		else if (chups[i].position.x > 5.0f - chups[i].myBO->fRadius)
		{
			chups[i].position.x = 5.0f - chups[i].myBO->fRadius;
			chups[i].velocity.x *= -1.0f;
		}
		// floor
		if (chups[i].position.y < -1.0f + chups[i].myBO->fRadius)
		{
			chups[i].position.y = -1.0f + chups[i].myBO->fRadius;
			chups[i].velocity.y *= -1.0f;
		}
		// front wall/camera
		if (chups[i].position.z > chups[i].myBO->fRadius) // 13 is segmentZLength + cameraDepth from CanyonManager.cpp
		{
			chups[i].position.z = chups[i].myBO->fRadius;
			chups[i].velocity.z *= -1.0f;
		}
	}
}
void ChupManagerSingleton::Render()
{
	for (int i = 0; i < chups.size(); i++)
	{
		chups.at(i).Render();
	}
}