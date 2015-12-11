/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __MYOCTANT_H_
#define __MYOCTANT_H_

#include "RE\ReEng.h"
#include "MyBoundingObjectClass.h"
#include "Chupacabra.h"

//System Class
class MyOctant
{
	static uint m_nMaxSubLevel;
	uint m_nLevel = 0;
	uint m_nChildren = 0;
	MyOctant* m_pParent = nullptr;
	MyOctant* m_pChild[8];

	float m_fSize = 0.0f; //Size of the octant

	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton

	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the Object Class

	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the Object Class
	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides


public:
	// constructor for creating biggest box/root
	MyOctant(std::vector<vector3> a_lVectorList);

	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MyOctant(vector3 a_v3Center, float a_fSize);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	MyOctant(MyOctant const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	MyOctant& operator=(MyOctant const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MyOctant(void);
	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- MyOctant& other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(MyOctant& other);
	
	/*
	USAGE: Gets the Octant size
	ARGUMENTS: ---
	OUTPUT: Size of the octant
	*/
	float GetSize(void);
	// list of MyBoundingObjectClass objects to see what's inside the octant node
	std::vector<Chupacabra*> objectsInNode;
	/*
	USAGE:
	ARGUMENTS:
	- vector3 a_v3Color = REDEFAULT -> Color of the Object to display if the value is REDEFAULT it
	-- will display Objects in white and colliding ones in red.
	OUTPUT: ---
	*/
	void Display(vector3 a_v3Color = REDEFAULT);
	void Subdivide(void);
	MyOctant* GetParent();
	MyOctant* GetChild(uint nIndex);
	void KillBranch(void);
	void CheckForBOInOctant(Chupacabra* chup);
	void CheckBOCollisions(void);
	int GetChildren(); //returns the number of children
	void ClearList();


private:
	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

#endif //__MYOCTANT_H__
