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
	//�v���C���[�̃A�j���[�V�����̃C���X�^���X�쐬�B
	m_enemyAnim = NewGO<EnemyAnimation>(0, "enemyAnim");
	m_appearcolor = boarcolor[rand() % boarcolor.size()];
	//���f���̏�����
	if (m_appearcolor == 1 ) {
		m_EnTestSkinModel = NewGO<SkinModelRender>(0);
		m_EnTestSkinModel->Init("Assets/modelData/enemy/DragonBoar/Blue/DrBoarBl.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
	}
	else if (m_appearcolor == 2)
	{
		m_EnTestSkinModel = NewGO<SkinModelRender>(0);
		m_EnTestSkinModel->Init("Assets/modelData/enemy/DragonBoar/Gold/DrBoarGo.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
	}
	else if (m_appearcolor == 3)
	{
		m_EnTestSkinModel = NewGO<SkinModelRender>(0);
		m_EnTestSkinModel->Init("Assets/modelData/enemy/DragonBoar/Green/DrBoarGr.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
	}
	else if (m_appearcolor == 4)
	{
		m_EnTestSkinModel = NewGO<SkinModelRender>(0);
		m_EnTestSkinModel->Init("Assets/modelData/enemy/DragonBoar/Red/DrBoarRe.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
	}
	m_position = { 300.0f, 0.0f, 100.0f };
	m_rotation.SetRotationDegY(90.0f);
	//�L�����R���������B
	m_charaCon.Init(200.0f, 150.0f, m_position);
	return true;
}
void EnTest::Move()
{
	//�v���C���[��ǂ�������B
	
	if (m_player != nullptr) {
		Vector3 playerLen = m_player->GetPosition() - m_position;
		playerLen.Normalize();
		m_movespeed = playerLen * 1.2f;
		m_movespeed.y = m_speedY;
		m_position += m_movespeed;
	}
}

void EnTest::Turn()
{
	//�v���C���[�Ɍ����ĉ�]������
	
	if (m_player != nullptr) {
		Vector3 playerLen = m_player->GetPosition() - m_position;
		float angle = atan2(playerLen.x, playerLen.z);
		m_rotation.SetRotation(Vector3::AxisY, angle);
	}
	
}

void EnTest::Attack()
{
	if (m_status == Attack_state && m_player != nullptr) {
		
	}
}

void EnTest::Update()
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
	//turntimer++;
	/*if (turntimer < 50)
	{
		m_addrot.SetRotationDeg(Vector3::AxisY, 2.0f);
		m_rotation *= m_addrot;
	}*/
	m_position = m_charaCon.Execute(1.0f, m_movespeed);
	m_EnTestSkinModel->SetScale({ 40.0, 40.0, 40.0 });
	m_EnTestSkinModel->SetRotation(m_rotation);
	m_EnTestSkinModel->SetPosition(m_position);
	m_EnTestSkinModel->PlayAnimation(m_animState,0.0f);
}