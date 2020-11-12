#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{

}
bool Player::Start()
{
	//�A�j���[�V���������[�h�B
	animClip[enStay01].Load("Assets/animData/player/blad/stay_01.tka");
	animClip[enStay02].Load("Assets/animData/player/sword/stay_02.tka");
	animClip[enStay01].SetLoopFlag(true);
	animClip[enStay02].SetLoopFlag(true);
	//���f���̏������B
	m_playerSkinModel = NewGO<SkinModelRender>(0);
	m_playerSkinModel->Init("Assets/modelData/player/player.tkm", animClip, enAnimationClipNum);
	Quaternion qRot;
	qRot.SetRotationDegX(0.0f);
	m_playerSkinModel->SetRotation(qRot);
	m_charaCon.Init(50.0f, 100.0f, m_position);
	return true;
}
void Player::Update()
{
	//�v���C���[�̃��[�u�X�s�[�h���X�V�B
	m_moveSpeed.x = g_pad[0]->GetLStickXF() * -5.0f;
	m_moveSpeed.z = g_pad[0]->GetLStickYF() * -5.0f;
	//���W��ݒ�B
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);

	if (
		fabsf(m_moveSpeed.z) > 0.0f &&
		fabsf(m_moveSpeed.x) > 0.0f) {
		float rot = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(Vector3::AxisY, rot);
	}
	m_playerSkinModel->SetRotation(m_rotation);


	if (GetAsyncKeyState('B')) {
		//�u���[�h���[�h�B
		m_animState = enStay01;
	}
	else if(GetAsyncKeyState('S')){
		//�c�C���\�[�h���[�h�B
		m_animState = enStay02;
	}
	//�A�j���[�V�������Đ��B
	m_playerSkinModel->PlayAnimation(m_animState, 0.0f);
}