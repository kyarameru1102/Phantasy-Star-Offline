#include "stdafx.h"
#include "Game.h"


Game::Game()
{

}

Game::~Game()
{
}

bool Game::Start()
{
	//static AnimationClip animationClip[1];
	//animationClip[0].Load("Assets/animData/unityChan/idle.tka");
	//animationClip[0].SetLoopFlag(true);

	////Unity�����̃��f���̏������B
	//m_ladySkinModelRender = NewGO<SkinModelRender>(0, "UnityChan");
	//m_ladySkinModelRender->Init("Assets/modelData/unityChan.tkm", animationClip, 1);
	//m_ladySkinModelRender->PlayAnimation(0, 0.0f);
	//�v���C���[�쐬�B
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
    return true;
}

void Game::Update()
{
   
}
