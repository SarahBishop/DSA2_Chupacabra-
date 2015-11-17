#include "MyEntitySingleton.h"
//  MyEntitySingleton
MyEntitySingleton* MyEntitySingleton::m_pInstance = nullptr;
void MyEntitySingleton::Init(void)
{
	m_nData = 0;
}
void MyEntitySingleton::Release(void)
{
	m_lData.clear();
}
MyEntitySingleton* MyEntitySingleton::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntitySingleton();
	}
	return m_pInstance;
}
void MyEntitySingleton::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
MyEntitySingleton::MyEntitySingleton() { Init(); }
MyEntitySingleton::MyEntitySingleton(MyEntitySingleton const& other) { }
MyEntitySingleton& MyEntitySingleton::operator=(MyEntitySingleton const& other) { return *this; }
MyEntitySingleton::~MyEntitySingleton() { Release(); };
//Accessors
void MyEntitySingleton::SetData(int a_nData) { m_nData = a_nData; }
int MyEntitySingleton::GetData(void) { return m_nData; }
void MyEntitySingleton::SetDataOnVector(int a_nData) { m_lData.push_back(a_nData); }
int& MyEntitySingleton::GetDataOnVector(int a_nIndex)
{
	int nIndex = static_cast<int>(m_lData.size());
	assert(a_nIndex >= 0 && a_nIndex < nIndex);
	return m_lData[a_nIndex];
}
//--- Non Standard Singleton Methods
// generate a specified number of entities
void MyEntitySingleton::GenerateNewEntity(String nm, vector3 v3Pos, vector3 v3Vel, vector3 v3Accel, float fMass, float fMaxAccel)
{
	// create temporary entity, change its attributes, then add to vector
	MyEntityClass temp = MyEntityClass(nm);	
	temp.SetPosition(v3Pos);
	temp.SetVelocity(v3Vel);
	temp.SetAcceleration(v3Accel);
	temp.SetMass(fMass);
	temp.SetMaxAccel(fMaxAccel);
	vectorOfEntities.push_back(temp);
}
// update all entities
void MyEntitySingleton::Update()
{
	for (int i = 0; i < vectorOfEntities.size(); i++)
	{
		vectorOfEntities[i].Update();
	}
}




