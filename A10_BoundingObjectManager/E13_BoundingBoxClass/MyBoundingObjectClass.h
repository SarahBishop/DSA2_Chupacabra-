#ifndef MY_BOUNDING_OBJECT_CLASS
#define MY_BOUNDING_OBJECT_CLASS

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class MyBoundingObjectClass
{
public:
	// attributes for sphere
	vector3 center;
	float fRadius;
	int nSubdivisions;
	std::vector<vector3> myList;
	bool isColliding;
	PrimitiveClass* m_pSphere;
	vector3 v3Color;

	// box attributes
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the box Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the box Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the box Class
	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides

	// constructor
	MyBoundingObjectClass(std::vector<vector3> listOfVertex);
	
	// methods
	bool IsColliding(MyBoundingObjectClass* pOther);

	// box methods
	void SetModelMatrix(matrix4 a_m4ToWorld);
	matrix4 GetModelMatrix(void);
	vector3 GetCenterLocal(void);
	vector3 GetCenterGlobal(void);
	vector3 GetHalfWidth(void);

	// set color of primitive
	void SetColor(vector3 a_v3Color);
};

#endif //MY_BOUNDING_OBJECT_CLASS