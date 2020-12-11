#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "PlayerStatusUI.h"

Title::Title()
{
	
}

Title::~Title()
{
	//DeleteGO(m_ladySkinModelRender);
	//DeleteGO(m_bgSkinModelRender);
	DeleteGO(m_spriteRender);
	//DeleteGO(m_playerStatusUI);
}

bool Title::Start()
{
	//背景モデル初期化。
	//m_bgSkinModelRender = NewGO<SkinModelRender>(0, "backGround");
	//m_bgSkinModelRender->Init("Assets/modelData/bg.tkm");
	//spriteテスト。
	m_spriteRender = NewGO<SpriteRender>(0, "Sprite");
	m_spriteRender->Init("Assets/image/Title_tes.DDS", 780.0f, 1280.0f);

	//m_playerStatusUI = NewGO<PlayerStatusUI>(0);

	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}

	m_spriteRender->SetPosition(m_spritePosition);
}
