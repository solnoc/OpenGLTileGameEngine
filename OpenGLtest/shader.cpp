#include "shader.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "error_checking.h"

shader::shader(std::string filepath)
    :m_filepath(filepath), m_rendererId(0)
{
    shaderSourceString source = parseShaderFile(filepath);
    m_rendererId = createShader(source.vertexString, source.fragmentString);
}

shader::~shader()
{
    GLCall(glDeleteProgram(m_rendererId));
}

unsigned int shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int lenght;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
        char* a = (char*)alloca(sizeof(char) * lenght);
        GLCall(glGetShaderInfoLog(id, lenght, &lenght, a));
        std::cout << "Failed to compile shader." << std::endl;
        std::cout << a << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}
unsigned int shader::createShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}
shaderSourceString shader::parseShaderFile(std::string filepath)
{
    std::ifstream in(filepath);

    enum class shaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream shaderStrings[2];
    shaderType type = shaderType::NONE;
    while (std::getline(in, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = shaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = shaderType::FRAGMENT;
            }
        }
        else
        {
            shaderStrings[(int)type] << line << '\n';
        }
    }
    return { shaderStrings[0].str(), shaderStrings[1].str() };
}

void shader::Bind() const
{
    GLCall(glUseProgram(m_rendererId));
}
void shader::Unbind() const
{
    GLCall(glUseProgram(0));
}
void shader::setUniform1i(const std::string& name, int v1)
{
    GLCall(glUniform1i(getUniformLocation(name), v1));
}
void shader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    GLCall(glUniform4f(getUniformLocation(name), v1, v2, v3, v4));
}
int shader::getUniformLocation(const std::string& name)
{
    if (m_locationCache.find(name) != m_locationCache.end())
        return m_locationCache[name];

    GLCall(unsigned int location = glGetUniformLocation(m_rendererId, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist..." << std::endl;
    m_locationCache[name] = location;
    return location;
}