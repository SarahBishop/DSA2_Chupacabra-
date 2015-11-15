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
	mngr->SetPosition(mngr->GetPosition().x, abs(time % 2 - 1), mngr.GetPosition().z)
}