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

void CRenderer::RenderTexture(CTexture * _pTexture, SRect _destRect, SVector2 _mirror,
	float _angle)
{
	// destination rect
	SRect rect;

	// get width and height of texture
	SDL_QueryTexture(_pTexture->GetSDLTexture(), nullptr, nullptr, &rect.w, &rect.h);

	// render texture
	RenderTexture(_pTexture, _destRect, rect, _mirror, _angle);
}

void CRenderer::RenderTexture(CTexture * _pTexture, SRect _destRect, SRect _srcRect, 
	SVector2 _mirror, float _angle)
{
	// create rotation point
	SDL_Point rotationPoint;
	rotationPoint.x = _destRect.w / 2;
	rotationPoint.y = _destRect.h / 2;

	// flip enum
	SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;
	
	// flip horizontal if mirror x != 0
	if (_mirror.X != 0)
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

	// flip vertical if mirror y != 0 and x == 0
	else if (_mirror.X == 0 && _mirror.Y != 0)
		flip = SDL_RendererFlip::SDL_FLIP_VERTICAL;

	// render texture with angle
	SDL_RenderCopyEx(
		m_pRenderer,					// sdl renderer
		_pTexture->GetSDLTexture(),		// sdl texture
		&_srcRect,						// source rect
		&_destRect,						// destination rect
		_angle,							// angle of image
		&rotationPoint,					// rotation center
		flip							// flags
		);
}

// present rendered image
void CRenderer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}
#pragma endregion