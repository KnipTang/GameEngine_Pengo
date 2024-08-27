#include <string>
#include <format>
#include "FpsComponent.h"
#include "GameObject.h"

FpsComponent::FpsComponent(dae::GameObject* gameObject, dae::TextObject* textObject)
	: Component(gameObject), m_TextObject(textObject)
{
}

void FpsComponent::Update(float deltaTime)
{
	m_FpsTimer += deltaTime;
	m_FrameCount++;
	if (m_FpsTimer >= m_MaxDelay)
	{
		m_CurrentFps = m_FrameCount / m_FpsTimer;

		std::string fpsString{ std::format("{:.1f}",  m_CurrentFps) + " FPS" };
		m_TextObject->SetText(fpsString);

		m_FrameCount = 0;
		m_FpsTimer = 0.0f;
	}
}