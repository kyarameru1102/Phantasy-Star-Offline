#include "stdafx.h"
#include "EnBehaviorTest.h"
#include "PlayerStatusUI.h"

EnBehaviorTest::EnBehaviorTest()
{
}

EnBehaviorTest::~EnBehaviorTest()
{
}

bool EnBehaviorTest::Start()
{
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
	m_bg = NewGO<BackGround>(0, "backGround");
	/*m_drBoar[0] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[0]->SetPosition({ 300.0f, 0.0f, -100.0f });
	m_drBoar[1] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[1]->SetPosition({ 300.0f, 0.0f, 100.0f });
	m_drBoar[2] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[2]->SetPosition({ -300.0f, 0.0f, -100.0f });*/
	m_boss = NewGO<BossBoar>(0, "drBoar");
	m_boss->SetPosition({ 1000.0f, 0.0f, -500.0f });

	return true;
}

void EnBehaviorTest::Update()
{
	
}