#ifndef BOUNDING_OBJECT_MANAGER
#define BOUNDING_OBJECT_MANAGER

class BoundingObjectManager
{
	static BoundingObjectManager* instance;

private:
	BoundingObjectManager();

public:
	static BoundingObjectManager* GetInstance();
	static void ReleaseInstance();
};
#endif //BOUNDING_OBJECT_MANAGER