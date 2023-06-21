#pragma once

class vertexBuffer {
private:
	unsigned int m_rendererId;

public:
	vertexBuffer(const void* data, unsigned int size);
	~vertexBuffer();

	void Bind() const;
	void Unbind() const;

	void updateBuffer(const void* data, unsigned int size);
};