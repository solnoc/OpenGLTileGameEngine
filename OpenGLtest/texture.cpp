#include "texture.h"

#include "error_checking.h"
#include "stb_image.h"

texture::texture(const std::string& filepath)
	:m_rendererId(0), m_filepath(filepath), m_localBuffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 4);

	GLCall(glGenTextures(1, &m_rendererId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

texture::~texture()
{
	GLCall(glDeleteTextures(1, &m_rendererId));
}

void texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererId));
}

void texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}