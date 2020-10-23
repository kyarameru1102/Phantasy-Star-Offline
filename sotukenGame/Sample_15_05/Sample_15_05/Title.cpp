#include "stdafx.h"
#include "Title.h"

Title::Title()
{
	
}

Title::~Title()
{
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
	m_spriteRender->Init("Assets/image/sample_01.dds", 100.0f, 100.0f);
	return true;
}

void Title::Update()
{
	if (m_ok) {
		m_spritePosition.x += 1.0f;
	}
	else {
		m_spritePosition.x -= 1.0f;
	}
	if (m_spritePosition.x >= 600.0f) {
		m_ok = false;
	}
	if (m_spritePosition.x <= -600.0f) {
		m_ok = true;
	}
	addRot += 1.0f;
	m_rot.SetRotationDegZ(addRot);
	m_spriteRender->SetRotation(m_rot);
	m_spriteRender->SetPosition(m_spritePosition);
}
