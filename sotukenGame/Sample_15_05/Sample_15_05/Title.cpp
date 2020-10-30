#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	
}

Title::~Title()
{
	DeleteGO(m_ladySkinModelRender);
	DeleteGO(m_bgSkinModelRender);
	DeleteGO(m_spriteRender);
}

bool Title::Start()
{
	//Unityちゃんのモデルの初期化。
	m_ladySkinModelRender = NewGO<SkinModelRender>(0,"UnityChan");
	m_ladySkinModelRender->Init("Assets/modelData/unityChan.tkm");
	//背景モデル初期化。
	m_bgSkinModelRender = NewGO<SkinModelRender>(0, "backGround");
	m_bgSkinModelRender->Init("Assets/modelData/bg.tkm");
	//spriteテスト。
	m_spriteRender = NewGO<SpriteRender>(0, "Sprite");
	m_spriteRender->Init("Assets/image/Title.DDS", 1280.0f, 1000.0f);
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Game>(0, "Game");
		//DeleteGO(this);
	}
	m_spriteRender->SetPosition(m_spritePosition);
}
