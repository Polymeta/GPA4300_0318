#pragma region project include
#include "MainScene.h"
#include "Player.h"
#include "ContentManagement.h"
#pragma endregion

#pragma region public override function
// initialize scene
void GMainScene::Init()
{
	// create textured object
	GPlayer* pObj = new GPlayer(SVector2(100, 45), SVector2(68, 92),
		CEngine::Get()->GetRenderer(), "Texture/Character/Player/T_Samus_Idle.png");

	pObj->SetSpeed(1.0f);

	// add object to cm
	CEngine::Get()->GetCM()->AddPersistantObject(pObj);
}

// cleaning up scene
void GMainScene::Clean()
{

}
#pragma endregion