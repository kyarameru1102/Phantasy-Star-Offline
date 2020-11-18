#include "stdafx.h"
#include "Player.h"

const float MAX_SPEED_Y = 50.0f; //Y方向のスピードの最大値。
const float FLAME_NUM = 40.0f;  //フレーム数。
const float FLUCTUATION_VALUE_Y = MAX_SPEED_Y / FLAME_NUM; //Y方向のスピードの変動値。
                                                           //Y方向のスピードの最大値をフレーム数で割って、
                                                           //1フレームあたりの変動値を求める。
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
	animClip[attackAndChang01].Load("Assets/animData/player/blad/attackAndChange_01.tka");
	animClip[attackAndChang02].Load("Assets/animData/player/sword/attackAndChange_02.tka");
	animClip[enStay01].SetLoopFlag(true);
	animClip[enStay02].SetLoopFlag(true);
	animClip[enChange01].SetLoopFlag(true);
	animClip[enChange02].SetLoopFlag(true);
	animClip[attackAndChang01].SetLoopFlag(true);
	animClip[attackAndChang02].SetLoopFlag(true);

	//モデルの初期化。
	m_playerSkinModel = NewGO<SkinModelRender>(0);
	m_playerSkinModel->Init("Assets/modelData/player/player.tkm", animClip, enAnimationClipNum);
	Quaternion qRot;
	qRot.SetRotationDegX(0.0f);
	m_playerSkinModel->SetRotation(qRot);
	m_position.y = 200.0f;
	m_playerSkinModel->SetPosition(m_position);
	m_charaCon.Init(50.0f, 100.0f, m_position);

	m_gameCam = FindGO<GameCamera>("gameCamera");
	return true;
}
void Player::Update()
{
	Vector3 cameraDir = m_gameCam->GetTarget() - m_gameCam->GetPosition();
	cameraDir.y = 0.0f;
	cameraDir.Normalize();

	Vector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		Vector3::AxisY
	);
	//プレイヤーのムーブスピードを計算。
	m_moveSpeed = cameraDirX * g_pad[0]->GetLStickXF() * -10.0f +
		cameraDir * g_pad[0]->GetLStickYF() * 10.0f;

	if (m_charaCon.IsOnGround() != false) {
		//地面の上にいる。
		if (g_pad[0]->IsPress(enButtonB)) {
			//Bボタンを押した。
			//ジャンプフラグを立てる。
			m_jumpFlag = true;
			//Yスピードを最大値にする。
			m_speedY = MAX_SPEED_Y;
		}
		else {
			//フラグを下す。
			m_jumpFlag = true;
			//Yスピードを0にする。
			m_speedY = 0.0f;
		}
	}
	if (m_jumpFlag != false || m_charaCon.IsOnGround() != true) {
		//ジャンプしているまたは、落下している。
		m_speedY -= FLUCTUATION_VALUE_Y;
	}

	if (m_speedY <= -MAX_SPEED_Y) {
		//Yスピードの最低値を固定する。
		m_speedY = -MAX_SPEED_Y;
	}
	//ムーブスピードにYスピードを加算。
	m_moveSpeed.y += m_speedY;

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


	if (g_pad[0]->IsTrigger(enButtonX)) {
		//武器変更のフラグを立てる。
		m_changeAnimFlag = true;
		m_Chang01State = enChange01;
		m_Chang02State = enChange02;
		m_changeAnimTime = 35;
	}

	if (m_changeAnimFlag != false) {
		//武器の状態によって武器変更のアニメーションを決める。
		if (m_weaponState == enBladState) {
			m_animState = enChange01;
		}
		else if(m_weaponState == enSwordState){
			m_animState = enChange02;
		}
		//タイマーを加算。
		m_changeAnimTimer++;
		if (m_changeAnimTimer > m_changeAnimTime) {
			//武器変更のアニメーションが終わった。
			//m_weaponStateが武器変更前の状態で、変更後の状態にする。
			if (m_weaponState == enBladState) {
				m_weaponState = enSwordState;
				m_animState = enStay02;
			}
			else if (m_weaponState == enSwordState) {
				m_weaponState = enBladState;
				m_animState = enStay01;
			}
			//フラグをfalseにする。
			m_changeAnimFlag = false;
			//タイマーをリセット。
			m_changeAnimTimer = 0;
		}
	}
	//アニメーションを再生。
	float aa = m_changeAnimTime / 60.0f;
	m_playerSkinModel->PlayAnimation(m_animState, aa);
}