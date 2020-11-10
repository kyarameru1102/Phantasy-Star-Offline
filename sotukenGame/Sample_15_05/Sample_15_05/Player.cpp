#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//アニメーションをロード。
	animClip[enStay01].Load("Assets/animData/player/blad/stay_01.tka");
	animClip[enStay02].Load("Assets/animData/player/sword/stay_02.tka");
	animClip[enStay01].SetLoopFlag(true);
	animClip[enStay02].SetLoopFlag(true);
	//モデルの初期化。
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
		//ブレードモード。
		m_animState = enStay01;
	}
	else if(GetAsyncKeyState('S')){
		//ツインソードモード。
		m_animState = enStay02;
	}
	//アニメーションを再生。
	m_playerSkinModel->PlayAnimation(m_animState, 0.0f);
}