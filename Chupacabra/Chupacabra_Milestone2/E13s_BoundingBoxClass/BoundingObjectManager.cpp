#include "BoundingObjectManager.h"

BoundingObjectManager* BoundingObjectManager::instance;


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
void BoundingObjectManager::CreateBoundingObj(std::vector<vector3> a_lVectorList)
{
	objects.push_back(new MyBoundingObjectClass(a_lVectorList)); 
}
void BoundingObjectManager::CreateBoundingObj(std::vector<vector3> a_lVectorList, bool isSphere)
{
	objects.push_back(new MyBoundingObjectClass(a_lVectorList, isSphere));
}

void BoundingObjectManager::ToggleVisibility()
{
	isVisible = !isVisible; 
}

int BoundingObjectManager::GetNumBoxes()
{
	return objects.size();
}

void BoundingObjectManager::SetColor(int object, vector3 color)
{
	objects.at(object)->SetColor(color); 
}

void BoundingObjectManager::ToggleAABB()
{
	aabbVisible = !aabbVisible;
}

void BoundingObjectManager::CheckCollisions()
{
	for (int i = 0; i < objects.size()-1; ++i)
	{
		for (int j = i+1; j < objects.size(); ++j)
		{
			if (objects[i]->IsColliding(objects[j]))
			{
				objects[i]->SetColor(RERED); 
				objects[j]->SetColor(RERED); 
			}
		}
	}
}
void BoundingObjectManager::ToggleResolution()
{
	canCollide = !canCollide;
}

BoundingObjectManager::BoundingObjectManager()
{
	instance = nullptr;
}
