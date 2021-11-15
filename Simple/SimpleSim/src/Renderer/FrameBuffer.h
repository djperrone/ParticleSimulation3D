#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(unsigned int width, unsigned int height);
	FrameBuffer(const std::string& shaderPath, unsigned int width, unsigned int height);
	~FrameBuffer();
	void Draw();
	void BeginScene();
	void EndScene();
	void Bind();
	void UnBind();
private:
	unsigned int m_FrameBufferID, m_VertexArrayID, m_VertexBufferID;
	unsigned int  m_ColorAttachment, m_RenderBufferObject;
	std::unique_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
public:
	unsigned int rbo;
	unsigned int textureColorbuffer;
	unsigned int quadVAO, quadVBO;
	std::unique_ptr<Shader> m_Shader;
	unsigned int framebuffer;
	//std::unique_ptr<Texture> m_Texture;
};
