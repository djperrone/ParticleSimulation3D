#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>


class Texture
{
public:
	Texture() = default;
	Texture(const std::string& path);
	Texture(unsigned int width, unsigned int height);
	Texture(const std::string& path, GLuint glFormat);
	Texture(const char* path, const std::string& directory, const std::string& type, bool gamma = false);

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetID() const { return m_TextureID; }
	inline std::string GetType() const { return m_Type; }
	inline std::string GetPath() const { return m_Path; }

	void SetID(unsigned int id) { m_TextureID = id; }
	void SetType(const std::string& type) { m_Type = type; }
	void SetPath(const std::string& path) { m_Path = path; }

public:
	//static std::unordered_map<std::string, Texture> LoadedTextures;
	

private:
	unsigned int m_TextureID;
	int m_Width, m_Height, m_NumChannels;
	std::string m_Type, m_Path;

	void LoadTexture(const std::string& path);
	void LoadTexture(const char* path, const std::string& directory, const std::string& type, bool gamma = false);

};

