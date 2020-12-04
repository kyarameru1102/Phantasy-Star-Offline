#include "stdafx.h"
#include "DrBoar.h"
#include "Player.h"
DrBoar::DrBoar()
{
}

DrBoar::~DrBoar()
{
	DeleteGO(m_DrBoarSkinModel);
}

bool DrBoar::Start()
{
	//プレイヤーのアニメーションのインスタンス作成。
	m_enemyAnim = NewGO<EnemyAnimation>(0, "enemyAnim");
	//配色を決める。
	m_appearcolor = boarcolor[rand() % boarcolor.size()];
	//モデルの初期化
	if (m_appearcolor == 1) {
		m_DrBoarSkinModel = NewGO<SkinModelRender>(0);
		m_DrBoarSkinModel->Init("Assets/modelData/enemy/DragonBoar/Blue/DrBoarBl.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
		m_position = { 300.0f, 0.0f, -100.0f };
	}
	else if (m_appearcolor == 2)
	{
		m_DrBoarSkinModel = NewGO<SkinModelRender>(0);
		m_DrBoarSkinModel->Init("Assets/modelData/enemy/DragonBoar/Gold/DrBoarGo.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
		m_position = { 300.0f, 0.0f, 100.0f };
	}
	else if (m_appearcolor == 3)
	{
		m_DrBoarSkinModel = NewGO<SkinModelRender>(0);
		m_DrBoarSkinModel->Init("Assets/modelData/enemy/DragonBoar/Green/DrBoarGr.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
		m_position = { -300.0f, 0.0f, -100.0f };
	}
	else if (m_appearcolor == 4)
	{
		m_DrBoarSkinModel = NewGO<SkinModelRender>(0);
		m_DrBoarSkinModel->Init("Assets/modelData/enemy/DragonBoar/Red/DrBoarRe.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
		m_position = { -300.0f, 0.0f, 100.0f };
	}
	
	m_rotation.SetRotationDegY(90.0f);
	//キャラコン初期化。
	m_charaCon.Init(200.0f, 150.0f, m_position);
	return true;
}
void DrBoar::Move()
{
	
	if (m_player != nullptr) {
		Vector3 playerLen = m_player->GetPosition() - m_position;
		playerLen.Normalize();
		m_movespeed = playerLen * 1.2f;
		m_movespeed.y = m_speedY;
		m_position += m_movespeed;
	}
}

void DrBoar::Turn()
{
	//プレイヤーに向けて回転させる
	/*if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
	}*/
	if (m_player != nullptr) {
		Vector3 playerLen = m_player->GetPosition() - m_position;
		float angle = atan2(playerLen.x, playerLen.z);
		m_rotation.SetRotation(Vector3::AxisY, angle);
	}
}
void DrBoar::Update()
{
	if (m_status == Idle_state) {
		m_animState = enIdle;
	}
	if (m_status == Attack_state) {
		m_animState = enRun;
	}
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
	}
	if (m_player != nullptr)
	{
		Move();
		Turn();
	}

	m_position = m_charaCon.Execute(1.0f, m_movespeed);
	m_DrBoarSkinModel->SetScale({ 40.0, 40.0, 40.0 });
	m_DrBoarSkinModel->SetRotation(m_rotation);
	m_DrBoarSkinModel->SetPosition(m_position);
	m_DrBoarSkinModel->PlayAnimation(m_animState, 0.0f);
}