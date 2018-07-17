#pragma region project include
#include "MoveObject.h"
#pragma endregion

#pragma region public override function
// update every frame
void CMoveObject::Update()
{
	// add position by movement * speed
	m_position = m_position + m_movement * m_speed;

	// update parent
	CTexturedObject::Update();
}

// render every frame
void CMoveObject::Render(CRenderer * _pRenderer)
{
	CTexturedObject::Render(_pRenderer);
}
#pragma endregion