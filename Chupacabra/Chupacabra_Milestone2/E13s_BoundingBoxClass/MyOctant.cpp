#include "MyOctant.h"
uint MyOctant::m_nMaxSubLevel = 3;
//  MyOctant
void MyOctant::Init(void)
{
	m_nLevel = 0;
	m_nChildren = 0;
	m_v3Center = vector3(0.0f);
	
	m_fSize = 0.0f;

	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
	m_v3HalfWidth = vector3(0.0f);

	MyOctant* m_pParent = nullptr;
	
	for (uint nChild = 0; nChild < 8; nChild++)
	{
		m_pChild[nChild] = nullptr;
	}
}
void MyOctant::Swap(MyOctant& other)
{
	std::swap(m_nLevel, other.m_nLevel);
	std::swap(m_nChildren, other.m_nChildren);
	std::swap(m_v3Center, other.m_v3Center);
	std::swap(m_fSize, other.m_fSize);

	std::swap(m_pMeshMngr, other.m_pMeshMngr);
}
void MyOctant::Release(void)
{
	if (m_nLevel == 0)
		KillBranch();

	/* No pointers allocated yet */
}
//The big 3
// constructor for root, to find parameters
MyOctant::MyOctant(std::vector<vector3> a_lVectorList)
{
	//Init the default values
	Init();

	//Count the points of the incoming list
	uint nVertexCount = a_lVectorList.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = a_lVectorList[0];

	// access megsh manager
	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > a_lVectorList[nVertex].x) //If min is larger than current
			m_v3Min.x = a_lVectorList[nVertex].x;
		else if (m_v3Max.x < a_lVectorList[nVertex].x)//if max is smaller than current
			m_v3Max.x = a_lVectorList[nVertex].x;

		if (m_v3Min.y > a_lVectorList[nVertex].y) //If min is larger than current
			m_v3Min.y = a_lVectorList[nVertex].y;
		else if (m_v3Max.y < a_lVectorList[nVertex].y)//if max is smaller than current
			m_v3Max.y = a_lVectorList[nVertex].y;

		if (m_v3Min.z > a_lVectorList[nVertex].z) //If min is larger than current
			m_v3Min.z = a_lVectorList[nVertex].z;
		else if (m_v3Max.z < a_lVectorList[nVertex].z)//if max is smaller than current
			m_v3Max.z = a_lVectorList[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth = (m_v3Max - m_v3Min) / 2.0f;
	m_fSize = m_v3HalfWidth.x;
}

MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{
	Init();
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;

	// setting new min and max
	m_v3Min.x = m_v3Center.x - m_fSize;
	m_v3Min.y = m_v3Center.y - m_fSize;
	m_v3Min.z = m_v3Center.z - m_fSize;

	m_v3Max.x = m_v3Center.x + m_fSize;
	m_v3Max.y = m_v3Center.y + m_fSize;
	m_v3Max.z = m_v3Center.z + m_fSize;

}
MyOctant::MyOctant(MyOctant const& other)
{
	m_nLevel = other.m_nLevel;
	m_v3Center = other.m_v3Center;
	m_fSize = other.m_fSize;
	m_nChildren = other.m_nChildren;
	m_pMeshMngr = other.m_pMeshMngr;
}
MyOctant& MyOctant::operator=(MyOctant const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyOctant temp(other);
		Swap(temp);
	}
	return *this;
}
MyOctant::~MyOctant() { Release(); };
//Accessors
float MyOctant::GetSize(void) { return m_fSize; }
//--- Non Standard Singleton Methods
void MyOctant::Display(vector3 a_v3Color)
{
	for (uint nChild = 0; nChild < m_nChildren; nChild++)
	{
		m_pChild[nChild]->Display(RERED);
	}
	m_pMeshMngr->AddCubeToQueue( glm::translate(m_v3Center) * glm::scale(vector3(m_fSize * 2.0f)), a_v3Color, WIRE);
	//m_pMeshMngr->AddCubeToQueue(glm::translate(IDENTITY_M4, m_v3Center) *
		//glm::scale(m_v3HalfWidth * 2.0f), a_v3Color, WIRE);
}

void MyOctant::Subdivide(void)
{
	//if (m_nLevel >= m_nMaxSubLevel)
	//	return;

	m_nChildren = 8;

	uint nIndex = 0;
	float fNewSize = m_fSize / 2.0f;//m_fSize / 2.0f;
	std::cout << fNewSize;

	vector3 vCenter = m_v3Center + vector3(fNewSize, fNewSize, fNewSize);
	m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
	m_pChild[nIndex]->m_pParent = this;
	m_pChild[nIndex]->m_nLevel = m_nLevel + 1;

	vCenter = m_v3Center + vector3(-fNewSize, fNewSize, fNewSize);
	nIndex++;
	m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
	m_pChild[nIndex]->m_pParent = this;
	m_pChild[nIndex]->m_nLevel = m_nLevel + 1;

	vCenter = m_v3Center + vector3(-fNewSize,-fNewSize, fNewSize);
	nIndex++;
	m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
	m_pChild[nIndex]->m_pParent = this;
	m_pChild[nIndex]->m_nLevel = m_nLevel + 1;

	vCenter = m_v3Center + vector3( fNewSize, -fNewSize, fNewSize);
	nIndex++;
	m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
	m_pChild[nIndex]->m_pParent = this;
	m_pChild[nIndex]->m_nLevel = m_nLevel + 1;

	vCenter = m_v3Center + vector3(fNewSize, fNewSize,-fNewSize);
	nIndex++;
	m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
	m_pChild[nIndex]->m_pParent = this;
	m_pChild[nIndex]->m_nLevel = m_nLevel + 1;

	vCenter = m_v3Center + vector3(-fNewSize, fNewSize,-fNewSize);
	nIndex++;
	m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
	m_pChild[nIndex]->m_pParent = this;
	m_pChild[nIndex]->m_nLevel = m_nLevel + 1;

	vCenter = m_v3Center + vector3(-fNewSize, -fNewSize,-fNewSize);
	nIndex++;
	m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
	m_pChild[nIndex]->m_pParent = this;
	m_pChild[nIndex]->m_nLevel = m_nLevel + 1;

	vCenter = m_v3Center + vector3(fNewSize, -fNewSize,-fNewSize);
	nIndex++;
	m_pChild[nIndex] = new MyOctant(vCenter, fNewSize);
	m_pChild[nIndex]->m_pParent = this;
	m_pChild[nIndex]->m_nLevel = m_nLevel + 1;
}

MyOctant * MyOctant::GetChild(uint nIndex)
{
	if(nIndex >= 8)
		return nullptr;

	return m_pChild[nIndex];
}
MyOctant* MyOctant::GetParent()
{
	/*if (m_pParent != nullptr)
	{
		return m_pParent;
	}
	else return nullptr;*/
	return m_pParent;
}
void MyOctant::KillBranch(void)
{
	for (uint nChild = 0; nChild < m_nChildren; nChild++)
	{
		m_pChild[nChild]->KillBranch();
	}
	for (uint nChild = 0; nChild < m_nChildren; nChild++)
	{
		if (m_pChild[nChild] != nullptr)
		{
			delete m_pChild[nChild];
			m_pChild[nChild] = nullptr;
		}
	}
}
void MyOctant::CheckForBOInOctant(Chupacabra* chup/*MyBoundingObjectClass* chup->myBO*/)
{	
	bool bColliding = true;

	//Check for X
	if (m_v3Max.x < chup->myBO->GetCenterGlobal().x - chup->myBO->fRadius)
		bColliding = false;
	if (m_v3Min.x > chup->myBO->GetCenterGlobal().x + chup->myBO->fRadius)
		bColliding = false;
	
	//Check for Y
	if (m_v3Max.y < chup->myBO->GetCenterGlobal().y - chup->myBO->fRadius)
		bColliding = false;
	if (m_v3Min.y > chup->myBO->GetCenterGlobal().y + chup->myBO->fRadius)
		bColliding = false;

	//Check for Z
	if (m_v3Max.z < chup->myBO->GetCenterGlobal().z - chup->myBO->fRadius)
		bColliding = false;
	if (m_v3Min.z > chup->myBO->GetCenterGlobal().z + chup->myBO->fRadius)
		bColliding = false;

	//return bColliding;
	// if true, add bo to colliding list
	if (bColliding)
	{
		objectsInNode.push_back(chup);
	}
}

int MyOctant::GetChildren()
{
	return m_nChildren;
}
void MyOctant::ClearList()
{
	for (int i = 0; i < objectsInNode.size(); i++)
	{
		objectsInNode.clear();
	}
}
//void MyOctant::CheckBOCollisions(void)
//{
//	for (uint nObjectA = 0; nObjectA < objectsInNode.size() - 1; nObjectA++)
//	{
//		for (uint nObjectB = nObjectA + 1; nObjectB < objectsInNode.size(); nObjectB++)
//		{
//			if (objectsInNode.at(nObjectA)->IsColliding(objectsInNode.at(nObjectB)))
//			{
//				m_llCollidingIndices[nObjectA].push_back(nObjectB);
//				m_llCollidingIndices[nObjectB].push_back(nObjectA);
//			}
//		}
//	}
//}
