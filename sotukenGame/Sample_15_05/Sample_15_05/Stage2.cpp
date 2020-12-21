#include "stdafx.h"
#include "Stage2.h"
#include "DrBoar.h"
#include "BackGround.h"

Stage2::Stage2()
{
}

Stage2::~Stage2()
{
	DeleteGO(m_backGround);
	QueryGOs<DrBoar>("drBoar2", [](DrBoar* drBoar)->bool
	{
		DeleteGO(drBoar);
		return true;
	});
}

bool Stage2::Start()
{
	m_backGround = NewGO<BackGround>(0);
	m_drBoar[0] = NewGO<DrBoar>(0, "drBoar2");
	m_drBoar[0]->SetPosition({ 300.0f, 0.0f, -100.0f });
	m_drBoar[1] = NewGO<DrBoar>(0, "drBoar2");
	m_drBoar[1]->SetPosition({ -300.0f, 0.0f, 100.0f });
	return true;
}

void Stage2::Update()
{
	if (m_downEnemy == ENEMY_NUM)
	{
		m_timer++;
		if (m_timer > 150) {
			m_sceanChangeOK = true;
		}
	}

	for (int i = 0; i < ENEMY_NUM; i++) {
		if (m_drBoar[i] != nullptr) {
			if (m_drBoar[i]->GetDeath()) {
				m_downEnemy++;
				m_drBoar[i] = nullptr;
			}
		}
	}
}
