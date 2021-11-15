#include "ParticleInstancingApp.h"

#include <spdlog/spdlog.h>

ParticleInstancingApp::ParticleInstancingApp()	
{	
	m_Camera = std::make_unique<Camera>();
	m_Context = std::make_unique<OpenGLContext>(*m_Camera);
	m_Renderer = std::make_unique <Renderer>(*m_Context, *m_Camera);
	
	m_Gui = std::make_unique<nova::Gui>(m_Context->GetWindow().Window);
    m_Context->SetWindowDimensions(800, 600);
    m_Camera->MovementSpeed = 10.0f;

	Init();
  
}

void ParticleInstancingApp::Init()
{
    glfwSetInputMode(GetWindow().Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glEnable(GL_DEPTH_TEST);
	spdlog::info("test");
   // m_Shader = std::make_unique<Shader>("src/AdvancedOpenGL/Shaders/BasicCubeShader.glsl");
    m_Shader = std::make_unique<Shader>("src/Shaders/InstancedSphereShader.glsl");
    m_Shader->Bind();
    m_Shader->SetUniform3f("albedo", materialData.albedo);
    m_Shader->SetFloat("ao", materialData.ao);
    m_Shader->SetFloat("metallic", materialData.metallic);  
    m_Shader->SetFloat("roughness", materialData.roughness);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
  
    InitSphere();
    InitSphereInstanceBuffer();
    InitLighting();

}

void ParticleInstancingApp::Update()
{
    BeginFrame();
    glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)GetWindow().Width / (float)GetWindow().Height, 0.1f, 100.0f);
    m_Shader->SetUniformMat4f("projection", projection);
    glm::mat4 view = m_Camera->GetViewMatrix();
    m_Shader->SetUniformMat4f("view", view);
    m_Shader->SetUniform3f("camPos", m_Camera->Position);

    glBindVertexArray(sphereVAO);

    glDrawElementsInstanced(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0, amount); 


    m_Gui->Draw(*m_Shader, materialData);
    EndFrame();
}




void ParticleInstancingApp::BeginFrame()
{
	float currentFrame = glfwGetTime();
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;
	
	m_Renderer->SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	m_Renderer->Clear();
	m_Context->HandleInput(m_DeltaTime);
	m_Gui->BeginFrame();
}

void ParticleInstancingApp::EndFrame() const
{
	m_Gui->EndFrame();
	m_Context->SwapBuffers();
}

void ParticleInstancingApp::InitSphere()
{
    glGenVertexArrays(1, &sphereVAO);

    unsigned int vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359;
    for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
    {
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(glm::vec3(xPos, yPos, zPos));
            uv.push_back(glm::vec2(xSegment, ySegment));
            normals.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow) // even rows: y == 0, y == 2; and so on
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
    indexCount = indices.size();
    spdlog::info("index count {}", indexCount);

    std::vector<float> data;
    for (unsigned int i = 0; i < positions.size(); ++i)
    {
        data.push_back(positions[i].x);
        data.push_back(positions[i].y);
        data.push_back(positions[i].z);
        if (normals.size() > 0)
        {
            data.push_back(normals[i].x);
            data.push_back(normals[i].y);
            data.push_back(normals[i].z);
        }
        if (uv.size() > 0)
        {
            data.push_back(uv[i].x);
            data.push_back(uv[i].y);
        }
    }
    glBindVertexArray(sphereVAO);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    unsigned int stride = (3 + 2 + 3) * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

}

void ParticleInstancingApp::InitSphereInstanceBuffer()
{
   
    //m_Shader->Bind();
   
    amount = nrRows * nrColumns * nrColumns;
    modelMatrices = new glm::mat4[amount];
    int i = 0;
    glm::mat4 model = glm::mat4(1.0f);
    for (int row = 0; row < nrRows; ++row)
    {
        for (int col = 0; col < nrColumns; ++col)
        {
            for (int z = 0; z < nrColumns; ++z)
            {
                // we clamp the roughness to 0.05 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
                // on direct lighting.

                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(
                    (col - (nrColumns / 2)) * spacing,
                    (row - (nrRows / 2)) * spacing,
                    (z - (nrRows / 2)) * spacing
                )) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
                // )) * glm::scale(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f));
                modelMatrices[i++] = model;
               
            }
        }
    }

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * amount, &modelMatrices[0], GL_STATIC_DRAW);
    UpdateSphereVAO();
}

void ParticleInstancingApp::UpdateSphereVAO()
{
    glBindVertexArray(sphereVAO);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glBindVertexArray(0);
}

void ParticleInstancingApp::InitLighting()
{
    for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
    {
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        m_Shader->SetUniform3f("lightPositions[" + std::to_string(i) + "]", newPos);
        m_Shader->SetUniform3f("lightColors[" + std::to_string(i) + "]", lightColors[i]);

       
       
    }
}

