#include "textComponent.h"
#include "transform.h"
#include "entity.h"

void TextComponent::Create(const std::string& text, const std::string& fontName, int fontSize, const Color& color, const Vector2D& origin)
{
	m_text = new Text();
	m_text->Create(text, fontName, fontSize, color);
	m_origin = origin;
}

void TextComponent::Destroy()
{
}

void TextComponent::Update()
{
}

void TextComponent::Draw()
{
	Transform transfrom = m_owner->GetTransform();
	m_text->Draw(transfrom.position, m_origin, transfrom.scale, transfrom.rotation);
}

void TextComponent::SetText(const std::string & text)
{
	m_text->SetText(text);
}

void TextComponent::SetColor(const Color& color)
{
	m_text->SetColor(color);
}
