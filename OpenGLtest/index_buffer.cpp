#include "error_checking.h"
#include "index_buffer.h"

indexBuffer::indexBuffer(const unsigned int* data, unsigned int count)
    :m_count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_rendererId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
indexBuffer::~indexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_rendererId));
}
void indexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
}
void indexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}