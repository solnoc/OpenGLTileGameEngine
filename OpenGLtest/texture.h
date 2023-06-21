#pragma once

#include <string>

class texture
{
private:
	unsigned int m_rendererId;
	std::string m_filepath;
	unsigned char* m_localBuffer;
	int m_width;
	int m_height;
	int m_bpp;

public:
	texture(const std::string& path);
	~texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
};

