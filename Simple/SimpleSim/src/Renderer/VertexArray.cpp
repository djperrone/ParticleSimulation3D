#include "VertexArray.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArrayID);	
	
}

VertexArray::~VertexArray()
{
	//spdlog::error("va dest\n");
	glDeleteVertexArrays(1, &m_VertexArrayID);
}

//void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferElement& element)
//{
//	Bind();
//	vb.Bind();
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3 * 3 * sizeof(float), GL_FLOAT, GL_FALSE, 
//		3 * sizeof(float), (void*)element.offset);
//}

void VertexArray::AddBuffer(const VertexBuffer& vb, unsigned int location, unsigned int size, GLenum type, unsigned char normalized, unsigned int stride, unsigned int offset)
{
	Bind();
	vb.Bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, type, normalized, stride, (void*)offset);
		
}



void VertexArray::Bind() const
{
	glBindVertexArray(m_VertexArrayID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
