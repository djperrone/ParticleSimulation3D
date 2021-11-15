#pragma once
#include "VertexBuffer.h"
#include <glad/glad.h>

//struct VertexBufferElement
//{
//	// Tell OpenGL how to interpret data
//	unsigned int location;
//	GLenum type;
//	unsigned int count; // vec3
//	unsigned int size;
//	unsigned int offset;
//	unsigned char normalized;	
//
//	static unsigned int GetSizeOfType(unsigned int type)
//	{
//		switch (type)
//		{
//		case GL_FLOAT:			return 4;
//		case GL_UNSIGNED_INT:	return 4;
//		case GL_UNSIGNED_BYTE:	return 1;
//		}
//		
//		return 0;
//	}
//};



class VertexArray
{
public:
	VertexArray();
	VertexArray(const VertexArray& other) = default;
	VertexArray(VertexArray&& other) = default;
	~VertexArray();

	//void Delete()const;

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetID() const { return m_VertexArrayID; }


	//void AddBuffer(const VertexBuffer& vb, const VertexBufferElement& element);
	void AddBuffer(const VertexBuffer& vb, unsigned int location, unsigned int size, GLenum type, unsigned char normalized, unsigned int stride, unsigned int offset);
private:
	unsigned int m_VertexArrayID;
};