#pragma region system include
#include <SDL.h>
#include <SDL_image.h>
#pragma endregion

#pragma region project include
#include "Renderer.h"
#include "Rect.h"
#include "Texture.h"
#include "Engine.h"
#pragma endregion

#pragma region constructor
// constructor
CRenderer::CRenderer(SDL_Window * _pWindow)
{
	// create renderer
	m_pRenderer = SDL_CreateRenderer(
		_pWindow,												// window to render to
		1,														// renderer index
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	// flags
		);
}
#pragma endregion

// destructor
CRenderer::~CRenderer()
{
	// destroy renderer
	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);
}

#pragma region public function
// clear current screen
void CRenderer::ClearScreen()
{
	SDL_RenderClear(m_pRenderer);
}

void CRenderer::RenderTexture(CTexture * _pTexture)
{
	// destination rect
	SRect rect;

	// get width and height of texture
	SDL_QueryTexture(_pTexture->GetSDLTexture(), nullptr, nullptr, &rect.w, &rect.h);

	// render texture
	RenderTexture(_pTexture, SRect(SCREEN_WIDTH, SCREEN_HEIGHT), rect);
}

void CRenderer::RenderTexture(CTexture * _pTexture, SRect _destRect)
{
	// destination rect
	SRect rect;

	// get width and height of texture
	SDL_QueryTexture(_pTexture->GetSDLTexture(), nullptr, nullptr, &rect.w, &rect.h);

	// render texture
	RenderTexture(_pTexture, _destRect, rect);
}

void CRenderer::RenderTexture(CTexture * _pTexture, SRect _destRect, SRect _srcRect)
{
	// render texture
	RenderTexture(_pTexture, _destRect, _srcRect, 0.0f);
}

void CRenderer::RenderTexture(CTexture * _pTexture, SRect _destRect, SRect _srcRect, float _angle)
{
	// create rotation point
	SDL_Point rotationPoint;
	rotationPoint.x = _destRect.w / 2;
	rotationPoint.y = _destRect.h / 2;

	// render texture with angle
	SDL_RenderCopyEx(
		m_pRenderer,					// sdl renderer
		_pTexture->GetSDLTexture(),		// sdl texture
		&_srcRect,						// source rect
		&_destRect,						// destination rect
		_angle,							// angle of image
		&rotationPoint,					// rotation center
		SDL_RendererFlip::SDL_FLIP_NONE	// flags
		);
}

// present rendered image
void CRenderer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}
#pragma endregion