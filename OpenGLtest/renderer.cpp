#include "renderer.h"

void renderer::Draw(vertexArray& va, indexBuffer& ib, shader& sh)
{
	va.Bind();
	ib.Bind();
	sh.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
void renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}