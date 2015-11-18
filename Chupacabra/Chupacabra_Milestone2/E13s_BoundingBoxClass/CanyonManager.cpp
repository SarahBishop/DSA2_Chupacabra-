#include "CanyonManager.h"

CanyonManager::CanyonManager()
{	
	segmentZLength = 8.0f;
	nearPlane = segmentZLength + cameraDepth;
	farPlane = 0;
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
}
void CanyonManager::Render()
{
	for (int i = 0; i < listOfSegments.size(); i++)
	{
		listOfSegments.at(i).Render();
	}
}
void CanyonManager::Update()
{
	for (int i = 0; i < listOfSegments.size(); i++)
	{
		listOfSegments.at(i).v3Position -= vector3(0.0f, 0.0f, 1.0f);

		// clipping planes
		if (listOfSegments.at(i).v3Position.z <= farPlane)
		{
			listOfSegments.at(i).v3Position = vector3(0.0f, 0.0f, nearPlane);
			
			//change canyon color
			float brightness = (rand() % 399 + 600) / 1000.f; // originally (rand() % 399 + 400) / 1000.f
			listOfSegments.at(i).v3Color = vector3(brightness, brightness * 0.68f, brightness * 0.3f); //originally vector3(brightness, brightness * 0.5f, 0.1f) for RIT colors
		}
	}
}