#ifndef _CHUP_MANAGER_SINGLETON_
#define _CHUP_MANAGER_SINGLETON_

#include "Chupacabra.h"
#include "Carlos.h"
#include <vector>

class ChupManagerSingleton{

	static ChupManagerSingleton* instance;
	float chupSpawnTimer = 0.f;
	
public: 
	static ChupManagerSingleton* GetInstance(); //gotta make a singleton
	//hold those chups
	std::vector<Chupacabra> chups; 

	// keeps track of all the collisions for each chup
	std::vector<std::vector<int>> m_llCollidingIndices;
	vector3 v3Distance;
	float fDistanceMag;
	float fRadiusSquared;
	glm::vec3 normalizedV3;

	float maxVel = 0.1f;
	//TODO
	//put all other functionality of the manager here
	MeshManagerSingleton* m_pMeshMngr; // for rendering multiple chups with one model
	// I know this is awful practice but I'm going to have to do this for now
	Carlos* carlosInstance = nullptr;
	// update Chupacabras
	void Update(float scaledDeltaTime);
	void GenerateChupacabras(uint numOfChups, bool isSphere);
	void Render();
	void SpawnNewChups(float scaledDeltaTime);
	void RecycleChups();
	// set chup to starting position
	void ResetChup(Chupacabra* chup);

	// find out who's colliding
	void CheckCollisions();

	// resolve collisions with all colliding objects
	vector3 ResolveCollisions(int currentChup, int index);


private:
	//dat private constructor
	ChupManagerSingleton(); 
};

#endif