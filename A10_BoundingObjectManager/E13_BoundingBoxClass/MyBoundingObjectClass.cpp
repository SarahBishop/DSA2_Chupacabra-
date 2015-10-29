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

	//we calculate the distance between all the values of min and max vectors
	m_v3HalfWidth.x = glm::distance(vector3(m_v3Min.x, 0.0f, 0.0f), vector3(m_v3Max.x, 0.0f, 0.0f)) / 2.0f;
	m_v3HalfWidth.y = glm::distance(vector3(0.0f, m_v3Min.y, 0.0f), vector3(0.0f, m_v3Max.y, 0.0f)) / 2.0f;
	m_v3HalfWidth.z = glm::distance(vector3(0.0f, 0.0f, m_v3Min.z), vector3(0.0f, 0.0f, m_v3Max.z)) / 2.0f;

}
bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass* other)
{
	// check for sphere collision
	// magnitude
	vector3 distance = other->center - center;
	float magnitude = distance.x * distance.x + distance.y * distance.y + distance.z * distance.z;
	magnitude = sqrt(magnitude);

	if ((fRadius + other->fRadius) > (magnitude))
	{
		isColliding = true;
		//return isColliding;
	}
	else
	{
		isColliding = false;
		return isColliding;
	}

	// if you reach this point, check for AABB collision


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

void MyBoundingObjectClass::SetColor(vector3 a_v3Color)
{
	v3Color = a_v3Color;
}