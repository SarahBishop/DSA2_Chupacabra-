#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { Init(); }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { Release(); }
void MyPrimitive::Release(void)
{
	super::Release();

	if (m_ColorBuffer2 > 0)
		glDeleteBuffers(1, &m_ColorBuffer2);

	if (m_VertexBuffer2 > 0)
		glDeleteBuffers(1, &m_VertexBuffer2);

	m_lVertexPos2.clear();
	m_lVertexCol2.clear();
}
void MyPrimitive::Init(void)
{
	super::Init();

	m_VertexBuffer2 = 0;
	m_ColorBuffer2 = 0;
}
void MyPrimitive::CompileObject(vector3 a_vColor)
{
	//Compile faces
	int nColorTotal = static_cast<int>(m_lVertexCol.size());
	for (int nColor = nColorTotal; nColor < m_nVertexCount; nColor++)
		m_lVertexCol.push_back(a_vColor);
	CompileOpenGL3X();
	//Compile Lines
	for (int i = 0; i < m_nVertexCount - 2; i += 3)
	{
		m_lVertexPos2.push_back(m_lVertexPos[i]);
		m_lVertexPos2.push_back(m_lVertexPos[i + 1]);

		m_lVertexPos2.push_back(m_lVertexPos[i + 1]);
		m_lVertexPos2.push_back(m_lVertexPos[i + 2]);
		
		m_lVertexPos2.push_back(m_lVertexPos[i + 2]);
		m_lVertexPos2.push_back(m_lVertexPos[i]);
	}
	int nVertices = m_lVertexPos2.size();
	for (int nVertex = 0; nVertex < nVertices; nVertex++)
	{
		m_lVertexCol2.push_back(vector3(1.0f - a_vColor.x, 1.0f - a_vColor.y, 1.0f - a_vColor.z));
	}

	// Create and initialize a buffer object for each shape.
	glGenBuffers(1, &m_VertexBuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer2);
	glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(vector3), &m_lVertexPos2[0], GL_STATIC_DRAW);

	//Initialize the color buffer for the object.
	glGenBuffers(1, &m_ColorBuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer2);
	glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(vector3), &m_lVertexCol2[0], GL_STATIC_DRAW);
}
void MyPrimitive::Render(matrix4 a_mProjectionMatrix, matrix4 a_mViewMatrix, matrix4 a_mToWorld)
{
	//Render the object in solid color
	super::Render(a_mProjectionMatrix, a_mViewMatrix, a_mToWorld);

	if (!m_bBinded)
		return;

	if (m_nVertexCount == 0)
		return;

	// Use the buffer and shader
	GLuint nProgram = m_pShaderMngr->GetShaderID("BasicColor");
	glUseProgram(nProgram);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nProgram, "MVP");
	GLuint v4Position = glGetAttribLocation(nProgram, "Position_b");
	GLuint v4Color = glGetAttribLocation(nProgram, "Color_b");

	//Final Projection of the Camera
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(a_mProjectionMatrix * a_mViewMatrix * a_mToWorld));

	//position
	glEnableVertexAttribArray(v4Position);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer2);
	glVertexAttribPointer(v4Position, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Color
	glEnableVertexAttribArray(v4Color);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer2);
	glVertexAttribPointer(v4Color, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Color and draw
	glDrawArrays(GL_LINES, 0, static_cast<int>(m_lVertexPos2.size()));

	glDisableVertexAttribArray(v4Position);
	glDisableVertexAttribArray(v4Color);
}