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
	//プレイヤー作成。
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
    return true;
}

void Game::Update()
{
   
}
