/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __MYENTITY_H_
#define __MYENTITY_H_

#include "MyBOManager.h"

class MyEntityClass
{
	vector3 m_v3Position = vector3(); //Position of the Entity
	quaternion m_qOrientation = quaternion();//Orientation of the Entity
	vector3 m_v3Scale = vector3(); //Scale of the Entity

	vector3 m_v3Velocity = vector3(); //Velocity of the Entity
	vector3 m_v3Acceleration = vector3(); //Acceleration of the Entity

	float m_fMass = 1.0f;	//Mass of the Entity
	float m_fMaxAcc = 0.1f; //Limit of the acceleration of the entity

	String m_sName = ""; // Name index

	MyBOManager* m_pColliderManager = nullptr; //Collider manager
	MeshManagerSingleton* m_pMeshManager = nullptr;//Mesh Manager

public:
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

	/*
	Method: Update
	Usage: Calculates the position of the entity based on the 
		acceleration and mass, will also update its mesh and collider
	Arguments: ---
	Output: ---
	*/
	void Update(void);
	/*
	Method: SetMaxAcc
	Usage: Accessor of Maximum acceleration
	Arguments: float a_fMaxAcc -> Max Acceleration input
	Output: ---
	*/
	void SetMaxAcc(float a_fMaxAcc);
	/*
	Method: SetMass
	Usage: Accessor of mass
	Arguments: float a_fMass -> mass input
	Output: ---
	*/
	void SetMass(float a_fMass);
	/*
	Method: SetPosition
	Usage: Accessor of Position
	Arguments: vector3 a_v3Position -> position input
	Output: ---
	*/
	void SetPosition(vector3 a_v3Position);
	/*
	Method: SetVelocity
	Usage: Accessor of velocity
	Arguments: vector3 a_v3Velocity -> velocity input
	Output: ---
	*/
	void SetVelocity(vector3 a_v3Velocity);
	/*
	Method: SetAcceleration
	Usage: Accessor of acceleration
	Arguments: vector3 a_v3Acceleration -> acceleration input
	Output: ---
	*/
	void SetAcceleration(vector3 a_v3Acceleration);

	/*
	Method: GetAcceleration
	Usage: Accessor of acceleration
	Arguments: ---
	Output: vector3 -> acceleration of entity
	*/
	vector3 GetAcceleration(void);

	/*
	Method: GetName
	Usage: Accessor of name
	Arguments: ---
	Output: String -> name of entity
	*/
	String GetName(void);

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