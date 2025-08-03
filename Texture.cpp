#include "Texture.h"
#include "Common.h"

Texture::Texture()
	: m_Width {64}
	, m_Height{32}
{
	m_Texture = SDL_CreateTexture(g_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_Width, m_Height);
	SDL_SetTextureScaleMode(m_Texture, SDL_SCALEMODE_NEAREST);
}


Texture::~Texture()
{
	free();
}

void Texture::free()
{
	if (m_Texture != NULL)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void Texture::updateTexture()
{
    void* pixels{};
    int pitch{};
    if (!SDL_LockTexture(m_Texture, NULL, &pixels, &pitch))
    {
        SDL_Log("Couldn't lock texture. SDL Error:%s\n", SDL_GetError());
        return;
    }

    Uint32* pixel_data = static_cast<Uint32*>(pixels);
    for (int h = 0; h < 32; ++h)
    {
        for (int w = 0; w < 64; ++w)
        {
            int pixel_index = h * (pitch / 4) + w;

            if (g_Display[w][h])
                pixel_data[pixel_index] = 0xFF40FF40FF;
            else
                pixel_data[pixel_index] = 0xFF101010FF;
        }
    }
    SDL_UnlockTexture(m_Texture);
}


void Texture::render(int x, int y, SDL_FRect* clip)
{
	SDL_FRect renderQuad = { (float)x, (float)y, 640, 480 };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderTexture(g_Renderer, m_Texture, clip, &renderQuad);
}
