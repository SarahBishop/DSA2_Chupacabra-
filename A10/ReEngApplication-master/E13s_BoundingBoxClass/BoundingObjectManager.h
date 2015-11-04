#ifndef BOUNDING_OBJECT_MANAGER
#define BOUNDING_OBJECT_MANAGER

#include "MyBoundingObjectClass.h"

class BoundingObjectManager
{
	static BoundingObjectManager* instance;

	
public:
	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();
	void CreateBoundingObj(std::vector<vector3> a_lVectorList);
	void ToggleVisibility(); 
	int GetNumBoxes(); 
	void SetColor(int object, vector3 color); 
	void SetVisibility(int object, bool visible);  
	void CheckCollisions(); 
	void ToggleAABB(); 

	std::vector<MyBoundingObjectClass*> objects; 
	bool isVisible;
	bool aabbVisible; 

private:
	BoundingObjectManager();
};

#endif //BOUNDING_OBJECT_MANAGER