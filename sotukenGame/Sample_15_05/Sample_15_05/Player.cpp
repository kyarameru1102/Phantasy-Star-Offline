#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Weapon.h"
#include "PlayerStatusUI.h"
#include "PlayerAttackAnimation.h"
const float MAX_SPEED_Y = 40.0f; //Y方向のスピードの最大値。
const float FLAME_NUM = 30.0f;  //フレーム数。
const float FLUCTUATION_VALUE_Y = MAX_SPEED_Y / FLAME_NUM; //Y方向のスピードの変動値。
                                                           //Y方向のスピードの最大値をフレーム数で割って、
                                                           //1フレームあたりの変動値を求める。
const float MAX_ANGLE = 360.0f;//最大の角度。
const float HALF_ANGLE = 180.0f;//半分の角度。
const float ROTATION_AMOUNT = 10.0f;//回転量。
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
	if (m_playerStatusUI != nullptr) {
		DeleteGO(m_playerStatusUI);
	}
	if (m_playerAnim != nullptr) {
		DeleteGO(m_playerAnim);
	}
}
void Player::GetExperiencePoint(const float experiencePoint)
{
	//経験値に倒した敵の経験値を加算する。
	m_experiencePoint += experiencePoint;
	//次に必要な経験値より今の経験値が多い間はレベルを加算する。
	while (m_experiencePoint >= m_nextExperiencePoint)
	{
		//レベルを加算。
		m_playerLevel++;
		//次に必要なレベルを1.1倍に増やす。
		m_nextExperiencePoint *= 1.1f;
		if (m_playerLevel > 1) {
			m_attackAnimNumX = 4;
			m_attackAnimNumY = 3;
		}
	}
}
void Player::YDirMove()
{
	if (m_charaCon.IsOnGround() != false) {
		//地面の上にいる。
		if (g_pad[0]->IsTrigger(enButtonA) && m_doNothingFlag != true) {
			//Aボタンを押した。
			//攻撃アニメーションをしていたら、止める。
			if (m_attackAnimationFlag != false) {
				m_attackAnimationFlag = false;
				m_playerAttackAnim->AttackEnd();
			}
			//ジャンプフラグを立てる。
			m_jumpFlag = true;
			//Yスピードを最大値にする。
			m_speedY = MAX_SPEED_Y;
			jumpStartTimer = 0;
			m_doNothingFlag = true;
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
		m_doNothingFlag = true;
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
void Player::Rotation()
{
	if (
		fabsf(m_moveSpeed.z) > 0.0f ||
		fabsf(m_moveSpeed.x) > 0.0f) {
		if (
			m_attackFlag != true &&
			m_kaihiFlag != true &&
			m_attackAngleFlag != true &&
			m_changeAnimFlag != true &&
			m_playerHP >= m_beforeHp &&
			m_playerHP > 0.0f &&
			m_specialAttackFlag != true
			) {
			//スティックの向いている方向の角度を求める。
			m_dir = m_moveSpeed;
			m_dir.Normalize();
			float sita = atan2f(m_moveSpeed.x, m_moveSpeed.z);
			sita = sita * HALF_ANGLE / M_PI;
			if (sita <= 0.0f) {
				sita += MAX_ANGLE;
			}

			//今向いている方向の角度を求める。
			Vector3 nowDir = Vector3::AxisZ;
			nowDir.Normalize();
			m_rotation.Apply(nowDir);
			m_angle = atan2f(nowDir.x, nowDir.z);
			m_angle = m_angle * HALF_ANGLE / M_PI;
			if (m_angle <= 0.0f) {
				m_angle += MAX_ANGLE;
			}

			//今向いている方向の角度からスティックの向いている方向の角度を引いて、
			//差を求める。
			float angleDifference = m_angle - sita;
			//上で求めた角度の誤差が回転量以内または、攻撃アニメーション中なら
			if (
				angleDifference <= ROTATION_AMOUNT && angleDifference >= -ROTATION_AMOUNT ||
				m_attackAnimationFlag != false
				) {
				//今向いている方向の角度にスティックの向いている方向の角度を代入する。
				m_angle = sita;
			}
			else if (m_angle <= sita) {
				//今向いている方向の角度がスティックの向いている方向の角度より、
				//小さい。
				if (angleDifference <= -HALF_ANGLE) {
					//角度の差が-180以下。
					//角度をマイナスする。
					m_angle -= ROTATION_AMOUNT;
				}
				else {
					//角度をプラスする。
					m_angle += ROTATION_AMOUNT;
				}
			}
			else if (m_angle >= sita) {
				//今向いている方向の角度がスティックの向いている方向の角度より、
				//大きい。
				if (angleDifference >= HALF_ANGLE) {
					//角度の差が180以上。
					//角度をプラスする。
					m_angle += ROTATION_AMOUNT;
				}
				else {
					//角度をマイナスする。
					m_angle -= ROTATION_AMOUNT;
				}

			}
		}
		m_rotation.SetRotationDeg(Vector3::AxisY, m_angle);
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
	m_playerAnim->InitAnimation();
	//モデルの初期化。
	m_playerSkinModel = NewGO<SkinModelRender>(0);
	m_playerSkinModel->Init(
		"Assets/modelData/player/player.tkm",
		m_playerAnim->GetAnimationClip(),
		enAnimationClipNum,
		"Assets/shader/model.fx",
		SkinModelRender::YUp
	);
	m_position.y += 100.0f;
	m_playerSkinModel->SetPosition(m_position);
	//キャラコン初期化。
	m_charaCon.Init(50.0f, 100.0f, m_position);
	//武器の座標、回転を適応させるボーンの番号を検索。
	m_weapon[0]->SetBoneNum(m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_r"));
	m_weapon[1]->SetBoneNum(m_playerSkinModel->GetModel().GetSkeleton().FindBoneID(L"ik_hand_l"));
	//プレイヤーのUIのインスタンスを作成。
	m_playerStatusUI = NewGO<PlayerStatusUI>(0, "playerStatusUI");

	m_playerAttackAnim = NewGO<PlayerAttackAnimation>(0, "playerAttackAnimation");
	//GameCameraのインスタンスを検索。
	m_gameCam = FindGO<GameCamera>("gameCamera");

	m_beforeHp = m_playerHP;
	return true;
}
void Player::Update()
{
	//アニメーションを待機状態に設定。
	m_animState = enStay_blad;

	//向きと移動スピードを設定。
	SetSpeed();

	if (m_changeAnimFlag != true &&//武器変更していない
		m_charaCon.IsOnGround() != false &&//地面の上にいる
		m_kaihiFlag != true &&//回避していない。
		m_attackFlag != true &&//攻撃中でない。
		m_playerHP == m_beforeHp &&
		m_playerHP > 0.0f &&
		m_specialAttackFlag != true
		) {
		m_doNothingFlag = false;
	}
	//Y方向の移動。
	YDirMove();

	//武器変更のフラグ。
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_doNothingFlag != true) {
		//武器変更のフラグを立てる。
		m_changeAnimFlag = true;
		m_doNothingFlag = true;
		//攻撃アニメーションをしていたら、止める。
		if (m_attackAnimationFlag != false) {
			m_attackAnimationFlag = false;
			m_playerAttackAnim->AttackEnd();
		}
	}

	if (m_doNothingFlag != true/*m_changeAnimFlag != true && m_kaihiFlag != true && m_charaCon.IsOnGround() != false*/) {
		//何もしていない。
		if (g_pad[0]->IsTrigger(enButtonX)/* && m_attackXOrY != attackY*/) {
			//Xボタンを押した。
			if (m_attackXOrY == attackX || m_attackXOrY == noAttack) {
				//Xボタンを押していたか、何も押していない。
				m_doNothingFlag = true;
				m_attackXOrY = attackX;
				m_playerAttackAnim->AttackFlag(enAttackTime01_blad, &m_attackAnimNumX, enAttackTime01_sword);
			}
		}
		else if (g_pad[0]->IsTrigger(enButtonY)/* && m_attackXOrY != attackX*/) {
			//Yボタンを押した。
			if (m_attackXOrY == attackY || m_attackXOrY == noAttack) {
				//Yボタンを押していたか、何も押していない。
				m_doNothingFlag = true;
				m_attackXOrY = attackY;
				m_playerAttackAnim->AttackFlag(enAttackTime06_blad, &m_attackAnimNumY, enAttackTime06_sword);
			}
		}
		else if (g_pad[0]->IsTrigger(enButtonRB2)) {
			if (m_attackXOrY == attackS || m_attackXOrY == noAttack) {
				m_doNothingFlag = true;
				m_attackXOrY = attackS;
				m_attackAnimationFlag = true;
				if (m_weaponState == enBladState) {
					m_specialAttackState = enBladState;
				}
				else if (m_weaponState == enSwordState) {
					m_specialAttackState = enSwordState;
				}
			}
		}

	}
	//プレイヤーを回転させる。
	Rotation();
	
	//回避のフラグ
	if (g_pad[0]->IsTrigger(enButtonB) && m_doNothingFlag != true) {
		//Bボタンを押した。
		m_kaihiFlag = true;
		m_animState = enKaihi_blad;
		m_doNothingFlag = true;
		//攻撃アニメーションをしていたら、止める。
		if (m_attackAnimationFlag != false) {
			m_attackAnimationFlag = false;
			m_playerAttackAnim->AttackEnd();
		}
	}

	//回避。
	if (m_kaihiFlag != false) {
		//タイマーを加算。
		m_kaihiTimer++;
		m_animState = enKaihi_blad;
		//回避中は進行方向に進む。
		m_moveSpeed = m_dir * 10.0f;
		if (m_kaihiTimer >= 50) {
			//タイマーが50以上になったら止まる。
			m_moveSpeed = Vector3::Zero;
		}
		if (m_kaihiTimer >= 60) {
			//タイマーが60以上になったら回避終了。
			m_kaihiTimer = 0;
			m_kaihiFlag = false;
		}
	}
	//武器変更。
	WeaponChange();
	//攻撃。
	if (m_attackAnimationFlag != false) {
		m_playerAttackAnim->Attack();
	}

	if (m_playerHP < m_beforeHp) {
		//ダメージを受けた。
		m_animState = enHit_blad;
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		m_doNothingFlag = true;
		if (!m_playerSkinModel->GetisAnimationPlaing()) {
			m_beforeHp = m_playerHP;
		}
	}

	if (m_playerHP <= 0.0f) {
		//HPが0になったので、死亡。
		m_animState = enDeath_blad;
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		m_doNothingFlag = true;
		if (!m_playerSkinModel->GetisAnimationPlaing()) {
			m_deathFlag = true;
		}
	}


	if (m_weaponState == enSwordState && m_attackXOrY != attackS) {
		//ソード状態なら1足してソード状態のアニメーションを流す。
		m_animState++;
	}
	//アニメーションを再生。
	//アニメーション補完時間。
	float complementaryTime = m_complementaryFlame / 60.0f;
	m_playerSkinModel->PlayAnimation(m_animState, complementaryTime);

	//とりあえずプレイヤーのY座標が-500以下になったら戻るようにする。
	if (m_charaCon.GetPosition().y <= -500.0f || m_deathFlag != false) {
		m_charaCon.SetPosition({ 0.0f, 500.0f, 0.0f });
		m_playerHP = 100.0f;
		m_beforeHp = m_playerHP;
		m_gameCam->ResetToPlayerVec();
		m_deathFlag = false;
	}

	//座標を設定。
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	m_playerSkinModel->SetPosition(m_position);
	//前のフレームの座標から現在のフレームの座標に
	//向かって伸びるベクトルを求める。
	m_weaponMoveSpeed = m_position - m_oldPosition;
	//前の座標を今の座標に置き換える。
	m_oldPosition = m_position;
	//HPを設定。
	m_playerStatusUI->SetCurrentPlayerHP(m_playerHP);
}