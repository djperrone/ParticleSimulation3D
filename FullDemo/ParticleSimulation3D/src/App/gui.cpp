#include "sapch.h"
#include "Gui.h"
#include <imgui.h>
#include <imconfig.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
//#include "common.h"

#include "Novaura/Novaura.h"

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

    void Gui::Draw()
    {
      /*  if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);*/




        static float f = 0.0f;
        static int counter = 0;
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
       // float tx = 0.0f;
      //  ImGui::InputFloat("test tx", &tx, 0.5f, 2, 0);// ImGui::SameLine(150);
       // int n = 0;
        //ImGui::SliderInt("test n", &n, 0, 10'000);

       // ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
      //  ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
       // ImGui::Checkbox("Another Window", &show_another_window);


       // ImGui::SliderFloat("v_mod", &common::velocity_modifier, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
       // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

       // if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
         //   counter++;
       // ImGui::SameLine();
        //ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    void Gui::Draw(Novaura::Shader& shader, Novaura::MaterialData& materialData)
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