#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	
}

Title::~Title()
{
	//DeleteGO(m_ladySkinModelRender);
	//DeleteGO(m_bgSkinModelRender);
	//DeleteGO(m_spriteRender);
}

bool Title::Start()
{
	AnimationClip animationClip[1];
	animationClip[0].Load("Assets/animData/unityChan/idle.tka");
	animationClip[0].SetLoopFlag(true);

	
	//Unity�����̃��f���̏������B
	m_ladySkinModelRender = NewGO<SkinModelRender>(0,"UnityChan");
	m_ladySkinModelRender->Init("Assets/modelData/unityChan.tkm",animationClip,1);
	
	//�w�i���f���������B
	//m_bgSkinModelRender = NewGO<SkinModelRender>(0, "backGround");
	//m_bgSkinModelRender->Init("Assets/modelData/bg.tkm");
	//sprite�e�X�g�B
	//m_spriteRender = NewGO<SpriteRender>(0, "Sprite");
	//m_spriteRender->Init("Assets/image/Title.DDS", 1280.0f, 1000.0f);
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
	//m_ladySkinModelRender->PlayAnimation(0, 0.0f);
	//m_spriteRender->SetPosition(m_spritePosition);
}
