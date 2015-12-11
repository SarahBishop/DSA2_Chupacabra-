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
	gameState = Game; 
	
	//Initialize positions
	//m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	//m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	chupManager = ChupManagerSingleton::GetInstance();


	chupManager->GenerateChupacabras(1, true);

	canyonManager = new CanyonManager();
	canyonManager->GenerateCanyon(35);
	cameraFX = new CameraEffect();
	player = Carlos::GetInstance();

	deltaTime = 0.f;

	// octtree
	m_pRoot = new MyOctant(vector3(0.0f, 0.0f, 0.0f), 20.0f);

	// loop through BO objects to check for their octants
	for (int i = 0; i < chupManager->chups.size(); i++)
	{
		m_pRoot->CheckForBOInOctant(&(chupManager->chups[i]));
	}
	std::cout << m_pRoot->objectsInNode.size();
	// check if there are more than 3 colliding objects in list
	m_pRoot->Subdivide();

	for (int j = 0; j < 8; j++)
	{
		pChild = m_pRoot->GetChild(j);

		pChild->Subdivide();
	}
}
// find the chups in the nodes again
void AppClass::FindChups(MyOctant* node)
{
	//if (node->GetParent()->objectsInNode.size() <= 0) return;
	if (node->GetParent() != nullptr)
	{
		// for each chup
		for (int i = 0; i < chupManager->chups.size(); i++)
		{
			// check for the octant
			node->CheckForBOInOctant(&chupManager->chups[i]);
		}
	}
	/*else
	{
	for (int i = 0; i < chupManager->chups.size(); i++)
	{
	node->CheckForBOInOctant(&(chupManager->chups[i]));
	}
	}*/
}
// performs collision detection in leaf nodes
void AppClass::RecurseSO(MyOctant* node)
{
	if (node->GetChildren() > 0)
	{
		for (int i = 0; i < node->GetChildren(); i++)
		{
			RecurseSO(node->GetChild(i));
		}
	}
	else
	{
		//call collision detection
		chupManager->CheckCollisions(node);
	}
}
void AppClass::Update(void)
{
	if (gameState == Start)
	{
		m_pMeshMngr->Print("Welcome to ", REWHITE); 
		m_pMeshMngr->PrintLine("CHUPACABRA", RERED);
		m_pMeshMngr->PrintLine("", REWHITE);
		m_pMeshMngr->PrintLine("Controls:", REWHITE);
		m_pMeshMngr->PrintLine("-Click to throw golf balls in defense of your goat!", REWHITE);
		m_pMeshMngr->PrintLine("-Press Spacebar to start \'P\' to pause wile in-game", REWHITE);
		m_pMeshMngr->PrintLine("-GET A GOOD SCORE!!!", REWHITE);
	}
	else if (gameState == Game)
	{
		//Update the system's time
		m_pSystem->UpdateTime();

		// std::cout << m_pSystem->LapClock(0) * 64.f; test expected frame-rate
		deltaTime = m_pSystem->LapClock(0);
		scaledDT = (float)(deltaTime * TIME_COEFFICIENT);

		//Update the mesh manager's time without updating for collision detection
		m_pMeshMngr->Update(false);

		//First person camera movement
		if (m_bFPC == true)
			CameraRotation();

		ArcBall();

		// navigate through the octtree
		chupManager->ClearIndices();
		//m_pRoot->ClearList();
		for (int i = 0; i < 8; i++)
		{
			pChild = m_pRoot->GetChild(i);
			//pChild->ClearList();

			for (int j = 0; j < 8; j++)
			{
				pChild = m_pRoot->GetChild(i)->GetChild(j);
				pChild->ClearList();
				// populate list
				FindChups(pChild);
			}
		}

		// check collisions in the now populated structure
		RecurseSO(m_pRoot);

		// update canyon
		canyonManager->Update(scaledDT);

		cameraFX->CameraBob();

		for (int i = 0; i < chupManager->chups.size(); i++)
		{
			chupManager->chups[i].myBO->SetModelMatrix(glm::translate(chupManager->chups[i].position));
		}

		//draw the projectiles 
		for (int i = 0; i < player->projectiles.size(); i++)
		{
			player->projectiles.at(i).Move(scaledDT);
			m_pMeshMngr->AddSphereToQueue(glm::translate(IDENTITY_M4, player->projectiles.at(i).position) * glm::scale(vector3(1.0f, 1.0f, 1.0f)));
			player->projectiles.at(i).bounding->SetModelMatrix(glm::translate(player->projectiles.at(i).position)); //move those bounding objects
		}

		player->Countdown(scaledDT);

		// update chupacabras
		chupManager->Update(scaledDT);

		//Add a representation of the Spheres to the render list
		vector3 v3Color = REWHITE;

		m_pMeshMngr->PrintLine(player->ShowScore(), REWHITE);

		if (starting)
		{
			gameState = Start; 
			starting = false; 
		}
	}
	else if (gameState == Pause)
	{
		m_pMeshMngr->PrintLine("Paused", REWHITE); 
		deltaTime = 0.0f; 
		m_pMeshMngr->Update(false); 
	}


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
	chupManager->Render();
	//m_pRoot->Display();
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
	SafeDelete(m_pBB1);
	SafeDelete(m_pBB2);
	//SafeDelete(instance);
	SafeDelete(canyonManager);
	SafeDelete(chupManager);

	if (m_pRoot != nullptr)
	{
		delete m_pRoot;
		m_pRoot = nullptr;
	}
}
