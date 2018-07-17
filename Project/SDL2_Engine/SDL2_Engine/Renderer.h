#pragma once

#pragma region project include
#include "Vector2.h"
#pragma endregion

#pragma region forward decleration
class SRect;
class CTexture;
class SDL_Window;
class SDL_Renderer;
#pragma endregion

/// <summary>
/// renderer class
/// </summary>
class CRenderer
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pWindow"></param>
	CRenderer(SDL_Window* _pWindow);

	/// <summary>
	/// destructor
	/// </summary>
	~CRenderer();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get sdl renderer
	/// </summary>
	/// <returns>sdl renderer</returns>
	inline SDL_Renderer* GetSDLRenderer() { return m_pRenderer; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// clear current screen
	/// </summary>
	void ClearScreen();

	/// <summary>
	/// render texture
	/// </summary>
	/// <param name="_pTexture">texture</param>
	void RenderTexture(CTexture* _pTexture);

	/// <summary>
	/// render texture
	/// </summary>
	/// <param name="_pTexture">texture</param>
	/// <param name="_destRect">destination rect on screen</param>
	/// <param name="_mirror">mirror value</param>
	/// <param name="_angle">angle of destination rect</param>
	void RenderTexture(CTexture* _pTexture, SRect _destRect, 
		SVector2 _mirror = SVector2(), float _angle = 0.0f);

	/// <summary>
	/// render texture
	/// </summary>
	/// <param name="_pTexture">texture</param>
	/// <param name="_destRect">destination rect on screen</param>
	/// <param name="_srcRect">source rect from image</param>
	/// <param name="_mirror">mirror value</param>
	/// <param name="_angle">angle of destination rect</param>
	void RenderTexture(CTexture* _pTexture, SRect _destRect, SRect _srcRect, 
		SVector2 _mirror = SVector2(), float _angle = 0.0f);

	/// <summary>
	/// present rendered image
	/// </summary>
	void Present();
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// sdl renderer
	/// </summary>
	SDL_Renderer* m_pRenderer = nullptr;
#pragma endregion
};