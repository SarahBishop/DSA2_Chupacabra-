#ifndef __CAMERA_EFFECT_H__
#define __CAMERA_EFFECT_H__ 
#include "RE\ReEngAppClass.h"
//#include "AppClass.h"
class CameraEffect
{
public:
	CameraEffect();
	~CameraEffect();
	void CameraBob();
	CameraManagerSingleton* mngr = nullptr;
};
#endif // __CAMERA_EFFECT_H__