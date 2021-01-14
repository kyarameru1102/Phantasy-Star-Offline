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
	//�U���^�C�}�[�����Z�B
	attackTimer++;
	//X�{�^����Y�{�^���ŏ����U���A�j���[�V���������߂�B
	if (m_player->GetAttackXOrY() == attackX) {
		//m_animState = enAttack01_blad;
		m_player->SetAnimState(enAttack01_blad);
	}
	else if (m_player->GetAttackXOrY() == attackY) {
		//m_animState = enAttack06_blad;
		m_player->SetAnimState(enAttack06_blad);
	}
	//m_attackNum�~2�����Z�����ԍ��̃A�j���[�V�����𗬂��B
	int animState = m_player->GetAnimState();
	animState += m_attackNum * 2;
	m_player->SetAnimState(animState);
	//m_animState += m_attackNum * 2;
	if (attackTimer > m_totalAttackAnimationTime) {
		//�U���A�j���[�V�����I���B
		AttackEnd();
	}
}
void PlayerAttackAnimation::SpecialAttackStateBlad()
{
	if (m_specialAttackStartFlag != true) {
		m_player->SetMoveSpeed(Vector3::Zero);
		//����U���̂͂��߂̃A�j���[�V�����𗬂��B
		m_player->SetAnimState(enSpecialAttack_01_blad);
		if (!m_player->GetPlayerSkinModelRemder().GetisAnimationPlaing()) {
			//�A�j���[�V�������I������B
			m_specialAttackStartFlag = true;
		}
	}
	else {
		if (g_pad[0]->IsPress(enButtonRB2)) {
			//�{�^���������B
			m_player->SetAnimState(enSpecialAttack_02_blad);
			//�ړ����Ȃ��B
			m_player->SetMoveSpeed(Vector3::Zero);
		}
		else {
			//�������B
			m_player->SetSpecialAttackFlag(true);
		}
	}
	if (m_player->GetSpecialAttackFlag() != false) {
		//�U�����[�V�����B
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
		//�U���^�C����0�ȉ��B
		m_attackAnimationTimeNum = attackTime01_blad;
		//m_attackAnimNum = attackAnimNum;
		if (m_player->GetWeaponState() == enSwordState) {
			//�\�[�h���
			m_attackAnimationTimeNum = attackTime01_sword;
		}
		//�^�C���ɍŏ��̍U�����Ԃ�����B
		m_totalAttackAnimationTime = m_attackAnimationTime[m_attackAnimationTimeNum];
		//�A���^�C���Ƀ^�C��������B
		m_continuousAttackTime = m_totalAttackAnimationTime;
		//�A���^�C������50�����B
		m_continuousAttackTime = m_switchAttackTime[m_attackAnimationTimeNum];

		m_player->SetAttackFlag(true);
		//m_attackFlag = true;
	}
	if (attackTimer >= m_continuousAttackTime && m_attackNum < *attackAnimNum) {
		//�A���^�C���ȍ~
		m_attackNum++;
		m_attackAnimationTimeNum++;
		//�U���A�j���[�V�����̍��v���ԂɎ��̍U���A�j���[�V�����̎��Ԃ����Z����B
		m_totalAttackAnimationTime = attackTimer + m_attackAnimationTime[m_attackAnimationTimeNum];
		m_continuousAttackTime = attackTimer + m_switchAttackTime[m_attackAnimationTimeNum];;
		//�t���O�𗧂ĂāA���̎��͍U�����ł�������ς����悤�ɂ���B
		//m_attackAngleFlag = false;
		m_player->SetAttackAngleFlag(false);

	}
}
void PlayerAttackAnimation::AttackEnd()
{
	if (m_attackAnimationTimeNum == enAttackTime09_blad ||
		m_attackAnimationTimeNum == enAttackTime09_sword) {
		//����`�F���W�̍U���A�j���[�V�����������B
		//����̏�Ԃ�ύX����B
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
		////�U���^�C�}�[�����Z�B
		//attackTimer++;
		////X�{�^����Y�{�^���ŏ����U���A�j���[�V���������߂�B
		//if (m_player->GetAttackXOrY() == attackX) {
		//	//m_animState = enAttack01_blad;
		//	m_player->SetAnimState(enAttack01_blad);
		//}
		//else if (m_player->GetAttackXOrY() == attackY) {
		//	//m_animState = enAttack06_blad;
		//	m_player->SetAnimState(enAttack06_blad);
		//}
		////m_attackNum�~2�����Z�����ԍ��̃A�j���[�V�����𗬂��B
		//int animState = m_player->GetAnimState();
		//animState += m_attackNum * 2;
		//m_player->SetAnimState(animState);
		////m_animState += m_attackNum * 2;
		//if (attackTimer > m_totalAttackAnimationTime) {
		//	//�U���A�j���[�V�����I���B
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