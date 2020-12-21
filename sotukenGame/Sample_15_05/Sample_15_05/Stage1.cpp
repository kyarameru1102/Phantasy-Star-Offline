#include "stdafx.h"
#include "Stage1.h"
#include "DrBoar.h"
#include "BackGround.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
	DeleteGO(m_backGround);
	QueryGOs<DrBoar>("drBoar", [](DrBoar* drBoar)->bool
	{
		DeleteGO(drBoar);
		return true;
	});
}

bool Stage1::Start()
{
	m_backGround = NewGO<BackGround>(0);
	m_drBoar[0] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[0]->SetPosition({ 400.0f, 0.0f, -200.0f });
	m_drBoar[1] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[1]->SetPosition({ 300.0f, 0.0f, 200.0f });
	m_drBoar[2] = NewGO<DrBoar>(0, "drBoar");
	m_drBoar[2]->SetPosition({ -300.0f, 0.0f, -200.0f });
	return true;
}

void Stage1::Update()
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

