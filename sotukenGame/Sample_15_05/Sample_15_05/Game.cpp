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
	//�v���C���[�쐬�B
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
    return true;
}

void Game::Update()
{
   
}
