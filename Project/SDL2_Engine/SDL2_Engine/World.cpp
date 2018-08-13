#pragma region system include
#include <string>
#pragma endregion

#pragma region project include
#include "World.h"
#include "Macro.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "Texture.h"
#include "Player.h"
#include "MoveEnemy.h"
#include "Sound.h"
#include "Helper.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#include <SDL.h>

#pragma region public function
// initialize world
void GWorld::Init(const char* _pFileName)
{
	SDL_Surface* pLevel = SDL_LoadBMP(_pFileName);

	char* pPixels = (char*)(pLevel->pixels);

	// string to define world
	/*string world;

	// add lines to world string
	// string 100x20
	// 1 block is 64 x 64 pixel
	// screen has 20 (width) and 12 (height) blocks
	// X = dirt (outside)
	// 0 = black (free, background)
	// W = way (walk on)
	// L = lava (death)
	// S = start point of player
	// E = move enemy
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000XXXXXX\n";
	world += "XXXXXX0000000000000000000000000000000000000000WWW0000000000WWWWWW00000000000000000000000000000XXXXXX\n";
	world += "XXXXXX00000000000000000000WWWW000000000000000000000000E0000000000000000000000000000000E00WWWWWXXXXXX\n";
	world += "XXXXXX00000000000000E000000000000000000000000000000WWWWWW0000000000000000000000E000WWWWWWWXXXXXXXXXX\n";
	world += "XXXXXX0000000000WWWWWWWW000000000000000000E00WWWWWWWXXXXWWWW000E000000000000WWWWWWWWXXXXXXXXXXXXXXXX\n";
	world += "XXXXXX00S000WWWWWXXXXXXWWWWWWWWLLWWWLLWWWWWWWWXXXXXXXXXXXXXWWWWWWWLWWWLLWWWWWXXXXXXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";*/

	// width and height of world
	int width = 0, height = 0;

	// name of world texture
	string texName = "World";

	// through world string
	for (int i = 0; i < pLevel->w * pLevel->h; i++)
	{
		// name of world texture
		texName = "World";

		// increase width
		width++;

		// if end of line increase height and reset width
		if (i % pLevel->w == 0)
		{
			height++;
			width = 0;
			//continue;
		}

		// create textured object
		CTexturedObject* pObj = new CTexturedObject(
			SVector2((width - 1) * WORLD_BLOCK_WIDTH, (height - 1) * WORLD_BLOCK_HEIGHT),
			SVector2(WORLD_BLOCK_WIDTH, WORLD_BLOCK_HEIGHT)
		);

		// set texture name of object
		pObj->SetTextureName(texName.c_str());

		// if texture not exists
		if (CEngine::Get()->GetTM()->GetTexture(texName) == nullptr)
		{
			// create new texture
			CTexture* pTexture = new CTexture("Texture/World/T_WorldSide.png", CEngine::Get()->GetRenderer());

			// add texture to tm
			CEngine::Get()->GetTM()->AddTexture(texName, pTexture);

			// set texture of object
			pObj->SetTexture(pTexture);

			SDL_Delay(500);
		}

		// if texture exists set texture of object
		else
		{
			pObj->SetTexture(CEngine::Get()->GetTM()->GetTexture(texName));
		}

		// x position of texture in atlas map
		int xPosOfTexture = 0;

		// get pixel colors
		unsigned char b = pPixels[0];
		unsigned char g = pPixels[1];
		unsigned char r = pPixels[2];

		// 0 = black (free, background) => r=0
		// X = dirt(outside)			=> r=64
		// W = way (walk on)			=> r=128
		// L = lava (death)				=> r=255
		// S = start point of player	=> b=255
		// E = move enemy				=> g=255 (MoveEnemy)
		char value;

		if (r == 0 && g == 0 && b == 0)
			value = '0';
		else if (r == 64 && g == 0 && b == 0)
			value = 'X';
		else if (r == 128 && g == 0 && b == 0)
			value = 'W';
		else if (r == 255 && g == 0 && b == 0)
			value = 'L';
		else if (g == 255)
			value = 'E';
		else if (b == 255)
			value = 'S';

		pPixels += 3;

		// switch char in world string
		switch (value)
		{
		// if dirt set position of texture in atlas map
		case 'X':
		{
			xPosOfTexture = WORLD_BLOCK_ATLAS_WIDTH;

			// set collision type to wall
			pObj->SetColType(ECollisionType::WALL);
			break;
		}

		// if way set position of texture in atlas map
		case 'W':
		{
			xPosOfTexture = 2 * WORLD_BLOCK_ATLAS_WIDTH;
			
			// set collision type to wall
			pObj->SetColType(ECollisionType::WALL);
			break;
		}

		// if lava set position of texture in atlas map
		case 'L':
		{
			xPosOfTexture = 3 * WORLD_BLOCK_ATLAS_WIDTH;
			
			// set collision type to wall
			pObj->SetColType(ECollisionType::WALL);
			break;
		}

		case 'S':
		{
			// create textured object
			GPlayer * pPlayer = new GPlayer(
				SVector2((width - 1) * WORLD_BLOCK_WIDTH, (height - 1) * WORLD_BLOCK_HEIGHT - PLAYER_HEIGHT), 
				SVector2(PLAYER_WIDTH, PLAYER_HEIGHT)
			);

			// set player values
			pPlayer->SetSpeed(PLAYER_SPEED);
			pPlayer->SetMirror(PLAYER_MIRROR);
			pPlayer->SetColType(ECollisionType::MOVE);
			pPlayer->ActivateGravity();

			// set texture name
			texName = "Player";

			// set texture name of object
			pPlayer->SetTextureName(texName.c_str());

			// if texture not exists
			if (CEngine::Get()->GetTM()->GetTexture(texName) == nullptr)
			{
				// create new texture
				CTexture* pTexture = new CTexture("Texture/Character/Player/T_Samus.png", CEngine::Get()->GetRenderer());

				// add texture to tm
				CEngine::Get()->GetTM()->AddTexture(texName, pTexture);

				// set texture of object
				pPlayer->SetTexture(pTexture);

				SDL_Delay(500);

				// initialize player
				pPlayer->Init();

				// create shot sound
				CSound* pSound = new CSound(GetAssetPath("Audio/S_Shot.wav", 4).c_str());

				// set shot sound of player
				pPlayer->SetShotSound(pSound);
			}

			// if texture exists set texture of object
			else
			{
				pPlayer->SetTexture(CEngine::Get()->GetTM()->GetTexture(texName));
			}

			// add player to persistant list
			CEngine::Get()->GetCM()->AddPersistantObject(pPlayer);
			break;
		}

		case 'E':
		{
			// create move enemy
			GMoveEnemy * pEnemy = new GMoveEnemy(
				SVector2((width - 1) * WORLD_BLOCK_WIDTH, (height - 1) * WORLD_BLOCK_HEIGHT - MOVE_ENEMY_HEIGHT),
				SVector2()
			);

			// initialize enemy
			pEnemy->Init();

			// set texture name
			texName = "MoveEnemy";

			// set texture name of object
			pEnemy->SetTextureName(texName.c_str());

			// if texture not exists
			if (CEngine::Get()->GetTM()->GetTexture(texName) == nullptr)
			{
				// create new texture
				CTexture* pTexture = new CTexture("Texture/Character/Enemy/T_MoveEnemy_Idle.png", CEngine::Get()->GetRenderer());

				// add texture to tm
				CEngine::Get()->GetTM()->AddTexture(texName, pTexture);

				// set texture of object
				pEnemy->SetTexture(pTexture);

				SDL_Delay(500);
			}

			// if texture exists set texture of object
			else
			{
				pEnemy->SetTexture(CEngine::Get()->GetTM()->GetTexture(texName));
			}

			pEnemy->SetLayer(1);

			// add player to persistant list
			CEngine::Get()->GetCM()->AddSceneObject(pEnemy);

			break;
		}

		default:
			break;
		}

		// set source rect of object
		pObj->SetSrcRect(SRect(xPosOfTexture, 0, WORLD_BLOCK_ATLAS_WIDTH, WORLD_BLOCK_ATLAS_HEIGHT));

		// add object to scene list
		CEngine::Get()->GetCM()->AddSceneObject(pObj);
	}

	// check all collision for scene objects
	for (CObject* pObj : CEngine::Get()->GetCM()->GetSceneObjects())
	{
		if (dynamic_cast<CMoveObject*>(pObj))
			((CMoveObject*)pObj)->CheckCollisionObjects();
	}

	// check all collision for persistant objects
	for (CObject* pObj : CEngine::Get()->GetCM()->GetPersistantObjects())
	{
		if (dynamic_cast<CMoveObject*>(pObj))
			((CMoveObject*)pObj)->CheckCollisionObjects();
	}

	SaveStringToFile("Hello World", "Save.txt");
}
#pragma endregion