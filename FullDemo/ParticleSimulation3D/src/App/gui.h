#pragma once
#include <imgui.h>
#include <imconfig.h>

#include <GLFW/glfw3.h>


#include "Novaura/Renderer/Shader.h"
#include "Novaura/Renderer/MaterialData.h"
#include "Novaura/Renderer/SphereData.h"

namespace nova {

	class Gui
	{
	public:
		Gui() = default;
		Gui(GLFWwindow* window);
		
		~Gui();
		
		void Draw();
		void Draw(Novaura::Shader& shader, Novaura::MaterialData& materialData, Novaura::SphereData& sphereData);
		void Draw(Novaura::Shader& shader, float& roughness, float& metallic, glm::vec3& albedo);
		void BeginFrame();
		void EndFrame();

	private:
	
		std::vector<bool> m_ActiveSlots;
		bool test = false;

	private:
		bool rotationReset = false;
		bool translationReset = false;


	private:
		GLFWwindow* m_Window;
		

	private:
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		bool albedoChanged = false;
		bool metallicChanged = false;
		bool roughnessChanged = false;
		bool aoChanged = false;
		bool scaleChanged = false;
	};
}