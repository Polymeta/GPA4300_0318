#pragma region system include
#include <iostream>
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Engine.h"
#include "MainScene.h"
#include "Renderer.h"
#include "Texture.h"	/// TODO: DELETE
#include "Rect.h"		/// TODO: DELETE
#pragma endregion

#pragma region constructor
CEngine::CEngine()
{
}

CEngine::~CEngine()
{
}
#pragma endregion

#pragma region public function
// initialize sdl
bool CEngine::Init()
{
	// initialize sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// error message
		LOG_ERROR("SDL not initialized!", SDL_GetError());

		return false;
	}

	// sdl initialized
	else
	{
		// create window
		m_pWindow = SDL_CreateWindow(
			"Natural Engine",			// name of window
			SDL_WINDOWPOS_CENTERED,		// position x of screen
			SDL_WINDOWPOS_CENTERED,		// position y of screen
			SCREEN_WIDTH,				// width
			SCREEN_HEIGHT,				// height
			SDL_WINDOW_SHOWN);			// flags

		// if window not created
		if (!m_pWindow)
		{
			// error message
			LOG_ERROR("Window could not be created!", SDL_GetError());

			return false;
		}

		// get surface from window
		m_pSurface = SDL_GetWindowSurface(m_pWindow);

		// if surface not created
		if (!m_pSurface)
		{
			// error message
			LOG_ERROR("Surface could not be created!", SDL_GetError());

			return false;
		}

		// initialize renderer
		m_pRenderer = new CRenderer(m_pWindow);

		// if renderer not created
		if (!m_pRenderer)
		{
			// error message
			LOG_ERROR("Renderer could not be created!", SDL_GetError());

			return false;
		}

		// engine is running
		m_isRunning = true;

		return true;
	}
}

// load content
bool CEngine::Load()
{
	// change scene to new scene
	ChangeScene(new GMainScene(this));

	return true;
}

// running engine
void CEngine::Run()
{
	// as long as engine running
	while (m_isRunning)
	{
		Update();

		Render();
	}
}

// cleaning up
void CEngine::Clean()
{
	// clean current scene
	if (m_pScene)
		m_pScene->Clean();

	// delete scene
	delete m_pScene;

	// delete renderer
	delete m_pRenderer;

	// free sdl components
	SDL_FreeSurface(m_pSurface);
	SDL_DestroyWindow(m_pWindow);
}

// change active scene
void CEngine::ChangeScene(CScene * _pScene)
{
	// if new scene nullptr return
	if (!_pScene)
		return;

	// if old scene valid
	if (m_pScene)
	{
		// clean and delete scene
		m_pScene->Clean();
		delete m_pScene;
	}

	// set new scene
	m_pScene = _pScene;

	// initialize new scene
	m_pScene->Init(m_pRenderer->GetSDLRenderer());
}
#pragma endregion

#pragma region private function
// update every frame
void CEngine::Update()
{

}

// render every frame
void CEngine::Render()
{
	// clear current screen
	m_pRenderer->ClearScreen();

	/// <summary>
	/// TODO: DELETE
	/// </summary>
	for (int i = 0; i < 4; i++)
	{
		CTexture texture = CTexture("PP.png", m_pRenderer);
		m_pRenderer->RenderTexture(&texture, SRect(i * 150, i * 50, 640, 360));
	}

	// present rendered image
	m_pRenderer->Present();
}
#pragma endregion