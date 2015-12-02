#include "ChupManagerSingleton.h"

ChupManagerSingleton* ChupManagerSingleton::instance; 

ChupManagerSingleton* ChupManagerSingleton::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ChupManagerSingleton();
	}
	return instance;
}

ChupManagerSingleton::ChupManagerSingleton()
{
	instance = nullptr; 
}
void ChupManagerSingleton::GenerateChupacabras(uint numOfChupas, bool isSphere)
{
	//code for rendering multiple chups with one model
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	//carlos
	carlosInstance = Carlos::GetInstance();

	for (int i = 0; i < numOfChupas; i++)
	{
		m_pMeshMngr->LoadModel("ChupStuff\\Chup.obj", "Chupacabra");
	}
	
	//m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Chupacabra");
	for (int i = 0; i < numOfChupas; i++)
	{
		//I added that -1.0f to the spawn point to try to get the chups closer to the center of the screen
		//--Sarah 
		chups.push_back(Chupacabra(vector3((i * -2.0f), (i * -4.0f), -36.0f), m_pMeshMngr->GetInstanceByIndex(i)->GetName()));
		chups[i].myBO = new MyBoundingObjectClass(m_pMeshMngr->GetVertexList(m_pMeshMngr->GetNameOfInstanceByIndex(i)), isSphere);
	}
}
void ChupManagerSingleton::Update(float scaledDeltaTime)
{
	// move the chupacabras
	for (int i = 0; i < chups.size(); i++)
	{
		chups[i].Move(scaledDeltaTime);
	}

	// keep chups inside canyon
	for (int i = 0; i < chups.size(); i++)
	{
		// left wall
		if (chups[i].position.x < -5.0f + chups[i].myBO->fRadius) // -5 is the left canyon wall's position
		{
			chups[i].position.x = -5.0f + chups[i].myBO->fRadius;
			chups[i].velocity.x *= -1.0f;
		}
		// right wall
		else if (chups[i].position.x > 5.0f - chups[i].myBO->fRadius)
		{
			chups[i].position.x = 5.0f - chups[i].myBO->fRadius;
			chups[i].velocity.x *= -1.0f;
		}
		// floor
		if (chups[i].position.y < -1.0f + chups[i].myBO->fRadius)
		{
			chups[i].position.y = -1.0f + chups[i].myBO->fRadius;
			chups[i].velocity.y *= -1.0f;
		}
		// front wall/camera
		//if (chups[i].position.z > chups[i].myBO->fRadius) // 13 is segmentZLength + cameraDepth from CanyonManager.cpp
		if (chups[i].position.z > 10.0f)
		{
			//chups[i].position.z = chups[i].myBO->fRadius;
			std::cout << " GAME OVER ";
			chups[i].position.z = -50.0f; // set chup back
			chups[i].position.y = 2.0f;
			//chups[i].velocity = vector3(2.0f - rand(), 0.0f, 0.02f); // reset velocity
			//chups[i].velocity.z *= -1.0f; // reverse
		}
	}

	// have chups collide off of each other
	vector3 v3Distance;
	for (int i = 0; i < chups.size() - 1; i++)
	{
		for (int j = i + 1; j < chups.size(); j++)
		{
			// find v3 distance between chupas
			v3Distance = chups[j].position - chups[i].position;

			// find magnitude of distance
			float fDistanceMag = ((v3Distance.x * v3Distance.x) + (v3Distance.y * v3Distance.y) + (v3Distance.z * v3Distance.z));

			// radius squared
			float fRadiusSquared = (chups[i].myBO->fRadius + chups[j].myBO->fRadius) * (chups[i].myBO->fRadius + chups[j].myBO->fRadius);

			// velocity magnitude
			chups[i].fVelMag = (chups[i].velocity.x * chups[i].velocity.x) + (chups[i].velocity.y * chups[i].velocity.y) + (chups[i].velocity.z * chups[i].velocity.z);
			chups[j].fVelMag = (chups[j].velocity.x * chups[j].velocity.x) + (chups[j].velocity.y * chups[j].velocity.y) + (chups[j].velocity.z * chups[j].velocity.z);

			if (chups[i].position != chups[j].position && chups[i].velocity != chups[j].velocity)
			{
				// if the distance between them is less than the sum of radii, then there is a collision
				if (fDistanceMag < fRadiusSquared)
				{
					// normalize fDistance vector
					glm::vec3 n = v3Distance / (sqrt(fDistanceMag));

					// pop the chups outside of each other to prevent clipping
					if (fDistanceMag < fRadiusSquared/1.75f)
					{
						vector3 v3UnClipChups(n * ((chups[i].myBO->fRadius + chups[j].myBO->fRadius)));// +chups[i].fVelMag + chups[j].fVelMag - fDistanceMag));
						chups[i].position -= v3UnClipChups;
					}
					
					// initial velocity
					// project chup's velocity onto normalized distance vector

					// floats to hold size of vel mag
					float fVel1 = glm::dot(chups[i].velocity, n);
					float fVel2 = glm::dot(chups[j].velocity, n);

					// limit acceleration
					if (fVel1 > chups[i].fMaxAccel) fVel1 = chups[i].fMaxAccel;
					if (fVel1 < chups[i].fMaxAccel * -1.0f) fVel1 = chups[i].fMaxAccel * -1.0f;
					if (fVel2 > chups[j].fMaxAccel) fVel2 = chups[j].fMaxAccel;
					if (fVel2 < chups[j].fMaxAccel * -1.0f) fVel2 = chups[j].fMaxAccel * -1.0f;

					// create intial velocity vector
					glm::vec3 u1 = fVel1 * n;
					glm::vec3 u2 = fVel2 * n;

					// find the final velocity  v1,v2:final  u1,u2:initial
					// v1 = (m1u1 + m2u2 + m2u2 - m2u1) / m1 + m2
					// v2 = (m1u1 + m2u2 + m1u1 - m1u2) / m1 + m2
					glm::vec3 v1 = ((chups[i].fMass * u1) + (chups[j].fMass * u2) + (chups[j].fMass * u2) - (chups[j].fMass * u1)) / (chups[i].fMass + chups[j].fMass);//((2.0f * chups[i].fMass * chups[j].velocity) + (chups[i].fMass * chups[i].velocity) - (chups[j].fMass * chups[i].velocity)) / (chups[i].fMass + chups[j].fMass);
					glm::vec3 v2 = ((chups[i].fMass * u1) + (chups[j].fMass * u2) + (chups[i].fMass * u1) - (chups[i].fMass * u2)) / (chups[i].fMass + chups[j].fMass);//((2.0f * chups[j].fMass * chups[i].velocity) + (chups[j].fMass * chups[j].velocity) - (chups[i].fMass * chups[j].velocity)) / (chups[j].fMass + chups[i].fMass);

					// vector perpendicular to distance vector
					glm::vec3 w1 = chups[i].velocity - u1;
					glm::vec3 w2 = chups[j].velocity - u2;

					// set ball's velocity to final velocity + perpedicular vector for a more natural collision 
					chups[i].velocity = v1 + w1;
					chups[j].velocity = v2 + w2;

					
				}
			}

		}
	}
	// have chups collide off projectiles
	std::vector<Projectile>& projectiles = carlosInstance->projectiles;
	for (int i = 0; i < projectiles.size(); i++)
	{
		for (int j = i + 1; j < chups.size(); j++)
		{
			// find v3 distance between chupas
			v3Distance = chups[j].position - projectiles[i].position;

			// find magnitude of distance
			float fDistanceMag = ((v3Distance.x * v3Distance.x) + (v3Distance.y * v3Distance.y) + (v3Distance.z * v3Distance.z));

			// radius squared
			float fRadiusSquared = (1 + chups[j].myBO->fRadius) * (1 + chups[j].myBO->fRadius);

			// velocity magnitude
			projectiles[i].fVelMag = (projectiles[i].velocity.x * projectiles[i].velocity.x) + (projectiles[i].velocity.y * projectiles[i].velocity.y) + (projectiles[i].velocity.z * projectiles[i].velocity.z);
			chups[j].fVelMag = (chups[j].velocity.x * chups[j].velocity.x) + (chups[j].velocity.y * chups[j].velocity.y) + (chups[j].velocity.z * chups[j].velocity.z);

			if (projectiles[i].position != chups[j].position && projectiles[i].velocity != chups[j].velocity)
			{
				// if the distance between them is less than the sum of radii, then there is a collision
				if (fDistanceMag < fRadiusSquared)
				{
					std::cout << " chup " << j << " hit ";
					// normalize fDistance vector
					glm::vec3 n = v3Distance / (sqrt(fDistanceMag));

					// pop the chups outside of each other to prevent clipping
					if (fDistanceMag < fRadiusSquared / 1.75f)
					{
						vector3 v3UnClipChups(n * ((1 + chups[j].myBO->fRadius)));// +projectiles[i].fVelMag + chups[j].fVelMag - fDistanceMag));
						projectiles[i].position -= v3UnClipChups;
					}

					// initial velocity
					// project chup's velocity onto normalized distance vector

					// floats to hold size of vel mag
					float fVel1 = glm::dot(projectiles[i].velocity, n);
					float fVel2 = glm::dot(chups[j].velocity, n);

					// limit acceleration
					if (fVel1 > projectiles[i].fMaxAccel) fVel1 = projectiles[i].fMaxAccel;
					if (fVel1 < projectiles[i].fMaxAccel * -1.0f) fVel1 = projectiles[i].fMaxAccel * -1.0f;
					if (fVel2 > chups[j].fMaxAccel) fVel2 = chups[j].fMaxAccel;
					if (fVel2 < chups[j].fMaxAccel * -1.0f) fVel2 = chups[j].fMaxAccel * -1.0f;

					// create intial velocity vector
					glm::vec3 u1 = fVel1 * n;
					glm::vec3 u2 = fVel2 * n;

					// find the final velocity  v1,v2:final  u1,u2:initial
					// v1 = (m1u1 + m2u2 + m2u2 - m2u1) / m1 + m2
					// v2 = (m1u1 + m2u2 + m1u1 - m1u2) / m1 + m2
					glm::vec3 v1 = ((projectiles[i].fMass * u1) + (chups[j].fMass * u2) + (chups[j].fMass * u2) - (chups[j].fMass * u1)) / (projectiles[i].fMass + chups[j].fMass);//((2.0f * projectiles[i].fMass * chups[j].velocity) + (projectiles[i].fMass * projectiles[i].velocity) - (chups[j].fMass * projectiles[i].velocity)) / (projectiles[i].fMass + chups[j].fMass);
					glm::vec3 v2 = ((projectiles[i].fMass * u1) + (chups[j].fMass * u2) + (projectiles[i].fMass * u1) - (projectiles[i].fMass * u2)) / (projectiles[i].fMass + chups[j].fMass);//((2.0f * chups[j].fMass * projectiles[i].velocity) + (chups[j].fMass * chups[j].velocity) - (projectiles[i].fMass * chups[j].velocity)) / (chups[j].fMass + projectiles[i].fMass);

					// vector perpendicular to distance vector
					glm::vec3 w1 = projectiles[i].velocity - u1;
					glm::vec3 w2 = chups[j].velocity - u2;

					// set ball's velocity to final velocity + perpedicular vector for a more natural collision 
					projectiles[i].velocity = v1 + w1;
					chups[j].velocity = v2 + w2;


				}
			}

		}
	}
}
void ChupManagerSingleton::Render()
{
	for (int i = 0; i < chups.size(); i++)
	{
		chups.at(i).Render();
	}
}