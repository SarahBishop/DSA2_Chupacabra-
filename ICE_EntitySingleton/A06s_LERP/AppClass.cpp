#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	m_lPositions.push_back(vector3(-4.0f, -2.0f, 5.0f));
	m_lPositions.push_back(vector3(1.0f, -2.0f, 5.0f));

	m_lPositions.push_back(vector3(-3.0f, -1.0f, 3.0f));
	m_lPositions.push_back(vector3(2.0f, -1.0f, 3.0f));

	m_lPositions.push_back(vector3(-2.0f, 0.0f, 0.0f));
	m_lPositions.push_back(vector3(3.0f, 0.0f, 0.0f));

	m_lPositions.push_back(vector3(-1.0f, 1.0f, -3.0f));
	m_lPositions.push_back(vector3(4.0f, 1.0f, -3.0f));

	m_lPositions.push_back(vector3(0.0f, 2.0f, -5.0f));
	m_lPositions.push_back(vector3(5.0f, 2.0f, -5.0f));

	m_lPositions.push_back(vector3(1.0f, 3.0f, -5.0f));

	fDuration = 1.0f;
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

	//Call the arcball method
	ArcBall();

	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock();

	//cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fTimeSpan;

	static int nIndex = 0;

	if (fRunTime > fDuration)
	{
		fRunTime = 0.0f;
		nIndex++;
		if (nIndex == static_cast<int>(m_lPositions.size()))
		{
			nIndex = 0;
		}
	}

	vector3 v3Vector1;
	vector3 v3Vector2;
	if (nIndex >= static_cast<int>(m_lPositions.size()) - 1)
	{
		v3Vector1 = m_lPositions[static_cast<int>(m_lPositions.size()) - 1];
		v3Vector2 = m_lPositions[0];
	}
	else
	{
		v3Vector1 = m_lPositions[nIndex];
		v3Vector2 = m_lPositions[nIndex + 1];
	}

	float fPercent = MapValue(static_cast<float>(fRunTime), 0.0f, fDuration, 0.0f, 1.0f);
	vector3 v3Position = glm::lerp(v3Vector1, v3Vector2, fPercent);
	m_pMeshMngr->SetModelMatrix(glm::translate(v3Position), "WallEye");

	for (int i = 0; i < static_cast<int>(m_lPositions.size()); i++)
	{
		m_pMeshMngr->AddSphereToQueue(glm::translate(m_lPositions[i]) * glm::scale(vector3(0.1f)), RERED, SOLID);
	}

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("\rfTimeSpan: %.3f, fRunSpan: %.3f, fDuration: %.3f                 ", fTimeSpan, fRunTime, fDuration);
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("nIndex: ");
	m_pMeshMngr->PrintLine(std::to_string(nIndex));

	m_pMeshMngr->Print("fTimeSpan: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimeSpan));

	m_pMeshMngr->Print("fRunSpan: ");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("fDuration: ");
	m_pMeshMngr->PrintLine(std::to_string(fDuration));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
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

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}