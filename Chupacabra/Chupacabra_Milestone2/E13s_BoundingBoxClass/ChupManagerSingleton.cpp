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
	//code for rendering multiple chups with one model
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	//carlos
	carlosInstance = Carlos::GetInstance();

	// full chup with legs for height reference
	m_pMeshMngr->LoadModel("ChupStuff\\Chup.obj", "ChupacabraFull");
	srand(time(NULL));

	m_pMeshMngr->LoadModel("ChupStuff\\ChupTorso.obj", "Chupacabra");
	m_pMeshMngr->LoadModel("ChupStuff\\ChupLegs.obj", "ChupacabraFrontLegs");
	m_pMeshMngr->LoadModel("ChupStuff\\ChupLegs.obj", "ChupacabraBackLegs");

}
void ChupManagerSingleton::GenerateChupacabras(uint numOfChupas, bool isSphere)
{
	// get the number of chups
	int existingNumChups = chups.size();

	for (int i = 0; i < numOfChupas; i++)
	{
		//I added that -1.0f to the spawn point to try to get the chups closer to the center of the screen
		//--Sarah 
		//std::cout << m_pMeshMngr->GetInstanceByIndex(3 * i + 1)->GetName() << " " << m_pMeshMngr->GetInstanceByIndex(3 * i + 2)->GetName() << " " << m_pMeshMngr->GetInstanceByIndex(3 * i + 3)->GetName();
		// create a chupa with a unique mesh ID
		// the mesh ID is i*3+1 because it loads one full and then three of each torso, front, and back legs
		chups.push_back(
			Chupacabra(
			vector3((i * -2.0f), (i * -4.0f), -36.0f),
			"Chupacabra",
			"ChupacabraFrontLegs",
			"ChupacabraBackLegs"
			)
			);
		chups[existingNumChups + i].INDEX = existingNumChups + i;
		ResetChup(&chups[i]);
		chups[existingNumChups + i].myBO = new MyBoundingObjectClass(m_pMeshMngr->GetVertexList("ChupacabraFull"), isSphere);

		// push new vector<int> to colliding indices vector
		std::vector<int> lVector;
		m_llCollidingIndices.push_back(lVector);

	}
}
void ChupManagerSingleton::ClearIndices()
{
	// clear collision list
	for (uint nObject = 0; nObject < m_llCollidingIndices.size(); nObject++)
	{
		m_llCollidingIndices[nObject].clear();
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
		// wall height
		if (chups[i].position.y < 10.f) {


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
		}
		// floor
		if (chups[i].position.y < -1.0f + chups[i].myBO->fRadius)
		{
			chups[i].position.y = -1.0f + chups[i].myBO->fRadius;
			// chasing
			if (chups[i].state == chups[i].CHASING) {
				chups[i].velocity.y *= -0.8f;
			}
			// bouncing
			if (chups[i].state == chups[i].BOUNCING)
			{
				chups[i].velocity.y *= -1.0f;
				chups[i].velocity.z += -0.1f;
			}
			// spawning
			if (chups[i].state == chups[i].SPAWNING) {
				// the fisrt time the chup hits the ground
				chups[i].velocity.y = -0.4f;// / chups[i].velocity.y;
				// stop lightning fast sideways movement
				chups[i].velocity.x = 0.f;
				// chase player
				chups[i].state = chups[i].CHASING;
			}

		}
		// front wall/camera
		//if (chups[i].position.z > chups[i].myBO->fRadius) // 13 is segmentZLength + cameraDepth from CanyonManager.cpp
		if (chups[i].position.z > 10.0f)
		{
			//chups[i].position.z = chups[i].myBO->fRadius;
			//std::cout << " GAME OVER ";
			ResetChup(&chups[i]);
			//chups[i].velocity = vector3(2.0f - rand(), 0.0f, 0.02f); // reset velocity
			//chups[i].velocity.z *= -1.0f; // reverse
		}
	}

	// check collision
	//CheckCollisions();
	ResolveAllCollisions();

	SpawnNewChups(scaledDeltaTime);
	RecycleChups();
}

void ChupManagerSingleton::ResolveAllCollisions() {
	std::cout << " <resolve all> " << std::endl;

	// Handle other chups
	for (int i = 0; i < chups.size(); i++)
	{
		if (m_llCollidingIndices[i].size() > 0)
		{
			for (int j = 0; j < m_llCollidingIndices[i].size(); j++)
			{
				chups[i].velocity += ResolveCollisions(i, m_llCollidingIndices[i][j]);
				

			}
			// find velocity magnitude
			float velMag = (chups[i].velocity.x * chups[i].velocity.x) + (chups[i].velocity.y * chups[i].velocity.y) + (chups[i].velocity.z * chups[i].velocity.z);
			if (velMag >(maxVel * maxVel))
			{
				// normalize velocity
				chups[i].velocity = chups[i].velocity / velMag;

				// multiply by maxVel
				chups[i].velocity = chups[i].velocity * maxVel;
			}
		}
	}

	// Handle Projectiles
	std::vector<Projectile>& projectiles = carlosInstance->projectiles;
	for (int i = 0; i < projectiles.size(); i++)
	{
		for (int j = 0; j < chups.size(); j++)
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
					//std::cout << " chup " << j << " hit ";

					if (chups[j].state != chups[j].BOUNCING) {
						carlosInstance->score += 100;
						chups[j].state = chups[j].BOUNCING;
					}

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

void ChupManagerSingleton::ResetChup(Chupacabra* chup) {
	if (rand() % 2 > 0) {
		chup->position = vector3(6, 20 + rand() % 10, -40 - rand() % 10);//vector3(-2.0f, 10.0f, -30.f);
		chup->velocity = vector3(-0.2, 0, 0.2);
	}
	else {
		chup->position = vector3(-6, 20 + rand() % 10, -40 - rand() % 10);//vector3(-2.0f, 10.0f, -30.f);
		chup->velocity = vector3(0.2, 0, 0.2);
	}

	//std::cout << " " << chup->position.z;
	chup->state = chup->SPAWNING;
}

void ChupManagerSingleton::SpawnNewChups(float scaledDeltaTime) {
	if (chups.size() < 100) {
		chupSpawnTimer += scaledDeltaTime;
		// scaled time is approx 1.0 per frame, so 700 = 700 frames. NOT 700ms.
		if (chupSpawnTimer > 500) {
			chupSpawnTimer -= 500;
			GenerateChupacabras(1, true);
			ResetChup(&chups[chups.size() - 1]);
		}
	}
}
void ChupManagerSingleton::RecycleChups() {
	int recycle = -1;
	for (int i = 0; i < chups.size(); i++) {
		if (chups[i].position.z < -70) {
			//std::cout << " " << i << " out of bounds: " << chups[i].position.z << ". Recycling... ";
			recycle = i;
			break;
		}
	}
	if (recycle > -1) {
		ResetChup(&chups[recycle]);
	}
}
void ChupManagerSingleton::Render()
{
	for (int i = 0; i < chups.size(); i++)
	{
		chups.at(i).Render();
	}
}
void ChupManagerSingleton::CheckCollisions()
{
	// have chups collide off of each other

	for (int i = 0; i < chups.size() - 1; i++)
	{
		for (int j = i + 1; j < chups.size(); j++)
		{
			// find v3 distance between chupas
			v3Distance = chups[j].position - chups[i].position;

			// find magnitude of distance
			fDistanceMag = ((v3Distance.x * v3Distance.x) + (v3Distance.y * v3Distance.y) + (v3Distance.z * v3Distance.z));

			// radius squared
			fRadiusSquared = (chups[i].myBO->fRadius + chups[j].myBO->fRadius) * (chups[i].myBO->fRadius + chups[j].myBO->fRadius);

			// velocity magnitude
			chups[i].fVelMag = (chups[i].velocity.x * chups[i].velocity.x) + (chups[i].velocity.y * chups[i].velocity.y) + (chups[i].velocity.z * chups[i].velocity.z);
			chups[j].fVelMag = (chups[j].velocity.x * chups[j].velocity.x) + (chups[j].velocity.y * chups[j].velocity.y) + (chups[j].velocity.z * chups[j].velocity.z);

			// make sure it is not checking itself
			if (chups[i].position != chups[j].position && chups[i].velocity != chups[j].velocity)
			{
				// if the distance between them is less than the sum of radii, then there is a collision
				if (fDistanceMag < fRadiusSquared)
				{
					
					// add colliding object to the other's colliding indices list
					bool containsJ = false;
					for (int a = 0; a < m_llCollidingIndices[i].size(); a++)
					{
						if (m_llCollidingIndices[i][a] == j) containsJ = true;
					}
					if (!containsJ) {
						m_llCollidingIndices[i].push_back(j);
					}

					bool containsI = false;
					for (int a = 0; a < m_llCollidingIndices[j].size(); a++)
					{
						if (m_llCollidingIndices[j][a] == i) containsI = true;
					}
					if (!containsI) {
						m_llCollidingIndices[j].push_back(i);
					}
				}
			}
		}
	}

}
void ChupManagerSingleton::CheckCollisions(MyOctant* node)
{
	// have chups collide off of each other
	if (node->objectsInNode.size() <= 1 || chups.size() <= 1) return;
	for (int n = 0; n < node->objectsInNode.size() - 1; n++)
	{
		for (int m = n + 1; m < node->objectsInNode.size(); m++)
		{
			int i = node->objectsInNode[n]->INDEX;
			int j = node->objectsInNode[m]->INDEX;

			// find v3 distance between chupas
			v3Distance = chups[j].position - chups[i].position;

			// find magnitude of distance
			fDistanceMag = ((v3Distance.x * v3Distance.x) + (v3Distance.y * v3Distance.y) + (v3Distance.z * v3Distance.z));

			// radius squared
			fRadiusSquared = (chups[i].myBO->fRadius + chups[j].myBO->fRadius) * (chups[i].myBO->fRadius + chups[j].myBO->fRadius);

			// velocity magnitude
			chups[i].fVelMag = (chups[i].velocity.x * chups[i].velocity.x) + (chups[i].velocity.y * chups[i].velocity.y) + (chups[i].velocity.z * chups[i].velocity.z);
			chups[j].fVelMag = (chups[j].velocity.x * chups[j].velocity.x) + (chups[j].velocity.y * chups[j].velocity.y) + (chups[j].velocity.z * chups[j].velocity.z);

			// make sure it is not checking itself
			if (chups[i].position != chups[j].position && chups[i].velocity != chups[j].velocity)
			{
				// if the distance between them is less than the sum of radii, then there is a collision
				if (fDistanceMag < fRadiusSquared)
				{					
					// add colliding object to the other's colliding indices list
					bool containsJ = false;
					for (int a = 0; a < m_llCollidingIndices[i].size(); a++)
					{
						if (m_llCollidingIndices[i][a] == j) containsJ = true;
					}
					if (!containsJ) {
						m_llCollidingIndices[i].push_back(j);
					}

					bool containsI = false;
					for (int a = 0; a < m_llCollidingIndices[j].size(); a++)
					{
						if (m_llCollidingIndices[j][a] == i) containsI = true;
					}
					if (!containsI) {
						m_llCollidingIndices[j].push_back(i);
					}
				}
			}
		}
	}
}
vector3 ChupManagerSingleton::ResolveCollisions(int currentChup, int index)
{
	// recalculate variables
	// find v3 distance between chupas
	if (currentChup == index) return vector3(0.f);
	std::cout << " collision " << currentChup << " x " << index;
	v3Distance = chups[index].position - chups[currentChup].position;
	// find magnitude of distance
	fDistanceMag = ((v3Distance.x * v3Distance.x) + (v3Distance.y * v3Distance.y) + (v3Distance.z * v3Distance.z));
	// radius squared
	fRadiusSquared = (chups[currentChup].myBO->fRadius + chups[index].myBO->fRadius) * (chups[currentChup].myBO->fRadius + chups[index].myBO->fRadius);


	// normalize fDistance vector
	normalizedV3 = v3Distance / (sqrt(fDistanceMag));

	// pop the chups outside of each other to prevent clipping
	if (fDistanceMag < fRadiusSquared / 1.75f)
	{
		vector3 v3UnClipChups(normalizedV3 * ((chups[currentChup].myBO->fRadius + chups[index].myBO->fRadius)));// +chups[currentChup].fVelMag + chups[index].fVelMag - fDistanceMag));
		chups[currentChup].position -= v3UnClipChups;
	}

	// initial velocity
	// project chup's velocity onto normalized distance vector

	// floats to hold size of vel mag
	float fVel1 = glm::dot(chups[currentChup].velocity, normalizedV3);
	float fVel2 = glm::dot(chups[index].velocity, normalizedV3);

	// limit acceleration
	if (fVel1 > chups[currentChup].fMaxAccel) fVel1 = chups[currentChup].fMaxAccel;
	if (fVel1 < chups[currentChup].fMaxAccel * -1.0f) fVel1 = chups[currentChup].fMaxAccel * -1.0f;
	if (fVel2 > chups[index].fMaxAccel) fVel2 = chups[index].fMaxAccel;
	if (fVel2 < chups[index].fMaxAccel * -1.0f) fVel2 = chups[index].fMaxAccel * -1.0f;

	// create intial velocity vector
	glm::vec3 u1 = fVel1 * normalizedV3;
	glm::vec3 u2 = fVel2 * normalizedV3;

	// find the final velocity  v1,v2:final  u1,u2:initial
	// v1 = (m1u1 + m2u2 + m2u2 - m2u1) / m1 + m2
	// v2 = (m1u1 + m2u2 + m1u1 - m1u2) / m1 + m2
	glm::vec3 v1 = ((chups[currentChup].fMass * u1) + (chups[index].fMass * u2) + (chups[index].fMass * u2) - (chups[index].fMass * u1)) / (chups[currentChup].fMass + chups[index].fMass);//((2.0f * chups[currentChup].fMass * chups[index].velocity) + (chups[currentChup].fMass * chups[currentChup].velocity) - (chups[index].fMass * chups[currentChup].velocity)) / (chups[currentChup].fMass + chups[index].fMass);
	glm::vec3 v2 = ((chups[currentChup].fMass * u1) + (chups[index].fMass * u2) + (chups[currentChup].fMass * u1) - (chups[currentChup].fMass * u2)) / (chups[currentChup].fMass + chups[index].fMass);//((2.0f * chups[index].fMass * chups[currentChup].velocity) + (chups[index].fMass * chups[index].velocity) - (chups[currentChup].fMass * chups[index].velocity)) / (chups[index].fMass + chups[currentChup].fMass);

	// vector perpendicular to distance vector
	glm::vec3 w1 = chups[currentChup].velocity - u1;
	glm::vec3 w2 = chups[index].velocity - u2;

	// set ball's velocity to final velocity + perpedicular vector for a more natural collision 
	vector3 changedVel = v1 + w1;
	return changedVel;
	//chups[currentChup].velocity = v1 + w1;
	//chups[index].velocity = v2 + w2;
}