#pragma region project include
#include "MainScene.h"
#include "Game.h"
#include "World.h"
#include "ContentManagement.h"
#include "TextFPS.h"
#include "Helper.h"
#include "Music.h"
#include "Config.h"
#pragma endregion

#pragma region public override function
// initialize scene
void GMainScene::Init()
{
	// create world
	m_pWorld = new GWorld();
	m_pWorld->Init(GetAssetPath("Texture/World/T_Level01.bmp", 4).c_str());

	// create fps text
	GTextFPS* pText = new GTextFPS("FPS: 0", GGame::Get()->m_PArialFont, SRect(GConfig::s_ScreenWidth / 2 - 50, 0, 100, 50));

	// add fps text to list
	CEngine::Get()->GetCM()->AddUIObject(pText);

	// create background music
	m_pBackgroundMusic = new CMusic(GetAssetPath("Audio/S_Background.wav", 4).c_str());

	// play music
	m_pBackgroundMusic->Play(true);
}

// cleaning up scene
void GMainScene::Clean()
{
	// delete world
	delete m_pWorld;

	// delete music
	delete m_pBackgroundMusic;

	// clean all objects
	CEngine::Get()->GetCM()->CleanScene();
	CEngine::Get()->GetCM()->CleanUI();
	CEngine::Get()->GetCM()->CleanPersistantObjects();
}
#pragma endregion