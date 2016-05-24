/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __MYENTITYMANAGER_H_
#define __MYENTITYMANAGER_H_

#include "MyEntityClass.h"

//System Class
class MyEntityManager
{
	uint m_nEntityCount = 0; //number of elements in the list
	static MyEntityManager* m_pInstance; // Singleton pointer
	std::vector<MyEntityClass*> m_lEntity; //list of elements
	std::map<String, uint> m_map;//Map relating the mesh and the index
	MyBOManager* m_pColliderManager = nullptr; //Collider manager
public:
	/*
	Method: GetInstance
	Usage: returns the singleton pointer
	Arguments: ---
	Output: MyEntityManager* -> singleton Accessor
	*/
	static MyEntityManager* GetInstance();
	/*
	Method: ReleaseInstance
	Usage: releases the singleton pointer
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);

	/*
	Method: GetEntity
	Usage: Gets the number of entries on vector
	Arguments: ---
	Output: int -> number of entries
	*/
	int GetEntityCount(void);

	/*
	Method: AddEntity
	Usage: Adds a new entry to the list of Entity
	Arguments: MyEntityClass* a_nEntity-> Entity to add
	Output: ---
	*/
	void AddEntity(MyEntityClass* a_nEntity);

	/*
	Method: AddEntity
	Usage: Adds a new entry to the list of Entity
	Arguments: String a_nsEntity-> Creates an entity
	Output: ---
	*/
	void AddEntity(String a_sEntity);

	/*
	Method: SetValues
	Usage: Sets the values for acceleration mass and maximum acceleration of the entity
	Arguments: 
		vector3 a_v3Acceleration -> acceleration
		float a_fMass -> mass
		float a_fMaxAcc -> maximum acceleration
		String a_sEntity -> entity id
	Output: ---
	*/
	void SetValues( vector3 a_v3Acceleration, float a_fMass, float a_fMaxAcc, String a_sEntity );
	
	/*
	Method: GetEntity
	Usage: Returns the entry in the specified index, nullptr if un-existent
	Arguments: int a_nIndex -> index to return
	Output: MyEntityClass* -> value on list
	*/
	MyEntityClass* GetEntity(int a_nIndex);

	/*
	Method: GetEntity
	Usage: Returns the entry in the specified index, nullptr if un-existent
	Arguments: int a_nIndex -> index to return
	Output: MyEntityClass* -> value on list
	*/
	MyEntityClass* GetEntity(String a_sEntity);

	/*
	Method: GetIndex
	Usage: Returns the index specified by name from the dictionary
	Arguments:
		String a_sIndex -> name of the index
	Output: index of the specified name, -1 if not found
	*/
	int GetIndex(String a_sEntity);

	/*
	Method: Update
	Usage: Updates all the Entity
	Arguments: ---
	Output: ---
	*/
	void Update(void);
	//void CheckCollision();
	/*
	Method: SetMaxAcc
	Usage: Accessor of Maximum acceleration
	Arguments: 
		float a_fMaxAcc -> Max Acceleration input
		String a_sEntity -> Entity ID
	Output: ---
	*/
	void SetMaxAcc(float a_fMaxAcc, String a_sEntity);

	/*
	Method: SetMass
	Usage: Accessor of mass
	Arguments: 
		float a_fMass -> mass input
		String a_sEntity -> Entity ID
	Output: ---
	*/
	void SetMass(float a_fMass, String a_sEntity);
	/*
	Method: SetPosition
	Usage: Accessor of Position
	Arguments: 
		vector3 a_v3Position -> position input
		String a_sEntity -> Entity ID
	Output: ---
	*/
	void SetPosition(vector3 a_v3Position, String a_sEntity);
	/*
	Method: SetVelocity
	Usage: Accessor of velocity
	Arguments:
		vector3 a_v3Velocity -> velocity input
		String a_sEntity -> Entity ID
	Output: ---
	*/
	void SetVelocity(vector3 a_v3Velocity, String a_sEntity);
	/*
	Method: SetAcceleration
	Usage: Accessor of acceleration
	Arguments:
		vector3 a_v3Acceleration -> acceleration input
		String a_sEntity -> Entity ID
	Output: ---
	*/
	void SetAcceleration(vector3 a_v3Acceleration, String a_sEntity);

private:
	/*
	Method: MyEntityManager
	Usage: Constructor
	Arguments: ---
	Output: Class object
	*/
	MyEntityManager(void);
	/*
	Method: MyEntityManager
	Usage: copy constructor
	Arguments: Class object to copy
	Output: Class object
	*/
	MyEntityManager(MyEntityManager const& other);
	/*
	Method: operator=
	Usage: copy assignment operator
	Arguments: Class object to copy
	Output: Class object
	*/
	MyEntityManager& operator=(MyEntityManager const& other);
	/*
	Method: ~MyEntityManager
	Usage: destructor
	Arguments: ---
	Output: ---
	*/
	~MyEntityManager(void);
	/*
	Method: Release
	Usage: Releases the memory of the singleton
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Init
	Usage: Initializes the default values
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

#endif //__MYENTITYMANAGER_H_