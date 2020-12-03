#include "stdafx.h"
#include "Game.h"
#include "PlayerStatusUI.h"
#include "Menu.h"

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_gameCam);
	//DeleteGO(m_bg);
	DeleteGO(m_playerStatusUI);

}

bool Game::Start()
{
	//プレイヤー作成。
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
	m_bg = NewGO<BackGround>(0, "backGround");
	m_playerStatusUI = NewGO<PlayerStatusUI>(0);
	m_drBoar = NewGO<DrBoar>(0, "drBoar");
    return true;
}

void Game::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart) && m_menu != nullptr) {
		DeleteGO(m_menu);
		m_menu = nullptr;
	}
	else if (g_pad[0]->IsTrigger(enButtonStart) && m_menu == nullptr) {
		m_menu = NewGO<Menu>(0);
    }
	
}
