#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Chupacabra"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Chupacabra");
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Chupacabra2");

	//m_pBB1 = new MyBoundingObjectClass(m_pMeshMngr->GetVertexList("Chupacabra"), true);
	//m_pBB2 = new MyBoundingObjectClass(m_pMeshMngr->GetVertexList("Chupacabra2"), true);

	// initiate singleton
	//BoundingObjectManager* instance = BoundingObjectManager::GetInstance();
	instance = BoundingObjectManager::GetInstance(); 
	chupManager = ChupManagerSingleton::GetInstance(); 
	instance->CreateBoundingObj(m_pMeshMngr->GetVertexList("Chupacabra"), true);
	instance->CreateBoundingObj(m_pMeshMngr->GetVertexList("Chupacabra2"), true);

	canyonManager = new CanyonManager();
	canyonManager->GenerateCanyon(35);
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	// update canyon
	canyonManager->Update();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Chupacabra");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Chupacabra2");

	//m_pBB1->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Steve"));
	//m_pBB2->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Creeper"));
	instance->objects[0]->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Chupacabra"));
	instance->objects[1]->SetModelMatrix(m_pMeshMngr->GetModelMatrix("Chupacabra2"));
	

	//Add a representation of the Spheres to the render list
	vector3 v3Color = REWHITE;
	//if (instance->objects[0]->IsColliding(instance->objects[1]))
	//	v3Color = RERED;
	for (int i = 0; i < instance->objects.size(); i++)
		instance->objects[i]->SetColor(REWHITE); 
	instance->CheckCollisions(); 

	//m_pMeshMngr->AddCubeToQueue(glm::translate(m_pBB1->GetCenterGlobal()) * glm::scale(m_pBB1->GetHalfWidthG() * 2.0f), v3Color, WIRE);
	//m_pMeshMngr->AddCubeToQueue(glm::translate(m_pBB2->GetCenterGlobal()) * glm::scale(m_pBB2->GetHalfWidthG() * 2.0f), v3Color, WIRE);

	//m_pMeshMngr->AddCubeToQueue(m_pBB1->GetModelMatrix() * glm::translate(IDENTITY_M4, m_pBB1->GetCenterLocal()) * glm::scale(m_pBB1->GetHalfWidth() * 2.0f), v3Color, WIRE);
	//m_pMeshMngr->AddCubeToQueue(m_pBB2->GetModelMatrix() * glm::translate(IDENTITY_M4, m_pBB2->GetCenterLocal()) * glm::scale(m_pBB2->GetHalfWidth() * 2.0f), v3Color, WIRE);

	//m_pMeshMngr->AddSphereToQueue(m_pBB1->GetModelMatrix() * glm::translate(IDENTITY_M4, m_pBB1->GetCenterLocal()) * glm::scale(glm::vec3(2.0f * m_pBB1->fRadiusG)), v3Color, WIRE);
	//m_pMeshMngr->AddSphereToQueue(m_pBB2->GetModelMatrix() * glm::translate(IDENTITY_M4, m_pBB2->GetCenterLocal()) * glm::scale(glm::vec3(2.0f * m_pBB2->fRadiusG)), v3Color, WIRE);

	for (int i = 0; i < instance->objects.size(); i++)
	{
		if (instance->aabbVisible)
			//m_pMeshMngr->AddCubeToQueue(glm::translate(instance->objects[i]->GetCenterGlobal()) * glm::scale(instance->objects[i]->GetHalfWidthG() * 2.0f), instance->objects[i]->v3Color, WIRE);
		if (instance->isVisible && instance->objects[i]->visible)
		{
			//m_pMeshMngr->AddCubeToQueue(instance->objects[i]->GetModelMatrix() * glm::translate(IDENTITY_M4, instance->objects[i]->GetCenterLocal()) * glm::scale(instance->objects[i]->GetHalfWidth() * 2.0f), instance->objects[i]->v3Color, WIRE);
			//m_pMeshMngr->AddSphereToQueue(instance->objects[i]->GetModelMatrix() * glm::translate(IDENTITY_M4, instance->objects[i]->GetCenterLocal()) * glm::scale(glm::vec3(2.0f * instance->objects[i]->fRadiusG)), instance->objects[i]->v3Color, WIRE);
			//instance->objects[0]->m_pSphere->RenderWire(glm::translate(matrix4(1.0f), instance->objects[0]->center)),;
			m_pMeshMngr->AddSphereToQueue(glm::translate(instance->objects[i]->GetCenterGlobal()) * glm::scale(vector3(instance->objects[i]->fRadius)), REWHITE, WIRE);
		}
	}

	// draw planes
	//m_pMeshMngr->AddPlaneToQueue(glm::translate(vector3(0.0f, -1.0f, 0.0f)) * glm::rotate(90.0f, vector3(1.0f, 0.0f, 0.0f)) * glm::scale(vector3(10.0f, 10.0f, 25.0f)), REWHITE); // floor
	//m_pMeshMngr->AddPlaneToQueue(glm::translate(vector3(5.0f, 4.0f, 0.0f)) * glm::rotate(90.0f, vector3(0.0f, 1.0f, 0.0f)) * glm::scale(vector3(10.0f, 10.0f, 25.0f)), REWHITE);
	//m_pMeshMngr->AddPlaneToQueue(glm::translate(vector3(-5.0f, 4.0f, 0.0f)) * glm::rotate(90.0f, vector3(0.0f, 1.0f, 0.0f)) * glm::scale(vector3(10.0f, 10.0f, 25.0f)), REWHITE);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	////Indicate the FPS
	//int nFPS = m_pSystem->GetFPS();
	////print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	////Print info on the screen
	//m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	//m_pMeshMngr->Print("FPS:");
	//m_pMeshMngr->PrintLine(std::to_string(nFPS), RERED);

	//// print bools
	//m_pMeshMngr->Print("BO Visible (V) : ");
	//m_pMeshMngr->PrintLine(std::to_string(instance->isVisible), RERED);
	//m_pMeshMngr->Print("AABB Visible (B) : ");
	//m_pMeshMngr->PrintLine(std::to_string(instance->aabbVisible), RERED);
	//m_pMeshMngr->Print("Collision Resolution (R) : ");
	//m_pMeshMngr->PrintLine(std::to_string(instance->canCollide), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		//m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	canyonManager->Render(); // render canyon

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	SafeDelete(m_pBB1);
	SafeDelete(m_pBB2);
	SafeDelete(instance);
	SafeDelete(canyonManager);
}