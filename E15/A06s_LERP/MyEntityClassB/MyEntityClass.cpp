#include "MyEntityClass.h"
//---
void MyEntityClass::Init(void)
{
	//Set initial values
	m_v3Position = vector3();
	m_qOrientation = quaternion();
	m_v3Scale = vector3();

	m_v3Velocity = vector3();
	m_v3Acceleration = vector3();

	m_fMass = 1.0f;
	m_fMaxAcc = 0.1f;

	m_sName = "";

	m_pColliderManager = MyBOManager::GetInstance();
	m_pMeshManager = MeshManagerSingleton::GetInstance();
}
void MyEntityClass::Swap(MyEntityClass& other)
{
	//Swap content between objects
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
	//No pointers allocated yet, it is not the responsability of this object to
	//deallocate the singletons
}
// The rule of 3
MyEntityClass::MyEntityClass(String a_sName)
{
	//Create a new object based on the name
	Init();//initialize members
	m_sName = a_sName;//set the name
	std::vector<vector3> list = m_pMeshManager->GetVertexList(m_sName);//Get the list of verts
	m_pColliderManager->AddObject(list, m_sName);//Construct a Bounding Object
}
MyEntityClass::MyEntityClass(MyEntityClass const& other)
{
	//Copy information from the other object
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
	//if this object is the same as the incoming one there is nothing to do
	if (this != &other)
	{
		Release(); //release the content of this object
		Init(); //Initialize the default values
		MyEntityClass temp(other);//create a temporal object using the incoming one's information
		Swap(temp); //Switch the content of this object and the temporal one
	}
	return *this;
}
// Destructor
MyEntityClass::~MyEntityClass()
{
	Release();//Call deallocators
}
//Accessors
void MyEntityClass::SetPosition(vector3 a_v3Position){ m_v3Position = a_v3Position; }
void MyEntityClass::SetVelocity(vector3 a_v3Velocity){ m_v3Velocity = a_v3Velocity; }
void MyEntityClass::SetAcceleration(vector3 a_v3Acceleration) { m_v3Acceleration = a_v3Acceleration; }
vector3 MyEntityClass::GetAcceleration(void) { return m_v3Acceleration; }
void MyEntityClass::SetMaxAcc(float a_fMaxAcc) { m_fMaxAcc = a_fMaxAcc; }
void MyEntityClass::SetMass(float a_fMass){ m_fMass = a_fMass; }
String MyEntityClass::GetName(void) { return m_sName; }
//---
void MyEntityClass::Update(void)
{
	//Calculate the acceleration based on the mass
	vector3 v3Acceleration = m_v3Acceleration * (1.0f / m_fMass);
	//Limit the acceleration based on the maximum acceleration for the object
	v3Acceleration = glm::clamp(v3Acceleration, -m_fMaxAcc, m_fMaxAcc);
	//Increase the velocity based on the acceleration
	m_v3Velocity = m_v3Velocity + v3Acceleration;
	//Set the position based on the position of this object and the acceleration
	m_v3Position = m_v3Position + m_v3Velocity;
	matrix4 m4ToWorld = glm::translate(m_v3Position);

	//Set the model matrix for the objects
	m_pMeshManager->SetModelMatrix(m4ToWorld, m_sName);
	m_pColliderManager->SetModelMatrix(m4ToWorld, m_sName);

	//Display the objects
	m_pMeshManager->AddInstanceToRenderList(m_sName);
	m_pColliderManager->DisplayReAlligned(m_sName);
}