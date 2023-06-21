#pragma once

#include "text_manager.h"

void textManager::changeText(dynamic* entity)
{
	this->current_text = entity;
}

void textManager::updateData()
{
	
	((float*)this->bufferData)[0] = -0.5f;
	((float*)this->bufferData)[1] = -0.5f;
	((float*)this->bufferData)[2] = 0.0f;
	((float*)this->bufferData)[3] = 0.0f;

	((float*)this->bufferData)[4] = -0.5f;
	((float*)this->bufferData)[5] = 0.0f;
	((float*)this->bufferData)[6] = 0.0f;
	((float*)this->bufferData)[7] = 1.0f;;

	((float*)this->bufferData)[8] = 0.0f;
	((float*)this->bufferData)[9] = 0.0f;
	((float*)this->bufferData)[10] = 1.0f;
	((float*)this->bufferData)[11] = 1.0f;

	((float*)this->bufferData)[12] = 0.0f;
	((float*)this->bufferData)[13] = -0.5f;
	((float*)this->bufferData)[14] = 1.0f;
	((float*)this->bufferData)[15] = 0.0f;

	this->m_vertexBuffer->updateBuffer(this->bufferData, 16 * sizeof(float));
}
void textManager::draw()
{
	if(displayText == false)
		return;


	this->current_text->getTexture()->Bind();

	this->m_shader->Bind();
	this->m_shader->setUniform1i("u_Texture", 0);

	this->m_renderer->Draw(*this->m_vertexArray, *this->m_indexBuffer, *this->m_shader);
}

textManager::textManager(Camera* camera)
	:objectManagerGeneric(camera)
{
	this->bufferDataSize = 16;
	this->indecesCount = 6;

	this->bufferData = new float[this->bufferDataSize];
	this->indeces = new unsigned int[this->indecesCount];

	this->indeces[0] = 0;
	this->indeces[1] = 1;
	this->indeces[2] = 2;
	this->indeces[3] = 2;
	this->indeces[4] = 3;
	this->indeces[5] = 0;

	this->m_vertexBuffer = new vertexBuffer((void*)0, this->bufferDataSize * sizeof(float));

	this->m_vertexBufferLayout = new vertexBufferLayout();
	this->m_vertexBufferLayout->push<float>(2);
	this->m_vertexBufferLayout->push<float>(2);

	this->m_indexBuffer = new indexBuffer(this->indeces, this->indecesCount);

	this->m_vertexArray = new vertexArray();
	this->m_vertexArray->addBuffer(*this->m_vertexBuffer, *this->m_vertexBufferLayout);

	this->m_shader = new shader("basic.shader");

	this->m_renderer = new renderer();

	this->displayText = false;
}
textManager::~textManager()
{
	delete this->m_renderer;
	delete this->m_shader;
	delete this->m_vertexArray;
	delete this->m_indexBuffer;
	delete this->m_vertexBufferLayout;
	delete this->m_vertexBuffer;

	delete[] this->indeces;
	delete[] this->bufferData;
}