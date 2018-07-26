#include "TextManager.h"

bool TextManager::Initialize(Engine * engine)
{
	engine = m_engine;

	TTF_Init();

	return true;
}

void TextManager::Shutdown()
{
	for (Text* text : m_texts)
	{
		delete text;
	}
	m_texts.clear();

	TTF_Quit();
}

Text * TextManager::CreateText(const std::string& text, const std::string& fontName, int size, const Color & color)
{
	Text* _text = new Text(text, fontName, size, color);
	assert(_text);

	m_texts.push_back(_text);

	return _text;
}

void TextManager::DestroyText(Text * text)
{
	std::vector<Text*>::iterator iter = std::find(m_texts.begin(), m_texts.end(), text);
	if (iter != m_texts.end())
	{
		delete *iter;
		m_texts.erase(iter);
	}

}
