#pragma once

#include "OpenGLContext.h"


#include "Camera/Camera.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/FrameBuffer.h"

#include <memory>

#include "Renderer/Texture.h"

#include "Renderer/MaterialData.h"
#include "GUI/Gui.h"

class ParticleInstancingApp
{
public:
	ParticleInstancingApp();

	void Init();
	void Update();
	//void Render();

	inline bool IsRunning() const { return m_Context->IsRunning(); }
	inline Window& GetWindow() { return m_Context->GetWindow(); }
	inline const Window& GetWindow() const { return m_Context->GetWindow(); }

private:
	void BeginFrame();
	void EndFrame() const;


private:
	//OpenGLContext m_Context;
	std::unique_ptr < OpenGLContext> m_Context;
	//Camera m_Camera;
	std::unique_ptr < Camera> m_Camera;
	std::unique_ptr<Renderer> m_Renderer;
	std::unique_ptr<nova::Gui> m_Gui;

	MaterialData materialData;

	

private:	

private:
	std::unique_ptr<Shader> m_Shader;	


private:
	float m_DeltaTime = 0.0f;
	float m_LastFrame = 0.0f;

	glm::mat4* modelMatrices;
	float roughness = 0.4f;
	float metallic = 1.0f;
	glm::vec3 albedo = glm::vec3(35.0f / 255.0f, 137.0f / 255.0f, 218.0f / 255.0f);
	
	

	void InitSphere();
	void InitSphereInstanceBuffer();
	void UpdateSphereVAO();
	void InitLighting();
private:
	unsigned int indexCount, sphereVAO;
	int nrRows =    5;
	int nrColumns = 5;
	unsigned int amount = nrRows * nrColumns * nrColumns;

	float spacing = 2.5;
private:
	unsigned int instanceVBO;

private:	
	glm::vec3 lightPositions[4] = {
		glm::vec3(-20.0f,  20.0f, 20.0f),
		glm::vec3(20.0f,  20.0f, 20.0f),
		glm::vec3(-20.0f, -20.0f, 20.0f),
		glm::vec3(20.0f, -20.0f, 20.0f),
	};
	glm::vec3 lightColors[4] = {
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f)
	};
};