#pragma once
#include <vector>
#include "Vertex.h"
#include <iostream>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(float* vertices, unsigned int size);	
	VertexBuffer(const std::vector<Vertex>& vertices);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetID() const { return m_VertexBufferID; }

private:
	unsigned int m_VertexBufferID;
};