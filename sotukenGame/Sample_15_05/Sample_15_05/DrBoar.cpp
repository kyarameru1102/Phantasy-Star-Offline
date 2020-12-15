#include "stdafx.h"
#include "DrBoar.h"
#include "Player.h"
DrBoar::DrBoar()
{
}

DrBoar::~DrBoar()
{
	DeleteGO(m_skinModelRender);
}

bool DrBoar::Start()
{
	//�v���C���[�̃A�j���[�V�����̃C���X�^���X�쐬�B
	m_enemyAnim = NewGO<EnemyAnimation>(0, "enemyAnim");
	//�z�F�����߂�B
	m_appearcolor = boarcolor[rand() % boarcolor.size()];
	//���f���̏�����
	if (m_appearcolor == 1) {
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->Init("Assets/modelData/enemy/DragonBoar/Blue/DrBoarBl.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
		m_position = { 300.0f, 0.0f, -100.0f };
	}
	else if (m_appearcolor == 2)
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->Init("Assets/modelData/enemy/DragonBoar/Gold/DrBoarGo.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
		m_position = { 300.0f, 0.0f, 100.0f };
	}
	else if (m_appearcolor == 3)
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->Init("Assets/modelData/enemy/DragonBoar/Green/DrBoarGr.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
		m_position = { -300.0f, 0.0f, -100.0f };
	}
	else if (m_appearcolor == 4)
	{
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->Init("Assets/modelData/enemy/DragonBoar/Red/DrBoarRe.tkm", m_enemyAnim->GetAnimationClip(), enAnimationClip_num);
		m_position = { -300.0f, 0.0f, 100.0f };
	}
	
	m_rotation.SetRotationDegY(90.0f);
	//�L�����R���������B
	m_charaCon.Init(145.0f, 200.0f, m_position);

	m_player = FindGO<Player>("player");

	return true;
}
void DrBoar::Move()
{
	m_status = Move_state;
	Vector3 playerLen = m_toPlayer;
	playerLen.Normalize();
	m_movespeed = playerLen * 1.2f;
	m_movespeed.y = m_speedY;
	m_position = m_charaCon.Execute(1.0f, m_movespeed);
}

void DrBoar::Turn()
{
	Vector3 playerLen = m_player->GetPosition() - m_position;
	float angle = atan2(playerLen.x, playerLen.z);
	m_rotation.SetRotation(Vector3::AxisY, angle);
}

void DrBoar::Attack()
{
	if (m_toPlayer.Length() <= 190.0f)
	{
		m_status = Attack_state;
	}
}

void DrBoar::Die()
{
	if (m_hp <= 0)
	{
		m_status = Die_state;
	}
}

void DrBoar::Update()
{
	//���t���[�������͂���B
	m_toPlayer = m_player->GetPosition() - m_position;

	//�v���C���[�����ȏ�߂Â�����B
	{
		if (m_status != Attack_state && m_status != Die_state) {
			Move();
			Turn();
		}
	}
	//����ɋ������߂Â��ƁB
	Attack();

	//�̗͂��[���ɂȂ��
	Die();

	switch (m_status)
	{
	case Idle_state:
		m_animState = enIdle;
		break;
	case Move_state:
		m_animState = enRun;
		break;
	case Attack_state:
		m_animState = enHornattack;
		if (!m_skinModelRender->GetisAnimationPlaing()) {
			m_status = Idle_state;
			m_animState = enIdle;
			m_skinModelRender->PlayAnimation(m_animState, 0.0f);
		}
		break;
	case Die_state:
		m_animState = enDie;
		break;
	default:
		break;
	}
	
	m_skinModelRender->SetScale({ 40.0, 40.0, 40.0 });
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->PlayAnimation(m_animState, 0.0f);
	//�f�o�b�O�p�B
	printf_s( "%d", m_animState);
}