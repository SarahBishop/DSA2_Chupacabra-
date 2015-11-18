#include "CanyonSegment.h"

CanyonSegment::CanyonSegment(vector3 v3Pos, vector3 v3Col, float zLength_)
{
	v3Position = v3Pos;
	v3Color = v3Col;
	zLength = zLength_;
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
}

void CanyonSegment::Render()
{
	// draw planes
	m_pMeshMngr->AddPlaneToQueue(glm::translate(v3Position + vector3(0.0f, -1.0f, 0.0f)) * glm::scale(vector3(10.0f, 10.0f, zLength)) * glm::rotate(90.0f, vector3(1.0f, 0.0f, 0.0f)), v3Color); // floor
	m_pMeshMngr->AddPlaneToQueue(glm::translate(v3Position + vector3(5.0f, 4.0f, 0.0f)) * glm::scale(vector3(10.0f, 10.0f, zLength)) * glm::rotate(90.0f, vector3(0.0f, 1.0f, 0.0f)), v3Color); // right wall
	m_pMeshMngr->AddPlaneToQueue(glm::translate(v3Position + vector3(-5.0f, 4.0f, 0.0f)) * glm::scale(vector3(10.0f, 10.0f, zLength)) * glm::rotate(90.0f, vector3(0.0f, 1.0f, 0.0f)), v3Color); // left wall
}
CanyonSegment::~CanyonSegment()
{

}