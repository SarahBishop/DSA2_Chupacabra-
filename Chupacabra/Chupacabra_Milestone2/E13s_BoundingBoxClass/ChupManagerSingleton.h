#ifndef _CHUP_MANAGER_SINGLETON_
#define _CHUP_MANAGER_SINGLETON_

#include "Chupacabra.h"
#include <vector>

class ChupManagerSingleton{

	static ChupManagerSingleton* instance;
	
public: 
	static ChupManagerSingleton* GetInstance(); //gotta make a singleton
	//hold those chups
	std::vector<Chupacabra> chups; 

	//TODO
	//put all other functionality of the manager here
	MeshManagerSingleton* m_pMeshMngr; // for rendering multiple chups with one model

	// update Chupacabras
	void Update();
	void GenerateChupacabras(uint numOfChups, bool isSphere);
	void Render();


private:
	//dat private constructor
	ChupManagerSingleton(); 
};

#endif