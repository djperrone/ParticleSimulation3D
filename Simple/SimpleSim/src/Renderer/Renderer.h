#pragma once

#include <glad/glad.h>
#include <memory>
#include "Camera/Camera.h"
#include "Core/OpenGLContext.h"

class Renderer
{
public:
	Renderer() = default;
	Renderer(OpenGLContext& context, Camera& camera);
	void SetClearColor(float r, float g, float b, float a = 1.0f);
	void Clear();
	void Init();

	

private:
	OpenGLContext& m_Context;
	Camera& m_Camera;
};