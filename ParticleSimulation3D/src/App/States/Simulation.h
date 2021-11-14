#pragma once
#include "Novaura/StateMachine/State.h"
#include "Novaura/Camera/CameraController.h"
//#include "Novaura/Primitives/Rectangle.h"
#include "StateInfo.h"
#include "Novaura/Renderer/MaterialData.h"
#include "Novaura/Renderer/Shader.h"


//#include "../common.h"
#include "../gui.h"


namespace ParticleSimulation {


	class Simulation : public Novaura::State
	{
	public:
		Simulation();		
		//Simulation(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::CameraController> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine);
		Simulation(std::shared_ptr<Novaura::Window> window, std::shared_ptr<Novaura::PerspectiveCamera> cameraController, std::shared_ptr<Novaura::StateMachine> stateMachine);
		
		virtual void OnEnter() override;

		virtual void HandleInput() override;
		virtual void Update(float deltaTime)override;
		virtual void Draw(float deltaTime) override;

		virtual void OnExit() override;

		virtual void Pause() override;
		virtual void Resume() override;

	
	private:		

		std::unique_ptr<nova::Gui> m_Gui;

		unsigned int amount = 100;
		glm::mat4* modelMatrices;

		Novaura::MaterialData materialData;


		std::unique_ptr<Novaura::Shader> m_Shader;


		void InitSphere();
		void InitSphereInstanceBuffer();
		void UpdateSphereVAO();
		void InitLighting();
	private:
		unsigned int indexCount, sphereVAO;
		int nrRows = 20;
		int nrColumns = 20;
		float spacing = 2.5;
	private:
		unsigned int instanceVBO;

	private:
		glm::vec3 lightPositions[4] = {
			glm::vec3(-10.0f,  10.0f, 10.0f),
			glm::vec3(10.0f,  10.0f, 10.0f),
			glm::vec3(-10.0f, -10.0f, 10.0f),
			glm::vec3(10.0f, -10.0f, 10.0f),
		};
		glm::vec3 lightColors[4] = {
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f),
			glm::vec3(300.0f, 300.0f, 300.0f)
		};



	};
}
