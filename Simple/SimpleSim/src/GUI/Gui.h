#pragma once
#include <imgui/imgui.h>
#include <imgui/imconfig.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>


#include "Renderer/Shader.h"
#include "Renderer/MaterialData.h"

namespace nova {

	class Gui
	{
	public:
		Gui() = default;
		Gui(GLFWwindow* window);
		
		~Gui();
		
		void Draw();
		void Draw(Shader& shader, MaterialData& materialData);
		void Draw(Shader& shader, float& roughness, float& metallic, glm::vec3& albedo);
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

	};
}