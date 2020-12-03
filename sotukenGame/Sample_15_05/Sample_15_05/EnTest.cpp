#include "stdafx.h"
#include "EnTest.h"
#include "Player.h"
EnTest::EnTest()
{

}
EnTest::~EnTest()
{

}

bool EnTest::Start()
{
	//アニメーションクリップのロード
	m_animationClip[enIdle].Load("Assets/animData/DragonBoar/boar_idle.tka");
	m_animationClip[enIdle].SetLoopFlag(true);
	m_animationClip[enWalk].Load("Assets/animData/DragonBoar/boar_walk.tka");
	m_animationClip[enWalk].SetLoopFlag(true);
	m_animationClip[enRun].Load("Assets/animData/DragonBoar/boar_run.tka");
	m_animationClip[enRun].SetLoopFlag(true);
	m_animationClip[enDie].Load("Assets/animData/DragonBoar/boar_die.tka");
	m_animationClip[enDie].SetLoopFlag(true);
	//モデルの初期化
	m_EnTestSkinModel = NewGO<SkinModelRender>(0);
	m_EnTestSkinModel->Init("Assets/modelData/enemy/DragonBoar/Gold/DrBoarGo.tkm", m_animationClip, enAnimationClip_num);
	m_position = { 300.0f, 0.0f, 100.0f };
	m_rotation.SetRotationDegY(90.0f);

	return true;
}
void EnTest::Move()
{
	//プレイヤーを追いかける。
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
	}
	if (m_player != nullptr) {
		Vector3 playerLen = m_player->GetPosition() - m_position;
		playerLen.Normalize();
		m_movespeed = playerLen * 1.2f;
		m_position += m_movespeed;
	}
}

void EnTest::Turn()
{
	//プレイヤーに向けて回転させる
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
	}
	if (m_player != nullptr) {
		Vector3 playerLen = m_player->GetPosition() - m_position;
		float angle = atan2(playerLen.x, playerLen.z);
		m_rotation.SetRotation(Vector3::AxisY, angle);
	}
	
}
void EnTest::Update()
{
	Move();
	Turn();
	//turntimer++;
	/*if (turntimer < 50)
	{
		m_addrot.SetRotationDeg(Vector3::AxisY, 2.0f);
		m_rotation *= m_addrot;
	}*/
	
	m_EnTestSkinModel->SetScale({ 40.0, 40.0, 40.0 });
	m_EnTestSkinModel->SetRotation(m_rotation);
	m_EnTestSkinModel->SetPosition(m_position);
	m_EnTestSkinModel->PlayAnimation(m_animState,0.0f);
}