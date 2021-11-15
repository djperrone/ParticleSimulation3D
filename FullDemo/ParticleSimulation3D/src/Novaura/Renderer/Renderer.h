#pragma once

namespace Novaura {

	class Renderer
	{
	public:
		Renderer() = default;
		//Renderer(OpenGLContext& context, Camera& camera);
		static void SetClearColor(float r, float g, float b, float a = 1.0f);
		static void Clear();
		void Init();	

	private:
		//OpenGLContext& m_Context;
		//Camera& m_Camera;
	};
}
