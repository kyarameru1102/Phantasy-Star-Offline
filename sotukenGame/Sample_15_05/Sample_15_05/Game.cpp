#include "stdafx.h"
#include "Game.h"
#include "PlayerStatusUI.h"

Game::Game()
{

}

Game::~Game()
{
}

bool Game::Start()
{
	//プレイヤー作成。
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
	m_bg = NewGO<BackGround>(0, "backGround");
	m_playerStatusUI = NewGO<PlayerStatusUI>(0);
    return true;
}

void Game::Update()
{
   
}
