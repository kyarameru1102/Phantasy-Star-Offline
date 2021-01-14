#include "stdafx.h"
#include "PlayerStatus.h"

PlayerStatus::PlayerStatus()
{
}

PlayerStatus::~PlayerStatus()
{
	DeleteGO(m_spriteRender);
}

bool PlayerStatus::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/image/PlayerStatusUI.DDS", 400, 304);
	m_spriteRender->SetPosition({ -250.0f, 50.0f, 0.0f });

	m_player = FindGO<Player>("player");

	return true;
}

void PlayerStatus::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart)) {
		DeleteGO(this);
	}
}