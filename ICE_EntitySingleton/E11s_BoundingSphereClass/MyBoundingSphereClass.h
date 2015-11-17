/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __MYBOUNDINGSPHERECLASS_H_
#define __MYBOUNDINGSPHERECLASS_H_

#include "RE\ReEng.h"


//System Class
class MyBoundingSphereClass
{
	float m_fRadius = 0.0f; //Radius of the Bounding Sphere
	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Sphere Class
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Sphere Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Sphere Class

public:
	/*
	Method: MyBoundingSphereClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MyBoundingSphereClass(std::vector<vector3> a_lVectorList);
	/*
	Method: MyBoundingSphereClass
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyBoundingSphereClass(MyBoundingSphereClass const& other);
	/*
	Method: operator=
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyBoundingSphereClass& operator=(MyBoundingSphereClass const& other);
	/*
	Method: ~MyBoundingSphereClass
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyBoundingSphereClass(void);

	/*
	Method: Swap
	Usage: Changes object contents for other object's
	Arguments:
		other -> object to swap content from
	Output: ---
	*/
	void Swap(MyBoundingSphereClass& other);

	/*
	Method: SetToWorldMatrix
	Usage: Sets the Bounding Sphere into world coordinates
	Arguments:
		matrix4 a_m4ToWorld -> Model to World matrix
	Output: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
	
	/*
	Method: GetCenter
	Usage: Gets the Bounding Sphere's center in world coordinates
	Arguments: ---
	Output: vector3 -> Center's of the sphere in world coordinates
	*/
	vector3 GetCenter(void);

	/*
	Method: GetRadius
	Usage: Gets the Bounding Sphere's radius
	Arguments: ---
	Output: float -> radius of the Bounding Sphere
	*/
	float GetRadius(void);

	/*
	Method: IsColliding
	Usage: Asks if there is a collision with another Bounding sphere Object
	Arguments: 
		MyBoundingSphereClass* const a_pOther -> Other object to check collision with
	Output: bool -> check of the collision
	*/
	bool IsColliding(MyBoundingSphereClass* const a_pOther);
	
private:
	/*
	Method: Release
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Init
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

#endif //__MYBOUNDINGSPHERECLASS_H__