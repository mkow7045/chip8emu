#ifndef TEXTURE_H
#define TEXTURE_H

#include "Common.h"
#include <string_view>

class Texture
{
public:
	Texture();

	~Texture();

	void free();

	void setBlendMode(SDL_BlendMode Blending);

	void setAlpha(std::int8_t alpha);

	void updateTexture();

	void render(int x, int y, SDL_FRect* clip = nullptr);

	int getWidth() const{ return m_Width; }
	int getHeight() const{ return m_Height; }

private:
	SDL_Texture* m_Texture;
	int m_Width{};
	int m_Height{};
};
#endif