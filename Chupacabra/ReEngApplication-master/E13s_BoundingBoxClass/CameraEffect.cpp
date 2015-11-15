// CameraEffect.cpp
#include "CameraEffect.h"

CameraEffect::CameraEffect()
{
	mngr = CameraManagerSingleton::GetInstance();
}


CameraEffect::~CameraEffect()
{
	mngr->ReleaseInstance();
}

void CameraEffect::CameraBob() {
	// bob camera linearly
	mngr->SetPosition(vector3(mngr->GetPosition(-1).x, abs(clock() % 400 - 200)/5000.f + 0.5f, mngr->GetPosition(-1).z));
	//std::cout << (clock()) << " ";
}