#pragma once

#pragma region project include
#include "MoveObject.h"
#include "Macro.h"
#pragma endregion

/// <summary>
/// bullet class
/// </summary>
class GBullet : public CMoveObject
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_position">position</param>
	/// <param name="_direction">direction</param>
	GBullet(SVector2 _position, SVector2 _direction) : CMoveObject(_position)
	{
		m_movement = _direction;
		m_speed = BULLET_SPEED;
		m_colType = ECollisionType::MOVE;
		m_rect.w = BULLET_SIZE;
		m_rect.h = BULLET_SIZE;
		m_pTag = BULLET_TAG;
		m_layer = 2;
	}

	/// <summary>
	/// destructor
	/// </summary>
	~GBullet() {}
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaTime">time since last frame</param>
	void Update(float _deltaTime) override
	{
		CMoveObject::Update(_deltaTime);

		// collide with object
		if (m_pCollideObject)
		{
			// remove bullet
			CEngine::Get()->GetCM()->RemoveObject(this);

			// if collide object is enemy
			if (m_pCollideObject->GetTag() == ENEMY_TAG)
			{
				// remove enemy
				CEngine::Get()->GetCM()->RemoveObject(m_pCollideObject);
			}
		}
	}

	/// <summary>
	/// render every frame
	/// </summary>
	/// <param name="_pRenderer">renderer</param>
	void Render(CRenderer* _pRenderer) override
	{
		CMoveObject::Render(_pRenderer);
	}
#pragma endregion

};