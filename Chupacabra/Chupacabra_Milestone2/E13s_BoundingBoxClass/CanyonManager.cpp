#include "CanyonManager.h"

CanyonManager::CanyonManager()
{	
	segmentZLength = 8.0f;
	nearPlane = segmentZLength + cameraDepth;
	farPlane = 0;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_pSystem = SystemSingleton::GetInstance(); 
	
	//m_pSystem->AddClock();

	// load canyon plane
	m_pMeshMngr->LoadModel("ChupStuff\\SkyPlane.obj", "SkyPlane");
}
void CanyonManager::GenerateCanyon(uint nSegments)
{
	srand(time(NULL));
	for (int i = 0; i < nSegments; i++)
	{
		float brightness = (rand() % 399 + 600) / 1000.f; // originally (rand() % 399 + 400) / 1000.f -- you can change the colors back if you want
		listOfSegments.push_back(CanyonSegment(vector3(0.0f, 0.0f, i * segmentZLength), vector3(brightness, brightness * 0.68f, brightness * 0.3f), segmentZLength)); //originally vector3(brightness, brightness * 0.5f, 0.1f) for RIT colors
	}

	farPlane = -segmentZLength * (nSegments - 1) + cameraDepth; // define farPlane 
	bgPosition = vector3(0.0f, 23.0f, farPlane);
	bgScale = vector3(10.0f, 20.0f, 0.0f);
}
void CanyonManager::Render()
{
	for (int i = 0; i < listOfSegments.size(); i++)
	{
		listOfSegments.at(i).Render();
	}
	//render the back plane
	m_pMeshMngr->AddInstanceToRenderList("SkyPlane");
	m_pMeshMngr->SetModelMatrix(glm::translate(bgPosition) * glm::scale(bgScale), "SkyPlane");
}
void CanyonManager::Update(float scaledDeltaTime)
{
	for (int i = 0; i < listOfSegments.size(); i++)
	{
		listOfSegments.at(i).v3Position -= scaledDeltaTime * vector3(0.0f, 0.0f, 1.0f);

		// clipping planes
		if (listOfSegments.at(i).v3Position.z <= farPlane)
		{
			listOfSegments.at(i).v3Position = vector3(0.0f, 0.0f, nearPlane + (listOfSegments.at(i).v3Position.z - farPlane) );
			
			//change canyon color
			float brightness = (rand() % 399 + 600) / 1000.f; // originally (rand() % 399 + 400) / 1000.f
			listOfSegments.at(i).v3Color = vector3(brightness, brightness * 0.68f, brightness * 0.3f); //originally vector3(brightness, brightness * 0.5f, 0.1f) for RIT colors
		}
	}
}