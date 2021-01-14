#include "stdafx.h"
#include "PlayerAttackAnimation.h"
#include "Player.h"
#include "PlayerAnimation.h"
PlayerAttackAnimation::PlayerAttackAnimation()
{
}


PlayerAttackAnimation::~PlayerAttackAnimation()
{
}
void PlayerAttackAnimation::SetAttackAnimationTime()
{
	m_attackAnimationTime[enAttackTime01_blad] = 120;
	m_attackAnimationTime[enAttackTime02_blad] = 100;
	m_attackAnimationTime[enAttackTime03_blad] = 120;
	m_attackAnimationTime[enAttackTime04_blad] = 100;
	m_attackAnimationTime[enAttackTime05_blad] = 106;
	m_attackAnimationTime[enAttackTime06_blad] = 100;
	m_attackAnimationTime[enAttackTime07_blad] = 100;
	m_attackAnimationTime[enAttackTime08_blad] = 130;
	m_attackAnimationTime[enAttackTime09_blad] = 110;
	m_attackAnimationTime[enAttackTime01_sword] = 80;
	m_attackAnimationTime[enAttackTime02_sword] = 80;
	m_attackAnimationTime[enAttackTime03_sword] = 90;
	m_attackAnimationTime[enAttackTime04_sword] = 90;
	m_attackAnimationTime[enAttackTime05_sword] = 90;
	m_attackAnimationTime[enAttackTime06_sword] = 90;
	m_attackAnimationTime[enAttackTime07_sword] = 80;
	m_attackAnimationTime[enAttackTime08_sword] = 110;
	m_attackAnimationTime[enAttackTime09_sword] = 150;

	m_switchAttackTime[enAttackTime01_blad] = 20;
	m_switchAttackTime[enAttackTime02_blad] = 30;
	m_switchAttackTime[enAttackTime03_blad] = 30;
	m_switchAttackTime[enAttackTime04_blad] = 30;
	m_switchAttackTime[enAttackTime05_blad] = 30;
	m_switchAttackTime[enAttackTime06_blad] = 30;
	m_switchAttackTime[enAttackTime07_blad] = 30;
	m_switchAttackTime[enAttackTime08_blad] = 30;
	m_switchAttackTime[enAttackTime09_blad] = 30;
	m_switchAttackTime[enAttackTime01_sword] = 20;
	m_switchAttackTime[enAttackTime02_sword] = 20;
	m_switchAttackTime[enAttackTime03_sword] = 30;
	m_switchAttackTime[enAttackTime04_sword] = 30;
	m_switchAttackTime[enAttackTime05_sword] = 30;
	m_switchAttackTime[enAttackTime06_sword] = 30;
	m_switchAttackTime[enAttackTime07_sword] = 20;
	m_switchAttackTime[enAttackTime08_sword] = 40;
	m_switchAttackTime[enAttackTime09_sword] = 30;
}
void PlayerAttackAnimation::NormalAttack()
{
	m_player->SetAttackAngleFlag(true);
	if (attackTimer >= m_continuousAttackTime) {
		//m_moveSpeed = Vector3::Zero;
		m_player->SetMoveSpeed(Vector3::Zero);

		//m_attackFlag = false;
		m_player->SetAttackFlag(false);
	}
	else {
		Vector3 moveSpeed = m_player->GetDir() * 5.0f;
		m_player->SetMoveSpeed(moveSpeed);
		//m_moveSpeed = m_dir * 5.0f;
		//m_attackFlag = true;
		m_player->SetAttackFlag(true);


	}
	//攻撃タイマーを加算。
	attackTimer++;
	//XボタンかYボタンで初期攻撃アニメーションを決める。
	if (m_player->GetAttackXOrY() == attackX) {
		//m_animState = enAttack01_blad;
		m_player->SetAnimState(enAttack01_blad);
	}
	else if (m_player->GetAttackXOrY() == attackY) {
		//m_animState = enAttack06_blad;
		m_player->SetAnimState(enAttack06_blad);
	}
	//m_attackNum×2を加算した番号のアニメーションを流す。
	int animState = m_player->GetAnimState();
	animState += m_attackNum * 2;
	m_player->SetAnimState(animState);
	//m_animState += m_attackNum * 2;
	if (attackTimer > m_totalAttackAnimationTime) {
		//攻撃アニメーション終了。
		AttackEnd();
	}
}
void PlayerAttackAnimation::SpecialAttackStateBlad()
{
	if (m_specialAttackStartFlag != true) {
		m_player->SetMoveSpeed(Vector3::Zero);
		//特殊攻撃のはじめのアニメーションを流す。
		m_player->SetAnimState(enSpecialAttack_01_blad);
		if (!m_player->GetPlayerSkinModelRemder().GetisAnimationPlaing()) {
			//アニメーションが終わった。
			m_specialAttackStartFlag = true;
		}
	}
	else {
		if (g_pad[0]->IsPress(enButtonRB2)) {
			//ボタン長押し。
			m_player->SetAnimState(enSpecialAttack_02_blad);
			//移動しない。
			m_player->SetMoveSpeed(Vector3::Zero);
		}
		else {
			//離した。
			m_player->SetSpecialAttackFlag(true);
		}
	}
	if (m_player->GetSpecialAttackFlag() != false) {
		//攻撃モーション。
		m_player->SetAnimState(enSpecialAttack_03_blad);
		m_timer++;
		m_player->SetMoveSpeed(Vector3::Zero);
		if (m_timer > 10 && m_timer < 50) {
			Vector3 v = m_player->GetDir() * m_speed;
			m_player->SetMoveSpeed(v);
			m_speed -= 50.0f / 40.0f;
			if (m_speed <= 0.0f) {
				m_speed = 0.0f;
			}
		}
		if (!m_player->GetPlayerSkinModelRemder().GetisAnimationPlaing()) {
			m_player->SetSpecialAttackFlag(false);
			m_player->SetSpecialAttackState(enNormalState);
			m_specialAttackStartFlag = false;
			m_speed = 50.0f;
			m_timer = 0;
			AttackEnd();
		}
	}
}
void PlayerAttackAnimation::SpecialAttackStateSword()
{

}
void PlayerAttackAnimation::AttackFlag(int attackTime01_blad, int* attackAnimNum, int attackTime01_sword)
{
	m_player->SetAttackAnimationFlag(true);
	//m_attackAnimationFlag = true;
	if (attackTimer <= 0) {
		//攻撃タイムが0以下。
		m_attackAnimationTimeNum = attackTime01_blad;
		//m_attackAnimNum = attackAnimNum;
		if (m_player->GetWeaponState() == enSwordState) {
			//ソード状態
			m_attackAnimationTimeNum = attackTime01_sword;
		}
		//タイムに最初の攻撃時間を入れる。
		m_totalAttackAnimationTime = m_attackAnimationTime[m_attackAnimationTimeNum];
		//連撃タイムにタイムを入れる。
		m_continuousAttackTime = m_totalAttackAnimationTime;
		//連撃タイムから50引く。
		m_continuousAttackTime = m_switchAttackTime[m_attackAnimationTimeNum];

		m_player->SetAttackFlag(true);
		//m_attackFlag = true;
	}
	if (attackTimer >= m_continuousAttackTime && m_attackNum < *attackAnimNum) {
		//連撃タイム以降
		m_attackNum++;
		m_attackAnimationTimeNum++;
		//攻撃アニメーションの合計時間に次の攻撃アニメーションの時間を加算する。
		m_totalAttackAnimationTime = attackTimer + m_attackAnimationTime[m_attackAnimationTimeNum];
		m_continuousAttackTime = attackTimer + m_switchAttackTime[m_attackAnimationTimeNum];;
		//フラグを立てて、この時は攻撃中でも方向を変えれるようにする。
		//m_attackAngleFlag = false;
		m_player->SetAttackAngleFlag(false);

	}
}
void PlayerAttackAnimation::AttackEnd()
{
	if (m_attackAnimationTimeNum == enAttackTime09_blad ||
		m_attackAnimationTimeNum == enAttackTime09_sword) {
		//武器チェンジの攻撃アニメーションだった。
		//武器の状態を変更する。
		if (m_player->GetWeaponState() == enBladState) {
			//m_weaponState = enSwordState;
			m_player->SetWeaponState(true);
		}
		else if (m_player->GetWeaponState() == enSwordState) {
			//m_weaponState = enBladState;
			m_player->SetWeaponState(false);
		}
	}
	//m_attackAnimationFlag = false;
	m_player->SetAttackAnimationFlag(false);
	
	attackTimer = 0;
	m_attackNum = 0;
	m_totalAttackAnimationTime = 0;
	//m_animState = enStay_blad;
	//m_attackAngleFlag = false;
	m_player->SetAttackXOrY(noAttack);
	m_player->SetAttackAngleFlag(false);

}
void PlayerAttackAnimation::Attack()
{
	if (m_player->GetSpecialAttackState() == enBladState) {
		SpecialAttackStateBlad();
	}
	else if (m_player->GetSpecialAttackState() == enSwordState){
		SpecialAttackStateSword();
	}
	else {
		NormalAttack();
	}
	//if (m_player->GetAttackAnimationFlag() != false) {
		//m_attackAngleFlag = true;
		//m_player->SetAttackAngleFlag(true);
		//if (attackTimer >= m_continuousAttackTime) {
		//	//m_moveSpeed = Vector3::Zero;
		//	m_player->SetMoveSpeed(Vector3::Zero);

		//	//m_attackFlag = false;
		//	m_player->SetAttackFlag(false);
		//}
		//else {
		//	Vector3 moveSpeed = m_player->GetDir() * 5.0f;
		//	m_player->SetMoveSpeed(moveSpeed);
		//	//m_moveSpeed = m_dir * 5.0f;
		//	//m_attackFlag = true;
		//	m_player->SetAttackFlag(true);


		//}
		////攻撃タイマーを加算。
		//attackTimer++;
		////XボタンかYボタンで初期攻撃アニメーションを決める。
		//if (m_player->GetAttackXOrY() == attackX) {
		//	//m_animState = enAttack01_blad;
		//	m_player->SetAnimState(enAttack01_blad);
		//}
		//else if (m_player->GetAttackXOrY() == attackY) {
		//	//m_animState = enAttack06_blad;
		//	m_player->SetAnimState(enAttack06_blad);
		//}
		////m_attackNum×2を加算した番号のアニメーションを流す。
		//int animState = m_player->GetAnimState();
		//animState += m_attackNum * 2;
		//m_player->SetAnimState(animState);
		////m_animState += m_attackNum * 2;
		//if (attackTimer > m_totalAttackAnimationTime) {
		//	//攻撃アニメーション終了。
		//	AttackEnd();
		//}
	//}
}
void PlayerAttackAnimation::SpecialAttackEnd()
{

}
bool PlayerAttackAnimation::Start()
{
	SetAttackAnimationTime();
	m_player = FindGO<Player>("player");
	m_playerAnim = FindGO<PlayerAnimation>("playerAnim");
	return true;
}

void PlayerAttackAnimation::Update()
{

}