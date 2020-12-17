#include "stdafx.h"
#include "Stage3.h"
#include "BackGround.h"
#include "BossBoar.h"

Stage3::Stage3()
{
}

Stage3::~Stage3()
{
	DeleteGO(m_backGround);
	DeleteGO(m_bossBoar);
}

bool Stage3::Start()
{
	m_backGround = NewGO<BackGround>(0);
	m_bossBoar = NewGO<BossBoar>(0,"drBoar");
	m_bossBoar->SetPosition({ 1000.0f, 0.0f, -500.0f });
    return true;
}

void Stage3::Update()
{
	if (m_downEnemy == 1)
	{
		m_timer++;
		if (m_timer > 150) {
			m_sceanChangeOK = true;
		}
	}

	if (m_bossBoar != nullptr) {
		if (m_bossBoar->GetDeath()) {
			m_downEnemy++;
			m_bossBoar = nullptr;
		}
	}

}
