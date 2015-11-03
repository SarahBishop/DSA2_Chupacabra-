#include "MyBoundingObjectClass.h"

MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> listOfVertex)
{
	// sphere attributes
	myList = listOfVertex;
	fRadius = 1.0f;
	nSubdivisions = 6;
	isColliding = false;
	v3Color = vector3(0.0f, 1.0f, 0.0f);
	m_pSphere = new PrimitiveClass();
	m_pSphere->GenerateSphere(fRadius, nSubdivisions, v3Color);

	// box attributes
	m_m4ToWorld = IDENTITY_M4;
	m_v3Center = vector3(0.0f);
	m_v3Min = vector3(0.0f);
	m_v3Max = vector3(0.0f);
	m_v3HalfWidth = vector3(0.0f);
	m_v3CenterG = vector3(0.0f);
	m_v3MinG = vector3(0.0f);
	m_v3MaxG = vector3(0.0f);
	m_v3HalfWidthG = vector3(0.0f);
	
	//Count the points of the incoming list
	uint nVertexCount = listOfVertex.size();

	//If there are none just return, we have no information to create the BS from
	if (nVertexCount == 0)
		return;

	//Max and min as the first vector of the list
	m_v3Max = m_v3Min = listOfVertex[0];

	//Get the max and min out of the list
	for (uint nVertex = 1; nVertex < nVertexCount; nVertex++)
	{
		if (m_v3Min.x > listOfVertex[nVertex].x) //If min is larger than current
			m_v3Min.x = listOfVertex[nVertex].x;
		else if (m_v3Max.x < listOfVertex[nVertex].x)//if max is smaller than current
			m_v3Max.x = listOfVertex[nVertex].x;

		if (m_v3Min.y > listOfVertex[nVertex].y) //If min is larger than current
			m_v3Min.y = listOfVertex[nVertex].y;
		else if (m_v3Max.y < listOfVertex[nVertex].y)//if max is smaller than current
			m_v3Max.y = listOfVertex[nVertex].y;

		if (m_v3Min.z > listOfVertex[nVertex].z) //If min is larger than current
			m_v3Min.z = listOfVertex[nVertex].z;
		else if (m_v3Max.z < listOfVertex[nVertex].z)//if max is smaller than current
			m_v3Max.z = listOfVertex[nVertex].z;
	}

	//with the max and the min we calculate the center
	m_v3Center = (m_v3Min + m_v3Max) / 2.0f;

	// rad
	fRadius = glm::length(m_v3Center - m_v3Max);

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth.x = glm::distance(vector3(m_v3Min.x, 0.0f, 0.0f), vector3(m_v3Max.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidth.y = glm::distance(vector3(0.0f, m_v3Min.y, 0.0f), vector3(0.0f, m_v3Max.y, 0.0f)) / 2.0f;
	m_v3HalfWidth.z = glm::distance(vector3(0.0f, 0.0f, m_v3Min.z), vector3(0.0f, 0.0f, m_v3Max.z)) / 2.0f;

}

MyBoundingObjectClass::MyBoundingObjectClass(MyBoundingObjectClass const& other) {
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;
}

MyBoundingObjectClass& MyBoundingObjectClass::operator = (MyBoundingObjectClass const& other) {
	myList = other.myList;
	m_m4ToWorld = other.m_m4ToWorld;

	m_v3Center = other.m_v3Center;
	m_v3Min = other.m_v3Min;
	m_v3Max = other.m_v3Max;

	m_v3CenterG = other.m_v3CenterG;
	m_v3MinG = other.m_v3MinG;
	m_v3MaxG = other.m_v3MaxG;

	m_v3HalfWidth = other.m_v3HalfWidth;
	m_v3HalfWidthG = other.m_v3HalfWidthG;
	return *this;
}

// check sphere colliders
bool MyBoundingObjectClass::IsSphereColliding(MyBoundingObjectClass* pOther) {
	float fSumofRadii = fRadius + pOther->fRadius;
	float fvecToCenter = abs(glm::distance(m_v3Center, pOther->m_v3Center));
	if (fSumofRadii > fvecToCenter)
	{
		return true;
	}
	return false;
}

bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass* pOther)
{
	// check for sphere collision
	// magnitude
	vector3 distance = pOther->center - center;
	float magnitude = distance.x * distance.x + distance.y * distance.y + distance.z * distance.z;
	magnitude = sqrt(magnitude);

	if ((fRadius + pOther->fRadius) > (magnitude))
	{ 
		isColliding = true;
		//return isColliding;
	}
	else
	{
		isColliding = false;
		return isColliding; // exits if no collision
	}

	// if you reach this point, check for AABB collision

	//Get all vectors in global space
	vector3 v3Min = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	vector3 v3Max = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	vector3 v3MinO = vector3(pOther->m_m4ToWorld * vector4(pOther->m_v3Min, 1.0f));
	vector3 v3MaxO = vector3(pOther->m_m4ToWorld * vector4(pOther->m_v3Max, 1.0f));

	/*
	Are they colliding?
	For boxes we will assume they are colliding, unless at least one of the following conditions is not met
	*/
	bool bColliding = true;

	//Check for X
	if (m_v3MaxG.x < pOther->m_v3MinG.x)
		bColliding = false;
	if (m_v3MinG.x > pOther->m_v3MaxG.x)
		bColliding = false;

	//Check for Y
	if (m_v3MaxG.y < pOther->m_v3MinG.y)
		bColliding = false;
	if (m_v3MinG.y > pOther->m_v3MaxG.y)
		bColliding = false;

	//Check for Z
	if (m_v3MaxG.z < pOther->m_v3MinG.z)
		bColliding = false;
	if (m_v3MinG.z > pOther->m_v3MaxG.z)
		bColliding = false;

	isColliding = bColliding;

	return bColliding;

}

void MyBoundingObjectClass::ToggleVisible() {
	// nah
}

void MyBoundingObjectClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	m_m4ToWorld = a_m4ToWorld;
}
matrix4 MyBoundingObjectClass::GetModelMatrix(void)
{
	return m_m4ToWorld;
}

vector3 MyBoundingObjectClass::GetCenterLocal(void)
{
	return m_v3Center;
}
vector3 MyBoundingObjectClass::GetCenterGlobal(void)
{
	return vector3(m_m4ToWorld * vector4(m_v3Center, 1.0f));
}
vector3 MyBoundingObjectClass::GetHalfWidth(void)
{
	return m_v3HalfWidth;
}
vector3 MyBoundingObjectClass::GetHalfWidthG(void){ return m_v3HalfWidthG; }

void MyBoundingObjectClass::SetColor(vector3 a_v3Color)
{
	v3Color = a_v3Color;
}

MyBoundingObjectClass::~MyBoundingObjectClass(){ Release(); };

void MyBoundingObjectClass::Release(void)
{

}