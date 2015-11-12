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