#include "BoundingObjectManager.h"

BoundingObjectManager* BoundingObjectManager::instance;

BoundingObjectManager::BoundingObjectManager()
{
	instance = nullptr; 
}

BoundingObjectManager* BoundingObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BoundingObjectManager();
	}
	return instance;
}

void BoundingObjectManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}