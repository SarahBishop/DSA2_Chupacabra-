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
	void CreateBoundingObj(std::vector<vector3> a_lVectorList, bool isSphere);
	void ToggleVisibility(); 
	int GetNumBoxes(); 
	void SetColor(int object, vector3 color); 
	void SetVisibility(int object, bool visible);  
	void CheckCollisions(); 
	void ToggleAABB(); 
	void ToggleResolution(); // toggle collision resolution

	std::vector<MyBoundingObjectClass*> objects; 
	bool isVisible = true;
	bool aabbVisible = true;
	bool canCollide = true; // true = collision resolution

private:
	BoundingObjectManager();
};

#endif //BOUNDING_OBJECT_MANAGER