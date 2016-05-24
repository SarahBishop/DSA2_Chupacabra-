/*--------------------------------------------------------------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2015/02
Modified: 2015/09
--------------------------------------------------------------------------------------------------*/
#ifndef __MYPRIMITIVE_H_
#define __MYPRIMITIVE_H_

#include "MyMesh.h"

class MyPrimitive : public MyMesh
{
	typedef MyMesh super;

	GLuint m_VertexBuffer2 = 0; //for lines
	GLuint m_ColorBuffer2 = 0; //for lines

	std::vector<vector3> m_lVertexPos2;	//List of Vertices
	std::vector<vector3> m_lVertexCol2;	//List of Colors

public:
	/* Constructor */
	MyPrimitive();
	/* Copy Constructor */
	MyPrimitive(const MyPrimitive& other);
	/* Copy Assignment Operator */
	virtual MyPrimitive& operator=(const MyPrimitive& other);

	/* Destructor */
	~MyPrimitive(void);

	/* Generates a cube shape */
	void GenerateCube(float a_fSize, vector3 a_vColor);
	/* Generates a cone shape */
	void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	/* Generates a cylinder shape */
	void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	/* Generates a tube shape */
	void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	/* Generates a Sphere shape */
	void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_vColor);

	/* Renders the primitive */
	virtual void Render(matrix4 a_mProjectionMatrix, matrix4 a_mViewMatrix, matrix4 mToWorld = IDENTITY_M4);

	/* Releases the object from memory */
	virtual void Release(void);

private:
	/* Initialize the object's fields */
	virtual void Init(void);
	/* Compiles the object with an specific color and name */
	void CompileObject(vector3 a_vColor);
	/* Adds a quad to the list points in the buffer to be compiled*/
	void AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);
};

#endif //__MYPRIMITIVE_H_