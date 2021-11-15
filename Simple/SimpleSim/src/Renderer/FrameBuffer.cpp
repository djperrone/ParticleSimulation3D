#include "FrameBuffer.h"
#include <glad/glad.h>
#include <iostream>
FrameBuffer::FrameBuffer()
{
	//glGenFramebuffers(1, &m_FrameBufferID);
 //   glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

 //   float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
 //       // positions   // texCoords
 //       -1.0f,  1.0f,  0.0f, 1.0f,
 //       -1.0f, -1.0f,  0.0f, 0.0f,
 //        1.0f, -1.0f,  1.0f, 0.0f,

 //       -1.0f,  1.0f,  0.0f, 1.0f,
 //        1.0f, -1.0f,  1.0f, 0.0f,
 //        1.0f,  1.0f,  1.0f, 1.0f
 //   };

 //   m_VertexArray = std::make_unique<VertexArray>();    
 //   m_VertexBuffer = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices));

 //   m_VertexArray->AddBuffer(*m_VertexBuffer, 0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
 //   m_VertexArray->AddBuffer(*m_VertexBuffer, 1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 2 * sizeof(float));
}

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
	m_Shader = std::make_unique<Shader>("src/Shaders/FrameBuffersScreen.glsl");

	m_Shader->Bind();
	m_Shader->SetInt("screenTexture", 0);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
     // positions   // texCoords
     -1.0f,  1.0f,  0.0f, 1.0f,
     -1.0f, -1.0f,  0.0f, 0.0f,
      1.0f, -1.0f,  1.0f, 0.0f,

     -1.0f,  1.0f,  0.0f, 1.0f,
      1.0f, -1.0f,  1.0f, 0.0f,
      1.0f,  1.0f,  1.0f, 1.0f
    };
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
   
}

FrameBuffer::FrameBuffer(const std::string& shaderPath, unsigned int width, unsigned int height)
{
	m_Shader = std::make_unique<Shader>(shaderPath);

	m_Shader->Bind();
	m_Shader->SetInt("screenTexture", 0);

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	 // positions   // texCoords
	 -1.0f,  1.0f,  0.0f, 1.0f,
	 -1.0f, -1.0f,  0.0f, 0.0f,
	  1.0f, -1.0f,  1.0f, 0.0f,

	 -1.0f,  1.0f,  0.0f, 1.0f,
	  1.0f, -1.0f,  1.0f, 0.0f,
	  1.0f,  1.0f,  1.0f, 1.0f
	};
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture

	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_FrameBufferID);
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteTextures(1, &textureColorbuffer);
    // not in youtube video
   // glDeleteTextures(1, &m_ColorAttachment);
   // glDeleteRenderbuffers(1, &m_RenderBufferObject);
}

void FrameBuffer::Draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);
	m_Shader->Bind();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FrameBuffer::BeginScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_DEPTH_TEST);


}

void FrameBuffer::EndScene()
{
	// prior to draw call
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glDisable(GL_DEPTH_TEST);

	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
}

void FrameBuffer::Bind()
{
	//glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    //glBindVertexArray(m_VertexArrayID);
    //glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
    //glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferObject);
    //glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
    //m_VertexArray->Bind();
   // glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

}

void FrameBuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


//FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
//{
//
//
//    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//        // positions   // texCoords
//        -1.0f,  1.0f,  0.0f, 1.0f,
//        -1.0f, -1.0f,  0.0f, 0.0f,
//         1.0f, -1.0f,  1.0f, 0.0f,
//
//        -1.0f,  1.0f,  0.0f, 1.0f,
//         1.0f, -1.0f,  1.0f, 0.0f,
//         1.0f,  1.0f,  1.0f, 1.0f
//    };
//
//    // m_VertexArray = std::make_unique<VertexArray>();
//     //m_VertexBuffer = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices));
//
//     //m_VertexArray->AddBuffer(*m_VertexBuffer, 0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//    //m_VertexArray->AddBuffer(*m_VertexBuffer, 1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 2 * sizeof(float));
//    glGenVertexArrays(1, &m_VertexArrayID);
//    glGenBuffers(1, &m_VertexBufferID);
//    glBindVertexArray(m_VertexArrayID);
//    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//
//    glGenFramebuffers(1, &m_FrameBufferID);
//    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
//    glGenTextures(1, &m_ColorAttachment);
//
//    //glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
//    glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
//
//    //glGenTextures(1, &textureColorbuffer);
//    //glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
//    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Context->GetWindow().Width, m_Context->GetWindow().Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//
//
//    glGenRenderbuffers(1, &m_RenderBufferObject);
//    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferObject);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferObject); // now actually attach it
//    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << '\n';
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//}
