#pragma once
#include <vector>
class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indicesData, unsigned int numIndices);
	IndexBuffer(const std::vector<unsigned int>& indices);
	IndexBuffer(const IndexBuffer&) = default;
	IndexBuffer(IndexBuffer&&) = default;
	~IndexBuffer();

	//void ReDo();

	void Bind();
	void UnBind();

	inline unsigned int GetCount() const { return m_Count; }
private:
	//std::vector<unsigned int> m_Indices;
	unsigned int m_IndexBufferID, m_Count;
};