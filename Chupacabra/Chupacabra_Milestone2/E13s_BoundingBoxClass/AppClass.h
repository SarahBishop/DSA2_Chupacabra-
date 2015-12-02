/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "MyBoundingBoxClass.h"
#include "MyBoundingObjectClass.h"
#include "BoundingObjectManager.h"
#include "CanyonManager.h"
#include "Chupacabra.h"
#include "ChupManagerSingleton.h"
#include "CameraEffect.h"
#include "Carlos.h"

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
	MyBoundingObjectClass* m_pBB1 = nullptr;
	MyBoundingObjectClass* m_pBB2 = nullptr;
	BoundingObjectManager* instance = nullptr; 
	CanyonManager* canyonManager = nullptr;
	ChupManagerSingleton* chupManager = nullptr; 
	Carlos* player = nullptr; 
	double deltaTime; // measures the time between frames for cpu-independent calculations
	float scaledDT; // delta time scaled to be approx 1.0 on most computers

	vector3 m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	vector3 m_v3O2 = vector3( 2.5f, 0.0f, 0.0f);

	CameraEffect* cameraFX = nullptr;

public:
	const float TIME_COEFFICIENT = 64.f;

	typedef ReEngAppClass super;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}

	/*
	ReadConfig
	Reads the configuration of the application to a file
	*/
	virtual void ReadConfig(void) final {}

	/*
	WriteConfig
	Writes the configuration of the application to a file
	*/
	virtual void WriteConfig(void) final {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName) final;

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void) final;

	/*
	Update
	Updates the scene
	*/
	virtual void Update(void) final;

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void) final;

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void) final;

	/*
	ProcessMouse
	Manage the response of key presses and mouse position
	*/
	virtual void ProcessMouse(void) final;

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void Release(void) final;
};

#endif //__APPLICATION_H_
