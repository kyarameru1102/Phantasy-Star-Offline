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
	DeleteGO(m_bg);
	DeleteGO(m_playerStatusUI);
	QueryGOs<DrBoar>("drBoar", [](DrBoar * drBoar)->bool
	{
		DeleteGO(drBoar);
		return true;
	});
}

bool Game::Start()
{
	//プレイヤー作成。
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
	m_bg = NewGO<BackGround>(0, "backGround");
	m_drBoar[0] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[0]->SetPosition({ 300.0f, 0.0f, -100.0f });
	m_drBoar[1] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[1]->SetPosition({ 300.0f, 0.0f, 100.0f });
	m_drBoar[2] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[2]->SetPosition({ -300.0f, 0.0f, -100.0f });
	
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
