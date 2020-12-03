#include "stdafx.h"
#include "EnBehaviorTest.h"

EnBehaviorTest::EnBehaviorTest()
{
}

EnBehaviorTest::~EnBehaviorTest()
{
}

bool EnBehaviorTest::Start()
{
	//“GƒeƒXƒgì¬
	m_player = NewGO<Player>(0, "player");
	m_gameCam = NewGO<GameCamera>(0, "gameCamera");
	m_entest = NewGO<EnTest>(0, "EnTest");
	//m_drboar = NewGO<DrBoar>(0, "DrBoar");
	m_bg = NewGO<BackGround>(0, "backGround");
	return true;
}

void EnBehaviorTest::Update()
{
	
}