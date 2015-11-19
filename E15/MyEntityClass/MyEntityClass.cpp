#include "MyEntityClass.h"
void MyEntityClass::Init(void)
{
	m_v3Position = vector3();
	m_qOrientation = quaternion();
	m_v3Scale = vector3();

	m_v3Velocity = vector3();
	m_v3Acceleration = vector3();

	m_fMass = 1.0f;
	m_fMaxAcc = 10.0f;

	m_sName = "";

	m_pColliderManager = MyBOManager::GetInstance();
	m_pMeshManager = MeshManagerSingleton::GetInstance();
}
void MyEntityClass::Swap(MyEntityClass& other)
{
	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_qOrientation, other.m_qOrientation);
	std::swap(m_v3Scale, other.m_v3Scale);

	std::swap(m_v3Velocity, other.m_v3Velocity);
	std::swap(m_v3Acceleration, other.m_v3Acceleration);

	std::swap(m_fMaxAcc, other.m_fMaxAcc);

	std::swap(m_pColliderManager, other.m_pColliderManager);
	std::swap(m_pMeshManager, other.m_pMeshManager);

	std::swap(m_sName, other.m_sName);
}
void MyEntityClass::Release(void)
{
}

MyEntityClass::MyEntityClass(String a_sName)
{
	Init();
	m_sName = a_sName;
	std::vector<vector3> list = m_pMeshManager->GetVertexList(m_sName);
	m_pColliderManager->AddObject(list, m_sName);
}

MyEntityClass::MyEntityClass(MyEntityClass const& other)
{
	m_v3Position = other.m_v3Position;
	m_qOrientation = other.m_qOrientation;
	m_v3Scale = other.m_v3Scale;

	m_v3Velocity = other.m_v3Velocity;
	m_v3Acceleration = other.m_v3Acceleration;

	m_fMaxAcc = other.m_fMaxAcc;
	m_sName = other.m_sName;

	m_pColliderManager = other.m_pColliderManager;
	m_pMeshManager = other.m_pMeshManager;
}

MyEntityClass& MyEntityClass::operator=(MyEntityClass const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyEntityClass temp(other);
		Swap(temp);
	}
	return *this;
}

MyEntityClass::~MyEntityClass()
{
}
void MyEntityClass::SetPosition(vector3 a_v3Position){ m_v3Position = a_v3Position; }
void MyEntityClass::SetVelocity(vector3 a_v3Velocity){ m_v3Velocity = a_v3Velocity; }
void MyEntityClass::SetMass(float a_fMass){ m_fMass = a_fMass; }

void MyEntityClass::Update(void)
{
	m_v3Position = m_v3Position + (m_v3Velocity * m_fMass);
	matrix4 m4ToWorld = glm::translate(m_v3Position);
	m_pMeshManager->AddInstanceToRenderList(m_sName);
	m_pMeshManager->SetModelMatrix(m4ToWorld, m_sName);
	//int nIndex = m_pColliderManager->GetIndex(m_sName);
	m_pColliderManager->DisplayReAlligned(m_sName);
	m_pColliderManager->SetModelMatrix(m4ToWorld, m_sName);
}