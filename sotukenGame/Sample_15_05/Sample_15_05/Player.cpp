#include "stdafx.h"
#include "Player.h"

Player::Player()
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
}

Player::~Player()
{

}

void Player::Update()
{
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