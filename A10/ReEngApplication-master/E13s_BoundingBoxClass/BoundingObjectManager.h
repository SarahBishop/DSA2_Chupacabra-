#ifndef BOUNDING_OBJECT_MANAGER
#define BOUNDING_OBJECT_MANAGER

#include "AppClass.h"

class BoundingObjectManager
{
private:
	BoundingObjectManager();
	static BoundingObjectManager* instance;
public:
	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();
	void createBoundingObj(std::vector<vector3> a_lVectorList);
	void ToggleVisibility(); 
	int GetNumBoxes(); 
	void SetColor(BoundingObjectClass object, COLOR16 color); 
	void SetVisibility(BoundingObjectClass object, bool visible); 
	void Render(std::vector<BoundingObjectClass> toRender); 
	void CheckCollisions(); 

};

#endif //BOUNDING_OBJECT_MANAGER