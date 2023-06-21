#include "error_checking.h"
#include "vertex_buffer.h"

vertexBuffer::vertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_rendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW));
}
vertexBuffer::~vertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_rendererId));
}
void vertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
}
void vertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
void vertexBuffer::updateBuffer(const void* data, unsigned int size)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}