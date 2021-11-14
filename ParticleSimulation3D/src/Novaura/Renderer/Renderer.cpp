#include "Renderer.h"
#include <glad/glad.h>

namespace Novaura {

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, 1.0f);
	}

	void Renderer::Clear()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
}
