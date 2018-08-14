#include <iostream>	///TODO: DELETE
#include <string>	///TODO: DELETE

#pragma region project include
#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "Texture.h"
#include "Physic.h"
#include "Renderer.h"
#include "Bullet.h"
#include "MenuScene.h"
#include "Sound.h"
#include "Animation.h"
#include "Time.h"	///TODO: DELETE
#pragma endregion

#pragma region public override function
// update every frame
void GPlayer::Update(float _deltaTime)
{
	// movement left
	if (CInput::GetKey(SDL_SCANCODE_A))
	{
		// set movement, forward and mirror
		m_movement.X = -1.0f;
		m_mirror.X = 1.0f;
		m_forward.X = -1.0f;
		m_pCurrentAnim = m_pRunAnim;
	}

	// movement right
	else if (CInput::GetKey(SDL_SCANCODE_D))
	{
		// set movemenet, forward and mirror
		m_movement.X = 1.0f;
		m_mirror.X = 0.0f;
		m_forward.X = 1.0f;
		m_pCurrentAnim = m_pRunAnim;
	}

	// no movement left or right
	else
	{
		m_movement.X = 0.0f;
		m_pCurrentAnim = m_pIdleAnim;
	}

	// update animation
	m_pCurrentAnim->Update(_deltaTime);

	// set source from animation
	m_srcRect = SRect(
		m_pCurrentAnim->GetCurrentTexturePosition().X,
		m_pCurrentAnim->GetCurrentTexturePosition().Y,
		m_pCurrentAnim->GetSize().X,
		m_pCurrentAnim->GetSize().Y
	);

	// if key space is pressed this frame and jump not active and grounded
	if (CInput::GetKeyDown(SDL_SCANCODE_SPACE) && !m_jump && m_grounded)
	{
		// set jump enable, gravity false and set jump time
		m_jump = true;
		m_jumpTime = PLAYER_JUMP_TIME;
		m_gravity = false;
	}

	// if key enter is pressed this frame spawn bullet
	if (CInput::GetKeyDown(SDL_SCANCODE_RETURN))
	{
		// spawn bullet
		GBullet* pBullet = new GBullet(m_position, m_forward);
		pBullet->AddPosition(SVector2(m_forward.X * PLAYER_WIDTH + 1, 48.0f));

		// set texture name of object
		pBullet->SetTextureName("Bullet");

		// if texture not exists
		if (CEngine::Get()->GetTM()->GetTexture("Bullet") == nullptr)
		{
			// create new texture
			CTexture* pTexture = new CTexture("Texture/Bullet/T_Bullet.png", CEngine::Get()->GetRenderer());

			// add texture to tm
			CEngine::Get()->GetTM()->AddTexture("Bullet", pTexture);

			// set texture of object
			pBullet->SetTexture(pTexture);
		}

		// if texture exists set texture of object
		else
		{
			pBullet->SetTexture(CEngine::Get()->GetTM()->GetTexture("Bullet"));
		}

		// add to list
		CEngine::Get()->GetCM()->AddPersistantObject(pBullet);

		// play shot sound
		m_pShotSound->Play();
	}

	// update parent
	CMoveObject::Update(_deltaTime);

	// if jump enabled
	if(m_jump)
	{
		// decrease jump time
		m_jumpTime -= _deltaTime;

		// if jump time under 0
		if (m_jumpTime <= 0.0f)
		{
			// deactivate jump and activate gravity
			m_jump = false;
			m_gravity = true;
		}

		// moveable default true
		bool moveable = true;

		// next position
		SVector2 nextPos = m_position;
		nextPos.Y -= PLAYER_JUMP_FORCE * _deltaTime;

		// next rect
		SRect nextRect = m_rect;
		nextRect.x = nextPos.X;
		nextRect.y = nextPos.Y;

		// through all collision objects
		for (CObject* pObj : m_pCollisionObjects)
		{
			// if current object is self continue
			if ((CMoveObject*)pObj && pObj == this)
				continue;

			// if collision type none
			if (((CTexturedObject*)pObj)->GetColType() == ECollisionType::NONE)
				continue;

			// set moveable by checking collision
			moveable = !CPhysic::RectRectCollision(nextRect, ((CTexturedObject*)pObj)->GetRect());

			// if not moveable cancel collision check
			if (!moveable)
				break;
		}

		// if still moveable set y position
		if (moveable)
		{
			m_position.Y -= PLAYER_JUMP_FORCE * _deltaTime;
			m_rect.y = m_position.Y;
		}
	}

	// set position of camera
	CEngine::Get()->GetRenderer()->SetCamera(
		SVector2(m_position.X + PLAYER_WIDTH / 2, m_position.Y + PLAYER_HEIGHT / 2)
	);

	// collide with object
	if (m_pCollideObject)
	{
		// if collide object is enemy
		if (m_pCollideObject->GetTag() == ENEMY_TAG)
		{
			// back to main menu
			CEngine::Get()->ChangeScene(new GMenuScene());
		}
	}

	/// <summary>
	/// TODO: DELETE
	/// </summary>
	// print player position
	std::string s = "Position Y: ";
	s += std::to_string(m_position.Y);
	LOG_ERROR("", s.c_str());
}

// render every frame
void GPlayer::Render(CRenderer * _pRenderer)
{
	CMoveObject::Render(_pRenderer);
}
#pragma endregion

#pragma region public function
// initialize player
void GPlayer::Init()
{
	// create idle animation
	m_pIdleAnim = new CAnimation(SVector2(0.0f, PLAYER_SRC_RECT_HEIGHT), 
		SVector2(PLAYER_SRC_RECT_WIDTH, PLAYER_SRC_RECT_HEIGHT), 1);

	// create run animation
	m_pRunAnim = new CAnimation(SVector2(), SVector2(PLAYER_SRC_RECT_WIDTH, PLAYER_SRC_RECT_HEIGHT), 10);
	m_pRunAnim->SetAnimationTime(0.5f);

	// set idle to current animation
	m_pCurrentAnim = m_pIdleAnim;
}
#pragma endregion