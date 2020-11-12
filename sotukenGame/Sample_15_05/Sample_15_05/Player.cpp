#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_playerSkinModel);
}
bool Player::Start()
{
	//アニメーションをロード。
	animClip[enStay01].Load("Assets/animData/player/blad/stay_01.tka");
	animClip[enStay02].Load("Assets/animData/player/sword/stay_02.tka");
	animClip[enChange01].Load("Assets/animData/player/blad/change_01.tka");
	animClip[enChange02].Load("Assets/animData/player/sword/change_02.tka");
	animClip[enStay01].SetLoopFlag(true);
	animClip[enStay02].SetLoopFlag(true);
	animClip[enChange01].SetLoopFlag(true);
	animClip[enChange02].SetLoopFlag(true);

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
	//プレイヤーのムーブスピードを更新。
	m_moveSpeed.x = g_pad[0]->GetLStickXF() * -5.0f;
	m_moveSpeed.z = g_pad[0]->GetLStickYF() * -5.0f;
	//座標を設定。
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);

	if (
		fabsf(m_moveSpeed.z) > 0.0f &&
		fabsf(m_moveSpeed.x) > 0.0f) {
		float rot = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(Vector3::AxisY, rot);
	}
	m_playerSkinModel->SetRotation(m_rotation);


	//if (g_pad[0]->IsPress(enButtonX)) {
	//	//Xボタンで構えを切り替える。
	//	m_animState++;
	//	if (m_animState > enStay02) {
	//		//構えを戻す。
	//		m_animState = enStay01;
	//	}
	//}
	/*if (g_pad[0]->IsPress(enButtonX)) {
		m_changeAnimFlag = true;
	}
	if (m_changeAnimFlag != false) {

		m_changeAnimTimer++;
		if (m_changeAnimTimer >= m_changeAnimTime) {

		}
	}*/
	//アニメーションを再生。
	m_playerSkinModel->PlayAnimation(m_animState, 0.0f);
}