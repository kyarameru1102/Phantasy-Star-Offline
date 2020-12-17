#include "stdafx.h"
#include "Stage1.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	m_title = NewGO<Title>(0);
	DeleteGO(m_backGround);
	for (int i = 0; i < ENEMY_NUM; i++) {
		DeleteGO(m_drBoar[i]);
	}
}

bool Stage1::Start()
{
	m_backGround = NewGO<BackGround>(0);
	m_drBoar[0] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[1] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[1]->SetPosition({ 200.0f, 0.0f, 100.0f });

	return true;
}

void Stage1::Update()
{
	if (m_downEnemy < 2) {
		m_downEnemy += m_drBoar[0]->GetDeathCount();
		m_downEnemy += m_drBoar[1]->GetDeathCount();
	}
	if (g_pad[0]->IsTrigger(enButtonSelect)) {
		m_game = FindGO<Game>("Game");
		DeleteGO(m_game);
		DeleteGO(this);
	}

	if (m_downEnemy == 2) {
		m_timer++;
		if (m_timer > 150) {
			m_game = FindGO<Game>("Game");
			DeleteGO(m_game);
			DeleteGO(this);
		}
	}
}
