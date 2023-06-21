#pragma once

#include <string>
#include <unordered_map>

struct shaderSourceString
{
	std::string vertexString;
	std::string fragmentString;
};

class shader
{
private:
	unsigned int m_rendererId;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_locationCache;

public:
	shader(std::string filepath);
	~shader();

	void setUniform1i(const std::string& name, int v1);
	void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);

	void Bind() const;
	void Unbind() const;

private:
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertex_shader, const std::string& fragment_shader);
	shaderSourceString parseShaderFile(std::string filepath);
	int getUniformLocation(const std::string& name);
};

