#ifndef __MYENTITY_H_
#define __MYENTITY_H_

#include "MyBOManager.h"
class MyEntityClass
{
	vector3 m_v3Position = vector3();
	quaternion m_qOrientation = quaternion();
	vector3 m_v3Scale = vector3();

	vector3 m_v3Velocity = vector3();
	vector3 m_v3Acceleration = vector3();

	float m_fMass = 1.0f;
	float m_fMaxAcc = 10.0f;

	

	MyBOManager* m_pColliderManager = nullptr;
	MeshManagerSingleton* m_pMeshManager = nullptr;

public:
	String m_sName = "";
	/*
	Method: MyEntityClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MyEntityClass(String a_sName);

	/*
	Method: MyEntityClass
	Usage: Constructor
	Arguments: class object
	Output: class object
	*/
	MyEntityClass(MyEntityClass const& other);

	/*
	Method: operator=
	Usage: Copy Assigment operator
	Arguments: ---
	Output: class object
	*/
	MyEntityClass& operator=(MyEntityClass const& other);

	/*
	Method: MyBOClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	~MyEntityClass();

	void Update(void);

	void SetMass(float a_fMass);
	void SetPosition(vector3 a_v3Position);
	void SetVelocity(vector3 a_v3Velocity);
	void SetAcceleration(vector3 a_v3Acceleration);
	void SetMaxAccel(float a_fAccel);

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


protected:
	/*
	Method: MyBOClass
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	void Init(void);
	/*
	Method: Swap
	Usage: Exchanges member information with object
	Arguments:  class object
	Output: ---
	*/
	void Swap(MyEntityClass& other);
	/*
	Method: Release
	Usage: Releases the allocated memory
	Arguments: ---
	Output: ---
	*/
	void Release(void);
};
#endif //__MYENTITY_H_