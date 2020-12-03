#include "stdafx.h"
#include "Player.h"

const float MAX_SPEED_Y = 50.0f; //Y方向のスピードの最大値。
const float FLAME_NUM = 40.0f;  //フレーム数。
const float FLUCTUATION_VALUE_Y = MAX_SPEED_Y / FLAME_NUM; //Y方向のスピードの変動値。
                                                           //Y方向のスピードの最大値をフレーム数で割って、
                                                           //1フレームあたりの変動値を求める。
const int ATTACK_ANIM_NUM_X = 4;//Xボタンの攻撃アニメーションの数。
const int ATTACK_ANIM_NUM_Y = 3;//Yボタンの攻撃アニメーションの数。
                                //入る数はアニメーションの数-１の数値を入れる。
Player::Player()
{
}
Player::~Player()
{
	if (m_playerSkinModel != nullptr) {
		DeleteGO(m_playerSkinModel);
	}
	if (m_weapon[0] != nullptr) {
		DeleteGO(m_weapon[0]);
	}
	if (m_weapon[1] != nullptr) {
		DeleteGO(m_weapon[1]);
	}
}
void Player::AttackFlag(int attackTime01_blad, int attackAnimNum, int attackTime01_sword)
{
	m_attackFlag = true;
	if (attackTimer <= 0) {
		//攻撃タイムが0以下。
		m_attackAnimationTimeNum = attackTime01_blad;
		m_attackAnimNum = attackAnimNum;
		if (m_weaponState == enSwordState) {
			//ソード状態
			m_attackAnimationTimeNum = attackTime01_sword;
		}
		//タイムに最初の攻撃時間を入れる。
		m_totalAttackAnimationTime = m_playerAnim->GetAttackAnimationTime()[m_attackAnimationTimeNum];
		//連撃タイムにタイムを入れる。
		m_continuousAttackTime = m_totalAttackAnimationTime;
		//連撃タイムから50引く。
		m_continuousAttackTime = 30;
	}
	if (attackTimer >= m_continuousAttackTime && m_attackNum < m_attackAnimNum) {
		//連撃タイム以降
		m_attackNum++;
		m_attackAnimationTimeNum++;
		//攻撃アニメーションの合計時間に次の攻撃アニメーションの時間を加算する。
		m_totalAttackAnimationTime = attackTimer + m_playerAnim->GetAttackAnimationTime()[m_attackAnimationTimeNum];
		m_continuousAttackTime = attackTimer + 30;
		//フラグを立てて、この時は攻撃中でも方向を変えれるようにする。
		m_attackAngleFlag = true;
	}
}
void Player::Attack()
{
	if (m_attackFlag != false) {
		m_moveSpeed = Vector3::Zero;
		//攻撃タイマーを加算。
		attackTimer++;
		//XボタンかYボタンで初期攻撃アニメーションを決める。
		if (m_attackAnimNum == ATTACK_ANIM_NUM_X) {
			m_animState = enAttack01_blad;
		}
		else {
			m_animState = enAttack06_blad;
		}
		//m_attackNum×2を加算した番号のアニメーションを流す。
		m_animState += m_attackNum * 2;
		if (attackTimer > m_totalAttackAnimationTime) {
			//攻撃アニメーション終了。
			if (m_attackAnimationTimeNum == enAttackTime09_blad ||
				m_attackAnimationTimeNum == enAttackTime09_sword) {
				//武器チェンジの攻撃アニメーションだった。
				//武器の状態を変更する。
				if (m_weaponState == enBladState) {
					m_weaponState = enSwordState;
				}
				else if (m_weaponState == enSwordState) {
					m_weaponState = enBladState;
				}
			}
			m_attackFlag = false;
			attackTimer = 0;
			m_attackNum = 0;
			m_totalAttackAnimationTime = 0;
			m_animState = enStay_blad;
		}
	}
}
void Player::YDirMove()
{
	if (m_charaCon.IsOnGround() != false) {
		//地面の上にいる。
		if (g_pad[0]->IsTrigger(enButtonA)) {
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
				m_animState = enJumpStart_blad;
		}
	}
	if (m_charaCon.IsOnGround() != true) {
		//ジャンプしているまたは、落下している。
		m_speedY -= FLUCTUATION_VALUE_Y;
		if (jumpStartTimer >= 40) {
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
void Player::SetSpeed()
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
		if (g_pad[0]->IsPress(enButtonRB1)) {
			m_magnificationSpeed = 10.0f;
			m_animState = enRun_blad;
		}
		else {
			m_magnificationSpeed = 5.0f;
			m_animState = enWalk_blad;
		}
	}
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
	m_weapon[0]->SetBoneNum(m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_r"));
	m_weapon[1]->SetBoneNum(m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_l"));

	//GameCameraのインスタンスを検索。
	m_gameCam = FindGO<GameCamera>("gameCamera");
	return true;
}
void Player::Update()
{
	//アニメーションを待機状態に設定。
	m_animState = enStay_blad;

	//向きと移動スピードを設定。
	SetSpeed();

	//Y方向の移動。
	YDirMove();

	//武器変更。
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_attackFlag != true) {
		//武器変更のフラグを立てる。
		m_changeAnimFlag = true;
	}
	WeaponChange();
	//攻撃のフラグを立てる。
	if (m_changeAnimFlag != true) {
		if (g_pad[0]->IsTrigger(enButtonX)) {
			AttackFlag(enAttackTime01_blad, ATTACK_ANIM_NUM_X, enAttackTime01_sword);
		}
		else if (g_pad[0]->IsTrigger(enButtonY)) {
			AttackFlag(enAttackTime06_blad, ATTACK_ANIM_NUM_Y, enAttackTime06_sword);
		}
	}
	//プレイヤーを回転させる。
	if (
		fabsf(m_moveSpeed.z) > 0.0f &&
		fabsf(m_moveSpeed.x) > 0.0f) {

		if (m_attackFlag != true || m_attackAngleFlag != false) {
			m_angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
			m_attackAngleFlag = false;
		}
		m_rotation.SetRotation(Vector3::AxisY, m_angle);
	}
	m_playerSkinModel->SetRotation(m_rotation);
	//攻撃。
	Attack();
	
	if (m_weaponState == enSwordState) {
		//ソード状態なら1足してソード状態のアニメーションを流す。
		m_animState++;
	}
	//アニメーションを再生。
	//アニメーション補完時間。
	float complementaryTime = m_complementaryFlame / 60.0f;
	m_playerSkinModel->PlayAnimation(m_animState, complementaryTime);

	//とりあえずプレイヤーのY座標が-500以下になったら戻るようにする。
	if (m_charaCon.GetPosition().y <= -500.0f) {
		m_charaCon.SetPosition({ 0.0f, 500.0f, 0.0f });
	}

	//座標を設定。
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);
	//前のフレームの座標から現在のフレームの座標に
	//向かって伸びるベクトルを求める。
	m_weaponMoveSpeed = m_position - m_oldPosition;
	//前の座標を今の座標に置き換える。
	m_oldPosition = m_position;
}