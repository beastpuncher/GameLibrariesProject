#pragma once
#include "engine.h"
#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "renderComponent.h"
#include "text.h"
#include "color.h"

class ENGINE_API TextComponent : public IRenderComponent
{
public:
	TextComponent(Entity* owner) : IRenderComponent(owner) {}

	void Create(const std::string& text,const std::string& fontName, int fontSize, const Color& color ,const Vector2D& origin = Vector2D::zero);
	void Destroy();
	void Update();

	void Draw();

	void SetText(const std::string& text);
	void SetColor(const Color& color);

protected:
	Text* m_text = nullptr;
	Vector2D m_origin;
};