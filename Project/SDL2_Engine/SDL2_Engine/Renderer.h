#pragma once

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
	void RenderTexture(CTexture* _pTexture, SRect _destRect);

	/// <summary>
	/// render texture
	/// </summary>
	/// <param name="_pTexture">texture</param>
	/// <param name="_destRect">destination rect on screen</param>
	/// <param name="_srcRect">source rect from image</param>
	void RenderTexture(CTexture* _pTexture, SRect _destRect, SRect _srcRect);

	/// <summary>
	/// render texture
	/// </summary>
	/// <param name="_pTexture">texture</param>
	/// <param name="_destRect">destination rect on screen</param>
	/// <param name="_srcRect">source rect from image</param>
	/// <param name="_angle">angle of destination rect</param>
	void RenderTexture(CTexture* _pTexture, SRect _destRect, SRect _srcRect, float _angle);

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