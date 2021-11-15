#include "Gui.h"
#include <spdlog/spdlog.h>

namespace nova {	

    Gui::Gui(GLFWwindow* window)
        : m_Window(window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        //io.ConfigFlags |= ImGuiConfigFlags_ViewPortsNoTaskBarIcons; //???
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge; //???

        // Setup ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowWounding/WindowBg so platform windows can look identical to regualr ones.
        ImGuiStyle& style = ImGui::GetStyle();

        // Setup platform renderer bindings

        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

   

    Gui::~Gui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Gui::Draw(Shader& shader, MaterialData& materialData)
    {
        
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Begin("FPS");                        // Create a window called "Hello, world!" and append into it.

            roughnessChanged = ImGui::SliderFloat("roughness", &materialData.roughness, 0.0f, 1.0f);
            metallicChanged = ImGui::SliderFloat("metallic", &materialData.metallic, 0.0f, 1.0f);
            aoChanged = ImGui::SliderFloat("ao", &materialData.ao, 0.0f, 1.0f);
            albedoChanged = ImGui::ColorEdit3("albedo", (float*)&materialData.albedo); // Edit 3 floats representing a color         

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            if (metallicChanged)
            {
                shader.SetFloat("metallic", materialData.metallic);
                metallicChanged = false;
                spdlog::info("metallic changed");
            }

            if (roughnessChanged)
            {
                shader.SetFloat("roughness", materialData.roughness);
                roughnessChanged = false;
                spdlog::info("roughness changed");
            }

            if (aoChanged)
            {
                shader.SetFloat("ao", materialData.ao);
                aoChanged = false;
                spdlog::info("ao changed");
            }

            if (albedoChanged)
            {
                shader.SetUniform3f("albedo", materialData.albedo);
                albedoChanged = false;
                spdlog::info("albedo changed");
            }


            ImGui::End();
    }

    void Gui::Draw(Shader& shader, float& roughness, float& metallic, glm::vec3& albedo)
    {
    }

    void Gui::Draw()
    {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::Begin("FPS");                       // Create a window called "Hello, world!" and append into it.

    

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

  

    void Gui::BeginFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Gui::EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

   
}

