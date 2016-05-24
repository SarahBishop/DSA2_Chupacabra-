#ifndef _CANYON_MANAGER_
#define _CANYON_MANAGER_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "CanyonSegment.h"

class CanyonManager
{
public:
	std::vector<CanyonSegment> listOfSegments;

	// clipping planes
	float nearPlane;
	float farPlane;
	float cameraDepth = 5.0f; // padding to prevent camera clipping

	float segmentZLength;

	CanyonManager();
	void GenerateCanyon(uint nSegments);
	void Render();
	void Update();


};

#endif //_CANYON_MANAGER_