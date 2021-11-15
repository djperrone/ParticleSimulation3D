#include "Renderer.h"
#include <glm/glm.hpp>
//Renderer::Renderer()
//{
//	glEnable(GL_DEPTH_TEST);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	//SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}

Renderer::Renderer(OpenGLContext& context, Camera& camera)
	: m_Context(context), m_Camera(camera)
{
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	SetClearColor(0.05f, 0.05f, 0.05f, 1.0f);

	
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, 1.0f);
}

void Renderer::Clear()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

