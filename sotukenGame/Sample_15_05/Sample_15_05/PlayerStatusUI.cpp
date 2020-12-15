#include "stdafx.h"
#include "PlayerStatusUI.h"

const float PLAYER_MAX_HP = 100.0f;  //プレイヤーの最大HP。

PlayerStatusUI::PlayerStatusUI()
{
}

PlayerStatusUI::~PlayerStatusUI()
{
	DeleteGO(m_statusSprite);
	DeleteGO(m_hpSprite);
	DeleteGO(m_ppSprite);
	DeleteGO(m_hpBerSprite);
	DeleteGO(m_ppBerSprite);
}

bool PlayerStatusUI::Start()
{
	//画像の初期化。
	m_statusSprite = NewGO<SpriteRender>(0);
	m_statusSprite->Init("Assets/image/status.DDS", 151.0f, 404.0f);

	m_hpBerSprite = NewGO<SpriteRender>(1);
	m_hpBerSprite->Init("Assets/image/hp_pp_ber.DDS", 26.0f, 266.0f);

	m_ppBerSprite = NewGO<SpriteRender>(1);
	m_ppBerSprite->Init("Assets/image/hp_pp_ber.DDS", 26.0f, 266.0f);

	m_hpSprite = NewGO<SpriteRender>(1, "Sprite");
	m_hpSprite->Init("Assets/image/hp.DDS", 20.0f, 260.0f);

	m_ppSprite = NewGO<SpriteRender>(1);
	m_ppSprite->Init("Assets/image/pp.DDS", 20.0f, 260.0f);

	//画像のピボットを設定。
	m_spritePivot[en_playerUIHP] = { 1.0f, 1.0f };
	m_hpSprite->SetPivot(m_spritePivot[en_playerUIHP]);

	m_spritePivot[en_playerUIPP] = { 1.0f, 1.0f };
	m_ppSprite->SetPivot(m_spritePivot[en_playerUIPP]);

	m_spritePivot[en_playerUIHPBer] = { 1.0f, 1.0f };
	m_hpBerSprite->SetPivot(m_spritePivot[en_playerUIHPBer]);

	m_spritePivot[en_playerUIPPBer] = { 1.0f, 1.0f };
	m_ppBerSprite->SetPivot(m_spritePivot[en_playerUIPPBer]);

	//画像の座標を設定。
	m_spritePosition[en_playerUIStatus] = { 430.0f, -250.0f, 0.0f };
	m_spritePosition[en_playerUIHP] = { 520.0f, -240.0f, 0.0f };
	m_spritePosition[en_playerUIPP] = { 520.0f, -280.0f, 0.0f };
	m_spritePosition[en_playerUIHPBer] = { 523.0f, -237.0f, 0.0f };
	m_spritePosition[en_playerUIPPBer] = { 523.0f, -277.0f, 0.0f };

	//現在のプレイヤーHPを設定。
	//m_currentPlayerHP = PLAYER_MAX_HP;

	return true;
}

void PlayerStatusUI::Update()
{
	m_hp = m_currentPlayerHP / PLAYER_MAX_HP;
	m_spriteScale[en_playerUIHP].x = m_hp;
	m_hp = m_currentPlayerHP;

	if (g_pad[0]->IsPress(enButtonRight) && m_currentPlayerHP < PLAYER_MAX_HP) {
		m_currentPlayerHP += 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonLeft) && m_currentPlayerHP > 0.0f) {
		m_currentPlayerHP -= 1.0f;
	}

	m_hpSprite->SetScale(m_spriteScale[en_playerUIHP]);

	m_statusSprite->SetPosition(m_spritePosition[en_playerUIStatus]);
	m_hpSprite->SetPosition(m_spritePosition[en_playerUIHP]);
	m_ppSprite->SetPosition(m_spritePosition[en_playerUIPP]);
	m_hpBerSprite->SetPosition(m_spritePosition[en_playerUIHPBer]);
	m_ppBerSprite->SetPosition(m_spritePosition[en_playerUIPPBer]);
}
