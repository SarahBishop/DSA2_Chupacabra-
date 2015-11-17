#ifndef _MY_ENTITY_SINGLETON_
#define _MY_ENTITY_SINGLETON_

#include "MyEntityClass.h"

class MyEntitySingleton
{
	int m_nData = 0; //number of elements in the list
	static MyEntitySingleton* m_pInstance; // Singleton pointer
	std::vector<int> m_lData; //list of elements
	std::vector<MyEntityClass> vectorOfEntities; // holds all entities
public:
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	static MyEntitySingleton* GetInstance();
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetData(void);
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetData(int a_nData = 1);
	/* Property GetData/SetData */
	//__declspec(property(get = GetData, put = SetData)) int Data;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetDataOnVector(int a_nData);
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	int& GetDataOnVector(int a_nIndex);

	// generate a specified number of entities
	void GenerateNewEntity(String nm, vector3 v3Pos, vector3 v3Vel, vector3 v3Accel, float fMass, float fMaxAccel);
	// update all entities
	void Update();

private:
	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	MyEntitySingleton(void);
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	MyEntitySingleton(MyEntitySingleton const& other);
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	MyEntitySingleton& operator=(MyEntitySingleton const& other);
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	~MyEntitySingleton(void);
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method:
	Usage:
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

#endif //_MY_ENTITY_SINGLETON_
