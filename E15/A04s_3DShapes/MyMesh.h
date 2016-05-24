/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2015/08
Notes: This is a simplified version of MeshClass
inside of ReEng.dll, its stripped out of a lot
of functionality in order to focuss on important
concepts of OpenGL, please use a MeshClass object
for better functionality.
----------------------------------------------*/
#ifndef __MYMESH_H_
#define __MYMESH_H_

#include "RE\ReEng.h"

//System Class
class MyMesh
{
protected:
	bool m_bBinded = false; //Binded flag
	int m_nVertexCount = 0; //Number of Vertices in this Mesh

	GLuint m_vao = 0;			//OpenGL Vertex Array Object
	GLuint m_VertexBuffer = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer = 0;	//OpenGL Buffer (Will hold the color buffer pointer)

	ShaderManagerSingleton* m_pShaderMngr = nullptr;	//Shader Manager

	std::vector<vector3> m_lVertexPos;	//List of Vertices
	std::vector<vector3> m_lVertexCol;	//List of Colors

public:
	/* Constructor */
	MyMesh(void);
	/* Copy Constructor */
	MyMesh(MyMesh const& other);
	/* Copy Assignment Operator*/
	MyMesh& operator=(MyMesh const& other);
	/* Destructor */
	~MyMesh(void);

	/* Swaps the contents of the object with another object's content */
	void Swap(MyMesh& other);

	/* Compiles the Mesh for OpenGL 3.X use*/
	void CompileOpenGL3X(void);

	/* Returns the total number of vertices in this Mesh */
	int GetVertexTotal(void);

	/* Adds a new point to the vector of vertices */
	void AddVertexPosition(vector3 a_v3Input);

	/* Adds a new color to the vector of vertices */
	void AddVertexColor(vector3 a_v3Input);

	/* Renders the shape */
	virtual void RenderList(matrix4 a_mProjectionMatrix, matrix4 a_mViewMatrix, float* a_fMatrixArray, int a_nInstances);

	/* Renders the shape asking for its position in the world and a color */
	virtual void Render(matrix4 a_mProjectionMatrix, matrix4 a_mViewMatrix, matrix4 a_mToWorld = IDENTITY_M4);

protected:
	/* Initialize the object's fields */
	virtual void Init(void);
	/* Releases the object from memory */
	virtual void Release(void);
	/* Completes the information missing to create the mesh */
	void CompleteMesh(void);

public:
	/* Completes the triangle information */
	void CompleteTriangleInfo(void);
};

#endif //__MYMESH_H_