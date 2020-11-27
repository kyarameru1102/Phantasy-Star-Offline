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
	if (m_weapon[0] != nullptr) {
		DeleteGO(m_weapon[0]);
	}
	if (m_weapon[1] != nullptr) {
		DeleteGO(m_weapon[1]);
	}
	}
void Player::YDirMove()
{
	if (m_charaCon.IsOnGround() != false) {
		//地面の上にいる。
		if (g_pad[0]->IsPress(enButtonA)) {
			//Aボタンを押した。
			//ジャンプフラグを立てる。
			m_jumpFlag = true;
			//Yスピードを最大値にする。
			m_speedY = MAX_SPEED_Y;
			jumpStartTimer = 0;
		}
		else {
			//フラグを下す。
			m_jumpFlag = false;
			//Yスピードを0にする。
			m_speedY = 0.0f;
		}
	}
	if (m_jumpFlag != false) {
		//ジャンプした時、アニメーションを流す。
		jumpStartTimer++;
		if (jumpStartTimer <= 40) {
			m_complementaryTime = 10.0f;
				m_animState = enJumpStart_blad;
		}
	}
	if (m_charaCon.IsOnGround() != true) {
		//ジャンプしているまたは、落下している。
		m_speedY -= FLUCTUATION_VALUE_Y;
		if (jumpStartTimer >= 40) {
			m_complementaryTime = 10.0f;
				m_animState = enStayInTheAir_blad;
		}
	}

	if (m_speedY <= -MAX_SPEED_Y) {
		//Yスピードの最低値を固定する。
		m_speedY = -MAX_SPEED_Y;
	}
	//ムーブスピードにYスピードを加算。
	m_moveSpeed.y += m_speedY;

}
void Player::WeaponChange()
{
	if (m_changeAnimFlag != false) {
		m_complementaryTime = 10.0f;
		m_animState = enChange_blad;
		//武器変更時は動かない。
		m_moveSpeed = Vector3::Zero;
		//タイマーを加算。
		m_changeAnimTimer++;
		if (m_changeAnimTimer > m_changeAnimTime) {
			//武器変更のアニメーションが終わった。
			//m_weaponStateが武器変更前の状態で、変更後の状態にする。
			if (m_weaponState == enBladState) {
				m_weaponState = enSwordState;
			}
			else if (m_weaponState == enSwordState) {
				m_weaponState = enBladState;
			}
			//フラグをfalseにする。
			m_changeAnimFlag = false;
			//タイマーをリセット。
			m_changeAnimTimer = 0;
		}
	}
}
void Player::SetWeaponTR()
{
	//ボーンから武器の座標、回転、スケールを設定。
	m_playerSkinModel->GetModel().GetSkeleton().GetBone(m_weapon01Num)->CalcWorldTRS(
		m_weaponPos,
		m_weaponRot,
		m_weaponScale
	);
	Quaternion weaponRot = Quaternion::Identity;
	weaponRot.SetRotationDegX(90.0f);
	weaponRot.Multiply(m_weaponRot);
	//座標にムーブスピードを加算。
	m_weaponPos += m_moveSpeed;
	m_weapon[0]->SetPosition(m_weaponPos);
	m_weapon[0]->SetRtation(weaponRot);

	//ボーンから武器の座標、回転、スケールを設定。
	m_playerSkinModel->GetModel().GetSkeleton().GetBone(m_weapon02Num)->CalcWorldTRS(
		m_weaponPos,
		m_weaponRot,
		m_weaponScale
	);
	weaponRot = Quaternion::Identity;
	weaponRot.SetRotationDegX(90.0f);
	weaponRot.Multiply(m_weaponRot);
	//座標にムーブスピードを加算。
	m_weaponPos += m_moveSpeed;
	m_weapon[1]->SetPosition(m_weaponPos);
	m_weapon[1]->SetRtation(weaponRot);

	m_playerSkinModel->GetModel().GetSkeleton().GetBone(m_weapon03Num)->CalcWorldTRS(
		m_rootPos,
		m_rot,
		m_rootScale
	);
}
void Player::SetDirAndSpeed()
{
	//カメラを考慮したプレイヤーの移動方向を計算する。
	Vector3 cameraDir = m_gameCam->GetTarget() - m_gameCam->GetPosition();
	cameraDir.y = 0.0f;
	cameraDir.Normalize();

	Vector3 cameraDirX;
	cameraDirX.Cross(
		cameraDir,
		Vector3::AxisY
	);
	//プレイヤーのムーブスピードを計算。
	m_moveSpeed = cameraDirX * g_pad[0]->GetLStickXF() * -m_magnificationSpeed +
		cameraDir * g_pad[0]->GetLStickYF() * m_magnificationSpeed;

	if (fabs(m_moveSpeed.x) > 0.0f || fabs(m_moveSpeed.z) > 0.0f) {
		//移動している。
		if (g_pad[0]->IsPress(enButtonB)) {
			m_magnificationSpeed = 10.0f;
			m_animState = enRun_blad;
		}
		else {
			m_magnificationSpeed = 5.0f;
			m_animState = enWalk_blad;
		}
		m_complementaryTime = 10.0f;
	}
	if (
		fabsf(m_moveSpeed.z) > 0.0f &&
		fabsf(m_moveSpeed.x) > 0.0f) {
		float rot = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(Vector3::AxisY, rot);
	}
	m_playerSkinModel->SetRotation(m_rotation);
}
bool Player::Start()
{
	//武器のインスタンス作成。
	m_weapon[0] = NewGO<Weapon>(0, "weapon_01");
	m_weapon[1] = NewGO<Weapon>(0, "weapon_02");
	//プレイヤーのアニメーションのインスタンス作成。
	m_playerAnim = NewGO<PlayerAnimation>(0, "playerAnim");
	//モデルの初期化。
	m_playerSkinModel = NewGO<SkinModelRender>(0);
	m_playerSkinModel->Init(
		"Assets/modelData/player/player.tkm",
		m_playerAnim->GetAnimationClip(),
		enAnimationClipNum,
		"Assets/shader/model.fx",
		SkinModelRender::YUp
		);
	//キャラコン初期化。
	m_charaCon.Init(50.0f, 100.0f, m_position);
	//武器の座標、回転を適応させるボーンの番号を検索。
	m_weapon01Num = m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_r");
	m_weapon02Num = m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_l");

	m_weapon03Num = m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"root");
	//GameCameraのインスタンスを検索。
	m_gameCam = FindGO<GameCamera>("gameCamera");
	return true;
}
void Player::Update()
{
	//アニメーションを待機状態に設定。
	m_animState = enStay_blad;

	//武器の座標と回転を設定。
	SetWeaponTR();

	//向きと移動スピードを設定。
	SetDirAndSpeed();

	//Y方向の移動。
	YDirMove();

	//武器変更。
	if (g_pad[0]->IsPress(enButtonLB1)) {
		//武器変更のフラグを立てる。
		m_changeAnimFlag = true;
	}
	WeaponChange();
	if (m_attackFlag != true && g_pad[0]->IsPress(enButtonX)) {
		m_attackFlag = true;
	}
	if (m_attackFlag != false) {
		m_moveSpeed = Vector3::Zero;
		attackTimer++;
		m_animState = enAttack_blad;
		m_complementaryTime = 10.0f;
		int time = 120;
		if (m_weaponState == enSwordState) {
			time = 90;
		}
		if (attackTimer > time) {
			m_attackFlag = false;
			attackTimer = 0;
		}
	}
	
	if (m_weaponState == enSwordState) {
		//ソード状態なら1足してソード状態のアニメーションを流す。
		m_animState++;
	}
	//アニメーションを再生。
		float aa = m_complementaryTime / 60.0f;
		m_playerSkinModel->PlayAnimation(m_animState, aa);

	//とりあえずプレイヤーのY座標が-500以下になったら戻るようにする。
	if (m_charaCon.GetPosition().y <= -500.0f) {
		m_charaCon.SetPosition({ 0.0f, 500.0f, 0.0f });
	}

	//座標を設定。
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);
}