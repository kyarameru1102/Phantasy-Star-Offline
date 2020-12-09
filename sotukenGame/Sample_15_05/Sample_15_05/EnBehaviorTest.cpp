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
	//敵テスト作成
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
	//m_entest[0] = NewGO<EnTest>(0, "EnTest0");
	//m_entest[1] = NewGO<EnTest>(0, "EnTest1");
	m_drboar[0] = NewGO<DrBoar>(0, "DrBoar0");
	m_drboar[1] = NewGO<DrBoar>(0, "DrBoar1");
	//m_drboar[2] = NewGO<DrBoar>(0, "DrBoar2");
	//m_drboar[3] = NewGO<DrBoar>(0, "DrBoar3");
	m_bg = NewGO<BackGround>(0, "backGround");
	m_playerStatusUI = NewGO<PlayerStatusUI>(0);
	return true;
}

void EnBehaviorTest::Update()
{
	
}