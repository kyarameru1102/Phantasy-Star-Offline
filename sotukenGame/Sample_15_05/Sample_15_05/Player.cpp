#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	////アニメーションをロード。
	//animClip[enStay01].Load("Assets/animData/player/blad/stay_01.tka");
	//animClip[enStay02].Load("Assets/animData/player/sword/stay_02.tka");
	//animClip[enStay01].SetLoopFlag(true);
	//animClip[enStay02].SetLoopFlag(true);
	////モデルの初期化。
	//m_playerSkinModel = NewGO<SkinModelRender>(0);
	//m_playerSkinModel->Init("Assets/modelData/player/player.tkm", animClip, enAnimationClipNum);
	//Quaternion qRot;
	//qRot.SetRotationDegX(0.0f);
	//m_playerSkinModel->SetRotation(qRot);
	//m_charaCon.Init(50.0f, 100.0f, m_position);
}

Player::~Player()
{

}
bool Player::Start()
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
	m_charaCon.Init(50.0f, 100.0f, m_position);
	return true;
}
void Player::Update()
{
	m_moveSpeed = Vector3::Zero;
	if (GetAsyncKeyState(VK_UP)) {
		m_moveSpeed.z = 5.0f;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		m_moveSpeed.z = -5.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		m_moveSpeed.x = 5.0f;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		m_moveSpeed.x = -5.0f;
	}

	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);

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