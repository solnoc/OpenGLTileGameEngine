#pragma once
class indexBuffer{
private:
	unsigned int m_rendererId;
	unsigned int m_count;

public:
	indexBuffer(const unsigned int* data, unsigned int count);
	~indexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_count; }
};

