#ifndef _CANYON_SEGMENT_H_
#define _CANYON_SEGMENT_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class CanyonSegment
{
public:
	// planes that make up canyon
	/*PrimitiveClass* floor;
	PrimitiveClass* leftWall;
	PrimitiveClass* rightWall;*/

	// meshmanager
	MeshManagerSingleton* m_pMeshMngr;

	// position
	vector3 v3Position;
	/*vector3 v3leftPosition;
	vector3 v3floorPosition;
	vector3 v3rightPosition;*/

	// color
	vector3 v3Color;

	// length of segment
	float zLength;

	// constructor & destructor
	CanyonSegment(vector3 v3Pos, vector3 v3Col, float zLength_);
	~CanyonSegment();
	
	// draws planes
	void Render();


};

#endif //_CANYON_SEGMENT_H_