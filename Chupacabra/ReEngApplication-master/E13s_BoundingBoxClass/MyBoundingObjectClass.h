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
	float fRadiusG;
	int nSubdivisions;
	std::vector<vector3> myList;
	bool isColliding;
	PrimitiveClass* m_pSphere;
	vector3 v3Color;
	bool visible; 

	// box attributes
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the box 
	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the box 

	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the box 
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the box 

	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the box 
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the box 

	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides

	// constructor
	MyBoundingObjectClass(); // default
	MyBoundingObjectClass(std::vector<vector3> listOfVertex);
	MyBoundingObjectClass(std::vector<vector3> listOfVertex, bool isSphere); // overloaded constructor

	// copy constructor
	MyBoundingObjectClass(MyBoundingObjectClass const& other);

	// copy assingment
	MyBoundingObjectClass& operator=(MyBoundingObjectClass const& other);

	// destructor
	~MyBoundingObjectClass(void);

	void Release(void);
	
	// collision methods
	bool IsColliding(MyBoundingObjectClass* pOther);

	// box methods
	void SetModelMatrix(matrix4 a_m4ToWorld);
	matrix4 GetModelMatrix(void);
	vector3 GetCenterLocal(void);
	vector3 GetCenterGlobal(void);
	vector3 GetHalfWidth(void);
	vector3 GetHalfWidthG(void);

	void ToggleVisible(void);

	// set color of primitive
	void SetColor(vector3 a_v3Color);
	vector3 GetColor(); 
};

#endif //MY_BOUNDING_OBJECT_CLASS