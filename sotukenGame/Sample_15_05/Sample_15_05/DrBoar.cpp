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
	//�A�j���[�V�����N���b�v�̃��[�h
	m_animationClip[enIdle].Load("Assets/animData/DragonBoar/boar_idle.tka");
	m_animationClip[enIdle].SetLoopFlag(true);
	m_animationClip[enWalk].Load("Assets/animData/DragonBoar/boar_walk.tka");
	m_animationClip[enWalk].SetLoopFlag(true);
	m_animationClip[enRun].Load("Assets/animData/DragonBoar/boar_run.tka");
	m_animationClip[enRun].SetLoopFlag(true);
	m_animationClip[enDie].Load("Assets/animData/DragonBoar/boar_die.tka");
	m_animationClip[enDie].SetLoopFlag(true);
	//���f���̏�����
	m_DrBoarSkinModel = NewGO<SkinModelRender>(0);
	m_DrBoarSkinModel->Init("Assets/modelData/enemy/DragonBoar/Gold/DrBoarGo.tkm", m_animationClip, enAnimationClip_num);
	m_position = { 300.0f, 0.0f, 100.0f };
	m_rotation.SetRotationDegY(90.0f);
	//�L�����R���������B
	m_charaCon.Init(200.0f, 150.0f, m_position);
	return true;
}
void DrBoar::Move()
{
	//�v���C���[��ǂ�������B
	/*if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
	}*/
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
	//�v���C���[�Ɍ����ĉ�]������
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
	/*changeTimer++;
	if (changeTimer == 30)
	{
		m_animState = enWalk;
	}
	if (changeTimer == 50)
	{
		m_animState = enRun;
	}
	if (changeTimer == 70)
	{
		m_animState = enDie;
	}*/
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
	m_position = m_charaCon.Execute(1.0f, m_movespeed);
	m_DrBoarSkinModel->SetScale({ 40.0, 40.0, 40.0 });
	m_DrBoarSkinModel->SetRotation(m_rotation);
	m_DrBoarSkinModel->SetPosition(m_position);
	m_DrBoarSkinModel->PlayAnimation(m_animState, 0.0f);
}