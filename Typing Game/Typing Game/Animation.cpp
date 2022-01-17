#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(sf::Texture& texture, sf::Vector2i frameNum, float frameTime)
{
	m_frameNum = frameNum;
	m_frameTime = frameTime;
	this->setTexture(texture);
	m_currentFrame = sf::Vector2i(0, 0);
	m_currentTime = 0;
	CalculateRectSize();
	
}

void Animation::CalculateRectSize()
{
	m_rectSize = sf::Vector2i(this->getTexture()->getSize().x / m_frameNum.x, this->getTexture()->getSize().y / m_frameNum.y);
	CalculateRectUV();
	ApplyRect();
}

void Animation::CalculateRectUV()
{
	m_rectUV.x = m_currentFrame.x * m_rectSize.x;
	m_rectUV.y = m_currentFrame.y * m_rectSize.y;
}

void Animation::ApplyRect()
{
	CalculateRectUV();
	m_rect = sf::IntRect(m_rectUV, m_rectSize);
	this->setTextureRect(m_rect);
}

void Animation::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime >= m_frameTime)
	{
		m_currentFrame.x++;
		if (m_currentFrame.x == m_frameNum.x)
		{
			m_currentFrame.x = 0;
		}
		ApplyRect();
		m_currentTime = 0;
	}
}
